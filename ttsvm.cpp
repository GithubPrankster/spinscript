#include <cstdint>
#include <cstdio>
#include <array>

#include "spin_commons.h"

struct TTSVM{
    //64kb just for you!
    std::array<uint16_t, 0x10000> memory;
    uint16_t instruction = 0;

    //Jump stack
    std::array<uint16_t, 4> stack;
    uint16_t stack_ptr = 0;

    //16 bit PC
    uint16_t program_counter = 0;

    //Registers!!
    //A|X|Y|R0|R1|R2|R3
    std::array<uint16_t, 7> registers;

    //Scratch register for literals. Literally.
    uint16_t scratch = 0;

    //Flags
    bool halted = false;
    bool zero = false;

    TTSVM();
    constexpr inline void inc_pc(){ program_counter++; }

    constexpr inline void decode(uint8_t& val, uint8_t& inst, uint8_t& addr){ 
        inst =   instruction & 0b0000000000111111;
        val =   (instruction & 0b0000011111000000) >> 6;
        addr =   instruction >> 11;
    }

    uint16_t& assign(const uint8_t& type);
    void exec();
    void run_cycle();
};

TTSVM::TTSVM(){
    memory.fill(0);
    stack.fill(0);
    registers.fill(0);
}

uint16_t& TTSVM::assign(const uint8_t& type){
    uint16_t& endval = registers[type];
    switch(type){
        case ACCUMULATOR:
        case INDEX_X:
        case INDEX_Y:
        case REG0:
        case REG1:
        case REG2:
        case REG3: endval = registers[type]; break;
        case STACK_POINTER: endval = stack_ptr; break;
        case PROGRAM_COUNTER: endval = program_counter; break;
        case MEMORY: inc_pc(); endval = memory[program_counter]; break;
        case LITERAL:
        default: inc_pc(); scratch = memory[program_counter]; endval = scratch; break;
    }
    return endval;
}

void TTSVM::exec(){
    instruction = memory[program_counter];
    uint8_t val, inst, addr;
    decode(val,  inst, addr);

    uint16_t& operated = assign(addr);
    uint16_t& operative = assign(val);

    switch(inst){
        case SPS_ADD: operated += operative; break;
        case SPS_SUB: operated -= operative; break;

        case SPS_INC: operated++; break;
        case SPS_DEC: operated--; break;

        case SPS_ROR: operated |= operative; break;
        case SPS_AND: operated &= operative; break;
        case SPS_XOR: operated ^= operative; break;

        case SPS_NOT: operated = ~operated; break;
        case SPS_NEG: operated = operated; break;

        case SPS_ASL: operated <<= operative; break;
        case SPS_ASR: operated >>= operative; break;

        case SPS_MOV:{
            operated = operative;
            operative = 0;
        }break;

        case SPS_CMP: zero = operated == operative; break;

        case SPS_JMP: inc_pc(); program_counter = memory[program_counter]; break;
        case SPS_JPE: inc_pc(); program_counter = zero ? memory[program_counter] : program_counter; break;
        case SPS_JNE: inc_pc(); program_counter = !zero ? memory[program_counter] : program_counter; break;

        case SPS_HLT: halted = true; break;
        case SPS_DMP:{
            printf("Instruction: %d %X %x\n", val, inst, addr);
            printf("Program Counter = %X\n", program_counter);
            printf("Was last comparison zero?: %s\n", zero ? "Yes!" : "No.");
            printf("Accumulator = %X, Index X = %X, Index Y = %X\n", registers[0], registers[1], registers[2]);
            printf("REG0 = %X, REG1 = %X, REG2 = %X, REG3 = %X\n", registers[3], registers[4], registers[5], registers[6]);
            printf("Stack Pointer = %d\n", stack_ptr);
        }break;
        default: break;
    }
}

void TTSVM::run_cycle(){
    exec();
    inc_pc();
}

constexpr inline uint16_t INSTRUCT(const uint8_t& val, const uint8_t& inst, const uint8_t& addr){
    return ((addr & 0b11111) << 11) | ((val & 0b11111) << 6) | (inst & 0b111111);
}

//Main loop.
int main(int argc, char** argv){
    TTSVM emulator;

    emulator.memory[0] = INSTRUCT(LITERAL, SPS_MOV, ACCUMULATOR);
    emulator.memory[1] = 0x11FF;

    emulator.memory[2] = INSTRUCT(ACCUMULATOR, SPS_MOV, REG0);

    emulator.memory[3] = INSTRUCT(0, SPS_DMP, 0);
    emulator.memory[4] = INSTRUCT(0, SPS_HLT, 0);

    while(!emulator.halted){
        emulator.run_cycle();
    }
        
    return 0;
}