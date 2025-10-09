        .data
        .align 4
a:  .word 0x20 @ = 32 in decimal

b:  .word 0x10 @ = 16 in decimal

result:     .space 4 //result space for result
quotient:   .space 4


        .text       
        .global main
    
main:       nop
        ldr     r1, = a
        ldr     r2, = b 
        ldr     r3, = result
        mov     r0, #0
loop:
    cmp r0, r1
     bls stop
     add    r3,r3,r2
     add    r0,r0,#1
     b      loop

    str r3, [result]

stop:
        nop
        b       stop

