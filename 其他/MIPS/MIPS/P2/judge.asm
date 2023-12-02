.macro get_index(%des,%i)
  move %des, %i
  sll %des, %des, 2
.end_macro

.macro scanf_to(%des)
  li $v0, 12
  syscall
  sw $v0, str(%des)
.end_macro

.macro return_0
  li $v0, 10
  syscall
.end_macro

.data
  str: .space 100
  flag_1: .asciiz "1"
  flag_0: .asciiz "0"
  
.text
  #scanf("%d",&n);
  li $v0, 5
  syscall
  move $s0, $v0
  #scanf(str)
  li $t0, 0
  loop:
    get_index($s1, $t0)
    scanf_to($s1)
    addi $t0, $t0, 1
    bne $s0, $t0, loop
  
  #judge
  li $t0, 0
  move $t1, $s0
  addi $t1, $t1, -1
  
  loop_i:
    get_index($s1, $t0)
    lw $t3, str($s1)
    get_index($s1, $t1)
    lw $t2, str($s1)
    beq $t3, $t2, else
      if:
        la $a0, flag_0
        li $v0, 4
        syscall
        return_0
      else:
        addi $t0, $t0, 1
        addi $t1, $t1, -1
        bgt $t1, $t0, loop_i
        
  la $a0, flag_1
  li $v0, 4
  syscall
  return_0
      
      
  




























