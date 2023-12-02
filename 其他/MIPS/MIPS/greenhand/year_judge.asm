.data
  yes : .asciiz "1"
  no : .asciiz "0"
  
.text
    li $v0 5
    syscall 
    move $s0 $v0
    li $s1 4
    li $s2 100
    li $s3 400
    div $s0 $s3 # century runnian
    mfhi $s3
    bne $s3 $zero if_else_1
    
    if_1:
      la $a0 yes
      li $v0 4
      syscall
      j if_1_end
      
    if_else_1:
      div $s0 $s1 
      mfhi $s1
      div $s0 $s2
      mfhi $s2
      bne $s1 $zero if_else_2
      if_2:
      	bne $s2 $zero if_else_3
      	  if_3:
      	    la $a0 no
      	    li $v0 4
      	    syscall
      	    j if_3_end
      	  if_else_3:
      	    la $a0 yes
      	    li $v0 4
      	    syscall
      	    j if_3_end
      	  if_3_end:
      	    j if_2_end
        
      if_else_2:
        la $a0 no
        li $v0 4
        syscall
        j if_2_end
        
      if_2_end:
        j if_1_end
    	
    if_1_end:
      li $v0 10
      syscall