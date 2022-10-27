//
// Created by ADMIN on 16/10/2022.
//

#ifndef CPU_INSTRUCTION_H
#define CPU_INSTRUCTION_H
#include "cpu6502.h"
#include "opcode.h"
#include "bus.h"
void set_flag(cpu*my6502,bus*my_bus,uint16_t result);
extern int ADC(cpu*my6502,bus*my_bus,mode cpu_mode);
int AND(cpu*my6502,bus*my_bus,mode cpu_mode);
int ASL(cpu*my6502,bus*my_bus,mode cpu_mode);
int BPL(cpu*my6502,bus*my_bus,mode cpu_mode);
int BMI(cpu*my6502,bus*my_bus,mode cpu_mode);
int BIT(cpu*my6502,bus*my_bus,mode cpu_mode);
int BRK(cpu*my6502,bus*my_bus,mode cpu_mode);
int BVC(cpu*my6502,bus*my_bus,mode cpu_mode);
int BVS(cpu*my6502,bus*my_bus,mode cpu_mode);
int BCC(cpu*my6502,bus*my_bus,mode cpu_mode);
int BCS(cpu*my6502,bus*my_bus,mode cpu_mode);
int BNE(cpu*my6502,bus*my_bus,mode cpu_mode);
int CLC(cpu*my6502,bus*my_bus,mode cpu_mode);
int CLI(cpu*my6502,bus*my_bus,mode cpu_mode);
int CLD(cpu*my6502,bus*my_bus,mode cpu_mode);
int CLV(cpu*my6502,bus*my_bus,mode cpu_mode);
int CMP(cpu*my6502,bus*my_bus,mode cpu_mode);
int CPX(cpu*my6502,bus*my_bus,mode cpu_mode);
int CPY(cpu*my6502,bus*my_bus,mode cpu_mode);
int DEC(cpu*my6502,bus*my_bus,mode cpu_mode);
int DEX(cpu*my6502,bus*my_bus,mode cpu_mode);
int DEY(cpu*my6502,bus*my_bus,mode cpu_mode);
int EOR(cpu*my6502,bus*my_bus,mode cpu_mode);
int INC(cpu*my6502,bus*my_bus,mode cpu_mode);
int INX(cpu*my6502,bus*my_bus,mode cpu_mode);
int INY(cpu*my6502,bus*my_bus,mode cpu_mode);
int JMP(cpu*my6502,bus*my_bus,mode cpu_mode);
int JSR(cpu*my6502,bus*my_bus,mode cpu_mode);
int LDA(cpu*my6502,bus*my_bus,mode cpu_mode);
int LDX(cpu*my6502,bus*my_bus,mode cpu_mode);
int LDY(cpu*my6502,bus*my_bus,mode cpu_mode);
int LSR(cpu*my6502,bus*my_bus,mode cpu_mode);
int NOP(cpu*my6502,bus*my_bus,mode cpu_mode);
int ORA(cpu*my6502,bus*my_bus,mode cpu_mode);
int PHA(cpu*my6502,bus*my_bus,mode cpu_mode);
int PHP(cpu*my6502,bus*my_bus,mode cpu_mode);
int PHX(cpu*my6502,bus*my_bus,mode cpu_mode);
int PHY(cpu*my6502,bus*my_bus,mode cpu_mode);
int PLA(cpu*my6502,bus*my_bus,mode cpu_mode);
int PLP(cpu*my6502,bus*my_bus,mode cpu_mode);
int PLX(cpu*my6502,bus*my_bus,mode cpu_mode);
int PLY(cpu*my6502,bus*my_bus,mode cpu_mode);
int ROL(cpu*my6502,bus*my_bus,mode cpu_mode);
int ROR(cpu*my6502,bus*my_bus,mode cpu_mode);
int RTI(cpu*my6502,bus*my_bus,mode cpu_mode);
int RTS(cpu*my6502,bus*my_bus,mode cpu_mode);
int SBC(cpu*my6502,bus*my_bus,mode cpu_mode);
int SEC(cpu*my6502,bus*my_bus,mode cpu_mode);
int SED(cpu*my6502,bus*my_bus,mode cpu_mode);
int SEI(cpu*my6502,bus*my_bus,mode cpu_mode);
int STA(cpu*my6502,bus*my_bus,mode cpu_mode);
int STX(cpu*my6502,bus*my_bus,mode cpu_mode);
int STY(cpu*my6502,bus*my_bus,mode cpu_mode);
int STZ(cpu*my6502,bus*my_bus,mode cpu_mode);
int TAX(cpu*my6502,bus*my_bus,mode cpu_mode);
int TAY(cpu*my6502,bus*my_bus,mode cpu_mode);
int TSX(cpu*my6502,bus*my_bus,mode cpu_mode);
int TXA(cpu*my6502,bus*my_bus,mode cpu_mode);
int TXS(cpu*my6502,bus*my_bus,mode cpu_mode);
int TYA(cpu*my6502,bus*my_bus,mode cpu_mode);

#endif //CPU_INSTRUCTION_H
