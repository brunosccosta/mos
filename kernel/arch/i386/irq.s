.macro SAVE_REGS
	pusha
    pushw	%ds
	pushw	%es
	pushw	%fs
	pushw	%gs
    movw	$0x10, %ax
	movw	%ax, %ds
	movw	%ax, %es
    movw	%ax, %fs
    movw	%ax, %gs
    movl	%esp, %eax
    pushl	%eax
.endm		

.macro RESTORE_REGS
	popl	%eax
    popw	%gs
    popw	%fs
    popw	%es
    popw	%ds
    popa
    addl	$8, %esp
    iret	
.endm	

.global _irq1
_irq1:
    SAVE_REGS
    call irq_handler_1
    RESTORE_REGS    
