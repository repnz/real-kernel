[bits 16]
[org 0x7c00]

%define kernel_load_address 0x8000
%define drive 0x80
%define kernel_sector 2
%define kernel_sectors_length 12


jmp 0000:start

start:
	
	; initialize ds and es to zero
	mov ax,cs
	mov ds,ax
	mov es,ax
	
	mov si, load_msg
	call print_string

	mov ax, 0
	mov es, ax

	mov cl, kernel_sector ; sector
	mov al, kernel_sectors_length ; number of sectors
	mov bx, kernel_load_address
	call load_sector
	
	mov ax, 0
	mov es, ax
	mov bx, kernel_load_address
	jmp bx

wait_forever:
	mov si, sleep
	call print_string
	jmp $                        ; endless loop

load_sector: ; cl = sector number, al = number of sectors to load, es:bx address to load
	mov dl,drive ; drive
	mov dh,0     ; head
	mov ch,0     ; cylinder
	mov ah,2
	int 0x13
	jnc .done
	
	; print error
	mov si, error_loading
	call print_string

	jmp wait_forever
.done:
	ret

print_string: ; si = c string pointer
.print_loop:
	lodsb ; load char from si into al

	; if char is zero end done
	test al,al
	jz .done
	
	mov ah,0x0e ; 0x0e function for teletype printing character
	mov bx,0 ; set pageNumber and color to 0
	int 10h
	jmp .print_loop
.done:
	ret

load_msg db "Loading Kernel..", 10, 13, 0
error_loading db "Error Loading Kernel!", 10, 13, 0
line db 10, 13, 0
sleep db "Sleep Forever", 10, 13, 0

times 510 - ($-$$) db 0 ; fill sector with zeros
dw 0xaa55               ; boot sector signature