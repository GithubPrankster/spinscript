#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum{
    FALSE, TRUE
}BOOL;

typedef enum{
    MVM_ADD = 0xA0,
    MVM_SUB = 0xA1,
    MVM_PSH = 0xB0,
    MVM_POP = 0xB1,
    MVM_HLT = 0xF0,
    MVM_STT = 0xF1
}CMDS;

typedef struct{
    uint16_t memory[UINT16_MAX];
    uint8_t stk[16];
    uint16_t pc;
    uint8_t X, Y; 
    uint8_t A;
    uint8_t stk_count;
    BOOL halted;
}machina_vm;

void init_machina(machina_vm* mvm){
    mvm->pc = 0;
    mvm->X = 0;
    mvm->Y = 0;
    mvm->A = 0;
    mvm->stk_count = 0;
    mvm->halted = FALSE;
}

void interpret_machina(machina_vm* mvm, uint16_t inst){
    uint8_t opcode = inst >> 8;
    uint8_t op = inst & 0xFF;

    switch(opcode){
        case MVM_ADD:
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

void destroy_machina(machina_vm* mvm){
    free(mvm->stk);
    free(mvm->memory);
    free(mvm);
}

int main(int argc, char** argv){
    machina_vm* mvm = malloc(sizeof(machina_vm));
    FILE* handle = fopen("test.mh", "rb");

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