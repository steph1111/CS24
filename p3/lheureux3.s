# CS24 Program#3
# Stephanie L'Heureux 
# stephanielh1111@gmail.com 

.text
main:
    la s0, s_prompt
    sout s0                     # std::cout << "Euclid's Greatest Common Divisor Algorithm\n"

    la s0, s_m_prompt
    sout s0                     # std::cout << "m ?"
    din a0                      # a0 = m

    la s0, s_n_prompt
    sout s0                     # std::cout << "n ?"
    din a1                      # a1 = n

    jal ra, gcd                 # gcd(m, n)

    la s0, s_result
    sout s0                     # std::cout << "gcd(m, n) = "
    dout a0                     # std::cout << gcd(m, n)

    la s0, s_newline
    sout s0                     # std::cout << "\n"

    halt

# ---------------------------------------------------
# int gcd(int a0, int a1)
# Determines the greatest common factor that divides `m` and `n`, exactly.
#
# params:
#   a0: m 
#   a1: n
# return:
#   Greatest common factor of of `m` and `n`.
gcd:
    beq a1, zero, ret       # if (n == 0) goto ret
    mv t0, a0               # temp = m
    mv a0, a1               # m = n
    rem a1, t0, a0          # n = m % n
    addi sp, sp, -4         # Make room for the return address on the stack
    sw ra, 0(sp)            # Store the return address on the stack
    jal ra, gcd             # gcd(n, m % n) 
    lw ra, 0(sp)            # Load the return addres from the stack
    addi sp, sp, 4          # Move the stack pointer back
    ret:
        jr ra               # return m

.data
s_prompt:       .asciz "Euclid's Greatest Common Divisor Algorithm\n"
s_m_prompt:     .asciz "m ?"
s_n_prompt:     .asciz "n ?"
s_result:       .asciz "gcd(m, n) = "
s_newline:      .asciz "\n"
