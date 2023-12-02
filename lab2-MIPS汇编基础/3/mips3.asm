li $v0, 5
syscall						# scanf("%d", &$v0)
move $t0, $v0					# $t0 = $v0

li $v0, 5
syscall						# scanf("%d", &$v0)
move $t1, $v0					# $t1 = $v0

li $v0, 5
syscall						# scanf("%d", &$v0)
move $t2, $v0					# $t2 = $v0

beq $t2, 0, lable0				# if($t2 == 0)
	beq $t2, 1, lable1			# if($t2 == 1)
		beq $t2, 2, lable2		# if($t2 == 2)
			div $t0, $t1		# $t0 / $t1
			mflo $a0			# $a0 = $
			li $v0 1
			syscall			# printf("%d", $a0)
			li $v0 10
			syscall			# returnt0 / $t1
		lable2:
			mult $t0, $t1		# $a0 = $t0 - $t1
			mflo $a0			 
			li $v0 1
			syscall			# printf("%d", $a0)
			li $v0 10
			syscall			# return

	lable1:
		sub $a0, $t0, $t1		# $a0 = $t0 - $t1
		li $v0 1
		syscall				# printf("%d", $a0)
		li $v0 10
		syscall				# return
	
lable0:
	add $a0, $t0, $t1			# $a0 = $t0 + $t1
	li $v0 1
	syscall					# printf("%d", $a0)
	li $v0 10
	syscall					# return