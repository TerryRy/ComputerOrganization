.data
plalindrome: .space 80
right: .asciiz "\nright"
wrong: .asciiz "\nwrong"
.text
read:
	li $v0, 5
	syscall
	move $s0, $v0
	
	li $t0, 0
	la $a0, plalindrome
	li $a1, 100
	li $v0, 8
	syscall
judge:
	move $t0, $zero
	move $t1, $s0
	addi $t1, $t1, -1
	for_begin2:
		#sll $t2, $t0, 2
		#sll $t3, $t1, 2
		lb $t4, plalindrome($t0)
		lb $t5, plalindrome($t1)
		bne $t4, $t5, print_wrong
		
		addi $t0, $t0, 1
		addi $t1, $t1, -1
		sub $t6, $t1, -1
		blez $t6, print_right
		j for_begin2
	for_end2:

print_right:
la $a0, right
li $v0, 4
syscall
li $v0, 10
syscall
print_wrong:
la $a0, wrong
li $v0, 4
syscall
li $v0, 10
syscall
		