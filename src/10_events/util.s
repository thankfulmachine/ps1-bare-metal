.set noreorder

.section .text, "ax", @progbits
.global OpenEvent
.type OpenEvent, @function

OpenEvent:
  li $t2, 0xb0
	jr $t2
	li $t1, 8
	nop

.global EnableEvent
.type EnableEvent @function

EnableEvent:
	li $t2,0xb0
	jr $t2
	li $t1,12
	nop

.global EnterCriticalSection
.type EnterCriticalSection @function

EnterCriticalSection:
	li $a0,1
	syscall
	jr $ra
	nop

.global ExitCriticalSection
.type ExitCriticalSection @function

ExitCriticalSection:
	li $a0,2
	syscall
	jr $ra
	nop

.global ReturnFromException
.type ReturnFromException @function

ReturnFromException:
	li $t2,176
	jr $t2
	li $t1,23
	nop