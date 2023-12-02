li $v0, 5
syscall								# scanf("%d", %$v0)
li $t0, 2							# $t0 = 2
div $v0, $t0							# $v0 / $t0
mflo $t2								# $t2 = $ v0 / $ t0
beq $v0, 1, lable1						# if($v0 == 1)
	beq $v0, 2, lable2					# if($v0 == 2)
		loop:
			div $v0, $t0				# $v0 / $t0
			mfhi $t1					# $t1 = $v0 % $t0
			blez $t1, loop0				# if($t1 <= 0)
			addi $t0, $t0, 1				# $t0 ++	
				ble $t0, $t2, loop		# if($t0 <= $t2)
					li $a0, 1		# $a0 = 1
					li $v0, 1
					syscall			# printf("%d", $a0)
					li $v0, 10
					syscall			# return
			loop0:
				li $a0, 0			# $a0 = 0
				li $v0, 1
				syscall				# printf("%d", $a0)
				li $v0, 10
				syscall				# return
	lable2:
		li $a0, 1					# $a0 = 1
		li $v0, 1
		syscall						# printf("%d", $a0)
		li $v0, 10
		syscall						# return
lable1:
	li $a0, 0						# $a0 = 0
	li $v0, 1
	syscall							# printf("%d", $a0)
	li $v0, 10
	syscall							# return