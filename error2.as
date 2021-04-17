	 .fill 15	
	 nand 6,6,7 # bitwise nand between register6 and register7 and save the result in 6 
	 add  12,6,2
yay	 lbl	or 1,0,3
	 sub 5,8,6
	 nand 1,1,5
sec	 add 3,2,3
ori1 ori 5,9,yay
yay  slt 6,7,2
	 .fill 10
	 halt