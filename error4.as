	  add 1,3,6
	  or 5,2,1
first slt 15,4,11
	  slti 14,11,3
jtyp  sw 14,0,first
	  .fill 180
	  j -5 #shouldn't have error
	  ori 7,13,954
	  addi 12,0,5
	  addi 10,0,70
	  slt 13,10,12
	  beq 0,13,jtyp
	  xor 11,15,6 # error unkown opcode
	  jalr 9,7