        .data
        .align 4
a:  .word 0x20

b:  .word 0x10

result:     .space 4
quotient:   .space 4


        .text       
        .global main
    
main:       nop
        ldr     r1, = a
        ldr     r2, = b 
        ldr     r3, = result
        mov     r0, = #0
        

