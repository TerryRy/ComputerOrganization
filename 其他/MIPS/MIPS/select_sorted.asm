.data
  array: .space 400 # sotre the int
  message_input_n: .asciiz "Please input an integer as the length of the sequence:\n"
  message_input_array: .asciiz "Please input an integer followed with a line break:\n"
  message_output_array: .asciiz "The sortede sequence is:\n"
  space: .asciiz " "
  stack: .space 100
.text