.data
num: .space 8

.text
main:
    la $a3, num
    li $s1, 10
    li $s2, 20
    sw $s1, 0($a3)
    sw $s2, 4($a3)
    j end
end: