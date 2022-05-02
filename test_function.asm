Dump of assembler code for function _Z17printIfLessThan50h:
   0x0000000000401156 <+0>:	push   %rbp
   0x0000000000401157 <+1>:	mov    %rsp,%rbp
   0x000000000040115a <+4>:	sub    $0x10,%rsp
   0x000000000040115e <+8>:	mov    %edi,%eax
   0x0000000000401160 <+10>:	mov    %al,-0x4(%rbp)
   0x0000000000401163 <+13>:	cmpb   $0x31,-0x4(%rbp)
   0x0000000000401167 <+17>:	ja     0x40117e <_Z17printIfLessThan50h+40>
   0x0000000000401169 <+19>:	movzbl -0x4(%rbp),%eax
   0x000000000040116d <+23>:	mov    %eax,%esi
   0x000000000040116f <+25>:	mov    $0x402010,%edi
   0x0000000000401174 <+30>:	mov    $0x0,%eax
   0x0000000000401179 <+35>:	call   0x401030 <printf@plt>
   0x000000000040117e <+40>:	nop
   0x000000000040117f <+41>:	leave  
   0x0000000000401180 <+42>:	ret    
End of assembler dump.
