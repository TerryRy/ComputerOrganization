.macro scanf(%in)
  li $v0, 5
  syscall
  move %in, $v0
.end_macro

.macro print(%out)
  move $a0, %out
  li $v0, 1
  syscall
.end_macro

.macro return_0
  li $v0, 10
  syscall
.end_macro

.macro getindex(%i, %j, %m, %ans) #(i,j)'s address for m each line
  mul %i, %m
  mflo %ans
  add %ans, %ans, %j
  sll %ans, %ans, 2
.end_macro

.macro get_index(%i, %ans) # i's address
  move %ans, %i
  sll %ans, %ans, 2
.end_macro

.macro push(%tmp)
  sw %tmp, $sp
  subi $sp, $sp, 4
.end_macro

.macro pop(%tmp)
  addi $sp, $sp, 4
  lw %tmp, $sp
.end_macro

.data
  a: .space 400
  signal_input_1: .asciiz "Please input the total number: "
  signal_input_2: .asciiz "Please input the integers: "
  signal_output: .asciiz "The sorted numbers are: "
  space: .asciiz " "
  nxt: .asciiz "\n"
  
.text
  signal:
    li $v0, 4
    la $a0, signal_input_1
    syscall
    li $v0, 4
    la $a0, signal_input_2
    syscall
  #end_signal
  
  input:
    scanf($t1) #scanf(n)
    li $t0, 0 #i=0
    loop:
      beq $t0, $t1, loop_end
      scanf($t2)
      get_index($t0, $t3)
      sw $t2, a($t3)
      addi $t0, $t0, 1
      j loop
    loop_end:
      li $t0, 0
        
  bubble_sort:
    loop_i:
      beq $t0, $t1, loop_i_end # for(i=0; i<n; i++)
      li $t4, 0
      loop_j:
        add $t5, $t4, $t0 
        addi $t5, $t5, 1
        beq $t5, $t1, loop_j_end # j + 1 + i < n 
        get_index($t4, $t3)
        lw $t2, a($t3) # $t2 = a[j]
        addi $t3, $t3, 4
        lw $t6, a($t3) # $t6 = a[j+1]
        if:
        bgt $t2, $t6, if_greater
        if_less_or_equal:
          addi $t4, $t4, 1
          j loop_j
        if_greater:
          move $t7, $t2
          move $t2, $t6
          move $t6, $t7 # swap(a[j],a[j+1])
          get_index($t4, $t3)
          sw $t2, a($t3) 
          addi $t3, $t3, 4
          sw $t6, a($t3)
          addi $t4, $t4, 1
          j loop_j
      loop_j_end:
        addi $t0, $t0, 1
        j loop_i
    loop_i_end:
      li $t0, 0
      li $t2, 0
  
  put:
    li $v0, 4
    la $a0, signal_output
    syscall
    loop_i_2:
      beq $t0, $t1, loop_i_2_end
      get_index($t0, $t3)
      lw $t2, a($t3)
      print($t2)
      li $v0, 4
      la $a0, space
      syscall
      addi $t0, $t0, 1
      j loop_i_2
    loop_i_2_end:
      return_0
      
        
      
          
          
    
  