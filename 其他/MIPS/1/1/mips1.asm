li $v0, 5
syscall							# scan
li $t1, 4						# $t1 = 4
div $v0, $t1						# $v0 / $t1 = $hi ... $lo
mfhi $t0							# $t0 = $v0 % 4
ble $t0, 0, loop4					# if $t0 <= 0
	li $a0, 0					# $a0 = 0
	li $v0, 1
	syscall						# printf("%d", $a0)
	li $v0, 10
	syscall						# return
loop4:
	li $t1, 100					# $t1 = 100
	div $v0, $t1					# $v0 / $t1 = $hi ... $lo
	mfhi $t0						# $t0 = $v0 % 100
	ble $t0, 0, loop100				# if $t0 <= 0
		li $a0, 1				# $a0 = 1
		li $v0, 1
		syscall					# printf("%d", $a0)
		li $v0, 10
		syscall					# return
	loop100:
		li $t1, 400				# $t1 = 400
		div $v0, $t1				# $v0 / $t1 = $hi ... $lo
		mfhi $t0					# $t0 = $v0 % 400
		ble $t0, 0, loop400			# if $t0 <= 0
			li $a0, 0			# $a0 = 0
			li $v0, 1
			syscall				# printf("%d", $a0)
			li $v0, 10
			syscall				# return
		loop400:
		li $a0, 1				# $a0 = 1
		li $v0, 1
		syscall					# printf("%d", $a0)
		li $v0, 10
		syscall					# return
	
	
