.macro return_0
  li $v0, 10
  syscall
.end_macro

.data
  stu: .space 220
  #cnt: .space 440
  #Lucky: .asciiz "Lucky Word\n"
  #No_answer: .asciiz "No Answer\n0\n"

.text
  main:
    li $t0, 0
    li $a1, 8
    li $s0, 3
    li $s1, 12
    loop:
      slt $t1, $t0, $s0
      beq $t1, $zero, loop_end
      mult $s1, $t0
      mflo $t2
      la $a0, stu($t2) 
      li $v0, 8
      syscall
      addi $t2, $t2, 8
      li $v0, 5
      syscall
      sw $v0, stu($t2)
      addi $t0, $t0, 1
      j loop
   loop_end:
    
    
    
    li $v0, 10
    syscall
    
      
    