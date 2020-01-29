![Spinscript rules!](promo/spinscript_full.png)
# SPINscript
*SPINscript* is a scripting toolset created by Uneven to provide a behaviour similar to that of SCUMM (Script Creation Utility for Maniac Mansion) for his future
game projects. It is separated into the main *SPINscript* language, currently an Assembly-esque thing, *Paraphenalia*, a bytecode compiler for the language, and
*TTSVM*, a virtual machine which interprets the bytecode generated.

## What does SPIN in SPINscript stand for?
It stands for **Specially Powerful Incredibly Nonsensical**. Yep.

## And TTSVM?
That stands for **Tornado Twisting Scripting Virtual Machine**. Equally as weird. (an additional interpretation is text to speech virtual machine, but there is no speech in here... yet!)

## What about Paraphenalia?
Paraphenalia refers to something like tools in a usually funny way. There you go.

## How do I run some scripts?
Run make for `parasc` & `ttsvm`, compile (if you want) the example script with `paraphenalia example.spin` then run `ttsvm example.spc`!

## What does TTSVM have?
* 65k of dual-byte (word) memory.
* X, Y, A registers.
* 16 dual-byte (word) stack to push to, or pop to the registers, or just the void.
* Halting, system state dumping.

