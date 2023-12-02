.text
li $t1, 100             #n = 100
li $t2, 0               #i

for_begin1:             #for (int i = 0; i < n; i++)
slt $t3, $t2, $t1       #{
beq $t3, $0, for_end1  
nop        
#do something
addi $t2, $t2, 1        #i++
j for_begin1
nop                     #}    

for_end1:
li $v0, 10
syscall