#ifndef OPCODE_H
#define OPCODE_H
#include<stdint.h>
#include "cpu6502.h"
#include "bus.h"
typedef enum mode{
    none,//Do nothing
    adr, //Absolute address mode
    adr_Y,//Absolute address mode + value stored in register Y
    adr_X,//Absolute address mode + value stored in register X
    acc,//Accumulator
    imm,//Immediate mode
    zp,//Zero page address mode which memory start from 0x0000-0x00FF
    zp_Y,//Zero page + value store in register Y
    zp_X,//Zero page + value store in register Y
    ind_adr,//Indirect access address mode
    pre_ind_X,// Pre-indirect access mode with value in register X
    pre_ind_Y,//Pre-indirect access mode with value in register Y
    pos_ind_X,//Post-indirect access mode with value in register X
    pos_ind_Y//Post-indirect access mode with value in register Y 
}mode;
typedef struct opcode{
    char des[25];//Description
    uint8_t hexcode;//Hexdacimal of the instruction code
    char ins[3];//Instruction
    mode cpu_mode;
    int(*op_code)(cpu*,bus*,mode);
}opcode;
#endif