.text
li  $v0,5
syscall                 # $v0 contains integer read
move $s0, $v0           # $s0 = $v0
li  $s1, 0              # $s1:used for storing add_figure $s1 = 0
li  $t0, 1              # $t0:used for circling

loop:
bgt $t0, $s0, loop_end  # bgt:extend_order, skip to loop_end when $t0 > $s0
add $s1, $s1, $t0       # $s1 = $s1 + $t0
addi $t0, $t0, 1        # $t0 = $t0 + 1
j   loop                # skip to loop

loop_end:
move $a0, $s1           # $a0 = $s1
li  $v0, 1              # $v0 = 1  syscall put $a0
syscall         
li  $v0,10              # $v0 = 10
syscall                 # end       