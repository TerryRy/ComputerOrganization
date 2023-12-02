.data
str: .asciiz    "Hello World"

.text
la  $a0, str #load the str's address to $a0 
li  $v0, 4 #[load immediate]tell the cp to print
syscall #let's do it

li  $v0, 10 #end the program
syscall             