	addi 1,0,10	# R[1]=10 
	addi 2,0,20	# R[2]=20
	sub  3,1,2	# R[3]= -10
	sw   3,0,15	# Memory[0+15] = R[3] = -10
	lw   4,0,15	# R[4] = Memory[0+15] = -10
	nand 5,4,3	# R[5] = 4 and 3 = 9
	beq  5,0,1	# go to END
	addi 5,5,30 # R[5] = 39
END addi 5,5,-6 # R[5] = 33
	halt    