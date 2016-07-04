;BIOSCALL.ASM 	c runnable bios calls for screen manipulation.
;				ver 1.1 clearsc() using safe char write bios call.
; Calling convetions consistent with Microsoft and Turbo C compilers.

BIOS10	EQU		10H		;BIOS10 (HEX) CALL
SCRNRT	EQU		79D		;RIGHT EDGE OF SCREEN
;----------------------------------------------------------------
PUBLIC	_clearsc, _home, _csrplot, _writchr, _writbw, _writul
PUBLIC	_writrv, _writblr
;----------------------------------------------------------------

SAVSTK	MACRO			;MACRO TO SAVE REGS FOR C FUNCTION
		PUSH	BP
		MOV		BP,SP
		PUSH	DI
		PUSH	SI
		ENDM

RCLSTK	MACRO			;MACRO TO RECALL SAVED REGS FORC
		POP		SI
		POP		DI
		MOV		SP,BP
		POP		BP
		ENDM

;----------------------------------------------------------------

STACK	SEGMENT para stack 'STACK'
STACK	ENDS

_DATA	SEGMENT word public 'DATA'
_DATA	ENDS

_TEXT	SEGMENT byte public 'CODE'
		ASSUME CS:_TEXT, DS:_DATA, SS:STACK, ES:NOTHING

;----------------------------------------------------------------
;		clearsc()
;		CLEAR THE SCREE
;		RETURNS CURSOR TO HOME POSITION WHEN DONE

_clearsc		PROC near
		SAVSTK
		MOV		DX, 0			;START AT TOP LEFT
		MOV		BX, 0007H		;PAGE 0, B/W ATTRIBUTE = 07
		MOV		AH, 02H
		INT		BIOS10
		MOV		CX,80*25		;NO OF CHARS ON 80 x 25 SCREEN
		MOV		AL,' '
		MOV		AH,09H
		INT		BIOS10
		MOV		AH,02H			;HOME CURSOR
		INT		BIOS10
		RCLSTK
		RET
_clearsc		ENDP

;----------------------------------------------------------------
;		home()
;		HOME THE CURSOR

_home	PROC near
		SAVSTK
		MOV		DX,0
		MOV		BH,0
		MOV		AH,02H
		INT		BIOS10
		RCLSTK
		RET
_home	ENDP

;----------------------------------------------------------------
;		csrplot(X,Y)
;		MOVE CURSOR TO X,Y ON SCREEN; X AND Y ON STACK

_csrplot	PROC near
		SAVSTK
		MOV		CX,[BP+6]
		MOV		DH,CL		;Y POS IN DH
		MOV		CX,[BP+4]
		MOV		DL,CL		;X POS IN DL
		MOV		AH,02H		;SET CURS POS
		MOV		BH,0		;SCREEN 0
		INT		BIOS10
		RCLSTK
		RET
_csrplot	ENDP

;----------------------------------------------------------------
;		writchr(C,N)
;		WRITE CHAR C N TIMES AT CURSOT POSITION, NO ATTRIBUTE CHANGE

_writchr	PROC near
		SAVSTK
		MOV		AX,[BP+4]	;AL HAS CHAR
		MOV		AH,0AH		;WRITE CHAR CALL
		MOV		CX,[BP+6]	;N IN CX
		MOV		BX, 0		;PAGE 0
		INT		BIOS10
		CALL	INCCSR		;MOVE CSR TO RIGHT
		RCLSTK
		RET
_writchr	ENDP

;----------------------------------------------------------------
;		writbw(C,N)
;		WRITE CHAR C N TIMES IN NORMAL B/W MODE

_writbw	PROC near
		SAVSTK
		MOV		AX,[BP+4]	;AL HAS CHAR
		MOV		AH,09H		;WRITE CHAR AND ATTRIBUTE
		MOV		CX,[BP+6]	;X in CX
		MOV		BX,0007H	;B/W ON PAGE 0
		INT		BIOS10
		CALL	INCCSR		;MOVE CSR TO RIGHT
		RCLSTK
		RET
_writbw	ENDP

;----------------------------------------------------------------
;		writul(C,N)
;		WRITE CHAR C N TIMES IN UNDERLINE MODE

_writul	PROC near
		SAVSTK
		MOV		AX,[BP+4]	;AL HAS CHAR
		MOV		AH,09H		;WRITE CHAR AND ATTRIBUTE
		MOV		CX,[BP+6]	;N IN CX
		MOV		BX,0001H	;UL ON PAGE 0
		INT		BIOS10
		CALL	INCCSR		;MOVE CSR TO RIGHT
		RCLSTK
		RET
_writul	ENDP

;----------------------------------------------------------------
;		writrv(C,N)
;		WRITE CHAR C N TIMES IN REVERSE VIDEO MODE

_writrv	PROC near
		SAVSTK
		MOV		AX,[BP+4]	;AL HAS CHAR
		MOV		AH,09H		;WRITE CHAR AND ATTRIBUTE
		MOV		CX,[BP+6]	;N IN CX
		MOV		BX,0070H	;REV ON PAGE 0
		INT		BIOS10
		CALL	INCCSR		;MOVE CSR TO RIGHT
		RCLSTK
		RET
_writrv	ENDP

;----------------------------------------------------------------
;		writblr(C,N)
;		WRITE CHAR C N TIMES IN BLINKING REVERSE MODE

_writblr	PROC near
		SAVSTK
		MOV		AX,[BP+4]	;AL HAS CHAR
		MOV		AH,09H		;WRITE CHAR AND ATTRIBUTE
		MOV		CX,[BP+6]	;N IN CX
		MOV		BX,00F0H	;BLINKING REV ON PAGE 0
		INT		BIOS10
		CALL	INCCSR		;MOVE CSR TO RIGHT
		RCLSTK
		RET
_writblr	ENDP


;----------------------------------------------------------------
;		INCCSR	INREMENT CURSOR POSSITION

INCCSR	PROC near
		MOV		AH,03H
		MOV		BH,0
		INT		BIOS10		;LOCATE CURSOR, RESULT IN DX
		CMP		DL,SCRNRT	;AT OR OVER RT EDGE?
		JGE		OK1
		INC		DL			;INCREMENT COLUMN
OK1:	MOV		AH,02H
		INT		BIOS10
		RET
INCCSR	ENDP

;----------------------------------------------------------------

_TEXT	ENDS
		END

