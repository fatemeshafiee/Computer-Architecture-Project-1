	lui  1,17	#R[1] = 1114112    
	addi 2,1,3	#R[2] = 1114115
bt	or   3,1,2	#R[3] = 1114115
	addi 4,3,0	#R[4] = 1114115
	beq  4,3,bt	#pc = bt+pc+1
	add  4,4,1 	#no change
	ori  12,4,10	#no change
	addi  5,0,10       #R[5] = 10
	jalr 6,5	# pc =R[5] = 10 , R[6] = pc+1 = 9
	j    End	# pc = 12
five    addi 4,4,3	#R[4] = 1114118
	j    9          # pc = 8
End     addi 13,0,13
	halt    