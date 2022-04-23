// add r0 to r2 r1 times
(firstnum)
@10  // 10 as a constant or A
D=A // save 3 to D
@R0 // point A to R0
M=D // save D in memory[0]
(secondnum)
// increment D by 1
D=D+1 // D=3
@R1 // point memory to R1
M=D // set memory[1] to D
(loop)
@R5
@R1
D=M
@R2
M=M+D
@R0
M=M-1
D=M
@loop
D;JGT
// now divide result by 2 :)

// divides value at r0 by value at r1
(firstnum)
@R2  // get result from R2
D=M // save it to D
@R0 // point A to R0
M=D // save D in memory[0]
(secondnum)
@2  // 2 as constant
D=A // D=2
@R1 // point memory to R1
M=D // set memory[1] to D
// while r3 is less than r0, increment it by r1, and increment r4 by 1
(loop2)
@R1
D=M
@R3
M=M+D
@R4
M=M+1
@R3
D=M
@R0
D=M-D
@loop2
D;JGT
// if D>R0, we have a remainder, subtract R4 by 1
@R3
D=M
@R0
D=M-D
@end
D;JGE
@R4
M=M-1


(end)
@end
0;JLE
