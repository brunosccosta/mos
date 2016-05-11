.macro SAVE_REGS
	pushal	
	pushw	%ds
	pushw	%es
	pushw	%fs
	pushw	%gs
	pushl	%ebx
	movw	$0x10, %bx
	movw	%bx, %ds
	popl	%ebx
.endm		

.macro RESTORE_REGS
	popw	%gs
	popw	%fs
	popw	%es
	popw	%ds
	popal	
.endm		

.macro	INTERRUPT code
.global _asm_int_\code
_asm_int_\code:
	SAVE_REGS	
	pushw	$\code
	call	isr_default_int
	popl	%eax
	movb	$0x20, %al
	outb	%al, $0x20
	RESTORE_REGS	
	iret	
.endm		

.global _asm_exc_DZ
_asm_exc_DZ:		
	SAVE_REGS	
	call	isr_DZ_exc
	RESTORE_REGS	
	addl	$4, %esp
	iret

.global _asm_exc_GP
_asm_exc_GP:		
	SAVE_REGS	
	call	isr_GP_exc
	RESTORE_REGS	
	addl	$4, %esp
	iret	

.global _asm_exc_PF
_asm_exc_PF:		
	SAVE_REGS	
	call	isr_PF_exc
	RESTORE_REGS	
	addl	$4, %esp
	iret	

.global _asm_schedule
_asm_schedule:
	SAVE_REGS
	call	isr_schedule_int
	movb	$0x20, %al
	outb	%al, $0x20
	RESTORE_REGS	
	iret	

INTERRUPT	1	
INTERRUPT	2	
