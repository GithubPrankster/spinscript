# Machina
MachinaVM is an interpreted virtual machine based on various old architectures. machina.c documents the instructions used. It currently runs a test program. Bytecode only.

## How do I run things?
`machina test.mh`, it'll inform you if you screwed that up.

## What does it have?
* 65k of dual-byte (word) memory.
* X, Y, A registers.
* 16 dual-byte (word) stack to push to, or pop to the registers, or just the void.
* Halting, system state dumping.

