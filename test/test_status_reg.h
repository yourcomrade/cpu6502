#ifndef test_flag_H
#define test_flag_H
#include"../inc/cpu6502.h"
#include <stdio.h>
void test_flag(cpu*my6502){
    int i=get_N_flag(my6502->reg_sta);
    printf("i = %d",i);
    clr_N_flag((my6502));
    i=get_N_flag(my6502->reg_sta);
    printf("\nClear negative flag: %d sta: %d",i,my6502->reg_sta);
    clr_V_flag((my6502));
    i=get_V_flag(my6502->reg_sta);
    printf("\nClear overflow flag: %d sta: %d",i,my6502->reg_sta);
    clr_B_flag((my6502));
    i=get_B_flag(my6502->reg_sta);
    printf("\nClear Break flag: %d sta: %d",i,my6502->reg_sta);
    clr_D_flag((my6502));
    i=get_D_flag(my6502->reg_sta);
    printf("\nClear decimal flag: %d sta: %d",i,my6502->reg_sta);
    clr_I_flag(my6502);
    i=get_I_flag(my6502->reg_sta);
    printf("\nClear interrupt flag: %d sta: %d",i,my6502->reg_sta);
    clr_Z_flag(my6502);
    i=get_Z_flag(my6502->reg_sta);
    printf("\nClear zero flag: %d sta: %d",i,my6502->reg_sta);
    clr_C_flag(my6502);
    i=get_C_flag(my6502->reg_sta);
    printf("\nClear carry flag: %d sta: %d",i,my6502->reg_sta);

    set_N_flag(my6502);
    i=get_N_flag(my6502->reg_sta);
    printf("\nSet negative flag: %d sta: %d",i,my6502->reg_sta);

    set_V_flag(my6502);
    i=get_V_flag(my6502->reg_sta);
    printf("\nSet overflow flag: %d sta: %d",i,my6502->reg_sta);

    set_B_flag(my6502);
    i=get_B_flag(my6502->reg_sta);
    printf("\nSet break flag: %d sta: %d",i,my6502->reg_sta);

    set_D_flag(my6502);
    i=get_D_flag(my6502->reg_sta);
    printf("\nSet decimal flag: %d sta: %d",i,my6502->reg_sta);

    set_I_flag(my6502);
    i=get_I_flag(my6502->reg_sta);
    printf("\nSet interrupt flag: %d sta: %d",i,my6502->reg_sta);

    set_Z_flag(my6502);
    i=get_Z_flag(my6502->reg_sta);
    printf("\nSet zero flag: %d sta: %d",i,my6502->reg_sta);

    set_C_flag(my6502);
    i=get_C_flag(my6502->reg_sta);
    printf("\nSet carry flag: %d sta: %d",i,my6502->reg_sta);
}
#endif