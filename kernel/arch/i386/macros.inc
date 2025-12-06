# push all gp registers to the stack
.macro pushad
push %eax
push %ecx
push %edx
push %ebx
push %ebp
push %esi
push %edi
.endm

# pop all gp registers from the stack
.macro popad
pop %edi
pop %esi
pop %ebp
pop %ebx
pop %edx
pop %ecx
pop %eax
.endm
