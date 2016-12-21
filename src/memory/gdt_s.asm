global gdt_load_register

gdt_load_register:
  ; gdt_load - load the given GDT Descriptor into GDTR
  ; stack    : [esp + 4] the address of GDTR
  ;          : [esp    ] the return address
  mov eax, [esp + 4]
  lgdt [eax]
  ret
