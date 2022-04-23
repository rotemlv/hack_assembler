// place 16 values in r0 to r8 (as a start)
// label swap as swap variable
// bubble each from r0 to r8 to the edge
@5
D=A
@R0
M=D

@7
D=A
@R1
M=D

@1
D=A
@R2
M=D

@4
D=A
@R3
M=D

@15
D=A
@R4
M=D

@9
D=A
@R5
M=D

@2
D=A
@R6
M=D


@8
D=A
@R7
M=D

@16
D=A
@R8
M=D

// test so far (V)

// save memory pointer here:
@memory
M=0
// save swap variable here:
@swap
M=0
@swap2
M=0
// pointer to memory of first element
@index
M=0
@9
D=A
@maxvalue
M=D // BECAUSE: we got 9 elements in "array"
// improvement to previous sort, add swapped flag, if 1, keep going with outer while, else, stop
@swapped
M=1

// while index < 9
(while)
// while tmpindex < maxvalue-1
@j // inner index
M=0

@swapped // set swapped to 0
M=0
(inwhile)
// inner loop runs from j=0 to j=7
// go to memory at j
@j
D=M 
A=D // point to memory at j
D=M // save arr[j]
@swap
M=D // tmp = arr[j]
@j
D=M+1// j+1
A=D // point to mem[j+1]
D=M // d = arr[j+1]
@swap2
M=D // tmp2 = arr[j+1]
@swap
D=D-M // arr[j+1] - arr[j]
// JUMP if D>=0
@endinnerif
D;JGE
(innerif)
// swap arr[j],arr[j+1] (not that complicated, or is it?)
@swapped
M=1
@j
A=M
D=M
@swap
M=D

@j
A=M+1
D=M
@swap2
M=D

@swap2
D=M

@j
A=M
M=D // memory points to arr[j]

@swap
D=M

@j
A=M+1
M=D // memory points to arr[j+1]


// implement !!!


(endinnerif)

@j
M=M+1 //j++
D=M // 
@maxvalue
D=M-D // d = n - j -> d = 9 - j, when j is 7 we stop! meaning we jump if this is greater than 1
D=D-1 // hence
@inwhile
D;JGT

// check if swapped:
@swapped
D=M
// if NOT swapped, jump OVER the rest to end the loop
@endwhile
D;JEQ
// increment
@index
M=M+1
D=M
@maxvalue
D=M-D
@while
D;JGT
(endwhile)
// test loop

// end of prog-ram
(end)
@end
0;JLE