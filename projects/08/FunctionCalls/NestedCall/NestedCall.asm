(Sys.init)
@LCL
A=M
M=0
@4000
D=A
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=A
@13
M=D
@SP
M=M-1
A=M
D=M
@13
A=M
M=D
@5000
D=A
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=A
@13
M=D
@SP
M=M-1
A=M
D=M
@13
A=M
M=D
@$ret.0
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@5
D=D-A
@0
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Sys.main
0;JMP
($ret.0)
@1
D=A
@5
D=D+A
@13
M=D
@SP
M=M-1
A=M
D=M
@13
A=M
M=D
(LOOP)
@LOOP
0;JMP
(Sys.main)
@LCL
A=M
M=0
@0
D=A
@LCL
D=D+M
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1
@0
D=A
@LCL
D=D+M
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1
@0
D=A
@LCL
D=D+M
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1
@0
D=A
@LCL
D=D+M
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1
@0
D=A
@LCL
D=D+M
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1
@4001
D=A
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=A
@13
M=D
@SP
M=M-1
A=M
D=M
@13
A=M
M=D
@5001
D=A
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=A
@13
M=D
@SP
M=M-1
A=M
D=M
@13
A=M
M=D
@200
D=A
@SP
A=M
M=D
@SP
M=M+1
@1
D=A
@LCL
D=D+M
@13
M=D
@SP
M=M-1
A=M
D=M
@13
A=M
M=D
@40
D=A
@SP
A=M
M=D
@SP
M=M+1
@2
D=A
@LCL
D=D+M
@13
M=D
@SP
M=M-1
A=M
D=M
@13
A=M
M=D
@6
D=A
@SP
A=M
M=D
@SP
M=M+1
@3
D=A
@LCL
D=D+M
@13
M=D
@SP
M=M-1
A=M
D=M
@13
A=M
M=D
@123
D=A
@SP
A=M
M=D
@SP
M=M+1
@$ret.1
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@5
D=D-A
@1
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Sys.add12
0;JMP
($ret.1)
@0
D=A
@5
D=D+A
@13
M=D
@SP
M=M-1
A=M
D=M
@13
A=M
M=D
@0
D=A
@LCL
D=D+M
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1
@1
D=A
@LCL
D=D+M
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1
@2
D=A
@LCL
D=D+M
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1
@3
D=A
@LCL
D=D+M
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1
@4
D=A
@LCL
D=D+M
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M+D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M+D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M+D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M+D
@SP
M=M+1
@LCL
D=M
@13
M=D
@5
D=D-A
A=D
D=M
@14
M=D
@SP
A=M-1
D=M
@ARG
A=M
M=D
@ARG
D=M+1
@SP
M=D
@13
D=M
@1
D=D-A
A=D
D=M
@THAT
M=D
@13
D=M
@2
D=D-A
A=D
D=M
@THIS
M=D
@13
D=M
@3
D=D-A
A=D
D=M
@ARG
M=D
@13
D=M
@4
D=D-A
A=D
D=M
@LCL
M=D
@14
A=M
0;JMP
(Sys.add12)
@LCL
A=M
M=0
@4002
D=A
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=A
@13
M=D
@SP
M=M-1
A=M
D=M
@13
A=M
M=D
@5002
D=A
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=A
@13
M=D
@SP
M=M-1
A=M
D=M
@13
A=M
M=D
@0
D=A
@ARG
D=D+M
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1
@12
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M+D
@SP
M=M+1
@LCL
D=M
@13
M=D
@5
D=D-A
A=D
D=M
@14
M=D
@SP
A=M-1
D=M
@ARG
A=M
M=D
@ARG
D=M+1
@SP
M=D
@13
D=M
@1
D=D-A
A=D
D=M
@THAT
M=D
@13
D=M
@2
D=D-A
A=D
D=M
@THIS
M=D
@13
D=M
@3
D=D-A
A=D
D=M
@ARG
M=D
@13
D=M
@4
D=D-A
A=D
D=M
@LCL
M=D
@14
A=M
0;JMP
(END)
@END
0;JMP
