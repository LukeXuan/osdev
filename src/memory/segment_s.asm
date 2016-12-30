global segment_load_ds
global segment_load_es
global segment_load_ss
global segment_load_cs

segment_load_ds:
  ; segment_load_register - load the DS Register
  ; stack	: [esp + 4] the offset of the descriptor
  ;			: [esp    ] the return address
  mov ds, [esp + 4]
  ret

segment_load_es:
  ; segment_load_register - load the ES Register
  ; stack	: [esp + 4] the offset of the descriptor
  ;			: [esp    ] the return address
  mov es, [esp + 4]
  ret

segment_load_ss:
  ; segment_load_register - load the SS Register
  ; stack	: [esp + 4] the offset of the descriptor
  ;			: [esp    ] the return address
  mov ss, [esp + 4]
  ret

segment_load_cs:
  ; segment_load_register - load the CS Register
  ; stack	: [esp + 4] the offset of the descriptor
  ;			: [esp    ] the return address
  jmp 0x08:flush_cs

flush_cs:
  ret
