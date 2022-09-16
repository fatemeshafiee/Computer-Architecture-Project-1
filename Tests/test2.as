	addi 1,0,15  #R[1] = 15
	addi 2,0,10  #R[2] = 10
iter sub  1,1,2   #R[1] = 5
	lui  13,5    #R[13] = 327680
	addi  3,0,5  #R[3] = 5
	beq  3,1,-4  # j  to iter  pc<2
	sw   3,0,14  #memory[12] = 5
	sw   1,0,15  #memry[13] = -5	
	add  4,3,2   #R[4] = 15
	lw   5,0,15  #R[5] = -5
	slt  6,5,0   #R[6] = 1
	halt
Fill    .fill 5
	    .fill -1        