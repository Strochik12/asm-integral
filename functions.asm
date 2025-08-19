section .data
    const_minus2 dq -2.0  ; Constant -2.0
    const_14     dq 14.0  ; Constant 14.0
    const_5      dq 5.0   ; Constant 5.0
    const_2      dq 2.0   ; Constant 2.0
    const_6      dq 6.0   ; Constant 6.0
    const_minus1 dq -1.0  ; constant -1.0

section .text
global f1, f2, f3, df1, df2, df3
f1: ; y = ln(x)
    push ebp
    mov ebp, esp

    finit
    fldln2              ; st0 = ln(2)
    fld qword [ebp + 8] ; st0 = x, st1 = ln(2)
    fyl2x               ; st1 * log2(st0) → ln(2) * log2(x) = ln(x)

    leave
    ret
    
df1: ; y = 1 / x
    push ebp
    mov ebp, esp

    finit
    fld1                ; st0 = 1.0
    fld qword [ebp + 8] ; st0 = x, st1 = 1.0
    fdivp st1, st0      ; st1 / st0 (1.0 / x)

    leave
    ret
    
f2: ; y = -2x + 14
    push ebp
    mov ebp, esp

    finit
    fld qword [ebp + 8]        ; st0 = x
    fmul qword [const_minus2]  ; st0 = x * (-2.0)
    fadd qword [const_14]      ; st0 = (-2.0 * x) + 14.0

    leave
    ret
    
df2: ; y = -2
    push ebp
    mov ebp, esp

    finit
    fld qword [const_minus2]  ; st0 = -2.0

    leave
    ret
    
f3: ; y = 1 / (2 - x) + 6
    push ebp
    mov ebp, esp

    finit
    fld qword [const_2]     ; st0 = 2.0
    fsub qword [ebp + 8]    ; st0 = 2.0 - x
    fld1                    ; st0 = 1.0, st1 = (2.0 - x)
    fdivrp st1, st0         ; st0 = 1.0 / (2.0 - x)
    fadd qword [const_6]    ; st0 = (1.0 / (2.0 - x)) + 6.0

    leave
    ret
    
df3:
    push ebp
    mov ebp, esp

    finit
    fld qword [const_2]      ; st0 = 2.0
    fsub qword [ebp + 8]     ; st0 = 2.0 - x
    fmul st0, st0            ; st0 = (2 - x)^2
    fld qword [const_minus1] ; st0 = -1.0, st1 = (2 - x)^2
    fdivrp st1, st0          ; st0 = -1.0 / (2 - x)^2

    leave
    ret
