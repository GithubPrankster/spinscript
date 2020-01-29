#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum{
    FALSE, TRUE
}BOOL;

typedef enum{
    //Add to accumulator.
    SPS_ADD = 0xA0,
    //Subtract from accumulator.
    SPS_SUB = 0xA1,
    //Push to stack.
    SPS_PSH = 0xB0,
    //Pop off stack to Accumulator, X or Y registers, or to the void.
    SPS_POP = 0xB1,
    //Halt!
    SPS_HLT = 0xF0,
    //Dump current state of VM.
    SPS_STT = 0xF1
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
void init_machina(machina_vm* SPS){
    SPS->pc = 0;
    SPS->X = 0;
    SPS->Y = 0;
    SPS->A = 0;
    SPS->stk_count = 0;
    SPS->halted = FALSE;
}

//Interpret code on MachinaVM's memory.
void interpret_machina(machina_vm* SPS, uint16_t inst){
    uint8_t opcode = inst >> 8;
    uint8_t op = inst & 0xFF;

    switch(opcode){
        case SPS_ADD:
            SPS->A += op;
            break;
        case SPS_SUB:
            SPS->A -= op;
            break;
        case SPS_HLT:
            SPS->halted = TRUE;
            printf("System halted.\n");
            break;
        case SPS_PSH:
            if(SPS->stk[SPS->stk_count] != 0){
                SPS->stk[SPS->stk_count] = op;
            }
            else{
                SPS->stk_count++;
                SPS->stk[SPS->stk_count] = op;
            }
            break;
        case SPS_POP:
            switch(op){
                case 0:
                    SPS->A = SPS->stk[SPS->stk_count];
                    break;
                case 1:
                    SPS->X = SPS->stk[SPS->stk_count];
                    break;
                case 2:
                    SPS->Y = SPS->stk[SPS->stk_count];
                    break;
                default:
                    break;
            }
            SPS->stk[SPS->stk_count] = 0;
            SPS->stk_count--;
            break;
        case SPS_STT:
            printf("X = %d, Y = %d, A = %d\nPC = %d, STK_CNT = %d\n", SPS->X, SPS->Y, SPS->A, SPS->pc, SPS->stk_count);
            break;
        default:
            SPS->halted = TRUE;
            printf("Unknown operation %x for %x at point %d\n", opcode, op, SPS->pc);
            break;
    }
    SPS->pc += 2;
}

//Free memory that MachinaVM took for schemy reasons.
void destroy_machina(machina_vm* SPS){
    fprintf(stderr, "Freeing memory.\n");
    free(SPS->memory);
}

//Main loop.
int main(int argc, char** argv){
    machina_vm* SPS = malloc(sizeof(machina_vm));
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
            SPS->memory[counter] = c;
            c = fgetc(handle);
            counter++;
        } 

        while(SPS->halted == FALSE){
            interpret_machina(SPS, SPS->memory[SPS->pc] << 8 | SPS->memory[SPS->pc + 1]);
        }

        fclose(handle);
        destroy_machina(SPS);
        return 0;
    }
}