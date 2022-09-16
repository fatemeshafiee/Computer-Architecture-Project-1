add2 addi 2,0,2   #addi in add2
	 addi 3,2,-1  #addi in register 3
or4  ori  4,3,47  #
	 ori  5,4,39
	 slti 13,4,15
lui5 lui  12,27
	 sub 2,3,15 # sub 15 from 2 and save the result in 2
	 slt 4,1,2  #  compare 1,2 and save the result in 4
	 or  6,4,14 # bitwise or between register4 and register14 and save the result in 6 
	 .fill 15
	 j klm
	 halt
	 .space 17
	 add 1,4,9