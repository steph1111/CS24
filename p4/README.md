# Program#4 
## Description 
Using RISC-V/rv, write and test a program that allows the user to enter a 32-bit binary number (so input a string of length 32 where every character will be a 0 or a 1.) That binary number will be compared to a list of 32 32-bit entries, and you will return (and then print in "main") the index of the pattern that is the closest match (or "error" if none of the patterns are close.) Here, distance between two patterns is defined as the number of bits that are similar between the two patterns. Two patterns match if there are seven or fewer bits of difference between two patterns.

In addition to main you must have/use at least two functions. One function will be passed a pattern (`int`) and return an index 0-31 or -1. Another function ( a helper function) will be passed two patterns (`int`s) and return the number of bits of difference between them.
    
Here is a list of the patterns in integer form (IN THIS ORDER)
```
0
1431655765
858993459
1717986918
252645135
1515870810
1010580540
1768515945
16711935
1437226410
869020620
1721329305
267390960
1520786085
1019428035
1771465110
65535
1431677610
859032780
1718000025
252702960
1515890085
1010615235
1769576086
16776960
1437248085
869059635
1721342310
267448335
1520805210
1019462460
1771476585
```
## Notes
- you may assume that input is valid (length 32 binary strings)

## Sample Run
```
steveh@pengo:~/CS24/RISCV-Examples$ rv patterns.s
rv Version 3.4 Copyright (c) 2019 by Anthony J. Dos Reis
CS24: Pattern Matching Program
Enter Your Pattern
01234567890123456789012345678901
01100110100110010110011010011001
11
```
```
steveh@pengo:~/CS24/RISCV-Examples$ rv patterns.s
rv Version 3.4 Copyright (c) 2019 by Anthony J. Dos Reis
CS24: Pattern Matching Program
Enter Your Pattern
01234567890123456789012345678901
00110011010011000011001111001100
10
```
```
steveh@pengo:~/CS24/RISCV-Examples$ rv patterns.s
rv Version 3.4 Copyright (c) 2019 by Anthony J. Dos Reis
CS24: Pattern Matching Program
Enter Your Pattern
01234567890123456789012345678901
00110010001100110011001100110001
2
```
```
steveh@pengo:~/CS24/RISCV-Examples$ rv patterns.s
rv Version 3.4 Copyright (c) 2019 by Anthony J. Dos Reis
CS24: Pattern Matching Program
Enter Your Pattern
01234567890123456789012345678901
00000010000010010000001100000000
0
```
```
steveh@pengo:~/CS24/RISCV-Examples$ rv patterns.s
rv Version 3.4 Copyright (c) 2019 by Anthony J. Dos Reis
CS24: Pattern Matching Program
Enter Your Pattern
01234567890123456789012345678901
11110110100101111010010101110101
error
```
```
steveh@pengo:~/CS24/RISCV-Examples$ rv patterns.s
rv Version 3.4 Copyright (c) 2019 by Anthony J. Dos Reis
CS24: Pattern Matching Program
Enter Your Pattern
01234567890123456789012345678901
01011000110101010101101001001010
5
```