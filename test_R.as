	add 1,0,2  #addd register0 and register2 and save in 1
	sub 2,3,15 # sub 15 from 2 and save the result in 2
	slt 4,1,2  #  compare 1,2 and save the result in 4
	or  6,4,14 # bitwise or between register4 and register14 and save the result in 6 
	.fill 15	
	nand 6,6,7 # bitwise nand between register6 and register7 and save the result in 6 
	add  12,6,2 #addd register2 and register6 and save in 12
	.space 20
com	slt 1,2,3
	.fill com
