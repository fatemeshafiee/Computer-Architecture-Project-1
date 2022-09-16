    addi 2,0,15    #R[2] = 15
	add  1,0,2     #addd register0 and register2 and save in 1 R[1] = 15
	addi 3,0,-17   #R[3]  = -17
	add 15,2,2     #R[15] = 30
	sub  2,3,15    #sub 15 from 2 and save the result in 2 R[2] = -47
	slt  4,1,2     #compare 1,2 and save the result in 4  R[4] = 0
	addi 14,0,-10  #R[14] = -10
	or   6,4,14    #bitwise or between register4 and register14 and save the result in 6 R[6] = -10	
	addi 6,0,-6 
	addi 7,0,-7 
	nand 6,6,7     #bitwise nand between register6 and register7 and save the result in 6  R[6] = 7
	add  12,6,2    #addd register2 and register6 and save in 12  R[12] = -40
com slt  1,3,2     #R[1] = 0 
	 halt 
	.fill 15 
	.fill com 
	.space 20 
