# Program#3
## Description
Using rv for RISC-V, write and test a program that finds the Greatest Common Divisor of two integers using a recursive function that implements Euclid's GCD algorithm as described below. 

Your program should greet the user "Euclid's GCD algorithm", prompt the user to input two integers, and then output the result
```
"Euclid's Greatest Common Divisor Algorithm"
GCD(M,N) = M                      (if N is 0)
GCD(M,N) = GCD(N, M % N)   (if N > 0)
```
## Notes
- you may assume that inputs are non-negative

## Sample Run
```
steveh@pengo:~/CS24$ rv gcd.s
rv Version 3.4 Copyright (c) 2019 by Anthony J. Dos Reis
Euclid's Greatest Common Divisor Algorithm
m ?8
n ?12
gcd(m, n) = 4
steveh@pengo:~/CS24$
```