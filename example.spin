//Example code.
ADD ACC #2
ASL ACC #1

//Dump state!
DMP

//Compare accumulator to 8.
//If it's not equal to 8, jump
//to memory location 1.
CMP ACC #8
JNE $0001

//Dump final state and halt!
DMP
HLT