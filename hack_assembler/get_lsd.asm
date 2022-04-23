// test using memory as address

@1234
D=A
@constant
M=D
// constant = 1234

@10
D=A
@ten
M=D

@100
D=A
@hundred
M=D

@1000
D=A
@thousand
M=D

@10000
D=A
@tenthousand
M=D

@constant 
D=M
@digit_iso
M=D

// while digit_iso > 10_000
(while10k)

// if digit_iso > 10_000
@tenthousand
D=M
@digit_iso
D=M-D // d = digit_iso - 10_000

@endwhile10k
D;JLE
// subtract 10_000 from digit_iso
@tenthousand
D=M
@digit_iso
M=M-D


@while10k
0;JMP
(endwhile10k)


// while digit_iso > 1000
(while1k)

// if digit_iso > 1000
@thousand
D=M
@digit_iso
D=M-D // d = digit_iso - 1000

@endwhile1k
D;JLE
// subtract 1000 from digit_iso
@thousand
D=M
@digit_iso
M=M-D


@while1k
0;JMP
(endwhile1k)


// while digit_iso > 100
(while100)

// if digit_iso > 100
@hundred
D=M
@digit_iso
D=M-D // d = digit_iso - 100

@endwhile100
D;JLE
// subtract 1000 from digit_iso
@hundred
D=M
@digit_iso
M=M-D


@while100
0;JMP
(endwhile100)

// while digit_iso > 10
(while10)

// if digit_iso > 10
@ten
D=M
@digit_iso
D=M-D // d = digit_iso - 10

@endwhile10
D;JLE
// subtract 10 from digit_iso
@ten
D=M
@digit_iso
M=M-D


@while10
0;JMP
(endwhile10)

(end)
@end
0;JMP