#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum{
    FALSE, TRUE
}BOOL;

typedef enum{
    //Add to accumulator.
    MVM_ADD = 0xA0,
    //Subtract from accumulator.
    MVM_SUB = 0xA1,
    //Push to stack.
    MVM_PSH = 0xB0,
    //Pop off stack to Accumulator, X or Y registers, or to the void.
    MVM_POP = 0xB1,
    //Halt!
    MVM_HLT = 0xF0,
    //Dump current state of VM.
    MVM_STT = 0xF1
}CMDS;

typedef struct{
    //Kilobytes of memory for you.
    uint16_t memory[UINT16_MAX];
    //16 bytes of stack.
    uint8_t stk[16];
    //16-bit Program Counter.
    uint16_t pc;
    //X and Y registers.
    uint8_t X, Y; 
    //Accumulator, good for maths.
    uint8_t A;
    //Counter for stack.
    uint8_t stk_count;
    //Is the system halted?
    BOOL halted;
}machina_vm;

//Initialize MachinaVM.
void init_machina(machina_vm* mvm){
    mvm->pc = 0;
    mvm->X = 0;
    mvm->Y = 0;
    mvm->A = 0;
    mvm->stk_count = 0;
    mvm->halted = FALSE;
}

//Interpret code on MachinaVM's memory.
void interpret_machina(machina_vm* mvm, uint16_t inst){
    uint8_t opcode = inst >> 8;
    uint8_t op = inst & 0xFF;

    switch(opcode){
        case MVM_ADD:
            mvm->A += op;
            break;
        case MVM_SUB:
            mvm->A += op;
            break;
        case MVM_HLT:
            mvm->halted = TRUE;
            printf("System halted.\n");
            break;
        case MVM_PSH:
            if(mvm->stk[mvm->stk_count] != 0){
                mvm->stk[mvm->stk_count] = op;
            }
            else{
                mvm->stk_count++;
                mvm->stk[mvm->stk_count] = op;
            }
            break;
        case MVM_POP:
            switch(op){
                case 0:
                    mvm->A = mvm->stk[mvm->stk_count];
                    break;
                case 1:
                    mvm->X = mvm->stk[mvm->stk_count];
                    break;
                case 2:
                    mvm->Y = mvm->stk[mvm->stk_count];
                    break;
                default:
                    break;
            }
            mvm->stk[mvm->stk_count] = 0;
            mvm->stk_count--;
            break;
        case MVM_STT:
            printf("X = %d, Y = %d, A = %d\nPC = %d, STK_CNT = %d\n", mvm->X, mvm->Y, mvm->A, mvm->pc, mvm->stk_count);
            break;
        default:
            mvm->halted = TRUE;
            printf("Unknown operation %x for %x at point %d\n", opcode, op, mvm->pc);
            break;
    }
    mvm->pc += 2;
}

//Free memory that MachinaVM took for schemy reasons.
void destroy_machina(machina_vm* mvm){
    free(mvm->stk);
    free(mvm->memory);
    free(mvm);
}

//Main loop.
int main(int argc, char** argv){
    machina_vm* mvm = malloc(sizeof(machina_vm));
    if(argc < 2){
        fprintf(stderr, "You need to specify the code to interpret...\n");
        return -1;
    }
    else{
        FILE* handle = fopen(argv[1], "rb");
        if(!handle){
            fprintf(stderr, "You need to specify CORRECT code to interpret...\n");
            return -1;
        }

        uint16_t counter = 0;
        char c = fgetc(handle); 
        while (c != EOF){ 
            mvm->memory[counter] = c;
            c = fgetc(handle);
            counter++;
        } 

        while(mvm->halted == FALSE){
            interpret_machina(mvm, mvm->memory[mvm->pc] << 8 | mvm->memory[mvm->pc + 1]);
        }

        fclose(handle);
        destroy_machina(mvm);
        return 0;
    }
}