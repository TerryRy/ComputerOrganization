.data
num: .space 8

.text
main:
	la $v1, num
	li $s1, 10
	li $s2, 20
	sw $ra, 0($a3)
	sw $s1, -4($a3)
	sw $s2, -8($a3)
	move $sp, $a3
	jal add
	lw $ra, 0($sp)
	move $t0, $v0
	beq $t0, $0, end
	j end
end:
