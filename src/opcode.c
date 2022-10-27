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
        {"And with accumulator",0x35,"AND",zp_X,AND},
        {"Rotate left",0x36,"ROL",zp_X,ROL},
        {"Set carry flag",0x38,"SEC",none,SEC},
        {"And with accumulator",0x39,"AND",adr_Y,AND},
        {"And with accumulator",0x3d,"AND",adr_X,AND},
        {"Rotate left",0x3e,"ROL",adr_X,ROL},
        {"Return from interrupt",0x40,"RTI",none,RTI},
        {"Exclusive or",0x41,"EOR",pre_ind_X,EOR},
        {"Exclusive or",0x45,"EOR",zp,EOR},
        {"Logical shift right",0x46,"LSR",zp,LSR},
        {"Push accumulator to stack",0x48,"PHA",none,PHA},
        {"Exclusive or",0x49,"EOR",imm,EOR},
        {"Logical shift right",0x4a,"LSR",acc,LSR},
        {"Jump",0x4c,"JMP",adr,JMP},
        {"Exclusive or",0x4d,"EOR",adr,EOR},
        {"Logical shift right",0x4e,"LSR",adr,LSR},
        {"Branch on overflow clear",0x50,"BVC",none,BVC},
        {"Exclusive or",0x51,"EOR",pos_ind_Y,EOR},
        {"Exclusive or",0x55,"EOR",zp_X,EOR},
        {"Logical shift right",0x56,"LSR",zp_X,LSR},
        {"Clear interrupt disable",0x58,"CLI",none,CLI},
        {"Exclusive or",0x59,"EOR",adr_Y,EOR},
        {"Exclusive or",0x5d,"EOR",adr_X,EOR},
        {"Logical shift right",0x5e,"LSR",adr_X,LSR},
        {"Return from subroutine",0x60,"RTS",none,RTS},
        {"Add with carry",0x61,"ADC",pre_ind_X,ADC},
        {"Add with carry",0x65,"ADC",zp,ADC},
        {"Rotate right",0x66,"ROR",zp,ROR},
        {"Pull accumulator from stack",0x68,"PLA",none,PLA},
        {"Add with carry",0x69,"ADC",imm,ADC},
        {"Rotate right",0x6a,"ROR",acc,ROR},
        {"Jump indirect",0x6c,"JMP",ind_adr,JMP},
        {"Add with carry",0x6d,"ADC",adr,ADC},
        {"Rotate right",0x6e,"ROR",adr,ROR},
        {"Branch on overflow set",0x70,"BVS",none,BVS},
        {"Add with carry",0x71,"ADC",pos_ind_Y,ADC},
        {"Add with carry",0x75,"ADC",zp_X,ADC},
        {"Rotate right",0x76,"ROR",zp_X,ROR},
        {"Set interrupt disable",0x78,"SEI",none,SEI},
        {"Add with carry",0x79,"ADC",adr_Y,ADC},
        {"Add with carry",0x7d,"ADC",adr_X,ADC},
        {"Rotate right",0x7e,"ROR",adr_X,ROR},
        {"Store accumulator",0x81,"STA",pre_ind_X,STA},
        {"Store Y register",0x84,"STY",zp,STY},
        {"Store accumulator",0x85,"STA",zp,STA},
        {"Store X register",0x86,"STX",zp,STX},
        {"Decrement Y",0x88,"DEY",none,DEY},
        {"Transfer X to accumulator",0x8a,"TXA",none,TXA},
        {"Store Y register",0x8c,"STY",adr,STY},
        {"Store accumulator",0x8d,"STA",adr,STA},
        {"Store X register",0x8e,"STX",adr,STX},
        {"Branch on carry clear",0x90,"BCC",none,BCC},
        {"Store accumulator",0x91,"STA",pos_ind_Y,STA},
        {"Store Y register",0x94,"STY",zp_X,STY},
        {"Store accumulator",0x95,"STA",zp_X,STA},
        {"Store X register",0x96,"STX",zp_Y,STX},
        {"Transger Y to accumulator",0x98,"TYA",none,TYA},
        {"Store accumulator",0x99,"STA",adr_Y,STA},
        {"Transfer X to stack",0x9a,"TXS",none,TXS},
        {"Store accumulator",0x9d,"STA",adr_X,STA},
        {"Load into Y register",0xa0,"LDY",imm,LDY},
        {"Load into accumulator",0xa1,"LDA",pre_ind_X,LDA},
        {"Load into X register",0xa2,"LDX",imm,LDX},
        {"Load into Y register",0xa4,"LDY",zp,LDY},
        {"Load into accumulator",0xa5,"LDA",zp,LDA},
        {"Load into X register",0xa6,"LDX",zp,LDX},
        {"Transfer accumulator to Y",0xa8,"TAY",none,TAY},
        {"Load into accumulator",0xa9,"LDA",imm,LDA},
        {"Transfer accumulator to X",0xaa,"TAX",none,TAX},
        {"Load into Y register",0xac,"LDY",adr,LDY},
        {"Load into accumulator",0xad,"LDA",adr,LDA},
        {"Load into X register",0xae,"LDX",adr,LDX},
        {"Branch on carry set",0xb0,"BCS",none,BCS},
        {"Load into accumulator",0xb1,"LDA",pos_ind_Y,LDA},
        {"Load into Y register",0xb4,"LDY",zp_X,LDY},
        {"Load into accumulator",0xb5,"LDA",zp_X,LDA},
        {"Load into X register",0xb6,"LDX",zp_Y,LDX},
        {"Clear overflow flag",0xb8,"CLV",none,CLV},
        {"Load into accumulator",0xb9,"LDA",adr_Y,LDA},
        {"Transfer from stack to X",0xba,"TSX",none,TSX},
        {"Load into Y register",0xbc,"LDY",adr_X,LDY},
        {"Load into accumulator",0xbd,"LDA",adr_X,LDA},
        {"Load into Y register",0xbe,"LDX",adr_Y,LDX},
        {"Compare with Y",0xc0,"CPY",imm,CPY},
        {"Compare with accumulator",0xc1,"CMP",pre_ind_X,CMP},
        {"Compare with Y",0xc4,"CPY",zp,CPY},
        {"Compare with accumulator",0xc5,"CMP",zp,CMP},
        {"Decrement",0xc6,"DEC",zp,DEC},
        {"Increment Y register",0xc8,"INY",none,INY},
        {"Compare with accumulator",0xc9,"CMP",imm,CMP},
        {"Decrement X register",0xca,"DEX",none,DEX},
        {"Compare with Y",0xcc,"CPY",adr,CPY},
        {"Compare with accumulator",0xcd,"CMP",adr,CMP},
        {"Decrement",0xce,"DEC",adr,DEC},
        {"Branch on Not Equal",0xd0,"BNE",none,BNE},
        {"Compare with accumulator",0xd1,"CMP",pos_ind_Y,CMP},
        {"Compare with accumulator",0xd5,"CMP",zp_X,CMP},
        {"Decrement",0xd6,"DEC",zp_X,DEC},
        {"Clear decimal",0xd8,"CLD",none,CLD},
        {"Compare with accumulator",0xd9,"CMP",adr_Y,CMP},
        {"Compare with accumulator",0xdd,"CMP",adr_X,CMP},
        {"Decrement",0xde,"DEC",adr_X,DEC},
        {"Compare with X",0xe0,"CPX",imm,CPX},
        {"Subtract with carry",0xe1,"SBC",pre_ind_X,SBC},
        {"Compare with X",0xe4,"CPX",zp,CPX},
        {"Subtract with carry",0xe5,"SBC",zp,SBC},
        {"Increment memory",0xe6,"INC",zp,INC},
        {"Increment X register",0xe8,"INX",none,INX},
        {"Subtract with carry",0xe9,"SBC",imm,SBC},
        {"No operation",0xea,"NOP",none,NOP},
        {"Compare with X",0xec,"CPX",adr,CPX},
        {"Subtract with carry",0xed,"SBC",adr,SBC},
        {"Increment memory",0xee,"INC",adr,INC},
        {"Branch on equal",0xf0,"BEQ",none,BEQ},
        {"Subtract with carry",0xf1,"SBC",pos_ind_Y,SBC},
        {"Subtract with carry",0xf5,"SBC",zp_X,SBC},
        {"Increment memory",0xf6,"INC",zp_X,INC},
        {"Set decimal",0xf8,"SED",none,SED},
        {"Subtract with carry",0xf9,"SBC",adr_Y,SBC},
        {"Subtract with carry",0xfd,"SBC",adr_X,SBC},
        {"Increment memory",0xfe,"INC",adr_X,INC},
};
#endif