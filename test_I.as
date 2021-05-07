     addi 1,0,1   #addi
add2 addi 2,0,2   #addi in add2
     addi 3,2,-1  #addi in register 3
or4  ori  4,3,47  #
     ori  5,4,39
     slti 13,4,15
     lui  12,27
     sw   1,0,add2
     lw   8,0,or4
     jalr 13,10
     addi 1,0,8
     addi 2,0,8
     beq  1,2,done
     addi 1,0,10
     addi 2,0,8
     beq  1,2,forc
done .fill  15
forc .fill  16