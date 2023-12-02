.macro return_0
  li $v0, 10
  syscall
.end_macro

.macro push(%tmp)
  sw %tmp, ($sp)
  subi $sp, $sp, 4
.end_macro

.macro pop(%tmp)
  addi $sp, $sp, 4
  lw %tmp, ($sp)
.end_macro

.macro get_index(%des, %i)
  move %des, %i
  #sll %des, %des, 1
.end_macro

.data
  st: .space 2000

.text
  main:
    li $s2, 10
    li $t0, 1
    #scanf("%d",&n);
    li $v0, 5
    syscall
    move $s0, $v0 #s0 store:n
    bne $s0, $zero, deal
    move $a0, $t0
    li $v0, 1
    syscall
    return_0
    deal:
    #cal(n)
    move $a1, $s0 
    jal cal
    #printf_st
    subi $s1, $s1, 1
    for_put:
      li $v0, 1
      get_index($t2, $s1)
      lb $a0, st($t2)
      syscall
      subi $s1, $s1, 1
      bge $s1, $zero, for_put    
    return_0
    
  cal:
    x_1:
      bne $a1, $t0, else
      li $s1, 1 #tot=1
      sb $t0, st
      jr $ra
      
    else:
      push($ra)
      push($a1)
      subi $a1, $a1, 1
      jal cal
      pop($a1)
      pop($ra)
      #for(i=0; i<tot; i++)
      li $t1, 0
      li $t4, 0
      for:
        get_index($t2, $t1)
        lb $t3, st($t2)
        mult $t3, $a1
        mflo $t3
        add $t3, $t3, $t4
        div $t3, $s2
        mflo $t4 #add = tmp/10;
        mfhi $t3 #st[i] = tmp%10;
        sb $t3, st($t2)
        addi $t1, $t1, 1
        bne $t1, $s1, for
      #while(add) {
      #	st[tot++] = add%10;
      #             add/=10;
      #}
      end_for:
        beq $t4, $zero, end_while
        div $t4, $s2
        mfhi $t3
        move $t1, $s1
        addi $s1, $s1, 1
        get_index($t2, $t1)
        sb $t3, st($t2)
        mflo $t4
        j end_for
      end_while:
      jr $ra
      
    
