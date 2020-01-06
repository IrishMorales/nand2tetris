// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

@END
0;JMP

(PRESS_INIT)
	@i
	M=0
	@SCREEN
	M=-1

(PRESS_LOOP)
	@i
	D=M
	@SCREEN
	A=D+A
	M=-1
	D=A
	@i
	M=M+1
	
	@24575
	D=D-A
	@END
	D;JEQ
	
	@PRESS_LOOP
	0;JMP
	
(END)
	@KBD
	D=M
	@PRESS_INIT
	D;JNE
	
(END_INIT)
	@i
	M=0
	@SCREEN
	M=0

(END_LOOP)
	@i
	D=M
	@SCREEN
	A=D+A
	M=0
	D=A
	@i
	M=M+1
	
	@24575
	D=D-A
	@END
	D;JEQ
	
	@END_LOOP
	0;JMP
	
	@END
	0;JMP