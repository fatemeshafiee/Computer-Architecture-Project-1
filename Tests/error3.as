	 sub 2,7,15 # sub 15 from 2 and save the result in 2
lst	 slt 8,9,2  #  compare 1,2 and save the result in 4
	 or  1,4,14
jump j lst
	 jalr 16,14
	 add 4,5,6
	 sw 5,7,524287 #error for offset > 16
	 .fill 4287
	 j jump
	 lw 1,3,786
	 addi 1,0,983