//(firstnum)
@333  // 333 as a constant or A
D=A // save 333 to D
@R0 // point A to R0
M=D // save D in memory[0]
//(secondnum)
@33  // 33 as constant
D=A // D=33
@R1 // point memory to R1
M=D // set memory[1] to D
@R0 // move to r0
D=M // save value in D
@R1 // move to r1
D=D+M // add memory[1] to D
@R2 // move to r2
M=D // save result to memory