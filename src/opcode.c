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
        {"Or with accumulator",0x05,"ORA",zp,ORA},
        {"Arithmetic shift left",0x06,"ASL",zp,ASL},
        {"Push flag register",0x08,"PHP",none,PHP},
        {"Or with accumulator",0x09,"ORA",imm,ORA},
        {"Arithmetic shift left",0x0a,"ASL",zp,ASL},
        {"Or with accumulator",0x0d,"ORA",adr,ORA},
        {"Arithmetic shift left",0x0e,"ASL",adr,ASL},
};
#endif