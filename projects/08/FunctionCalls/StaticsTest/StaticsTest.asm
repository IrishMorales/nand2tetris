@261
D=A
@SP
M=D
(Sys.init)
@6
D=A
@SP
A=M
M=D
@SP
M=M+1
@8
D=A
@SP
A=M
M=D
@SP
M=M+1
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
@2
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Class1.set
0;JMP
($ret.0)
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
@23
D=A
@SP
A=M
M=D
@SP
M=M+1
@15
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
@2
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Class2.set
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
@$ret.2
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
@Class1.get
0;JMP
($ret.2)
@$ret.3
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
@Class2.get
0;JMP
($ret.3)
(WHILE)
@WHILE
0;JMP
(Class1.set)
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
@Class1.vm.0
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
@1
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
@Class1.vm.1
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
@SP
A=M
M=D
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
(Class1.get)
@Class1.vm.0
D=M
@SP
A=M
M=D
@SP
M=M+1
@Class1.vm.1
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
M=M-D
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
(Class2.set)
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
@Class2.vm.0
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
@1
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
@Class2.vm.1
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
@SP
A=M
M=D
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
(Class2.get)
@Class2.vm.0
D=M
@SP
A=M
M=D
@SP
M=M+1
@Class2.vm.1
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
M=M-D
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