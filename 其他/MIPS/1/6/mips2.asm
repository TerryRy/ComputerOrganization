.data
ch:.space 2005
.text
li $v0, 5
syscall
move $t0, $v0			# t0 = n
li $v0, 5
syscall
move $t1, $v0			# t1 = x
li $v0, 5
syscall
move $t2, $v0			# t2 = y
li $v0, 8
la $a0, ch
li $a1, 2005
syscall
loop:
	lb $t5, ch($t1)		# hold = ch[x]
	lb $t4, ch($t2)		
	sb $t4, ch($t1)		# ch[x] = ch[y]
	sb $t5, ch($t2)		# ch[y] = hold
	add $t1, $t1, 1
	add $t2, $t2, -1
	ble $t1, $t2, loop
li $v0, 4
syscall
li $v0, 10
syscall