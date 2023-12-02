.data
  line_i: .space 400
  line_j: .space 400
  x: .space 400
  y: .space 400
  #str: .asciiz      "-1" 
  
.macro scanf(%x)
  li $v0, 5
  syscall
  move %x, $v0
.end_macro

.macro print(%x)
  move %x, $a0
  li $v0, 1
  syscall
.end_macro

.macro getindex(%ans, %i)
  move %ans, %i
  sll %ans, %ans, 2
.end_macro

.macro return_0
  li $v0, 10
  syscall
.end_macro

.text
  scanf($t0)
  li $t1, 0
  loop:
  beq $t1, $t0, loop_end
    scanf($t2)
    scanf($t3)
    scanf($t4)
    scanf($t5)
    add $t4, $t4, $t2
    add $t5, $t5, $t3
    getindex($a0, $t1)
    sw $t2, line_i($a0)
    sw $t3, line_j($a0)
    sw $t4, x($a0)
    sw $t5, y($a0)
    addi $t1, $t1, 1
    j loop
  loop_end:
  move $t1, $t0
  
  scanf($t6)
  scanf($t7)
  
  deal:
  beq $t1, $zero, deal_end
    subi $t0, $t1, 1
    getindex($a0, $t0)
    lw $t2, line_i($a0)
    lw $t3, line_j($a0)
    lw $t4, x($a0)
    lw $t5, y($a0)
    if_1:
    bge $t6, $t2, if_2
    j if_end
    if_2:
    bge $t7, $t3, if_3
    j if_end
    if_3:
    bge $t4, $t6, if_4
    j if_end
    if_4:
    bge $t5, $t7, out
    j if_end
    out:
    print($t1)
    j deal_end
    if_end:
    addi $t1, $t1, 1
    j deal
  deal_end:
  return_0
    
    
    
    
    
    
  