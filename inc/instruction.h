//
// Created by ADMIN on 16/10/2022.
//

#ifndef CPU_INSTRUCTION_H
#define CPU_INSTRUCTION_H
#include "cpu6502.h"
#include "opcode.h"
#include "bus.h"
extern void set_flag(cpu*my6502,bus*my_bus,uint16_t result);
extern int ADC(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int AND(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int ASL(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int BPL(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int BMI(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int BIT(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int BRK(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int BVC(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int BVS(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int BCC(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int BCS(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int BNE(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int BEQ(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int CLC(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int CLI(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int CLD(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int CLV(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int CMP(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int CPX(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int CPY(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int DEC(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int DEX(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int DEY(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int EOR(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int INC(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int INX(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int INY(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int JMP(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int JSR(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int LDA(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int LDX(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int LDY(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int LSR(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int NOP(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int ORA(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int PHA(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int PHP(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int PHX(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int PHY(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int PLA(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int PLP(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int PLX(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int PLY(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int ROL(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int ROR(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int RTI(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int RTS(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int SBC(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int SEC(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int SED(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int SEI(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int STA(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int STX(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int STY(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int STZ(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int TAX(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int TAY(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int TSX(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int TXA(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int TXS(cpu*my6502,bus*my_bus,mode cpu_mode);
extern int TYA(cpu*my6502,bus*my_bus,mode cpu_mode);

#endif //CPU_INSTRUCTION_H
