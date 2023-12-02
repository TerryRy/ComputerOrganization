.macro return_0
  li $v0, 10
  syscall
.end_macro

.macro print_from(%des)
  lw $a0, array(%des)
  li $v0, 1
  syscall
.end_macro

.macro print_space
  la $a0, space
  li $v0, 4
  syscall
.end_macro

.macro get_index(%des, %num)
  move %des, %num
  sll %des, %des, 2
.end_macro

.macro println
  la $a0, nxt
  li $v0, 4
  syscall
.end_macro

.macro push(%tmp)
  sw %tmp, 0($sp)
  subi $sp, $sp, 4
.end_macro

.macro pop(%tmp)
  addi $sp, $sp, 4
  lw %tmp, 0($sp)
.end_macro

.data 
  vis: .space 40
  array: .space 40
  space: .asciiz " "
  nxt: .asciiz "\n"
  
.text

  main:
    #scanf n
    li $v0, 5
    syscall
    move $s0, $v0 # n->$s0
    li $t0, 0
    jal FullArray
    return_0
  
  
  
  FullArray:
    push($ra)
    
    if:
      blt $t0, $s0, else
      li $t1, 0
      loop:
        get_index($s1, $t1)
        print_from($s1)
        print_space
        addi $t1, $t1, 1
        bne $t1, $s0, loop
      loop_end:
        println
        pop($ra)
        jr $ra 
        
    else:
      li $t1, 0
      loop_i:
        get_index($s1, $t1)
        lw $t2, vis($s1)
        if_2:
          bne $t2, $zero, else_2
          li $t3, 1
          sw $t3, vis($s1)
          add $t3, $t3, $t1
          get_index($s1, $t0)
          sw $t3, array($s1)
          addi $t0, $t0, 1
          push($t1)
          jal FullArray
          pop($t1)
          get_index($s1, $t1)
          sw $zero, vis($s1)
          subi $t0, $t0, 1
        else_2:
          addi $t1, $t1, 1
          bne $t1, $s0, loop_i
      loop_i_end:
        pop($ra)
        jr $ra
        
  
  