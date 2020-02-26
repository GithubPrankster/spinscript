enum CMDS{
    /* Math Stuff!! */
    SPS_ADD = 0b000000,
    SPS_SUB = 0b000001,

    SPS_INC = 0b000010,
    SPS_DEC = 0b000011,

    SPS_ROR = 0b000100,
    SPS_AND = 0b000101,
    SPS_XOR = 0b000110,

    SPS_NOT = 0b000111,
    SPS_NEG = 0b001000,

    SPS_ASL = 0b001001,
    SPS_ASR = 0b001010,

    //Memory stuff!
    SPS_MOV = 0b001011,
    SPS_CMP = 0b001100,

    //Jump stuff!!
    SPS_JMP = 0b001101,
    SPS_JPE = 0b001110,
    SPS_JNE = 0b001111,

    //Debug stuff!
    SPS_HLT = 0b010000,
    SPS_DMP = 0b010001
};

enum OPERATIVE{
    ACCUMULATOR = 0b00000,
    INDEX_X = 0b00001,
    INDEX_Y = 0b00010,
    REG0 = 0b00011,
    REG1 = 0b00100,
    REG2 = 0b00101,
    REG3 = 0b00110,
    STACK_POINTER = 0b00111,
    PROGRAM_COUNTER = 0b01000,
    MEMORY = 0b01001,
    LITERAL = 0b01010
};

