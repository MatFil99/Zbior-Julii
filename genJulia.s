    section .data
    
msg: db '64-bit assembly main',10, 0
constFloat: dd 2.0
constFloat2: dd 4.0
saveXMM6: dd 0.0
saveXMM7: dd 0.0
saveXMM8: dd 0.0
saveXMM9: dd 0.0
saveXMM10: dd 0.0
saveXMM11: dd 0.0
saveXMM12: dd 0.0
saveXMM13: dd 0.0
saveXMM14: dd 0.0
saveXMM15: dd 0.0

    section     .text
    global      genJulia

genJulia:
;prolog:
    mov         rax, saveXMM6
    movsd       [rax], xmm6
    mov         rax, saveXMM7
    movsd       [rax], xmm7
    mov         rax, saveXMM8
    movsd       [rax], xmm8
    mov         rax, saveXMM9
    movsd       [rax], xmm9
    
   
; body
    mov         rax, rdi
    mov         rsi, 0  ; licznik petli
    mov         rdx, 0  ; licznik drugiej petli
    
    mov         rcx, 800
    mov         r8, constFloat
    mov         r9, constFloat2
    cvtsi2ss    xmm5, rcx
    divss       xmm4, xmm5 ; xmm4 - przemieszczenie odpowiadajace 1 pixelowi

    movss       xmm9, xmm2 ; wartosc x
start:
    mov         r10, 0
    movss       xmm5, xmm2 ; nowa wartosc ciagu Re(an)
    movss       xmm6, xmm3 ; nowa wartosc ciagu Im(an)
lop1:
    movss       xmm7, xmm5
    movss       xmm8, xmm6
    mulss       xmm7, xmm5
    mulss       xmm8, xmm6   
    subss       xmm7, xmm8
    addss       xmm7, xmm0
    movss       xmm8, xmm5
    movss       xmm5, xmm7  ; Re(an)
    mulss       xmm8, xmm6
    mulss       xmm8, [r8]  ; * 2
    addss       xmm8, xmm1  ; Im(an)
    movss       xmm6, xmm8
    mulss       xmm7, xmm7
    mulss       xmm8, xmm8
    addss       xmm7, xmm8  ; |an|^2 <= 4
    
    
    comiss      xmm7, [r9]
    
    ja          badWord
    
    
    inc         r10
    cmp         r10, 200    ; dokladnosc 200 wyraz
    js          lop1
    
goodWord:
    mov         [rax], byte 0
    jmp         incrLoop
badWord:
    mov         [rax], byte 255

incrLoop:
    inc         rax
;    mov         r10, 0
    inc         rsi
    addss       xmm2, xmm4
    cmp         rsi, 800
    js          start
    inc         rdx
    mov         rsi, 0
    movss       xmm2, xmm9 ; wracamy do poczatku (x)
    addss       xmm3, xmm4 ; przesuwamy w gore
    cmp         rdx, 800
    js          start
;epilog
    mov     rax, saveXMM6
    movsd   xmm6, [rax]
    mov     rax, saveXMM7
    movsd   xmm7, [rax]
    mov     rax, saveXMM8
    movsd   xmm8, [rax]
    mov     rax, saveXMM9
    movsd   xmm9, [rax]

end:
    ret