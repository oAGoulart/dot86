[![dot86](banner.png)]()

This is a w.i.p class assignment

### Instructions

#### Arithmetic operations

| opcode  | mnemonic | op1    | op2    |
| ------- | -------- | ------ | ------ |
| 00      | ADD      | r      | r/m    |
| 01      | ADD      | r/m    | r      |
| 02      | ADD      | RA     | imm8   |
| 03      | ADD      | RA     | imm32  |

### 32-bit ModR/M byte

The ModR/M byte is used to determine the operands of an instruction and is composed of the following fields:

| Mod  | Register index | R/M  |
| ---- | -------------- | ---- |
| 7..6 | 5..3           | 2..0 |

Which represents the following table:

|                   |     |     | RA  | RB  | RC  | RD  | SP  | BP  | SI  | DI  |
| ----------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Effective Address | Mod | R/M | 000 | 001 | 010 | 011 | 100 | 101 | 110 | 111 |
| [RA]              | 00  | 000 | 00  | 08  | 10  | 18  | 20  | 28  | 30  | 38  |
| [RB]              |     | 001 | 01  | 09  | 11  | 19  | 21  | 29  | 31  | 39  |
| [RC]              |     | 010 | 02  | 0A  | 12  | 1A  | 22  | 2A  | 32  | 3A  |
| [RD]              |     | 011 | 03  | 0B  | 13  | 1B  | 23  | 2B  | 33  | 3B  |
| [SP]              |     | 100 | 04  | 0C  | 14  | 1C  | 24  | 2C  | 34  | 3C  |
| disp32            |     | 101 | 05  | 0D  | 15  | 1D  | 25  | 2D  | 35  | 3D  |
| [SI]              |     | 110 | 06  | 0E  | 16  | 1E  | 26  | 2E  | 36  | 3E  |
| [DI]              |     | 111 | 07  | 0F  | 17  | 1F  | 27  | 2F  | 37  | 3F  |
| [RA]+disp8        | 01  | 000 | 40  | 48  | 50  | 58  | 60  | 68  | 70  | 78  |
| [RB]+disp8        |     | 001 | 41  | 49  | 51  | 59  | 61  | 69  | 71  | 79  |
| [RC]+disp8        |     | 010 | 42  | 4A  | 52  | 5A  | 62  | 6A  | 72  | 7A  |
| [RD]+disp8        |     | 011 | 43  | 4B  | 53  | 5B  | 63  | 6B  | 73  | 7B  |
| [SP]+disp8        |     | 100 | 44  | 4C  | 54  | 5C  | 64  | 6C  | 74  | 7C  |
| [BP]+disp8        |     | 101 | 45  | 4D  | 55  | 5D  | 65  | 6D  | 75  | 7D  |
| [SI]+disp8        |     | 110 | 46  | 4E  | 56  | 5E  | 66  | 6E  | 76  | 7E  |
| [SI]+disp8        |     | 111 | 47  | 4F  | 57  | 5F  | 67  | 6F  | 77  | 7F  |
| [RA]+disp32       | 10  | 000 | 80  | 88  | 90  | 98  | A0  | A8  | B0  | B8  |
| [RB]+disp32       |     | 001 | 81  | 89  | 91  | 99  | A1  | A9  | B1  | B9  |
| [RC]+disp32       |     | 010 | 82  | 8A  | 92  | 9A  | A2  | AA  | B2  | BA  |
| [RD]+disp32       |     | 011 | 83  | 8B  | 93  | 9B  | A3  | AB  | B3  | BB  |
| [SP]+disp32       |     | 100 | 84  | 8C  | 94  | 9C  | A4  | AC  | B4  | BC  |
| [BP]+disp32       |     | 101 | 85  | 8D  | 95  | 9D  | A5  | AD  | B5  | BD  |
| [SI]+disp32       |     | 110 | 86  | 8E  | 96  | 9E  | A6  | AE  | B6  | BE  |
| [DI]+disp32       |     | 111 | 87  | 8F  | 97  | 9F  | A7  | AF  | B7  | BF  |
| RA                | 11  | 000 | C0  | C8  | D0  | D8  | E0  | E8  | F0  | F8  |
| RB                |     | 001 | C1  | C9  | D1  | D9  | E1  | E9  | F1  | F9  |
| RC                |     | 010 | C2  | CA  | D2  | DA  | E2  | EA  | F2  | FA  |
| RD                |     | 011 | C3  | CB  | D3  | DB  | E3  | EB  | F3  | FB  |
| SP                |     | 100 | C4  | CC  | D4  | DC  | E4  | EC  | F4  | FC  |
| BP                |     | 101 | C5  | CD  | D5  | DD  | E5  | ED  | F5  | FD  |
| SI                |     | 110 | C6  | CE  | D6  | DE  | E6  | EE  | F6  | FE  |
| DI                |     | 111 | C7  | CF  | D7  | DF  | E7  | EF  | F7  | FF  |
