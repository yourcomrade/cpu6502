//
// Created by ADMIN on 16/10/2022.
//

#ifndef CPU_SYSTEM_H
#define CPU_SYSTEM_H
#include "memory.h"
#include "cpu6502.h"
#include "bus.h"
#include "opcode.h"
#include "instruction.h"
extern const opcode *searching(unsigned char hex_opcode);
extern void disassembler(char*file_name);
extern void load_program(char*file_name);

#endif //CPU_SYSTEM_H
