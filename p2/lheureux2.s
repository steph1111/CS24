# CS24 Program#2
# Stephanie L'Heureux 
# stephanielh1111@gmail.com
# lheureux2.s

.text
main:
    la a0, s_prompt             # a0 = s_prompt
    sout a0                     # Output a0 as string

    din s0                      # s0 = n    (input number of primes to find)

    # Output the first prime (2)
    la a0, s_first_prime
    sout a0

    li s1, 1                    # i = 1     (counter for loop iterations)
    li s2, 1                    # num = 1   (starting number to check)

    loop:
        bge s1, s0, done        # if (i >= n) goto done
        addi s2, s2, 2          # num += 2  (only check odds >= 3)
        mv a0, s2               # a0 = num  (prepare arg for function)
        jal ra, test_prime      # test_prime(num)
        beq a0, zero, loop      # if (a0 == 0) goto loop (number is not prime)

        # Output the found prime number
        dout s2
        la a0, s_newline
        sout a0
        
        addi s1, s1, 1          # i++       (increment prime count)
        j loop                  # goto loop

    done:
        halt

# ---------------------------------------------------
# bool test_prime(int a0)
# Determines if a number is prime
#
# params:
#   a0: Integer to test if it is prime
# return:
#   1 if the number is prime, otherwise 0
test_prime: mv t0, a0                   # t0 = a0 = n
    li t1, 3                    # i = 3
    li a0, 1                    # a0 = 1    (assume prime)

    test:
        mul t2, t1, t1          # t2 = i * i
        bgt t2, t0, ret         # if (n > i * i) goto ret
        rem a0, t0, t1          # a0 = n % i
        addi t1, t1, 2          # i += 2
        bne a0, zero, test      # if (n % i != 0)

    ret:
        jr ra

.data
s_prompt:       .asciz "How many primes? (min n value 1) "
s_first_prime:  .asciz "2\n"
s_newline:      .asciz "\n"
