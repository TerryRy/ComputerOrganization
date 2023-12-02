.data
  space: .space 40

.text
  li $t0, 10 #n
  li $t1, 0 #i
  loop:
  beq $t1, $t0, loop_end
  li $v0, 5
  syscall
  move $a0, $t1
  sll $a0, $a0, 2
  sw $v0, space($a0)
  addi $t1, $t1, 1
  j loop
  loop_end:
  li $v0, 5
  syscall
  move $t2,$v0 #t2 store max_height
  li $t1, 0
  li $t3, 0 #ans
  addi $t2, $t2, 30
  deal:
  beq $t1, $t0, deal_end
  move $a0, $t1
  sll $a0, $a0, 2
  lw $t4, space($a0)
  ble $t4, $t2, if
  
  else:
  j if_end
  
  if:
  addi $t3, $t3, 1
  j if_end
  
  if_end:
  addi $t1, $t1, 1
  j deal
  
  deal_end:
  move $a0, $t3
  li $v0, 1
  syscall
  
  li $v0, 10
  syscall
  
  
  