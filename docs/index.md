---
layout: default
---

{% include head.html %}

Hello, there!

This is a w.i.p class assignment

# A 32-bit variable instruction encoding RISC ISA

here shall be inserted something akin to an abstract

## overview

here shall be inserted information about the following sections and, if possible, a table of contents

### Basic information

- Bits: 32
- Maximum number of operands: 2
- Type: Register–Memory
- Design: RISC
- Number of registers: 8
- Instruction encoding: variable (8 to 48 bits)

#### Useful literature

<p>
DISCLAIMER: Under section 107 of the Copyright Act 1976, allowance is made for "fair use" for purposes such as criticism, comment, teaching, education, scholarship and research. Fair use is a use permitted by the copyright statute that might otherwise be infringing. Non-profit, educational or personal use tips the balance in favour of fair use.
</p>

[PATTERSON, Computer Organization and Design](http://home.ustc.edu.cn/~louwenqi/reference_books_tools/Computer_Organization_and_Design_3Rd.pdf)

[BRYANT, Computer Systems (2002)](http://gec.di.uminho.pt/DISCIP/LEI/ac0708/te%C3%B3ricas/capiv.pdf)

[BRYANT, Computer Systems (2015)](http://www.csapp.cs.cmu.edu/2e/ch4-preview.pdf)

[BISTRICEANU, CPU Implementation](http://www.cs.iit.edu/~virgil/cs470/Book/chapter5.pdf)

[DAMIAN, Logic Gates - Building an ALU](http://www.csc.villanova.edu/~mdamian/Past/csc2400fa13/assign/ALU.html)

[SCHMALZ, Organization of Computer Systems](https://www.cise.ufl.edu/~mssz/CompOrg/CDA-lang.html)

<hr>

### Instruction encoding

This section will discuss how instructions in this architecture are implemented.

### 8-bits operation code

The eight most-significant bits read from `ins_mem` (from bit **47** to bit **40**) at `pc` will always be used as the operation code.

#### Arithmetic operations

<div class="table-container">
  <table class="table-styled">
    <thead>
      <tr>
        <th>opcode</th>
        <th>mnemonic</th>
        <th>op1</th>
        <th>op2</th>
        <th>sz</th>
        <th>desc</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td>00</td>
        <td>ADD</td>
        <td>r</td>
        <td>r/m</td>
        <td>2:6</td>
        <td>adds <strong>r</strong> and <strong>r/m</strong>, stores at <strong>r</strong></td>
      </tr>
      <tr>
        <td>01</td>
        <td>ADD</td>
        <td>r/m</td>
        <td>r</td>
        <td>2:6</td>
        <td>adds <strong>r/m</strong> and <strong>r</strong>, stores at <strong>r/m</strong></td>
      </tr>
      <tr>
        <td>02</td>
        <td>ADD</td>
        <td>RA</td>
        <td>imm8</td>
        <td>2</td>
        <td>adds <strong>RA</strong> and <strong>imm8</strong>, stores at <strong>RA</strong></td>
      </tr>
      <tr>
        <td>03</td>
        <td>ADD</td>
        <td>RA</td>
        <td>imm32</td>
        <td>5</td>
        <td>adds <strong>RA</strong> and <strong>imm32</strong>, stores at <strong>RA</strong></td>
      </tr>
    </tbody>
  </table>
</div>

### 8-bits ModR/M value

The ModR/M byte is used to determine the operands of some instruction and is composed of the following fields:

insert image here

Which represents the following table:

<div class="table-container">
  <table class="table-styled">
    <thead>
      <tr>
        <th></th>
        <th></th>
        <th></th>
        <th>RA</th>
        <th>RB</th>
        <th>RC</th>
        <th>RD</th>
        <th>SP</th>
        <th>BP</th>
        <th>SI</th>
        <th>DI</th>
      </tr>
      <tr>
        <th>Effective Address</th>
        <th>Mod</th>
        <th>R/M</th>
        <th class="hollow">000</th>
        <th class="hollow">001</th>
        <th class="hollow">010</th>
        <th class="hollow">011</th>
        <th class="hollow">100</th>
        <th class="hollow">101</th>
        <th class="hollow">110</th>
        <th class="hollow">111</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td class="hollow">[RA]</td>
        <td class="hollow">00</td>
        <td class="hollow">000</td>
        <td>00</td>
        <td>08</td>
        <td>10</td>
        <td>18</td>
        <td>20</td>
        <td>28</td>
        <td>30</td>
        <td>38</td>
      </tr>
      <tr>
        <td class="hollow">[RB]</td>
        <td class="hollow"></td>
        <td class="hollow">001</td>
        <td>01</td>
        <td>09</td>
        <td>11</td>
        <td>19</td>
        <td>21</td>
        <td>29</td>
        <td>31</td>
        <td>39</td>
      </tr>
      <tr>
        <td class="hollow">[RC]</td>
        <td class="hollow"></td>
        <td class="hollow">010</td>
        <td>02</td>
        <td>0A</td>
        <td>12</td>
        <td>1A</td>
        <td>22</td>
        <td>2A</td>
        <td>32</td>
        <td>3A</td>
      </tr>
      <tr>
        <td class="hollow">[RD]</td>
        <td class="hollow"></td>
        <td class="hollow">011</td>
        <td>03</td>
        <td>0B</td>
        <td>13</td>
        <td>1B</td>
        <td>23</td>
        <td>2B</td>
        <td>33</td>
        <td>3B</td>
      </tr>
      <tr>
        <td class="hollow">[SP]</td>
        <td class="hollow"></td>
        <td class="hollow">100</td>
        <td>04</td>
        <td>0C</td>
        <td>14</td>
        <td>1C</td>
        <td>24</td>
        <td>2C</td>
        <td>34</td>
        <td>3C</td>
      </tr>
      <tr>
        <td class="hollow">disp32</td>
        <td class="hollow"></td>
        <td class="hollow">101</td>
        <td>05</td>
        <td>0D</td>
        <td>15</td>
        <td>1D</td>
        <td>25</td>
        <td>2D</td>
        <td>35</td>
        <td>3D</td>
      </tr>
      <tr>
        <td class="hollow">[SI]</td>
        <td class="hollow"></td>
        <td class="hollow">110</td>
        <td>06</td>
        <td>0E</td>
        <td>16</td>
        <td>1E</td>
        <td>26</td>
        <td>2E</td>
        <td>36</td>
        <td>3E</td>
      </tr>
      <tr>
        <td class="hollow">[DI]</td>
        <td class="hollow"></td>
        <td class="hollow">111</td>
        <td>07</td>
        <td>0F</td>
        <td>17</td>
        <td>1F</td>
        <td>27</td>
        <td>2F</td>
        <td>37</td>
        <td>3F</td>
      </tr>
      <tr class="odd">
        <td class="hollow">[RA]+disp8</td>
        <td class="hollow">01</td>
        <td class="hollow">000</td>
        <td>40</td>
        <td>48</td>
        <td>50</td>
        <td>58</td>
        <td>60</td>
        <td>68</td>
        <td>70</td>
        <td>78</td>
      </tr>
      <tr class="odd">
        <td class="hollow">[RB]+disp8</td>
        <td class="hollow"></td>
        <td class="hollow">001</td>
        <td>41</td>
        <td>49</td>
        <td>51</td>
        <td>59</td>
        <td>61</td>
        <td>69</td>
        <td>71</td>
        <td>79</td>
      </tr>
      <tr class="odd">
        <td class="hollow">[RC]+disp8</td>
        <td class="hollow"></td>
        <td class="hollow">010</td>
        <td>42</td>
        <td>4A</td>
        <td>52</td>
        <td>5A</td>
        <td>62</td>
        <td>6A</td>
        <td>72</td>
        <td>7A</td>
      </tr>
      <tr class="odd">
        <td class="hollow">[RD]+disp8</td>
        <td class="hollow"></td>
        <td class="hollow">011</td>
        <td>43</td>
        <td>4B</td>
        <td>53</td>
        <td>5B</td>
        <td>63</td>
        <td>6B</td>
        <td>73</td>
        <td>7B</td>
      </tr>
      <tr class="odd">
        <td class="hollow">[SP]+disp8</td>
        <td class="hollow"></td>
        <td class="hollow">100</td>
        <td>44</td>
        <td>4C</td>
        <td>54</td>
        <td>5C</td>
        <td>64</td>
        <td>6C</td>
        <td>74</td>
        <td>7C</td>
      </tr>
      <tr class="odd">
        <td class="hollow">[BP]+disp8</td>
        <td class="hollow"></td>
        <td class="hollow">101</td>
        <td>45</td>
        <td>4D</td>
        <td>55</td>
        <td>5D</td>
        <td>65</td>
        <td>6D</td>
        <td>75</td>
        <td>7D</td>
      </tr>
      <tr class="odd">
        <td class="hollow">[SI]+disp8</td>
        <td class="hollow"></td>
        <td class="hollow">110</td>
        <td>46</td>
        <td>4E</td>
        <td>56</td>
        <td>5E</td>
        <td>66</td>
        <td>6E</td>
        <td>76</td>
        <td>7E</td>
      </tr>
      <tr class="odd">
        <td class="hollow">[SI]+disp8</td>
        <td class="hollow"></td>
        <td class="hollow">111</td>
        <td>47</td>
        <td>4F</td>
        <td>57</td>
        <td>5F</td>
        <td>67</td>
        <td>6F</td>
        <td>77</td>
        <td>7F</td>
      </tr>
      <tr>
        <td class="hollow">[RA]+disp32</td>
        <td class="hollow">10</td>
        <td class="hollow">000</td>
        <td>80</td>
        <td>88</td>
        <td>90</td>
        <td>98</td>
        <td>A0</td>
        <td>A8</td>
        <td>B0</td>
        <td>B8</td>
      </tr>
      <tr>
        <td class="hollow">[RB]+disp32</td>
        <td class="hollow"></td>
        <td class="hollow">001</td>
        <td>81</td>
        <td>89</td>
        <td>91</td>
        <td>99</td>
        <td>A1</td>
        <td>A9</td>
        <td>B1</td>
        <td>B9</td>
      </tr>
      <tr>
        <td class="hollow">[RC]+disp32</td>
        <td class="hollow"></td>
        <td class="hollow">010</td>
        <td>82</td>
        <td>8A</td>
        <td>92</td>
        <td>9A</td>
        <td>A2</td>
        <td>AA</td>
        <td>B2</td>
        <td>BA</td>
      </tr>
      <tr>
        <td class="hollow">[RD]+disp32</td>
        <td class="hollow"></td>
        <td class="hollow">011</td>
        <td>83</td>
        <td>8B</td>
        <td>93</td>
        <td>9B</td>
        <td>A3</td>
        <td>AB</td>
        <td>B3</td>
        <td>BB</td>
      </tr>
      <tr>
        <td class="hollow">[SP]+disp32</td>
        <td class="hollow"></td>
        <td class="hollow">100</td>
        <td>84</td>
        <td>8C</td>
        <td>94</td>
        <td>9C</td>
        <td>A4</td>
        <td>AC</td>
        <td>B4</td>
        <td>BC</td>
      </tr>
      <tr>
        <td class="hollow">[BP]+disp32</td>
        <td class="hollow"></td>
        <td class="hollow">101</td>
        <td>85</td>
        <td>8D</td>
        <td>95</td>
        <td>9D</td>
        <td>A5</td>
        <td>AD</td>
        <td>B5</td>
        <td>BD</td>
      </tr>
      <tr>
        <td class="hollow">[SI]+disp32</td>
        <td class="hollow"></td>
        <td class="hollow">110</td>
        <td>86</td>
        <td>8E</td>
        <td>96</td>
        <td>9E</td>
        <td>A6</td>
        <td>AE</td>
        <td>B6</td>
        <td>BE</td>
      </tr>
      <tr>
        <td class="hollow">[DI]+disp32</td>
        <td class="hollow"></td>
        <td class="hollow">111</td>
        <td>87</td>
        <td>8F</td>
        <td>97</td>
        <td>9F</td>
        <td>A7</td>
        <td>AF</td>
        <td>B7</td>
        <td>BF</td>
      </tr>
      <tr class="odd">
        <td class="hollow">RA</td>
        <td class="hollow">11</td>
        <td class="hollow">000</td>
        <td>C0</td>
        <td>C8</td>
        <td>D0</td>
        <td>D8</td>
        <td>E0</td>
        <td>E8</td>
        <td>F0</td>
        <td>F8</td>
      </tr>
      <tr class="odd">
        <td class="hollow">RB</td>
        <td class="hollow"></td>
        <td class="hollow">001</td>
        <td>C1</td>
        <td>C9</td>
        <td>D1</td>
        <td>D9</td>
        <td>E1</td>
        <td>E9</td>
        <td>F1</td>
        <td>F9</td>
      </tr>
      <tr class="odd">
        <td class="hollow">RC</td>
        <td class="hollow"></td>
        <td class="hollow">010</td>
        <td>C2</td>
        <td>CA</td>
        <td>D2</td>
        <td>DA</td>
        <td>E2</td>
        <td>EA</td>
        <td>F2</td>
        <td>FA</td>
      </tr>
      <tr class="odd">
        <td class="hollow">RD</td>
        <td class="hollow"></td>
        <td class="hollow">011</td>
        <td>C3</td>
        <td>CB</td>
        <td>D3</td>
        <td>DB</td>
        <td>E3</td>
        <td>EB</td>
        <td>F3</td>
        <td>FB</td>
      </tr>
      <tr class="odd">
        <td class="hollow">SP</td>
        <td class="hollow"></td>
        <td class="hollow">100</td>
        <td>C4</td>
        <td>CC</td>
        <td>D4</td>
        <td>DC</td>
        <td>E4</td>
        <td>EC</td>
        <td>F4</td>
        <td>FC</td>
      </tr>
      <tr class="odd">
        <td class="hollow">BP</td>
        <td class="hollow"></td>
        <td class="hollow">101</td>
        <td>C5</td>
        <td>CD</td>
        <td>D5</td>
        <td>DD</td>
        <td>E5</td>
        <td>ED</td>
        <td>F5</td>
        <td>FD</td>
      </tr>
      <tr class="odd">
        <td class="hollow">SI</td>
        <td class="hollow"></td>
        <td class="hollow">110</td>
        <td>C6</td>
        <td>CE</td>
        <td>D6</td>
        <td>DE</td>
        <td>E6</td>
        <td>EE</td>
        <td>F6</td>
        <td>FE</td>
      </tr>
      <tr class="odd">
        <td class="hollow">DI</td>
        <td class="hollow"></td>
        <td class="hollow">111</td>
        <td>C7</td>
        <td>CF</td>
        <td>D7</td>
        <td>DF</td>
        <td>E7</td>
        <td>EF</td>
        <td>F7</td>
        <td>FF</td>
      </tr>
    </tbody>
  </table>
</div>

{% include foot.html %}
