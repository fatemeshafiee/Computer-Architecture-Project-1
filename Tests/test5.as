	addi 1,0,15	#R[1] = 15
	slti 2,1,16	#R[2] = 1
	addi 2,2,-1	#R[2] = 0
	addi 13,0,17	#R[13] = 17
	sw  13,2,15     #MEM(0+15) = 17
	addi 12,0,14	#R[12] = 14
	addi 11,0,13       #R[11] = 13
	sub 14,12,13	#R[14] = -3
	or  15,14,0	#R[15] = -3
	lw  10,2,15	#R[10]=mem(0+15)
	j   End
End	halt
	.fill 5
	.fill -14
