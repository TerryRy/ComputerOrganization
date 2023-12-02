.data
matrix: .space  256             # int matrix[8][8]   8*8*4 字节
                                # matrix[0][0]=0x00 matrix[0][1]=0x04
                                # matrix[1][0]=0x20 matrix[1][1]=0x24
str_enter:  .asciiz "\n"
str_space:  .asciiz " "

# use hong,%i:now_hang %j:now_lie
# (%i * 8 + %j) * 4 store in %ans 
.macro  getindex(%ans, %i, %j)
    sll %ans, %i, 3             # %ans = %i * 8
    add %ans, %ans, %j          # %ans = %ans + %j
    sll %ans, %ans, 2           # %ans = %ans * 4
.end_macro

.text
li  $v0, 5
syscall
move $s0, $v0                   # s0:hang_num
li  $v0, 5
syscall
move $s1, $v0                   # s1:lie_num

li  $t0, 0                      # $t0:used for circling

in_i:                           # circle hang
beq $t0, $s0, in_i_end
li  $t1, 0                      # $t1:used in lie_circle

in_j:                           # circle lie
beq $t1, $s1, in_j_end
li  $v0, 5
syscall                         # mind: Execute _ Basic 
getindex($t2, $t0, $t1)         # hong to calculate ($t0 * 8 + $t1) * 4 
sw  $v0, matrix($t2)            # matrix[$t0][$t1] = $v0
addi $t1, $t1, 1
j   in_j
in_j_end:
addi $t0, $t0, 1
j   in_i

in_i_end:
li  $t0, 0

out_i:
beq $t0, $s0, out_i_end
li  $t1, 0
out_j:
beq $t1, $s1, out_j_end
getindex($t2, $t0, $t1)
lw  $a0, matrix($t2)            # $a0 = matrix[$t0][$t1]
li  $v0, 1
syscall
la  $a0, str_space
li  $v0, 4
syscall                        
addi $t1, $t1, 1
j   out_j
out_j_end:
la  $a0, str_enter
li  $v0, 4
syscall                         
addi $t0, $t0, 1
j   out_i

out_i_end:
li  $v0, 10
syscall