     addi 1,0,1      #addi R[1] = 1
add2 addi 2,0,2      #addi in add2  R[2] = 2
     addi 3,2,-1     #addi in register 3 R[3] = 1
or4  ori  4,3,47     # R[4] = 47
     ori  5,4,39     # R[5] = 47
     slti 13,4,15    # R[13] = 0
     lui  12,27      # R[12] = 1769472
     sw   1,0,add2   # mem(1+0) = 1
     lw   8,0,or4    # R[8] = mem(0+3) =120848431
     addi 10,0,13    # R[10] = 13
     jalr 13,10      # R[13] = 11 , pc
     addi 1,0,8	     # R[1] = 8   
     addi 2,0,8	     # R[2] = 8  
     beq  1,2,done   # not taken
     addi 1,0,10     # R[1] = 10
     addi 2,0,8	     # R[2] = 8
     beq  1,2,forc   # not taken
     halt
done .fill  15
forc .fill  16  