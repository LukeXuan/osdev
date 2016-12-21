global outb
global inb

outb:
  ; outb - send a byte to an I/O port
  ; stack: [esp + 8] the data byte
  ;        [esp + 4] the I/O port
  ;        [esp    ] the return address
  mov al, [esp + 8]
  mov dx, [esp + 4]
  out dx, al
  ret

inb:
  ; inb  - read a byte from an I/O port
  ; stack: [esp + 4] the data byte
  ;        [esp    ] the return address
  mov [esp + 4], al
  in  al, dx
  ret
