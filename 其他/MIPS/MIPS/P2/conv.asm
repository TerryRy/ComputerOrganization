.macro return_0
  li $v0, 10
  syscall
.end_macro

.macro scanf_to(%des)
  li $v0, 5
  syscall
  move %des, $v0
.end_macro

.macro get_index(%des, %i, %j, %x)
  mult %i, %x
  mflo %des
  add %des, %des, %j
  sll %des, %des, 2
.end_macro

.data
  map1: .space 400
  map2: .space 400
  m1: .space 4
  m2: .space 4
  n1: .space 4
  n2: .space 4
  space: .asciiz " "
  nxt: .asciiz "\n"

.text
  #scanf m1,n1,m2,n2
  scanf_to($s2)
  sw $s2, m1
  scanf_to($s3)
  sw $s3, n1
  scanf_to($s4)
  sw $s4, m2
  scanf_to($s5)
  sw $s5, n2
  #scanf map1
  li $t0, 0
  loop_i:
    li $t1, 0
    loop_j:
      scanf_to($s0)
      get_index($s1, $t0, $t1, $s3)
      sw $s0, map1($s1)
      addi $t1, $t1, 1
      bne $t1, $s3, loop_j
    loop_j_end:
    addi $t0, $t0, 1
    bne $t0 ,$s2, loop_i
  #scanf map2
  li $t0, 0
  loop_i_2:
    li $t1, 0
    loop_j_2:
      scanf_to($s0)
      get_index($s1, $t0, $t1, $s5)
      sw $s0, map2($s1)
      addi $t1, $t1, 1
      bne $t1, $s5, loop_j_2
    loop_j_2_end:
    addi $t0, $t0, 1
    bne $t0 ,$s4, loop_i_2
  #int ix=m1-m2,jx=n1-n2;
  sub $s6, $s2, $s4
  sub $s7, $s3, $s5
  #deal
  li $t0, 0 #i
  loop_1:
    li $t1, 0 #j
    loop_2:
      li $t3, 0 #x
      li $s0, 0 #ans
      loop_3:
        li $t4, 0
        loop_4:
          add $t5, $t0, $t3
          add $t6, $t1, $t4
          get_index($s1, $t5, $t6, $s3)
          lw $t8, map1($s1)
          get_index($s1, $t3, $t4, $s5)
          lw $t9, map2($s1)
          mult $t8, $t9
          mflo $t8
          add $s0, $s0, $t8
          addi $t4, $t4, 1
          bne $t4, $s5, loop_4
        loop_4_end:
        addi $t3, $t3, 1
        bne $t3, $s4, loop_3
      loop_3_end:
      move $a0, $s0
      li $v0, 1
      syscall
      la $a0, space
      li $v0, 4
      syscall
      addi $t1, $t1, 1
      ble $t1, $s7, loop_2
     loop_2_end:
     la $a0, nxt
     li $v0, 4
     syscall
     addi $t0, $t0, 1
     ble $t0, $s6, loop_1
  
  return_0
          




