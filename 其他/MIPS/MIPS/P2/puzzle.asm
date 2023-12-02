.macro return_0
  li $v0, 10
  syscall
.end_macro

.macro pop(%tmp)
  addi $sp, $sp, 4
  lw %tmp, ($sp)
.end_macro

.macro push(%tmp)
  sw %tmp, ($sp)
  subi $sp, $sp, 4
.end_macro

.macro scanf_to(%des)
  li $v0, 5
  syscall
  move %des, $v0
.end_macro

.macro store_to(%des, %from)
  sw %from, map(%des)
.end_macro

.macro get_index(%des, %i, %j, %tmp)
  mult %i, %tmp
  mflo %des
  add %des, %des, %j
  sll %des, %des, 2
.end_macro

.data
  map: .space 400
  vis: .space 400

.text
  main:
    #scanf("%d%d",&n,&m);
    scanf_to($s0) #s0->n
    scanf_to($s1) #s1->m
    #scanf("%d",&map[i][j]);
    li $t0, 0
    loop_i:
      li $t1, 0
      loop_j:
        scanf_to($t2)
        get_index($t3, $t0, $t1, $s1)
        store_to($t3, $t2)
        addi $t1, $t1, 1
        bne $t1, $s1, loop_j
      loop_j_end:
      addi $t0, $t0, 1
      bne $t0, $s0, loop_i
    loop_i_end:
    #scanf("%d%d%d%d",&sx,&sy,&ex,&ey);
    scanf_to($s2)
    scanf_to($s3)
    scanf_to($s4)
    scanf_to($s5)
    #sx-=1; sy-=1; ex-=1; ey-=1;
    subi $s2, $s2, 1
    subi $s3, $s3, 1
    subi $s4, $s4, 1
    subi $s5, $s5, 1
    #dfs(sx,sy)
    li $s6, 0 #ans=0
    move $a1, $s2
    move $a2, $s3
    jal dfs
    #print("%d",ans);	
    move $a0, $s6
    li $v0, 1
    syscall
    return_0
  
  dfs:
    #if(x==ex&&y==ey)
    if_ex:
      bne $a1, $s4, else
      true_ex:
      bne $a2, $s5, else
      ture_ey:
        #ans++;
        addi $s6, $s6, 1
        #return;
        jr $ra
    
    else:  
      push($ra)
      push($a1)
      push($a2)
      li $t1, 1
      get_index($t0, $a1, $a2, $s1)
      sw $t1, vis($t0)
      #[x-1][y]
      state1:
        subi $a1, $a1, 1
        #in_map(x-1,y)
        jal in_map
        beq $a3, $zero, state2
        #!vis[x-1][y]
        get_index($t0, $a1, $a2, $s1)
        lw $t1, vis($t0)
        bne $t1, $zero, state2
        #!map[x-1][y]
        lw $t1, map($t0)
        bne $t1, $zero, state2
        jal dfs
        
      state2:
        addi $a1, $a1, 2
        #in_map
        jal in_map
        beq $a3, $zero, state3
        #!vis
        get_index($t0, $a1, $a2, $s1)
        lw $t1, vis($t0)
        bne $t1, $zero, state3
        #!map
        lw $t1, map($t0)
        bne $t1, $zero, state3
        jal dfs
      state3:
        subi $a1, $a1, 1
        subi $a2, $a2, 1
        #in_map
        jal in_map
        beq $a3, $zero, state4
        #!vis
        get_index($t0, $a1, $a2, $s1)
        lw $t1, vis($t0)
        bne $t1, $zero, state4
        #!map
        lw $t1, map($t0)
        bne $t1, $zero, state4
        jal dfs
      state4:
        addi $a2, $a2, 2
        #in_map
        jal in_map
        beq $a3, $zero, return
        #!vis
        get_index($t0, $a1, $a2, $s1)
        lw $t1, vis($t0)
        bne $t1, $zero, return
        #!map
        lw $t1, map($t0)
        bne $t1, $zero, return
        jal dfs
      #vis[x][y]=0;
      return:
      pop($a2)
      pop($a1)
      pop($ra)
      get_index($t0, $a1, $a2, $s1)
      sw $zero, vis($t0)
      jr $ra





  in_map:
    li $a3 1
    if:
      bge $a1, $s0, return0
      bge $a2, $s1, return0
      blt $a1, $zero, return0
      blt $a2, $zero, return0
      return1:
        jr $ra
      return0:
        li $a3, 0
        jr $ra