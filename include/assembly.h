#pragma once
#include <cstdint>
#include <stdexcept>
#include <string>
#include <regex>
#include <limits>
#include <vector>

namespace dot86 {

class Instruction;

std::string string_upper(const std::string& str)
{
  std::string upper;
  for (auto c = str.begin(); c != str.end(); c++)
    upper += toupper(*c);
  return upper;
}

std::string string_trim(const std::string& str)
{
  size_t first = str.find_first_not_of(' ');
  if (first == std::string::npos)
      return str;
  size_t last = str.find_last_not_of(' ');
  return str.substr(first, (last - first + 1));
}

class Operand {
public:
  Operand(const std::string& operand) :
    regDigit_(-1), dispSize_('\0'), type_('\0'), isUsed_(true)
  {
    if (operand.empty())
      isUsed_ = false;
    else {
      auto s = string_trim(operand);
      std::smatch ms;
      std::regex e("(\\[?)([A-Za-z]{2,}| *)\\+?([0-9]*)(\\]?)");

      std::regex_search(s, ms, e);
      reg_ = ms[2];
      disp_ = ms[3];

      FindDispSize_();
      FindRegDigit_();
      if (ms[1] == "[") {
        if (ms[4] == "]")
          type_ = 'm';
        else
          throw std::runtime_error("Bad operand format");
      }
      else if (reg_.empty())
        type_ = 'i';
      else
        type_ = 'r';
    }
  }

  constexpr uint8_t GetRegDigit() const noexcept
  {
    return regDigit_;
  }

  constexpr char GetDispSize() const noexcept
  {
    return dispSize_;
  }

  constexpr int8_t GetDisp8() const noexcept
  {
    return disp8_;
  }

  constexpr int32_t GetDisp32() const noexcept
  {
    return disp32_;
  }

  constexpr char GetType() const noexcept
  {
    return type_;
  }

  constexpr bool IsUsed() const noexcept
  {
    return isUsed_;
  }
  
  friend bool operator==(const Operand& l, const Operand& r)
  {
    return (l.reg_ == r.reg_ && l.disp_ == r.disp_);
  }

private:
  std::string reg_;
  std::string disp_;
  union {
    int8_t disp8_;
    int32_t disp32_;
  };
  uint8_t regDigit_;
  char dispSize_;
  char type_;
  bool isUsed_;

  friend Instruction;

  void FindDispSize_()
  {
    if (!disp_.empty()) {
      disp32_ = stol(disp_, nullptr, 0);
      if (disp32_ <= std::numeric_limits<int8_t>::max() && !reg_.empty())
        dispSize_ = 'b';
      else if (disp32_ <= std::numeric_limits<int32_t>::max())
        dispSize_ = 'd';
    }
  }

  void FindRegDigit_()
  {
    if (reg_.size() > 1) {
      if (reg_.at(0) == 'R')
        regDigit_ = reg_.at(1) - 41;
      else if (reg_.at(1) == 'P')
        regDigit_ = reg_.at(0) + reg_.at(1) + 1;
      else if (reg_.at(1) == 'I')
        regDigit_ = reg_.at(0) + reg_.at(1) - 4;
      else
        throw std::runtime_error("Could not find register digit");
      
      regDigit_ &= 0x7;
      if (regDigit_ > 5)
        regDigit_--;
    }
    else if (!disp_.empty() && dispSize_ != '\0')
      regDigit_ = 5;
  }
};

class Instruction {
public:
  Instruction(const std::string& mnemonic, const std::string& l, const std::string& r) :
    bytes_(), mnemonic_(mnemonic), left_(l), right_(r)
  {
    auto op = operations_.begin();
    for (; op != operations_.end(); op++) {
      if (mnemonic_ == op->mnemonic_) {
        if (op->type_ == 's') {
          if (left_ == Operand(op->left_)) {
            if (op->right_ == "imm32" && right_.GetDispSize() == 'd') {
              opcode_ = op->opcode_;
              break;
            }
          }
        }
        else if (op->type_ == 'r') {
          if (op->left_.find_first_of(left_.GetType()) != std::string::npos &&
              op->right_.find_first_of(right_.GetType()) != std::string::npos) {
            opcode_ = op->opcode_;
            break;
          }
        }
      }
    }
    if (op == operations_.end())
      throw std::runtime_error("Unable to find instruction");

    if (left_.GetType() == 'm') {
      auto t = left_;
      left_ = right_;
      right_ = t;
    }

    bytes_.emplace_back(opcode_);
    if (op->type_ == 'r') {
      FindModRm_();
      bytes_.emplace_back(modrm_);
    }
    
    auto t = right_.GetDispSize();
    if (t == 'b')
      bytes_.emplace_back(right_.GetDisp8());
    if (t == 'd') {
      auto d = right_.GetDisp32();
      auto p = reinterpret_cast<uint8_t*>(&d);
      bytes_.emplace_back(*p);
      bytes_.emplace_back(*(p + 1));
      bytes_.emplace_back(*(p + 2));
      bytes_.emplace_back(*(p + 3));
    }
  }

  constexpr std::vector<uint8_t>& GetBytes() noexcept
  {
    return bytes_;
  }

private:
  class Operation {
  public:
    Operation(const uint8_t opcode, const char type,
              const std::string& mnemonic, const std::string& left,
              const std::string& right) :
      opcode_(opcode), type_(type), mnemonic_(mnemonic), left_(left), right_(right)
    {
    };

  private:
    uint8_t opcode_;
    char type_;
    std::string mnemonic_;
    std::string left_;
    std::string right_;

    friend Instruction;
  };

  inline static const std::vector<Operation> operations_ = {
    { 0x0, 'r', "ADD", "r", "rm" },
    { 0x1, 'r', "ADD", "m", "r" },
    { 0x2, 's', "ADD", "RA", "imm32" }
    // TODO: add instructions here
  };

  std::vector<uint8_t> bytes_;
  std::string mnemonic_;
  Operand left_;
  Operand right_;
  uint8_t opcode_;
  uint8_t modrm_;

  void FindModRm_()
  {
    uint8_t m = 0;
    if (right_.GetType() == 'r')
      m = 3;
    else if (right_.GetType() == 'm' && right_.GetDispSize() != '\0' && !right_.reg_.empty())
      m = (right_.GetDispSize() == 'b') ? 1 : 2;
    
    modrm_ = (m << 6) | (left_.GetRegDigit() << 3) | right_.GetRegDigit();
  }
};

std::vector<uint8_t> assembly(std::string& code)
{
  std::smatch ms;
  std::regex e("([\\w\\d]{2,})([^\\,\20]*)\\,?([^\20]*)");
  std::vector<uint8_t> out;

  while (regex_search(code, ms, e)) {
    Instruction inst(string_upper(ms[1].str()),
                     string_upper(ms[2].str()),
                     string_upper(ms[3].str()));
    auto v = inst.GetBytes();
    for (auto i = v.begin(); i != v.end(); i++)
      out.emplace_back(*i);
    code = ms.suffix().str();
  }
  return out;
}

}
