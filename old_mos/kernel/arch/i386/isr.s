.global _isr0
_isr0:
    cli
    pushl	$0
    pushl	$0
    jmp isr_common_stub

.global _isr8
_isr8:
    cli
    pushl	$8
    jmp isr_common_stub

.global _isr13    
_isr13:
    cli
    pushl	$13
    jmp isr_common_stub
    
isr_common_stub:
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
    call	fault_handler
    popl	%eax
    popw	%gs
    popw	%fs
    popw	%es
    popw	%ds
    popa
    addl	$8, %esp
    iret
