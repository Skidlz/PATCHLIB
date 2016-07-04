; io401.asm  C calls for mpu-401 input/output

dataport    equ     330h    ;mpu401 data port
statport    equ     331h    ;mpu401 status/command port
drr         equ     40h     ;data receive ready mask
mpuack      equ     0FEh    ;mpu401 codes: acknowledge

tries       equ     0FFh    ;maximum tries on getting responce from mpu-401
;------------------------------------------------------
public  _getdata, _putdata, _putcmd
;------------------------------------------------------

savstk  macro       ;macro to save regs for C function
        push    bp
        mov     bp,sp
        push    di
        push    si
        endm

rclstk  macro       ;macro to recall saved regs for C
        pop     si
        pop     di
        mov     sp,bp
        pop     bp
        endm

;------------------------------------------------------

STACK	SEGMENT para stack 'STACK'
STACK	ENDS

_DATA	SEGMENT word public 'DATA'
_DATA	ENDS

_TEXT	SEGMENT byte public 'CODE'
		ASSUME CS:_TEXT, DS:_DATA, SS:STACK, ES:NOTHING

;------------------------------------------------------
;       putcmd(n)
;       output a command to mpu401, check for acknwldge

_putcmd proc
        savstk
        mov     dx,statport
        mov     cx,tries        ;retry counter in cl
lbl1:   in      al,dx           ;read status
        test    al,drr          ;find if bit 6 = 1
        jz      lbl2            ;o.k. so continue
        loop    lbl1            ;not ready - retry
        jmp     lbl5            ;timeout
lbl2:   mov     ax,[bp+4]       ;put char (as int) in a
        out     dx,al           ;*** output command ***
        mov     cx,tries
lbl3:   in      al,dx           ;read status
        rol     al,1            ;put bit 7 (dsr) to cf
        jnb     lbl4            ;if carry = 1, ready
        loop    lbl3            ;else retry
        jmp     lbl5            ;timeout, return -1
lbl4:   mov     dx,dataport
        in      al,dx           ;read data
        cmp     al,mpuack
        jz      cend            ;got ack so return it
lbl5:   mov     ax,-1           ;not ack, return -1
cend:   rclstk
        ret
_putcmd endp


;------------------------------------------------------
;       getdata()
;       get a byte of data from mpu-401

_getdata proc
        savstk
        mov     dx,statport
        mov     cx,tries        ;retry counter in cl
lbl6:   in      al,dx           ;read status
        rol     al,1            ;put bit 7 (dsr) to cf
        jnb     lbl7            ;if carry = 1, ready
        loop    lbl6            ;else retry
        mov     ax,-1           ;timeout, return -1
        jmp     gend
lbl7:   mov     dx,dataport
        sub     ah,ah           ;clear ah for C return
        in      al,dx           ;*** read data ***
gend:   rclstk
        ret                     ;return
_getdata endp


;------------------------------------------------------
;       putdata()
;       send a byte of data to mpu-401

_putdata proc
        savstk
        mov     dx,statport
        mov     cx,tries        ;retry counter in cl
lbl8:   in      al,dx           ;read status
        test    al,drr          ;test bit 6
        jz      lbl9            ;o.k. so continue
        loop    lbl8            ;else retry
        mov     ax,-1           ;timeout, return -1
        jmp     pdend
lbl9:   mov     dx,dataport
        mov     ax,[bp+4]       ;put int data in a
        out     dx,al           ;*** send data ***
pdend:  rclstk
        ret                     ;return
_putdata endp

;------------------------------------------------------
_TEXT	ENDS
		END
