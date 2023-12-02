li $v0, 5
syscall
move $t0, $v0		# t0 = a
li $v0, 5
syscall
move $t1, $v0		# t1 = b
bge $t0, $t1, begin
	move $t3, $t1
	move $t1, $t0
	move $t0, $t3
begin:
move $t2, $t1		# t2 = d
loop:
div $t0, $t1		# t0 / t1
mfhi $t3			# t4 = a % b
beqz $t3, loop_end 
	div $t0, $t1	# t0 / t1
	mfhi $t3		# t3 = a % b
	move $t2, $t3
	move $t0, $t1
	move $t1, $t3
	j loop
loop_end:
li $v0, 1
move $a0, $t2
syscall
li $v0, 10
syscall