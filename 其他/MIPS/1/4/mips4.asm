.data
arry1:.space 700
arry2:.space 700
sum:.space 700
max:.asciiz"max:"
min:.asciiz"min:"
a:.asciiz","
space:.asciiz" "
.text
li $v0, 5
syscall
move $t0, $v0				# m = $t0, 读入m
la $t1, arry1
li $t2, 1
li $a1, -800				# max
li $a2, 800				# min
loop1:
	li $v0, 5
	syscall
	sw $v0, 0($t1)			# 读入arry1[i]
	addi $t1, $t1, 4			# i ++
	addi $t2, $t2, 1			# i ++
	ble $t2, $t0, loop1
la $t1, arry2
li $t2, 1
loop2:
	li $v0, 5
	syscall
	sw $v0, 0($t1)			# 读入arry2[i]
	addi $t1, $t1, 4			# i ++
	addi $t2, $t2, 1			# i ++
	ble $t2, $t0, loop2
la $t1, arry1
la $t2, arry2
la $t3, sum
li $t4, 1
loop_sum:
	lw $t5, 0($t2)			# $t5 = arry2[i]
	lw $t6, 0($t1)			# $t6 = arry1[i]
	sub $t7, $t5, $t6		# sum[i] = arry2[i] - arry1[i]
	sw $t7, 0($t3)			# sum[i] = $t7
	ble $a1, $t7, loop_l		# max < sum[i]
		j exit_l
	loop_l:
		lw $a1, 0($t3)		# max = sum[i]
	exit_l:
	bge $a2, $t7, loop_h		# min > sum[i]
		j exit_h
	loop_h:
		lw $a2, 0($t3)		# min = sum[i]
	exit_h:
	add $t1, $t1, 4			# 移动下标
	add $t2, $t2, 4			# 移动下标
	add $t3, $t3, 4			# 移动下标
	add $t4, $t4, 1			# i ++
	ble $t4, $t0, loop_sum		# while(i <= m)
li $v0, 4
la $a0, max
syscall

li $v0, 1
move $a0, $a1
syscall

li $v0, 4
la $a0, a
syscall

la $a0, min
syscall

li $v0, 1
move $a0, $a2
syscall

li $v0, 4
la $a0, space
syscall

li $v0, 1
la $t3, sum
beq $t0, 1, loop_end
li $t4, 1
add $t0, $t0, -1
loop_print:
	lw $a0, 0($t3)			# $a0 = sum[i]
	syscall
	li $v0, 4
	la $a0, a
	syscall
	li $v0, 1
	add $t3, $t3, 4			# 移动下标
	add $t4, $t4, 1			# i ++
	ble $t4, $t0, loop_print		# while(i <= m)
loop_end:
lw $a0, 0($t3)
syscall
li $v0, 10
syscall					# return