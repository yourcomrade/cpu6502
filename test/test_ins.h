//
// Created by ADMIN on 16/10/2022.
//

#ifndef CPU_TEST_INS_H
#define CPU_TEST_INS_H
#include "../inc/bus.h"

#include "../inc/memory.h"

#include "../inc/instruction.h"

#include <stdio.h>
void init(mem*my_mem,cpu*my_cpu,bus*my_bus){
    reset(my_cpu);
    insert(my_mem,0,0x80);
    insert(my_mem,0x0001,0x80);
    insert(my_mem,0x0002,0x00);
    insert(my_mem,0x0003,0x80);
    insert(my_mem,0x0004,0x00);
    insert(my_mem,0x0005,0x80);
    insert(my_mem,0x0006,0x80);
    insert(my_mem,0x0007,0x00);
    insert(my_mem,0x0008,0x95);
    insert(my_mem,0x0009,0x80);
    insert(my_mem,0x000a,0x80);
    insert(my_mem,0x000b,0x80);
    insert(my_mem,0x3415,0x2e);
    insert(my_mem,0x0080,0x12);
    insert(my_mem,0x0081,0x13);
    insert(my_mem,0x0082,0x14);
    insert(my_mem,0x0083,0x15);
    insert(my_mem,0x0084,0x16);
    insert(my_mem,0x0085,0x17);
    insert(my_mem,0x0800,0x12);
    insert(my_mem,0x8080,0x12);
    insert(my_mem,0x0093,0x34);
    insert(my_mem,0x0092,0x15);
    insert(my_mem,0x0095,0x91);
    insert(my_mem,0x1325,0x45);
    insert(my_mem,0xfffe,0x80);
    insert(my_mem,0xffff,0x00);

    my_bus->read=1;
    //connect_bus(my_mem,my_bus);
    my_bus->my6502=my_cpu;
    my_bus->my_ram=my_mem;
    my_cpu->pc=0x0000;
    my_cpu->reg_A=0x10;
    my_cpu->reg_X=0x12;
    my_cpu->reg_Y=0x13;
}
void test_ADC(bus*my_bus,cpu*my_cpu){
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nImmediate mode: ADC #$19");
    ADC(my_cpu,my_bus,imm);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nAbsolute address mode: ADC $0080");
    ADC(my_cpu,my_bus,adr);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nAbsolute address mode with Y index: ADC $0080,Y");
    ADC(my_cpu,my_bus,adr_Y);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nAbsolute address mode with X index: ADC $0080,X");
    ADC(my_cpu,my_bus,adr_X);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nZero page address mode: ADC $80");
    ADC(my_cpu,my_bus,zp);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nZero page address mode with X index: ADC $80,X");
    ADC(my_cpu,my_bus,zp_X);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nPre index address mode: ADC ($80,X)");
    ADC(my_cpu,my_bus,pre_ind_X);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nPost index address mode: ADC ($80),Y");
    ADC(my_cpu,my_bus,pos_ind_Y);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);
    del_all(my_bus->my_ram->root);
}
void test_AND(bus*my_bus,cpu*my_cpu){
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nImmediate mode: AND #$19");
    AND(my_cpu,my_bus,imm);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nAbsolute address mode: AND $0080");
    AND(my_cpu,my_bus,adr);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);


    printf("\nAbsolute address mode with Y index: AND $0080,Y");
   AND(my_cpu,my_bus,adr_Y);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);


    printf("\nAbsolute address mode with X index: AND $0080,X");
    AND(my_cpu,my_bus,adr_X);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nZero page address mode: AND $80");
    AND(my_cpu,my_bus,zp);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nZero page address mode with X index: AND $80,X");
    AND(my_cpu,my_bus,zp_X);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nPre index address mode: AND ($80,X)");
    AND(my_cpu,my_bus,pre_ind_X);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nPost index address mode: AND ($80),Y");
    AND(my_cpu,my_bus,pos_ind_Y);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);
    del_all(my_bus->my_ram->root);
}

void test_ASL(bus*my_bus,cpu*my_cpu){
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nAccumulator mode: ASL A");
    ASL(my_cpu,my_bus,acc);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nAbsolute address mode: ASL $0080");
    ASL(my_cpu,my_bus,adr);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);
    printf("\nAddress 0x0080 content: %x", fetch(my_bus));

    printf("\nAbsolute address mode with X index: ASL $0080,X");
    ASL(my_cpu,my_bus,adr_X);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);
    printf("\nAddress 0x0092 content: %x", fetch(my_bus));

    printf("\nZero page address mode: ASL $80");
    ASL(my_cpu,my_bus,zp);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);
    printf("\nAddress 0x0080 content: %x", fetch(my_bus));

    printf("\nZero page address mode with X index: ASL $80,X");
    ASL(my_cpu,my_bus,zp_X);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);
    printf("\nAddress 0x0092 content: %x", fetch(my_bus));

    del_all(my_bus->my_ram->root);
}
void test_BPL(bus*my_bus,cpu*my_cpu){
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);
    printf("\nTest BPL if it's true");
    clr_N_flag(my_cpu);

    BPL(my_cpu,my_bus,none);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nTest BPL if it's false");
    set_N_flag(my_cpu);

    BPL(my_cpu,my_bus,none);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    del_all(my_bus->my_ram->root);

}
void test_BMI(bus*my_bus,cpu*my_cpu){
    printf("\nTest BMI if it's false");
    clr_N_flag(my_cpu);

    BMI(my_cpu,my_bus,none);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nTest BPL if it's true");
    set_N_flag(my_cpu);

    BMI(my_cpu,my_bus,none);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);
    del_all(my_bus->my_ram->root);

}
void test_BRK(bus*my_bus,cpu*my_cpu){
    printf("\nTest BRK");
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nBreak");
    BRK(my_cpu,my_bus,none);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);
    del_all(my_bus->my_ram->root);

}

