//
// Created by ADMIN on 26/10/2022.
//
#ifndef OPCODE_C
#define OPCODE_C
#include "../inc/instruction.h"
#include "../inc/opcode.h"
#define num_opcode 151
opcode my_opcode[]={
        {"Break",0x00,"BRK",none,BRK},
        {"Or with accumulator",0x01,"ORA",pre_ind_X,ORA},
};
#endif