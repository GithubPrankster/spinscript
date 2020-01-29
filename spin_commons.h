typedef enum{
    /* Math Stuff!! */
    //Add to accumulator.
    SPS_ADD = 0xA0,
    //Subtract from accumulator.
    SPS_SUB = 0xA1,
    //OR from accumulator.
    SPS_AOR = 0xA2,
    //AND from accumulator.
    SPS_AND = 0xA3,
    //XOR from accumulator.
    SPS_AXR = 0xA4,
    //Shift Accumulator to the left. (A.2)
    SPS_ASL = 0xA5,
    //Shift Accumulator to the right. (A/2)
    SPS_ASR = 0xA6,

    /* Stack Stuff!! */
    //Push to stack.
    SPS_PSH = 0xB0,
    //Pop off stack to Accumulator, X or Y registers, or to the void.
    SPS_POP = 0xB1,

    /* Jump Stuff!! */
    //Jump to somewhere. (usualy subroutine)
    SPS_JMP = 0xC0,
    //Jump IF Accumulator is equal to something.
    SPS_JPE = 0xC1,
    //Jump IF Accumulator is NOT equal to something.
    SPS_JNE = 0xC2,

    /* System Stuff!! */
    //Halt!
    SPS_HLT = 0xF0,
    //Dump current state of VM.
    SPS_STT = 0xF1,
    //Return from a subroutine.
    SPS_RTS = 0xF2,
}CMDS;