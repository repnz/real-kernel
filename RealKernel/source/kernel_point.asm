;------------------------------------------------------------
.286                 ; CPU type
;------------------------------------------------------------
.model TINY               ; memory of model
;---------------------- EXTERNS -----------------------------
extrn        _kernel_main:near     ; prototype of C func
;------------------------------------------------------------
;------------------------------------------------------------   
.code   
org        1000h       ; for BootSector
main:
        jmp short start     ; go to main
        nop
             
;----------------------- CODE SEGMENT -----------------------
start:  
        cli
        mov ax,cs               ; Setup segment registers
        mov ds,ax               ; Make DS correct
        mov es,ax               ; Make ES correct
        mov ss,ax               ; Make SS correct        
        mov bp,2000h
        mov sp,2000h            ; Setup a stack
        sti
                                ; start the program 
        call _kernel_main
		cli

		jmp $

        END main                ; End of program

