// come on, are you kidding?

// define array size

@9
D=A
@array_size
M=D 

// end define array size

// initialize "array"

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

// end initialization

// save memory pointer here:
@memory
M=0
// save swap variable here:
@swap
M=0
@swap2
M=0
@key // like key in insertion
M=0
@j  // reset j
M=0

// "pointer" to memory of SECOND element (insertion)
@index
M=1

// main for: i = 1, i < n (index := i)

(for)  // i=1,i<array_size,i++
@index
A=M
D=M // d = arr[i]
@key
M=D // key = arr[i]
@index
D=M // d = i
@j
M=D-1 // j = i - 1

// inner while: while j>=0 and arr[j] > key
(innerwhile)

// conditions:


	@condition_1
	M=0

	@j
	D=M
	@endcond1
	D;JLT
	@condition_1
	M=1 // condition_1 = j >= 0

	

	// reset condition_2:
	@condition_2
	M=0

	@j
	A=M
	D=M // d = arr[j]
	@key
	D=D-M // d = arr[j] - key, we want it ABOVE 0


	// if D>0, set condition_2 to 1
	@endcond2
	D;JLE

	@condition_2
	M=1

	(endcond2)

	(endcond1) // end of condition 1 --> if index<0, we don't bother with the second condition!

	@condition_1
	D=M

	@condition_2
	D=D&M // binary AND

	// if not D, jump over inner while
	@endinnerwhile
	D;JEQ

// end conditions

// do arr[j + 1] = arr[j] (not swap!)
@j
A=M
D=M // d = arr[j]
@j
A=M+1 // address: j+1
M=D // arr[j+1] = arr[j]
@j
M=M-1 // j--

@innerwhile
0;JMP // jump to inner while again!
(endinnerwhile)

// arr[j + 1] = key
@key
D=M
@j
A=M+1
M=D

@index
M=M+1
D=M
@array_size
D=M-D
@for
D;JGT
(endfor)

// end main for
(end_prog)
@end_prog
0;JMP

