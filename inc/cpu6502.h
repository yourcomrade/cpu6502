#ifndef CPU6502_H
#define CPU6502_H
///Header file for 6502 cpu
#include<stdint.h> 
///Header for uint
typedef struct CPU{
    uint16_t pc;///program counter or instruction pointer
    uint8_t reg_A;///register A
    uint8_t reg_X;///register X
    uint8_t reg_Y;///register Y
    uint8_t reg_sta;///Status register
    uint64_t clock;///For clock cycle
    uint8_t sp;///Stack pointer
    
}cpu;
///Function to get Negative flag from status register
extern uint8_t get_N_flag(uint8_t reg_sta);

///Function to set Negative flag for status register
extern void set_N_flag(cpu*my6502);
///Function to clear Negative flag for status register
extern void clr_N_flag(cpu*my6502);


///Function to get Overflow flag from status register
extern uint8_t get_V_flag(uint8_t reg_sta);
///Function to set Overflow flag for status register
extern void set_V_flag(cpu*my6502);
///Function to clear Overflow flag for status register
extern void clr_V_flag(cpu*my6502);


///Function to get Break flag from status register
extern uint8_t get_B_flag(uint8_t reg_sta);
///Function to set Break flag for status register
extern void set_B_flag(cpu*my6502);
///Function to clear Break flag for status register
extern void clr_B_flag(cpu*my6502);


///Function to get Decimal flag from status register
extern uint8_t get_D_flag(uint8_t reg_sta);
///Function to set Decimal flag for status register
extern void set_D_flag(cpu*my6502);
///Function to clear Decimalflag for status register
extern void clr_D_flag(cpu*my6502);


/// Function to get Interupt flag from status register
extern uint8_t get_I_flag(uint8_t reg_sta);
///Function to set Interrupt flag for status register
extern void set_I_flag(cpu*my6502);
///Function to clear Interrupt flag for status register
extern void clr_I_flag(cpu*my6502);


///Function to get Zero flag from status register
extern uint8_t get_Z_flag(uint8_t reg_sta);
///Function to set Zero flag for status register
extern void set_Z_flag(cpu*my6502);
///Function to clear Zero flag for status register
extern void clr_Z_flag(cpu*my6502);


///Function to get Carry flag from status register
extern uint8_t get_C_flag(uint8_t reg_sta);
///Function to set Carry flag for status register
extern void set_C_flag(cpu*my6502);
///Function to clear Carry flag for status register
extern void clr_C_flag(cpu*my6502);

extern void reset(cpu*my6502);
#endif