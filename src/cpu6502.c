//
// Created by ADMIN on 28/10/2022.
//
#ifndef CPU6502_C
#define CPU6502_C
#include "../inc/cpu6502.h"
///Function to get Negative flag from status register
uint8_t get_N_flag(uint8_t reg_sta){

    reg_sta&=0x80;
    reg_sta>>=7;
    return reg_sta;
}
///Function to set Negative flag for status register
void set_N_flag(cpu*my6502){
    (my6502->reg_sta)|=0x80;
}
///Function to clear Negative flag for status register
void clr_N_flag(cpu*my6502){
    (my6502->reg_sta)&=0x7f;
}


///Function to get Overflow flag from status register
uint8_t get_V_flag(uint8_t reg_sta){
    reg_sta&=0x40;
    reg_sta>>=6;
    return reg_sta;
}
///Function to set Overflow flag for status register
void set_V_flag(cpu*my6502){
    (my6502->reg_sta)|=0x40;
}
///Function to clear Overflow flag for status register
void clr_V_flag(cpu*my6502){
    (my6502->reg_sta)&=0xbf;
}


///Function to get Break flag from status register
uint8_t get_B_flag(uint8_t reg_sta){
    reg_sta&=0x10;
    reg_sta>>=4;
    return reg_sta;
}
///Function to set Break flag for status register
void set_B_flag(cpu*my6502){
    (my6502->reg_sta)|=0x10;
}
///Function to clear Break flag for status register
void clr_B_flag(cpu*my6502){
    (my6502->reg_sta)&=0xef;
}


///Function to get Decimal flag from status register
uint8_t get_D_flag(uint8_t reg_sta){
    reg_sta&=0x08;
    reg_sta>>=3;
    return reg_sta;
}
///Function to set Decimal flag for status register
void set_D_flag(cpu*my6502){
    (my6502->reg_sta)|=0x08;
}
///Function to clear Decimalflag for status register
void clr_D_flag(cpu*my6502){
    (my6502->reg_sta)&=0xf7;
}


/// Function to get Interupt flag from status register
uint8_t get_I_flag(uint8_t reg_sta){
    reg_sta&=0x04;
    reg_sta>>=2;
    return reg_sta;
}
///Function to set Interrupt flag for status register
void set_I_flag(cpu*my6502){
    (my6502->reg_sta)|=0x04;
}
///Function to clear Interrupt flag for status register
void clr_I_flag(cpu*my6502){
    (my6502->reg_sta)&=0xfb;
}


///Function to get Zero flag from status register
 uint8_t get_Z_flag(uint8_t reg_sta){
    reg_sta&=0x02;
    reg_sta>>=1;
    return reg_sta;
}
///Function to set Zero flag for status register
void set_Z_flag(cpu*my6502){
    (my6502->reg_sta)|=0x02;
}
///Function to clear Zero flag for status register
void clr_Z_flag(cpu*my6502){
    (my6502->reg_sta)&=0xfd;
}


///Function to get Carry flag from status register
 uint8_t get_C_flag(uint8_t reg_sta){
    reg_sta&=0x01;
    return reg_sta;
}
///Function to set Carry flag for status register
void set_C_flag(cpu*my6502){
    (my6502->reg_sta)|=0x01;
}
///Function to clear Carry flag for status register
void clr_C_flag(cpu*my6502){
    (my6502->reg_sta)&=0xfe;
}
void reset(cpu*my6502){
    my6502->clock=7;
    my6502->pc=0xfffc;///Start to read indirect address store in 0xfffc-0xfffd
    my6502->reg_A=0;
    my6502->reg_sta=0;
    my6502->reg_Y=0;
    my6502->reg_X=0;
    my6502->sp=0xff;
    ///Note stack pointer starts from 0x01ff-0x0100
}
#endif