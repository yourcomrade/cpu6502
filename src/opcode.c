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
        {"Branch on plus",0x10,"BPL",none,BPL},
        {"Or with accumulator",0x11,"ORA",pos_ind_Y,ORA},
        {"Or with accumulator",0x15,"ORA",zp_X,ORA},
        {"Arithmetic shift left",0x16,"ASL",zp_X,ASL},
        {"Clear carry flag",0x18,"CLC",none,CLC},
        {"Or with accumulator",0x19,"ORA",adr_Y,ORA},
        {"Or with accumulator",0x1d,"ORA",adr_X,ORA},
        {"Arithmetic shift left",0x1e,"ASL",adr_X,ASL},
        {"Jump subroutine",0x20,"JSR",none,JSR},
        {"And with accumulator",0x21,"AND",pre_ind_X,AND},
        {"Test bit",0x24,"BIT",zp,BIT},
        {"And with accumulator",0x25,"AND",zp,AND},
        {"Rotate left",0x26,"ROL",zp,ROL},
        {"Pull status register from stack",0x28,"PLP",none,PLP},
        {"And with accumulator",0x29,"AND",imm,AND},
        {"Rotate left",0x2a,"ROL",acc,ROL},
        {"Test bit",0x2c,"BIT",adr,BIT},
        {"And with accumulator",0x2d,"AND",adr,AND},
        {"Rotate left",0x2e,"ROL",adr,ROL},
        {"Branch on minus",0x30,"BMI",none,BMI},
        {"And with accumulator",0x31,"AND",pos_ind_Y,AND},

};
#endif