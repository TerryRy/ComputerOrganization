.data
	my_character: .byte 'm'
.text
	la $a0, my_character
	li $v0, 4
	syscall
	
	li $v0, 10
	syscall