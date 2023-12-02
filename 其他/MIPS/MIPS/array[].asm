.data
array: .space 40           # 10 * 4 = 40 byte
                           # address :array[0]=0x00 array[1]=0x04

str:   .asciiz "The numbers are:\n"
space: .asciiz " "

.text
li $v0,5
syscall                    # input a int
move $s0, $v0              # $s0 is n
li $t0, 0                  # $t0:used for circling

loop_in:
beq $t0, $s0, loop_in_end  # $t0 == $s0 skip to loop_in_end
li $v0, 5
syscall                    # input a int
sll $t1, $t0, 2            # $t1 = $t0 << 2
sw $v0, array($t1)         # store int in array + $t1
addi $t0, $t0, 1           # $t0 = $t0 + 1
j loop_in                  # skip to loop_in

loop_in_end:
la $a0, str
li $v0, 4
syscall                    # print a0(char
li $t0, 0

loop_out:
beq $t0, $s0, loop_out_end
sll $t1, $t0, 2            # $t1 = $t0 << 2
lw $a0, array($t1)         # load array + $t1 to $a0
li $v0, 1
syscall                    # print $a0(int
la $a0, space
li $v0, 4
syscall                    # print $a0(char
addi $t0, $t0, 1
j loop_out

loop_out_end:
li $v0, 10
syscall                    # end