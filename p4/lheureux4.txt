# CS24 Program#4
# Stephanie L'Heureux 
# stephanielh1111@gmail.com 

.text
main:
    la a0, s_prompt
    sout a0                     # Print welcome prompt

    la a0, buffer               # Load address of the input buffer
    sin a0                      # String input into buffer

    jal ra, stob                # stob(a0)
    jal ra, best_match          # best_match(a0)

    bltz a0, error              # if (i <= 0) goto error
        dout a0                 # Print index of best match
        halt                    # return 0
    error:
        la a0, s_error
        sout a0                 # Print error message in the case of no match
    halt                        # return 0


# ---------------------------------------------------
# int stob(std::string a0)
# String to binary converter.
#
# params:
#   a0: String of length 32 representing a binary number.
# return:
#   The input string converted to a integer.
stob:
    add t0, a0, 32              # stop = &str_param[size]   (Keep a reference to one past the end of the string as where to stop)
    mv t1, a0                   # str = str_param           (Store the string somehere that is not a0 so it can be overwritten)
    mv a0, zero                 # bin = 0                   (Binary representation starts at 0)
    loop_str:
        lb t2, 0(t1)            # bit = str[i]              (Load the current bit)
        addi t2, t2, -48        # bit -= 48                 (48 is the character value of 0, subtract to get 0 or 1 as an int)
        slli a0, a0, 1          # bin <<= 1                 (Move bits over to the left by one position to make roomfor next bit)
        add a0, a0, t2          # bin += bit                (Append new bit)
        addi t1, t1, 1          # i++                       (Increment string position)
        bne t1, t0, loop_str    # if (&str_param[i] != stop) goto loop_s
    jr ra                       # return bin


# ---------------------------------------------------
# int best_match(int a0)
# Finds the index of the closest matching pattern compared to the provided input.
# Two patterns match if there are seven or fewer bits of difference between two patterns.
#
# params:
#   a0: User inputted integer.
# return:
#   An index 0-31 or -1 if not found. 
best_match:
    # Store variables on the stack
    addi sp, sp, -24
    sw s0, 0(sp)
    sw s2, 4(sp)
    sw s3, 8(sp)
    sw s4, 12(sp)
    sw s5, 16(sp)
    sw ra, 20(sp)

    la s0, list                 # base = &a[0]          (Load address of the base of the array)
    add s1, s0, 128             # stop = &a[size]       (Keep a reference to one past the end of the array as where to stop) 
    mv s2, a0                   # user_in = param_1     (Save the user in in a saved register)
    mv s3, zero                 # i = 0                 (Counter starts at 0)  
    li s4, 7                    # max_diffs = 7         (Maximum number of differences for two patterns to match)
   
    loop_list:
        mv a0, s2               # param_1 = user_in
        lw a1, 0(s0)            # param_2 = a[i]
        jal ra, hamming_dist    # hamming_dist(user_in, a[i])
        ble a0, s4, ret         # if (count_diff <= max_diffs) goto ret
        addi s3, s3, 1          # i++                   (Track current index)
        addi s0, s0, 4          # i++                   (move base of array)
        bne s0, s1, loop_list   # if (&a[i] != &a[size]) goto loop_list 

    li s3, -1                   # i = -1                (No pattern close enough)
    ret:
        mv a0, s3               # ret_val = i
        # Restore values from the stack
        lw s0, 0(sp)
        lw s2, 4(sp)
        lw s3, 8(sp)
        lw s4, 12(sp)
        lw s5, 16(sp)
        lw ra, 20(sp)
        addi sp, sp, 24
        jr ra                   # return ret_val


# ---------------------------------------------------
# int hamming_dist(int a0, int a1)
# Count the number of bits of difference between two inputs..
#
# params:
#   a0, a1: Integers to be compared.
# return:
#   The number of bits of difference between them.
hamming_dist:
    xor t0, a0, a1          # diff = user_in ^ pattern  (Exclusive or will return a number where different bits are one)
    mv a0, zero             # count_diff = 0
    ham_loop:
        andi t1, t0, 1      # last_bit = diff & 1       (Get the last bit)
        add a0, a0, t1      # count_diff += last_bit    (Add last bit to counter)
        srli t0, t0, 1      # t0 >>= 1                  (Move bits to the right to cut off last bit)
        bnez t0, ham_loop   # if (diff != 0) goto ham_loop
    jr ra                   # return count_diff


.data
buffer:     .zero 33
list:       .word 0, 1431655765, 858993459
            .word 1717986918, 252645135, 1515870810
            .word 1010580540, 1768515945, 16711935
            .word 1437226410, 869020620, 1721329305
            .word 267390960, 1520786085, 1019428035
            .word 1771465110, 65535, 1431677610
            .word 859032780, 1718000025, 252702960
            .word 1515890085, 1010615235, 1769576086
            .word 16776960, 1437248085, 869059635
            .word 1721342310, 267448335, 1520805210
            .word 1019462460, 1771476585
s_prompt:   .asciz "CS24: Pattern Matching Program\nEnter Your Pattern\n01234567890123456789012345678901\n"
s_error:    .asciz "error\n"
