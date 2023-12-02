.macro return_0
  li $v0, 10
  syscall
.end_macro

.macro add_G(%i, %j, %tmp)
  mult %i, %tmp
  mflo $t7
  add $t7, $t7, %j
  sll $t7, $t7, 2
  li $t6, 1
  sw $t6, G($t7)
.end_macro

.macro scanf_to(%des)
  li $v0, 5
  syscall
  move %des, $v0
.end_macro

.macro vis_1(%des)
  sll %des, %des, 2
  li $t6, 1
  sw $t6, vis(%des)
  srl %des, %des, 2
.end_macro

.macro vis_0(%des)
  sll %des, %des, 2
  li $t6, 0
  sw $t6, vis(%des)
  srl %des, %des, 2
.end_macro

.macro get_index(%des, %i, %j, %tmp)
  mult %i, %tmp
  mflo %des
  add %des, %des, %j
  sll %des, %des, 2
.end_macro

.macro get_vis(%ans, %tmp)
  sll %tmp, %tmp, 2
  lw %ans, vis(%tmp)
  srl %tmp, %tmp, 2
.end_macro

.macro pop(%tmp)
  addi $sp, $sp, 4
  lw %tmp, ($sp)
.end_macro

.macro push(%tmp)
  sw %tmp, ($sp)
  subi $sp, $sp, 4
.end_macro

.macro printf(%ans)
  li $v0, 1
  move $a0, %ans
  syscall
.end_macro

.data
  G: .space 256
  vis: .space 256
  flag_0: .asciiz "0"
  flag_1: .asciiz "1"

.text
  main:
    # scanf("%d%d", &n, &m);
    scanf_to($s0) 
    scanf_to($s1)
    # scanf(x,y)
    li $t0, 0
    loop:
      scanf_to($t1)
      scanf_to($t2)
      subi $t1, $t1, 1
      subi $t2, $t2, 1
      add_G($t1, $t2, $s0)
      add_G($t2, $t1, $s0)
      addi $t0, $t0, 1
      bne $t0, $s1, loop
    loop_end:
      nop
    
    move $a1, $zero
    li $s1, 0 # ans=0
    jal dfs
    printf($s1)
    return_0
    
  dfs:
    # flag = 1
    li $t0 1 
    # for(i = 0; i < n; i++) flag &= book[i];
    li $t1 0
    loop_vis:
      get_vis($t2, $t1)
      and $t0, $t0, $t2
      addi $t1, $t1, 1
      bne $t1, $s0, loop_vis
    loop_vis_end:
      if:
        beq $t0, $zero, else
        get_index($t1, $a1, $zero, $s0)
        lw $t2, G($t1)
        beq $t2, $zero, else
        li $s1, 1
        jr $ra
        
    else:
     push($ra)
     push($a1)
      #  book[x] = 1;
      vis_1($a1)
      
      li $t0, 0
      loop_dfs:
         get_vis($t2, $t0)
         bne $zero, $t2, else_dfs
         get_index($t1, $a1, $t0, $s0)
         lw $t2, G($t1)
         beq $t2, $zero, else_dfs
           move $a1, $t0
           jal dfs
           pop($a1)
           push($a1)
         else_dfs:
         addi $t0, $t0, 1
         bne $t0, $s0, loop_dfs
      
      vis_0($a1)
      pop($a1)
      pop($ra)
      jr $ra