void test_CMP(bus*my_bus,cpu*my_cpu){
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nImmediate mode: CMP #$19");
    CMP(my_cpu,my_bus,imm);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nAbsolute address mode: CMP $0080");
    CMP(my_cpu,my_bus,adr);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nAbsolute address mode with Y index: CMP $0080,Y");
    CMP(my_cpu,my_bus,adr_Y);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nAbsolute address mode with X index: CMP $0080,X");
    CMP(my_cpu,my_bus,adr_X);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nZero page address mode: CMP $80");
    CMP(my_cpu,my_bus,zp);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nZero page address mode with X index: CMP $80,X");
    CMP(my_cpu,my_bus,zp_X);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nPre index address mode: CMP ($80,X)");
    CMP(my_cpu,my_bus,pre_ind_X);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nPost index address mode: CMP ($80),Y");
    CMP(my_cpu,my_bus,pos_ind_Y);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);
    del_all(my_bus->my_ram->root);
}

void test_CPX(bus*my_bus,cpu*my_cpu){
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nImmediate mode: CPX #$19");
    CPX(my_cpu,my_bus,imm);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nAbsolute address mode: CPX $0080");
    CPX(my_cpu,my_bus,adr);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);


    printf("\nZero page address mode: CMP $80");
    CMP(my_cpu,my_bus,zp);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    del_all(my_bus->my_ram->root);
}

void test_DEC(bus*my_bus,cpu*my_cpu){
        printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
        ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

        printf("\nContent at address 0x0080: %x", get_val(my_bus->my_ram,0x0080));
        printf("\nAbsolute address mode: DEC $0080");
        DEC(my_cpu,my_bus,adr);
        printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
        ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

        printf("\nContent at address 0x0080: %x", get_val(my_bus->my_ram,0x0080));
        printf("\nContent at address 0x0092: %x", get_val(my_bus->my_ram,0x0092));
        printf("\nAbsolute address mode with X index: CMP $0080,X");
        DEC(my_cpu,my_bus,adr_X);
        printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
        ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);
        printf("\nContent at address 0x0092: %x", get_val(my_bus->my_ram,0x0092));
        printf("\nContent at address 0x0080: %x", get_val(my_bus->my_ram,0x0080));
        printf("\nZero page address mode: DEC $80");
        DEC(my_cpu,my_bus,zp);
        printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
        ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);
        printf("\nContent at address 0x0080: %x", get_val(my_bus->my_ram,0x0080));
        printf("\nContent at address 0x0092: %x", get_val(my_bus->my_ram,0x0092));
        printf("\nZero page address mode with X index: CMP $80,X");
        DEC(my_cpu,my_bus,zp_X);
        printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
        ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);
    printf("\nContent at address 0x0092: %x", get_val(my_bus->my_ram,0x0092));

        del_all(my_bus->my_ram->root);
}
void test_EOR(bus*my_bus,cpu*my_cpu){
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nImmediate mode: EOR #$80");
    EOR(my_cpu,my_bus,imm);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nAbsolute address mode: EOR $0080");
    EOR(my_cpu,my_bus,adr);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nAbsolute address mode with Y index: EOR $0080,Y");
   EOR(my_cpu,my_bus,adr_Y);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nAbsolute address mode with X index: EOR $0080,X");
    EOR(my_cpu,my_bus,adr_X);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nZero page address mode: EOR $80");
    EOR(my_cpu,my_bus,zp);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nZero page address mode with X index: EOR $80,X");
   EOR(my_cpu,my_bus,zp_X);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nPre index address mode: EOR ($80,X)");
    EOR(my_cpu,my_bus,pre_ind_X);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nPost index address mode: EOR ($80),Y");
    EOR(my_cpu,my_bus,pos_ind_Y);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);
    del_all(my_bus->my_ram->root);
}
void test_JSR(bus*my_bus,cpu*my_cpu){
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x sp: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta,my_cpu->sp);
    printf("\n Test JSR $0080");
    JSR(my_cpu,my_bus,none);

    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x sp: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta,my_cpu->sp);



    del_all(my_bus->my_ram->root);
}
void test_LDA(bus*my_bus,cpu*my_cpu){
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nImmediate mode: LDA #$80");
    LDA(my_cpu,my_bus,imm);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nAbsolute address mode: LDA $8080");
    LDA(my_cpu,my_bus,adr);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nAbsolute address mode with Y index: LDA $0080,Y");
    LDA(my_cpu,my_bus,adr_Y);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nAbsolute address mode with X index: LDA $0080,X");
    LDA(my_cpu,my_bus,adr_X);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nZero page address mode: LDA $80");
    LDA(my_cpu,my_bus,zp);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nZero page address mode with X index: LDA $80,X");
    LDA(my_cpu,my_bus,zp_X);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nPre index address mode: LDA ($80,X)");
    LDA(my_cpu,my_bus,pre_ind_X);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);

    printf("\nPost index address mode: LDA ($80),Y");
   LDA(my_cpu,my_bus,pos_ind_Y);
    printf("\nclock: %d pc: %x A: %x X: %x Y: %x flag: %x",my_cpu->clock,my_cpu->pc\
    ,my_cpu->reg_A,my_cpu->reg_X,my_cpu->reg_Y,my_cpu->reg_sta);
    del_all(my_bus->my_ram->root);
}
#endif //CPU_TEST_INS_H
