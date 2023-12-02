.text
  ori $a0, $0, 1
  jal loop
  add $a2, $a2, $a0
  li $v0, 10
  syscall
  
  loop:
  sll $a1, $a0, 3
  sub $a2, $ra, $a1
  jr $ra
  add $a2, $a1, $a0