.text
  li $v0, 5
  syscall
  move $s0, $v0 #n
  
  li $t0, 2 #i
  
  loop:
  beq $t0, $s0, loop_end #if(to==s0) to_end
    div $s0, $t0 #s0/t0
    mfhi $t1 #t1=s0%t0
    if:
    beq $t1, $zero, yes #if(t1==0)
    no:
      addi $t0, $t0, 1 #i++
      j loop
    yes: 
      mflo $a0
      li $v0, 1
      syscall
      j loop_end
  loop_end:
  li $v0, 10
  syscall
    