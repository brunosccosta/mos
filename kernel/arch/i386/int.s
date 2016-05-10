.extern	$isr_default_int, $isr_schedule_int

.macro	SAVE_REGS	$0
	pushal	
	push	$ds
	push	$es
	push	$fs
	push	$gs
	pushl	%ebx
	movw	$0x10, %bx
	movw	%bx, $ds
	popl	%ebx
.endm		

.macro	RESTORE_REGS	$0
	pop	$gs
	pop	$fs
	pop	$es
	pop	$ds
	popal	
.endm		

.macro	INTERRUPT	$1
.global	_asm_int_%1	
_asm_int_%1:		
	SAVE_REGS	
	push	$%1
	call	$isr_default_int
	popl	%eax	default_int	#
	movb	$0x20,%al
	outb	%al,$0x20
	RESTORE_REGS	
	iret	
.endm		

.extern	isr_GP_exc,	$isr_PF_exc
.global	_asm_syscalls,	$_asm_exc_PF,$_asm_exc_GP
_asm_syscalls:		
	SAVE_REGS	
	pushl	%eax
	call	$do_syscalls
	popl	%eax
	cli	
	sti	
	RESTORE_REGS	
	iret	


_asm_exc_GP:		
	SAVE_REGS	
	call	$isr_GP_exc
	RESTORE_REGS	
	addl	$4,%esp
	iret	

_asm_exc_PF:		
	SAVE_REGS	
	call	$isr_PF_exc
	RESTORE_REGS	
	addl	$4,%esp
	iret	

global	_asm_schedule	
_asm_schedule:		
	SAVE_REGS	
	call	$isr_schedule_int
	movb	$0x20,%al
	outb	%al,$0x20
	RESTORE_REGS	
	iret	

INTERRUPT	1	
INTERRUPT	2	
