#ifndef INS_C
#define INS_C
#include "../inc/instruction.h"
#include <stdint.h>
/// @brief Function for setting flag register for 6502
/// @param my6502 
/// @param my_bus 
/// @param result

void set_flag(cpu*my6502,bus*my_bus,uint16_t result){
 /// Check for the Zero flag
            if((result&0x00ff)==0){
                ///It only check for the 8-bits result, doesn't care about carry bit or not
                set_Z_flag(my6502);
            }
            else{
                clr_Z_flag(my6502);
            }
            /// Check for Carry flag
            if(((result&0x0f00)>>8)>0){
                set_C_flag(my6502);
            } 
            else{
                clr_C_flag(my6502);
            }
            /// Check for Negative flag
            if(((result&0x0080)>>7)>0){
                /// It only cares about the 7th bits of results if 7th bit is 1 then this flag is set
                set_N_flag(my6502);
            }else{
                clr_N_flag(my6502);
            }
            // Check for Overflow flag

            if((((result^(my6502->reg_A))&(result^(my_bus->data)))&0x0080)>0){
                /// This flag is little tricky to deal with
                ///  Basically if we have positive+positive=negative 
                /// or negative+negative=positive, this flag will be set
                /// negative is checked by examing 7th bit of result and 2 components
                set_V_flag(my6502);
            }else{
                clr_V_flag(my6502);
            }
}

/// @brief Add with carry instruction in 6502
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
extern int ADC(cpu*my6502,bus*my_bus,mode cpu_mode){
    ///This instruction can affect 4 flags: Negative, Overflow, Carry and Zero
    ///This instruction always stores results in register A (accumulator)
    ///First we need to check if the mode is binary or not
    int i=get_D_flag(my6502->reg_sta);
    if(i==0){
        ///if it's the binary mode
        /// Now we have to consider which address mode it is
        switch (cpu_mode)
        {
            ///Immediate mode: just add number directly to register A
        case imm:{
            (my6502->pc)++;
            write(my_bus,my6502->pc,0,1);

           uint16_t result=(my6502->reg_A)+ fetch(my_bus)+ get_C_flag(my6502->reg_sta);
            set_flag(my6502,my_bus,result);
            my6502->reg_A=result;
            my6502->clock+=2;

            break;
        }
        /// Absolute address mode
        case adr:{
            (my6502->pc)++;
            write(my_bus,(my6502->pc),0,1);///Read the next address
            uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
            (my6502->pc)++;
            write(my_bus,(my6502->pc),0,1);///Read the next address
            uint16_t addr_hi= fetch(my_bus);///Take the high address
            uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low);///Combine address
            write(my_bus,addr,0,1);///Tell the memory to get content of that address
            uint16_t result=fetch(my_bus)+ get_C_flag(my6502->reg_sta)+(my6502->reg_A);
            set_flag(my6502,my_bus,result);
            my6502->reg_A=result;
            my6502->clock+=4;
            break;
        }
        case adr_Y:///Absolute address mode with Y index
        {
            (my6502->pc)++;
            write(my_bus,(my6502->pc),0,1);///Read the next address
            uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
            (my6502->pc)++;
            write(my_bus,(my6502->pc),0,1);///Read the next address
            uint16_t addr_hi= fetch(my_bus);///Take the high address
            uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_Y);///Combine address
            write(my_bus,addr,0,1);///Read data from address
            uint16_t result=fetch(my_bus)+ get_C_flag(my6502->reg_sta)+(my6502->reg_A);
            set_flag(my6502,my_bus,result);
            my6502->reg_A=result;
            if(addr>0x00FF){
                ///If the address is crossing Zero page
                my6502->clock+=5;
            }
            else{
                my6502->clock+=4;
            }
            break;
        }
        case adr_X:///Absolute Address mode with X index
        {
            (my6502->pc)++;
            write(my_bus,(my6502->pc),0,1);///Read the next address
            uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
            (my6502->pc)++;
            write(my_bus,(my6502->pc),0,1);///Read the next address
           uint16_t addr_hi= fetch(my_bus);///Take the high address
            uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_X);///Combine address
            write(my_bus,addr,0,1);///Read data from address
            uint16_t result=fetch(my_bus)+ get_C_flag(my6502->reg_sta)+(my6502->reg_A);
            set_flag(my6502,my_bus,result);
            my6502->reg_A=result;
            if(addr>0x00FF){
                ///If the address is crossing Zero page
                my6502->clock+=5;
            }
            else{
                my6502->clock+=4;
            }
            break;
        }
        case zp: ///Zero page address mode
        {
            (my6502->pc)++;
            write(my_bus,(my6502->pc),0,1);///Read the next address
            uint16_t addr= fetch(my_bus);
            write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
            uint16_t result= fetch(my_bus)+ get_C_flag(my6502->reg_sta)+(my6502->reg_A);
            set_flag(my6502,my_bus,result);
            my6502->reg_A=result;
            my6502->clock+=3;
            break;
        }
        case zp_X:///Zero page with X index
        {
            (my6502->pc)++;
            write(my_bus,(my6502->pc),0,1);///Read the next address
            uint16_t addr= fetch(my_bus)+(my6502->reg_X);
            write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
            uint16_t result= fetch(my_bus)+ get_C_flag(my6502->reg_sta)+(my6502->reg_A);
            set_flag(my6502,my_bus,result);
            my6502->reg_A=result;
            my6502->clock+=4;
            break;
        }
        case pre_ind_X:/// Indirect address mode with X index
        {
            ///This address mode has syntax as: ADC ($80,X)
            ///For ex: X=0x01, then the ADC will first find
            ///adress stored at 0x0081 and 0x0082
            ///Then it will take the content of that new found address
            ///Note this address is Little Endian and the value must be Zero page
            ///For ex: ADC ($0800,X) is invalid
            (my6502->pc)++;
            write(my_bus,(my6502->pc),0,1);
            uint16_t ind_addr_low= fetch(my_bus)+(my6502->reg_X);
            write(my_bus,ind_addr_low,0,1);
            uint16_t addr_low= fetch(my_bus);
            uint16_t ind_addr_hi= ind_addr_low+1;
            write(my_bus,ind_addr_hi,0,1);
            uint16_t addr_hi= fetch(my_bus);

            uint16_t addr=(addr_hi<<8)|(addr_low);
            write(my_bus,addr,0,1);
            uint16_t result= fetch(my_bus)+my6502->reg_A+ get_C_flag(my6502->reg_sta);
            set_flag(my6502,my_bus,result);
            my6502->reg_A=result;
            my6502->clock+=6;
            break;
        }
        case pos_ind_Y:{///Post indirect address mode with Y index
            ///Syntax: ADC ($80),Y if Y=0x02
            ///First it will find address at 0x0080 and 0x0081
            ///If they are 0x12 and 0x13 then new indirect address
            ///will be 0x1312+0x02=0x1314 and it will take value at address 0x1314
            (my6502->pc)++;
            write(my_bus,my6502->pc,0,1);
            uint16_t ind_ind_addr= fetch(my_bus);///Indirect of indirect address
            write(my_bus,ind_ind_addr,0,1);
            uint16_t ind_addr_low= fetch(my_bus);
            write(my_bus,ind_ind_addr+1,0,1);
            uint16_t ind_addr_hi= fetch(my_bus);
            uint16_t addr=(ind_addr_hi<<8)|(ind_addr_low)+my6502->reg_Y;
            write(my_bus,addr,0,1);
            uint16_t result= fetch(my_bus)+my6502->reg_A+ get_C_flag(my6502->reg_sta);
            set_flag(my6502,my_bus,result);
            my6502->reg_A=result;
            if(addr>0x00ff){
                ///If address crossed the Zero page
                my6502->clock+=6;
            }
            else{
                my6502->clock+=5;
            }
            break;
        }
        default:
            break;
        }
    }
    return 0;
}
/// @brief AND instruction
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 0
int AND(cpu*my6502,bus*my_bus,mode cpu_mode){
    ///Check for BCD mode
    ///This instruction can affect 4 flags: Negative, Overflow, Carry and Zero
    ///This instruction always stores results in register A (accumulator)
    ///First we need to check if the mode is binary or not
    int i=get_D_flag(my6502->reg_sta);
    if(i==0){
        ///if it's the binary mode
        /// Now we have to consider which address mode it is
        switch (cpu_mode)
        {
            ///Immediate mode: just add number directly to register A
            case imm:{
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);

                uint16_t result=(my6502->reg_A)& fetch(my_bus);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=2;

                break;
            }
                /// Absolute address mode
            case adr:{
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low);///Combine address
                write(my_bus,addr,0,1);///Tell the memory to get content of that address
                uint16_t result=fetch(my_bus)&(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=4;
                break;
            }
            case adr_Y:///Absolute address mode with Y index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_Y);///Combine address
                write(my_bus,addr,0,1);///Read data from address
                uint16_t result=fetch(my_bus)&(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                if(addr>0x00FF){
                    ///If the address is crossing Zero page
                    my6502->clock+=5;
                }
                else{
                    my6502->clock+=4;
                }
                break;
            }
            case adr_X:///Absolute Address mode with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_X);///Combine address
                write(my_bus,addr,0,1);///Read data from address
                uint16_t result=fetch(my_bus)&(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                if(addr>0x00FF){
                    ///If the address is crossing Zero page
                    my6502->clock+=5;
                }
                else{
                    my6502->clock+=4;
                }
                break;
            }
            case zp: ///Zero page address mode
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                uint16_t result= fetch(my_bus)&(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=3;
                break;
            }
            case zp_X:///Zero page with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus)+(my6502->reg_X);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                uint16_t result= fetch(my_bus)&(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=4;
                break;
            }
            case pre_ind_X:/// Indirect address mode with X index
            {
                ///This address mode has syntax as: ADC ($80,X)
                ///For ex: X=0x01, then the ADC will first find
                ///adress stored at 0x0081 and 0x0082
                ///Then it will take the content of that new found address
                ///Note this address is Little Endian and the value must be Zero page
                ///For ex: ADC ($0800,X) is invalid
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);
                uint16_t ind_addr_low= fetch(my_bus)+(my6502->reg_X);
                write(my_bus,ind_addr_low,0,1);
                uint16_t addr_low= fetch(my_bus);
                uint16_t ind_addr_hi= ind_addr_low+1;
                write(my_bus,ind_addr_hi,0,1);
                uint16_t addr_hi= fetch(my_bus);

                uint16_t addr=(addr_hi<<8)|(addr_low);
                write(my_bus,addr,0,1);
                uint16_t result= fetch(my_bus)&(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=6;
                break;
            }
            case pos_ind_Y:{///Post indirect address mode with Y index
                ///Syntax: ADC ($80),Y if Y=0x02
                ///First it will find address at 0x0080 and 0x0081
                ///If they are 0x12 and 0x13 then new indirect address
                ///will be 0x1312+0x02=0x1314 and it will take value at address 0x1314
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t ind_ind_addr= fetch(my_bus);///Indirect of indirect address
                write(my_bus,ind_ind_addr,0,1);
                uint16_t ind_addr_low= fetch(my_bus);
                write(my_bus,ind_ind_addr+1,0,1);
                uint16_t ind_addr_hi= fetch(my_bus);
                uint16_t addr=(ind_addr_hi<<8)|(ind_addr_low)+my6502->reg_Y;
                write(my_bus,addr,0,1);
                uint16_t result= fetch(my_bus)&(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                if(addr>0x00ff){
                    ///If address crossed the Zero page
                    my6502->clock+=6;
                }
                else{
                    my6502->clock+=5;
                }
                break;
            }
            default:
                break;
        }
    }
    return 0;
}
int ASL(cpu*my6502,bus*my_bus,mode cpu_mode){
    ///Check for BCD mode
    if(get_D_flag(my6502->reg_sta)==0){
        switch (cpu_mode) {
            case acc:///Accumulator mode which is the mode the result is stored directly into register A
            {
                my6502->reg_A=(my6502->reg_A)<<1;
                set_flag(my6502,my_bus,my6502->reg_A);
                my6502->clock+=2;
                break;}
            case zp:///Zero page address mode, the result is stored in that address
            {
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,0,1);
                char result= fetch(my_bus)<<1;
                uint8_t temp=my6502->reg_A;
                ///We need to temporary store result into A register
                ///to avoid changing Overflow flag which this instruction
                ///never changes this flag
                my6502->reg_A=result;
                set_flag(my6502,my_bus,result);
                my6502->reg_A=temp;
                write(my_bus,addr,result,0);
                my6502->clock+=5;
                break;

            }
            case zp_X:///Zero page address mode with X index
            {
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr= fetch(my_bus)+my6502->reg_X;
                write(my_bus,addr,0,1);
                char result= fetch(my_bus)<<1;
                uint8_t temp=my6502->reg_A;
                ///We need to temporary store result into A register
                ///to avoid changing Overflow flag which this instruction
                ///never changes this flag
                my6502->reg_A=result;
                set_flag(my6502,my_bus,result);
                my6502->reg_A=temp;
                write(my_bus,addr,result,0);
                my6502->clock+=6;
                break;
            }
            case adr:///Absolute address mode
            {
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr_low= fetch(my_bus);
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr_hi= fetch(my_bus);
                uint16_t addr=(addr_hi<<8)|addr_low;
                write(my_bus,addr,0,1);
                char result= fetch(my_bus)<<1;
                uint8_t temp=my6502->reg_A;
                my6502->reg_A=result;
                set_flag(my6502,my_bus,result);
                my6502->reg_A=temp;
                write(my_bus,addr,result,0);
                my6502->clock+=6;
                break;
            }
            case adr_X:///Absolute address mode with X index
            {
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr_low= fetch(my_bus);
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr_hi= fetch(my_bus);
                uint16_t addr=(addr_hi<<8)|addr_low+my6502->reg_X;
                write(my_bus,addr,0,1);
                char result= fetch(my_bus)<<1;
                uint8_t temp=my6502->reg_A;
                my6502->reg_A=result;
                set_flag(my6502,my_bus,result);
                my6502->reg_A=temp;
                write(my_bus,addr,result,0);
                my6502->clock+=7;
                break;
            }
            default:
                break;

        }
    }
    return 0;
}
/// @brief Branch if plus, it will check the Negative flag N, if N=0, then it will branch
/// it works by formular: pc=pc+2+rr 
/// pc: current address of instruction stored in program counter (pc)
/// rr: a 8-bits hexadecimal value
/// if N=1 then rr=0
/// else we need to check for rr to see if it's a negative number i.e: 0b1xxxxxxx or positive i.e: 0b0xxxxxxx
/// for label which position is before this instruction, rr is negative number
/// for label which position is after this instruction, rr is positive number
/// This also means that if label is too far then assembler will raise error
/// @warning Branch out of range
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int BPL(cpu*my6502,bus*my_bus,mode cpu_mode){
    if(get_N_flag(my6502->reg_sta)==0){
        (my6502->pc)++;
        write(my_bus,my6502->pc,0,1);
        uint8_t ind_addr= fetch(my_bus);
        if((ind_addr&0x80)>0){
            ///This mean the label's position is before this instruction because it's a negative number
            my6502->pc=(my6502->pc)-ind_addr;
        }
        else{
            ///This means the label's position is after this instruction beacause it's a positive number
            my6502->pc+=ind_addr;
        }
        my6502->clock+=2;
    }
    else{
        my6502->pc+=2;
    }
    return 0;

}
/// @brief Brach if minus, if Negative flag N=1, then it will branch
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int BMI(cpu*my6502,bus*my_bus,mode cpu_mode){
    if(get_N_flag(my6502->reg_sta)==1){
        (my6502->pc)++;
        write(my_bus,my6502->pc,0,1);
        uint8_t ind_addr= fetch(my_bus);
        if((ind_addr&0x80)>0){
            ///This mean the label's position is before this instruction because it's a negative number
            my6502->pc=(my6502->pc)-ind_addr;
        }
        else{
            ///This means the label's position is after this instruction beacause it's a positive number
            my6502->pc+=ind_addr;
        }
        my6502->clock+=2;
    }
    else{
        my6502->pc+=2;
    }
    return 0;

}
int BIT(cpu*my6502,bus*my_bus,mode cpu_mode){
    ///Check for BCD mode
    if(get_D_flag(my6502->reg_sta)==0){
        switch (cpu_mode) {
            case zp:
            {
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,0,1);
                uint8_t val= fetch(my_bus);
                uint8_t res=(my6502->reg_A)&val;
                if(get_N_flag(res)>0){
                    ///If the result is negative
                    set_N_flag(my6502);
                }
                else{
                    clr_N_flag(my6502);
                }
                if(get_V_flag(res)){
                    ///If it's overflow
                    set_V_flag(my6502);
                }
                else{
                    clr_V_flag(my6502);
                }
                break;
            }
            case adr:///Absolute address mode
            {

                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr_low= fetch(my_bus);
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr_hi= fetch(my_bus);
                uint16_t addr=(addr_hi<<8)|addr_low;
                write(my_bus,addr,0,1);
                char val= fetch(my_bus);
                uint8_t res=(my6502->reg_A)&val;
                if(get_N_flag(res)>0){
                    ///If the result is negative
                    set_N_flag(my6502);
                }
                else{
                    clr_N_flag(my6502);
                }
                if(get_V_flag(res)){
                    ///If it's overflow
                    set_V_flag(my6502);
                }
                else{
                    clr_V_flag(my6502);
                }
                break;
            }
            default:
                break;
        }
    }
    return 0;
}
/// @brief Break instruction: mostly to create software interrupt
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int BRK(cpu*my6502,bus*my_bus,mode cpu_mode){
    my6502->pc+=2;///Increase program counter by 2
    set_B_flag(my6502);///Set break flag
    my6502->sp++;
    uint8_t addr_hi=(my6502->pc)&(0xff00)>>8;
    ///Push program counter's address to the stack
    write(my_bus,my6502->sp,addr_hi,0);
    my6502->sp++;
    uint8_t addr_low=(my6502->pc)&(0x00ff);
    write(my_bus,my6502->sp,addr_low,0);
    ///Push status register to the stack
    my6502->sp++;
    write(my_bus,my6502->sp,my6502->reg_sta,0);
    ///Start to fetch content to program counter from address 0xfffe(L)-0xffff(H)
    write(my_bus,0xfffe,0,1);
    uint16_t new_addr_low= fetch(my_bus);
    write(my_bus,0xffff,0,1);
    uint16_t new_addr_hi= fetch(my_bus);
    my6502->pc=(new_addr_hi<<8)|new_addr_low;
    my6502->clock+=7;
    return 0;
}
/// @brief Branch if Overflow clear, branch if V=0
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int BVC(cpu*my6502,bus*my_bus,mode cpu_mode){
    if(get_V_flag(my6502->reg_sta)==0){
        (my6502->pc)++;
        write(my_bus,my6502->pc,0,1);
        uint8_t ind_addr= fetch(my_bus);
        if((ind_addr&0x80)>0){
            ///This mean the label's position is before this instruction because it's a negative number
            my6502->pc=(my6502->pc)-ind_addr;
        }
        else{
            ///This means the label's position is after this instruction beacause it's a positive number
            my6502->pc+=ind_addr;
        }
        my6502->clock+=2;
    }
    else{
        my6502->pc+=2;
    }
    return 0;
}
/// @brief Branch if Overflow set, if V=1
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int BVS(cpu*my6502,bus*my_bus,mode cpu_mode){
    if(get_V_flag(my6502->reg_sta)==1){
        (my6502->pc)++;
        write(my_bus,my6502->pc,0,1);
        uint8_t ind_addr= fetch(my_bus);
        if((ind_addr&0x80)>0){
            ///This mean the label's position is before this instruction because it's a negative number
            my6502->pc=(my6502->pc)-ind_addr;
        }
        else{
            ///This means the label's position is after this instruction beacause it's a positive number
            my6502->pc+=ind_addr;
        }
        my6502->clock+=2;
    }
    else{
        my6502->pc+=2;
    }
    return 0;
}
/// @brief Branch if Carry clear, branch if C=0
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int BCC(cpu*my6502,bus*my_bus,mode cpu_mode){
    if(get_C_flag(my6502->reg_sta)==0){
        (my6502->pc)++;
        write(my_bus,my6502->pc,0,1);
        uint8_t ind_addr= fetch(my_bus);
        if((ind_addr&0x80)>0){
            ///This mean the label's position is before this instruction because it's a negative number
            my6502->pc=(my6502->pc)-ind_addr;
        }
        else{
            ///This means the label's position is after this instruction beacause it's a positive number
            my6502->pc+=ind_addr;
        }
        my6502->clock+=2;
    }
    else{
        my6502->pc+=2;
    }
    return 0;
}
/// @brief Branch if Carry set, branch if C=1
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int BCS(cpu*my6502,bus*my_bus,mode cpu_mode){
    if(get_C_flag(my6502->reg_sta)==1){
        (my6502->pc)++;
        write(my_bus,my6502->pc,0,1);
        uint8_t ind_addr= fetch(my_bus);
        if((ind_addr&0x80)>0){
            ///This mean the label's position is before this instruction because it's a negative number
            my6502->pc=(my6502->pc)-ind_addr;
        }
        else{
            ///This means the label's position is after this instruction beacause it's a positive number
            my6502->pc+=ind_addr;
        }
        my6502->clock+=2;
    }
    else{
        my6502->pc+=2;
    }
    return 0;
}
/// @brief Branch if equal or Branch if Z =0
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int BEQ(cpu*my6502,bus*my_bus,mode cpu_mode){
    if(get_Z_flag(my6502->reg_sta)==0){
        (my6502->pc)++;
        write(my_bus,my6502->pc,0,1);
        uint8_t ind_addr= fetch(my_bus);
        if((ind_addr&0x80)>0){
            ///This mean the label's position is before this instruction because it's a negative number
            my6502->pc=(my6502->pc)-ind_addr;
        }
        else{
            ///This means the label's position is after this instruction beacause it's a positive number
            my6502->pc+=ind_addr;
        }
        my6502->clock+=2;
    }
    else{
        my6502->pc+=2;
    }
    return 0;
}
/// @brief Branch if Not equal or Branch if Z=0
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int BNE(cpu*my6502,bus*my_bus,mode cpu_mode){
    if(get_Z_flag(my6502->reg_sta)==1){
        (my6502->pc)++;
        write(my_bus,my6502->pc,0,1);
        uint8_t ind_addr= fetch(my_bus);
        if((ind_addr&0x80)>0){
            ///This mean the label's position is before this instruction because it's a negative number
            my6502->pc=(my6502->pc)-ind_addr;
        }
        else{
            ///This means the label's position is after this instruction beacause it's a positive number
            my6502->pc+=ind_addr;
        }
        my6502->clock+=2;
    }
    else{
        my6502->pc+=2;
    }
    return 0;
}
/// @brief Clear carry flag
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int CLC(cpu*my6502,bus*my_bus,mode cpu_mode){
    clr_C_flag(my6502);
    return 0;
}
/// @brief Clear decimal flag
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int CLD(cpu*my6502,bus*my_bus,mode cpu_mode){
    clr_D_flag(my6502);
    return 0;
}
/// @brief Clear overflow flag
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int CLV(cpu*my6502,bus*my_bus,mode cpu_mode){
    clr_V_flag(my6502);
    return 0;
}
/// @brief Clear Interrupt flag or Enable interrupt
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int CLI(cpu*my6502,bus*my_bus,mode cpu_mode){
    clr_I_flag(my6502);
    return 0;
}
/// @brief Compare memory with accumulator, Note it only affect status register
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int CMP(cpu*my6502,bus*my_bus,mode cpu_mode){
    int i=get_D_flag(my6502->reg_sta);
    if(i==0){
        ///if it's the binary mode
        /// Now we have to consider which address mode it is
        switch (cpu_mode)
        {
            ///Immediate mode: just add number directly to register A
        case imm:{
            (my6502->pc)++;
            write(my_bus,my6502->pc,0,1);
            uint8_t temp=my6502->reg_A;
           uint16_t result=(my6502->reg_A)- fetch(my_bus);
            my6502->reg_A=result;///Trick to avoid set Overflow flag
            set_flag(my6502,my_bus,result);
           my6502->reg_A=temp;
            my6502->clock+=2;

            break;
        }
        /// Absolute address mode
        case adr:{
            (my6502->pc)++;
            write(my_bus,(my6502->pc),0,1);///Read the next address
            uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
            (my6502->pc)++;
            write(my_bus,(my6502->pc),0,1);///Read the next address
            uint16_t addr_hi= fetch(my_bus);///Take the high address
            uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low);///Combine address
            write(my_bus,addr,0,1);///Tell the memory to get content of that address
            uint16_t result=(my6502->reg_A)-fetch(my_bus);
            uint8_t temp=my6502->reg_A;
            my6502->reg_A=result;
            set_flag(my6502,my_bus,result);
            my6502->reg_A=temp;

            my6502->clock+=4;
            break;
        }
        case adr_Y:///Absolute address mode with Y index
        {
            (my6502->pc)++;
            write(my_bus,(my6502->pc),0,1);///Read the next address
            uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
            (my6502->pc)++;
            write(my_bus,(my6502->pc),0,1);///Read the next address
            uint16_t addr_hi= fetch(my_bus);///Take the high address
            uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_Y);///Combine address
            write(my_bus,addr,0,1);///Read data from address
            uint16_t result=(my6502->reg_A)-fetch(my_bus);
            uint8_t temp=my6502->reg_A;
            my6502->reg_A=result;
            set_flag(my6502,my_bus,result);
            my6502->reg_A=temp;
            if(addr>0x00FF){
                ///If the address is crossing Zero page
                my6502->clock+=5;
            }
            else{
                my6502->clock+=4;
            }
            break;
        }
        case adr_X:///Absolute Address mode with X index
        {
            (my6502->pc)++;
            write(my_bus,(my6502->pc),0,1);///Read the next address
            uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
            (my6502->pc)++;
            write(my_bus,(my6502->pc),0,1);///Read the next address
           uint16_t addr_hi= fetch(my_bus);///Take the high address
            uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_X);///Combine address
            write(my_bus,addr,0,1);///Read data from address
            uint16_t result=(my6502->reg_A)-fetch(my_bus);
            uint8_t temp=my6502->reg_A;
            my6502->reg_A=result;
            set_flag(my6502,my_bus,result);
            my6502->reg_A=temp;
            if(addr>0x00FF){
                ///If the address is crossing Zero page
                my6502->clock+=5;
            }
            else{
                my6502->clock+=4;
            }
            break;
        }
        case zp: ///Zero page address mode
        {
            (my6502->pc)++;
            write(my_bus,(my6502->pc),0,1);///Read the next address
            uint16_t addr= fetch(my_bus);
            write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
            uint16_t result= (my6502->reg_A)-fetch(my_bus);
            uint8_t temp=my6502->reg_A;
            my6502->reg_A=result;
            set_flag(my6502,my_bus,result);
            my6502->reg_A=temp;
            my6502->clock+=3;
            break;
        }
        case zp_X:///Zero page with X index
        {
            (my6502->pc)++;
            write(my_bus,(my6502->pc),0,1);///Read the next address
            uint16_t addr= fetch(my_bus)+(my6502->reg_X);
            write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
            uint16_t result= (my6502->reg_A)-fetch(my_bus);
            uint8_t temp=my6502->reg_A;
            my6502->reg_A=result;
            set_flag(my6502,my_bus,result);
           my6502->reg_A=temp;
            my6502->clock+=4;
            break;
        }
        case pre_ind_X:/// Indirect address mode with X index
        {
            ///This address mode has syntax as: ADC ($80,X)
            ///For ex: X=0x01, then the ADC will first find
            ///adress stored at 0x0081 and 0x0082
            ///Then it will take the content of that new found address
            ///Note this address is Little Endian and the value must be Zero page
            ///For ex: ADC ($0800,X) is invalid
            (my6502->pc)++;
            write(my_bus,(my6502->pc),0,1);
            uint16_t ind_addr_low= fetch(my_bus)+(my6502->reg_X);
            write(my_bus,ind_addr_low,0,1);
            uint16_t addr_low= fetch(my_bus);
            uint16_t ind_addr_hi= ind_addr_low+1;
            write(my_bus,ind_addr_hi,0,1);
            uint16_t addr_hi= fetch(my_bus);

            uint16_t addr=(addr_hi<<8)|(addr_low);
            write(my_bus,addr,0,1);
            uint16_t result= (my6502->reg_A)-fetch(my_bus);
            uint8_t temp=my6502->reg_A;
            my6502->reg_A=result;
            set_flag(my6502,my_bus,result);
            my6502->reg_A=temp;
            my6502->clock+=6;
            break;
        }
        case pos_ind_Y:{///Post indirect address mode with Y index
            ///Syntax: ADC ($80),Y if Y=0x02
            ///First it will find address at 0x0080 and 0x0081
            ///If they are 0x12 and 0x13 then new indirect address
            ///will be 0x1312+0x02=0x1314 and it will take value at address 0x1314
            (my6502->pc)++;
            write(my_bus,my6502->pc,0,1);
            uint16_t ind_ind_addr= fetch(my_bus);///Indirect of indirect address
            write(my_bus,ind_ind_addr,0,1);
            uint16_t ind_addr_low= fetch(my_bus);
            write(my_bus,ind_ind_addr+1,0,1);
            uint16_t ind_addr_hi= fetch(my_bus);
            uint16_t addr=(ind_addr_hi<<8)|(ind_addr_low)+my6502->reg_Y;
            write(my_bus,addr,0,1);
            uint16_t result= my6502->reg_A-fetch(my_bus);
            uint8_t temp=my6502->reg_A;
            my6502->reg_A=result;
            set_flag(my6502,my_bus,result);
            my6502->reg_A=temp;
            if(addr>0x00ff){
                ///If address crossed the Zero page
                my6502->clock+=6;
            }
            else{
                my6502->clock+=5;
            }
            break;
        }
        default:
            break;
        }
    }
    return 0;
}
/// @brief Compare memory and index X
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int CPX(cpu*my6502,bus*my_bus,mode cpu_mode){
    if(get_D_flag(my6502->reg_sta)==0){
        switch (cpu_mode) {
            case imm:{
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint8_t temp=my6502->reg_X;
                uint16_t result=(my6502->reg_X)- fetch(my_bus);
                my6502->reg_X=result;///Trick to avoid set Overflow flag
                set_flag(my6502,my_bus,result);
                my6502->reg_X=temp;
                my6502->clock+=2;
                break;
            }
            case zp:{
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                uint16_t result= (my6502->reg_X)-fetch(my_bus);
                uint8_t temp=my6502->reg_X;
                my6502->reg_X=result;
                set_flag(my6502,my_bus,result);
                my6502->reg_X=temp;
                my6502->clock+=3;
                break;
            }
            case adr:{
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low);///Combine address
                write(my_bus,addr,0,1);///Tell the memory to get content of that address
                uint16_t result=(my6502->reg_X)-fetch(my_bus);
                uint8_t temp=my6502->reg_X;
                my6502->reg_X=result;
                set_flag(my6502,my_bus,result);
                my6502->reg_X=temp;
                my6502->clock+=4;
                break;
            }
            default:
                break;
        }
    }
    return 0;
}
/// @brief Compare memory and Y index
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int CPY(cpu*my6502,bus*my_bus,mode cpu_mode){
    if(get_D_flag(my6502->reg_sta)==0){
        switch (cpu_mode) {
            case imm:{
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint8_t temp=my6502->reg_Y;
                uint16_t result=(my6502->reg_Y)- fetch(my_bus);
                my6502->reg_Y=result;///Trick to avoid set Overflow flag
                set_flag(my6502,my_bus,result);
                my6502->reg_Y=temp;
                my6502->clock+=2;
                break;
            }
            case zp:{
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                uint16_t result= (my6502->reg_Y)-fetch(my_bus);
                uint8_t temp=my6502->reg_Y;
                my6502->reg_Y=result;
                set_flag(my6502,my_bus,result);
                my6502->reg_Y=temp;
                my6502->clock+=3;
                break;
            }
            case adr:{
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low);///Combine address
                write(my_bus,addr,0,1);///Tell the memory to get content of that address
                uint16_t result=(my6502->reg_Y)-fetch(my_bus);
                uint8_t temp=my6502->reg_Y;
                my6502->reg_Y=result;
                set_flag(my6502,my_bus,result);
                my6502->reg_Y=temp;
                my6502->clock+=4;
                break;
            }
            default:
                break;
        }
    }
    return 0;
}
/// @brief Decrement the value content of memory
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int DEC(cpu*my6502,bus*my_bus,mode cpu_mode){
    int i=get_D_flag(my6502->reg_sta);
    if(i==0){
        ///if it's the binary mode
        /// Now we have to consider which address mode it is
        switch (cpu_mode)
        {

                /// Absolute address mode
            case adr:{
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low);///Combine address
                write(my_bus,addr,0,1);///Tell the memory to get content of that address
                uint8_t res= fetch(my_bus)-1;
                if((res&0x80)>0){
                    ///Check for negative
                    set_N_flag(my6502);
                }
                else{
                    clr_N_flag(my6502);
                }
                if(res==0){
                    set_Z_flag(my6502);
                }
                else{
                    clr_Z_flag(my6502);
                }
                write(my_bus,addr,res,0);
                my6502->clock+=6;
                break;
            }
            case adr_X:///Absolute Address mode with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_X);///Combine address
                write(my_bus,addr,0,1);///Read data from address
                uint8_t res= fetch(my_bus)-1;
                if((res&0x80)>0){
                    ///Check for negative
                    set_N_flag(my6502);
                }
                else{
                    clr_N_flag(my6502);
                }
                if(res==0){
                    set_Z_flag(my6502);
                }
                else{
                    clr_Z_flag(my6502);
                }
                write(my_bus,addr,res,0);
               my6502->clock+=7;
                break;
            }
            case zp: ///Zero page address mode
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                uint8_t res= fetch(my_bus)-1;
                if((res&0x80)>0){
                    ///Check for negative
                    set_N_flag(my6502);
                }
                else{
                    clr_N_flag(my6502);
                }
                if(res==0){
                    set_Z_flag(my6502);
                }
                else{
                    clr_Z_flag(my6502);
                }
                write(my_bus,addr,res,0);
                my6502->clock+=5;
                break;
            }
            case zp_X:///Zero page with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus)+(my6502->reg_X);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                uint8_t res= fetch(my_bus)-1;
                if((res&0x80)>0){
                    ///Check for negative
                    set_N_flag(my6502);
                }
                else{
                    clr_N_flag(my6502);
                }
                if(res==0){
                    set_Z_flag(my6502);
                }
                else{
                    clr_Z_flag(my6502);
                }
                write(my_bus,addr,res,0);
                my6502->clock+=6;
                break;
            }

            default:
                break;
        }
    }
    return 0;
}
/// @brief Decrement index X by 1
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int DEX(cpu*my6502,bus*my_bus,mode cpu_mode){
    if(get_D_flag(my6502->reg_sta)==0){
        (my6502->reg_X)--;
        my6502->clock+=2;
    }
    return 0;
}
/// @brief Decrement index Y by 1
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int DEY(cpu*my6502,bus*my_bus,mode cpu_mode){
    if(get_D_flag(my6502->reg_sta)==0){
        (my6502->reg_Y)--;
        my6502->clock+=2;
    }
    return 0;
}
/// @brief Exclusive-or Memory with Accumulator, only affect Negative and Zero flag
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int EOR(cpu*my6502,bus*my_bus,mode cpu_mode){
    int i=get_D_flag(my6502->reg_sta);
    if(i==0){
        ///if it's the binary mode
        /// Now we have to consider which address mode it is
        switch (cpu_mode)
        {
            ///Immediate mode: just add number directly to register A
            case imm:{
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);

                uint8_t result=(my6502->reg_A)^ fetch(my_bus);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=2;

                break;
            }
                /// Absolute address mode
            case adr:{
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low);///Combine address
                write(my_bus,addr,0,1);///Tell the memory to get content of that address
                uint8_t result=fetch(my_bus)^ (my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=4;
                break;
            }
            case adr_Y:///Absolute address mode with Y index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_Y);///Combine address
                write(my_bus,addr,0,1);///Read data from address
                uint8_t result=fetch(my_bus)^(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                if(addr>0x00FF){
                    ///If the address is crossing Zero page
                    my6502->clock+=5;
                }
                else{
                    my6502->clock+=4;
                }
                break;
            }
            case adr_X:///Absolute Address mode with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_X);///Combine address
                write(my_bus,addr,0,1);///Read data from address
                uint8_t result=fetch(my_bus)^(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                if(addr>0x00FF){
                    ///If the address is crossing Zero page
                    my6502->clock+=5;
                }
                else{
                    my6502->clock+=4;
                }
                break;
            }
            case zp: ///Zero page address mode
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                uint8_t result= fetch(my_bus)^(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=3;
                break;
            }
            case zp_X:///Zero page with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus)+(my6502->reg_X);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                uint8_t result= fetch(my_bus)^(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=4;
                break;
            }
            case pre_ind_X:/// Indirect address mode with X index
            {
                ///This address mode has syntax as: ADC ($80,X)
                ///For ex: X=0x01, then the ADC will first find
                ///adress stored at 0x0081 and 0x0082
                ///Then it will take the content of that new found address
                ///Note this address is Little Endian and the value must be Zero page
                ///For ex: ADC ($0800,X) is invalid
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);
                uint16_t ind_addr_low= fetch(my_bus)+(my6502->reg_X);
                write(my_bus,ind_addr_low,0,1);
                uint16_t addr_low= fetch(my_bus);
                uint16_t ind_addr_hi= ind_addr_low+1;
                write(my_bus,ind_addr_hi,0,1);
                uint16_t addr_hi= fetch(my_bus);

                uint16_t addr=(addr_hi<<8)|(addr_low);
                write(my_bus,addr,0,1);
                uint8_t result= fetch(my_bus)^(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=6;
                break;
            }
            case pos_ind_Y:{///Post indirect address mode with Y index
                ///Syntax: ADC ($80),Y if Y=0x02
                ///First it will find address at 0x0080 and 0x0081
                ///If they are 0x12 and 0x13 then new indirect address
                ///will be 0x1312+0x02=0x1314 and it will take value at address 0x1314
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t ind_ind_addr= fetch(my_bus);///Indirect of indirect address
                write(my_bus,ind_ind_addr,0,1);
                uint16_t ind_addr_low= fetch(my_bus);
                write(my_bus,ind_ind_addr+1,0,1);
                uint16_t ind_addr_hi= fetch(my_bus);
                uint16_t addr=(ind_addr_hi<<8)|(ind_addr_low)+my6502->reg_Y;
                write(my_bus,addr,0,1);
                uint8_t result= fetch(my_bus)^(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                if(addr>0x00ff){
                    ///If address crossed the Zero page
                    my6502->clock+=6;
                }
                else{
                    my6502->clock+=5;
                }
                break;
            }
            default:
                break;
        }
    }
    return 0;
}
/// @brief Increment content of memory by 1
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int INC(cpu*my6502,bus*my_bus,mode cpu_mode){
    int i=get_D_flag(my6502->reg_sta);
    if(i==0){
        ///if it's the binary mode
        /// Now we have to consider which address mode it is
        switch (cpu_mode)
        {

            /// Absolute address mode
            case adr:{
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low);///Combine address
                write(my_bus,addr,0,1);///Tell the memory to get content of that address
                uint8_t res= fetch(my_bus)+1;
                if((res&0x80)>0){
                    ///Check for negative
                    set_N_flag(my6502);
                }
                else{
                    clr_N_flag(my6502);
                }
                if(res==0){
                    set_Z_flag(my6502);
                }
                else{
                    clr_Z_flag(my6502);
                }
                write(my_bus,addr,res,0);
                my6502->clock+=6;
                break;
            }
            case adr_X:///Absolute Address mode with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_X);///Combine address
                write(my_bus,addr,0,1);///Read data from address
                uint8_t res= fetch(my_bus)+1;
                if((res&0x80)>0){
                    ///Check for negative
                    set_N_flag(my6502);
                }
                else{
                    clr_N_flag(my6502);
                }
                if(res==0){
                    set_Z_flag(my6502);
                }
                else{
                    clr_Z_flag(my6502);
                }
                write(my_bus,addr,res,0);
                my6502->clock+=7;
                break;
            }
            case zp: ///Zero page address mode
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                uint8_t res= fetch(my_bus)+1;
                if((res&0x80)>0){
                    ///Check for negative
                    set_N_flag(my6502);
                }
                else{
                    clr_N_flag(my6502);
                }
                if(res==0){
                    set_Z_flag(my6502);
                }
                else{
                    clr_Z_flag(my6502);
                }
                write(my_bus,addr,res,0);
                my6502->clock+=5;
                break;
            }
            case zp_X:///Zero page with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus)+(my6502->reg_X);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                uint8_t res= fetch(my_bus)+1;
                if((res&0x80)>0){
                    ///Check for negative
                    set_N_flag(my6502);
                }
                else{
                    clr_N_flag(my6502);
                }
                if(res==0){
                    set_Z_flag(my6502);
                }
                else{
                    clr_Z_flag(my6502);
                }
                write(my_bus,addr,res,0);
                my6502->clock+=6;
                break;
            }

            default:
                break;
        }
    }
    return 0;
}
/// @brief Increment index X by 1
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int INX(cpu*my6502,bus*my_bus,mode cpu_mode){
    if(get_D_flag(my6502->reg_sta)==0){
        (my6502->reg_X)++;
        my6502->clock+=2;
    }
    return 0;
}
/// @brief Increment index Y by 1
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int INY(cpu*my6502,bus*my_bus,mode cpu_mode){
    if(get_D_flag(my6502->reg_sta)==0){
        (my6502->reg_Y)++;
        my6502->clock+=2;
    }
    return 0;
}
/// @brief Jump instruction 
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int JMP(cpu*my6502,bus*my_bus,mode cpu_mode){
    int i=get_D_flag(my6502->reg_sta);
    if(i==0){
        ///if it's the binary mode
        /// Now we have to consider which address mode it is
        switch (cpu_mode)
        {

            /// Absolute address mode
            case adr:{
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low);///Combine address
                my6502->pc=addr;
                my6502->clock+=3;
                break;
            }
            case ind_adr:///Indirect address mode
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t ind_addr_low= fetch(my_bus);///Take the indirect low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t ind_addr_hi= fetch(my_bus);///Take the indirect high address
                uint16_t ind_addr=((uint16_t)(ind_addr_hi<<8))|(ind_addr_low);///Combine indirect address
                write(my_bus,ind_addr,0,1);
                uint16_t addr_low= fetch(my_bus);///Take the low address
                write(my_bus,ind_addr+1,0,1);
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=(addr_hi<<8)|addr_low;
                my6502->pc=addr;

                my6502->clock+=5;
                
                break;
            }
            default:
                break;
        }
    }
    return 0;
}
/// @brief Jump subroutine
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int JSR(cpu*my6502,bus*my_bus,mode cpu_mode){
    if(get_D_flag(my6502->reg_sta)==0){
        my6502->pc++;
        write(my_bus,my6502->pc,0,1);
        uint16_t addr_low= fetch(my_bus);
        my6502->pc++;
        write(my_bus,my6502->pc,0,1);
        uint16_t addr_hi= fetch(my_bus);
        uint16_t addr=(addr_hi<<8)|addr_low;
        ///Start to push current address of program counter to stack

        my6502->sp--;
        uint8_t cur_addr_hi=(my6502->pc)>>8;
        write(my_bus,my6502->sp,cur_addr_hi,0);
        my6502->sp--;
        uint8_t cur_addr_low=(my6502->pc)&0x00ff;
        write(my_bus,my6502->sp,cur_addr_low,0);
        ///Jump to new address
        my6502->pc=addr;
        my6502->clock+=6;
    }
    return 0;
}
/// @brief Load into Accumulator
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int LDA(cpu*my6502,bus*my_bus,mode cpu_mode){
    int i=get_D_flag(my6502->reg_sta);
    if(i==0){
        ///if it's the binary mode
        /// Now we have to consider which address mode it is
        switch (cpu_mode)
        {
            ///Immediate mode: just add number directly to register A
            case imm:{
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);

                my6502->reg_A= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_A);

                my6502->clock+=2;

                break;
            }
                /// Absolute address mode
            case adr:{
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low);///Combine address
                write(my_bus,addr,0,1);///Tell the memory to get content of that address
                my6502->reg_A= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_A);
                my6502->clock+=4;
                break;
            }
            case adr_Y:///Absolute address mode with Y index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_Y);///Combine address
                write(my_bus,addr,0,1);///Read data from address
                my6502->reg_A= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_A);
                if(addr>0x00FF){
                    ///If the address is crossing Zero page
                    my6502->clock+=5;
                }
                else{
                    my6502->clock+=4;
                }
                break;
            }
            case adr_X:///Absolute Address mode with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_X);///Combine address
                write(my_bus,addr,0,1);///Read data from address
                my6502->reg_A= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_A);
                if(addr>0x00FF){
                    ///If the address is crossing Zero page
                    my6502->clock+=5;
                }
                else{
                    my6502->clock+=4;
                }
                break;
            }
            case zp: ///Zero page address mode
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                my6502->reg_A= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_A);
                my6502->clock+=3;
                break;
            }
            case zp_X:///Zero page with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus)+(my6502->reg_X);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                my6502->reg_A= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_A);
                my6502->clock+=4;
                break;
            }
            case pre_ind_X:/// Indirect address mode with X index
            {
                ///This address mode has syntax as: ADC ($80,X)
                ///For ex: X=0x01, then the ADC will first find
                ///adress stored at 0x0081 and 0x0082
                ///Then it will take the content of that new found address
                ///Note this address is Little Endian and the value must be Zero page
                ///For ex: ADC ($0800,X) is invalid
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);
                uint16_t ind_addr_low= fetch(my_bus)+(my6502->reg_X);
                write(my_bus,ind_addr_low,0,1);
                uint16_t addr_low= fetch(my_bus);
                uint16_t ind_addr_hi= ind_addr_low+1;
                write(my_bus,ind_addr_hi,0,1);
                uint16_t addr_hi= fetch(my_bus);

                uint16_t addr=(addr_hi<<8)|(addr_low);
                write(my_bus,addr,0,1);
                my6502->reg_A= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_A);
                my6502->clock+=6;
                break;
            }
            case pos_ind_Y:{///Post indirect address mode with Y index
                ///Syntax: ADC ($80),Y if Y=0x02
                ///First it will find address at 0x0080 and 0x0081
                ///If they are 0x12 and 0x13 then new indirect address
                ///will be 0x1312+0x02=0x1314 and it will take value at address 0x1314
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t ind_ind_addr= fetch(my_bus);///Indirect of indirect address
                write(my_bus,ind_ind_addr,0,1);
                uint16_t ind_addr_low= fetch(my_bus);
                write(my_bus,ind_ind_addr+1,0,1);
                uint16_t ind_addr_hi= fetch(my_bus);
                uint16_t addr=(ind_addr_hi<<8)|(ind_addr_low)+my6502->reg_Y;
                write(my_bus,addr,0,1);
                my6502->reg_A= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_A);
                if(addr>0x00ff){
                    ///If address crossed the Zero page
                    my6502->clock+=6;
                }
                else{
                    my6502->clock+=5;
                }
                break;
            }
            default:
                break;
        }
    }
    return 0;
}
/// @brief Load into register X
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int LDX(cpu*my6502,bus*my_bus,mode cpu_mode){
    int i=get_D_flag(my6502->reg_sta);
    if(i==0){
        ///if it's the binary mode
        /// Now we have to consider which address mode it is
        switch (cpu_mode)
        {
            ///Immediate mode: just add number directly to register A
            case imm:{
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);

                my6502->reg_X= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_X);

                my6502->clock+=2;

                break;
            }
                /// Absolute address mode
            case adr:{
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low);///Combine address
                write(my_bus,addr,0,1);///Tell the memory to get content of that address
                my6502->reg_X= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_X);
                my6502->clock+=4;
                break;
            }
            case adr_Y:///Absolute address mode with Y index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_Y);///Combine address
                write(my_bus,addr,0,1);///Read data from address
                my6502->reg_X= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_X);
                if(addr>0x00FF){
                    ///If the address is crossing Zero page
                    my6502->clock+=5;
                }
                else{
                    my6502->clock+=4;
                }
                break;
            }

            case zp: ///Zero page address mode
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                my6502->reg_X= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_X);
                my6502->clock+=3;
                break;
            }
            case zp_Y:///Zero page with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus)+(my6502->reg_Y);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                my6502->reg_X= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_X);
                my6502->clock+=4;
                break;
            }

            default:
                break;
        }
    }
    return 0;
}
/// @brief Load into register Y
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int LDY(cpu*my6502,bus*my_bus,mode cpu_mode){
     int i=get_D_flag(my6502->reg_sta);
    if(i==0){
        ///if it's the binary mode
        /// Now we have to consider which address mode it is
        switch (cpu_mode)
        {
            ///Immediate mode: just load number directly to register Y
            case imm:{
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);

                my6502->reg_Y= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_Y);

                my6502->clock+=2;

                break;
            }
                /// Absolute address mode
            case adr:{
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low);///Combine address
                write(my_bus,addr,0,1);///Tell the memory to get content of that address
                my6502->reg_Y= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_Y);
                my6502->clock+=4;
                break;
            }
            case adr_X:///Absolute address mode with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_X);///Combine address
                write(my_bus,addr,0,1);///Read data from address
                my6502->reg_Y= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_Y);
                if(addr>0x00FF){
                    ///If the address is crossing Zero page
                    my6502->clock+=5;
                }
                else{
                    my6502->clock+=4;
                }
                break;
            }

            case zp: ///Zero page address mode
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                my6502->reg_Y= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_Y);
                my6502->clock+=3;
                break;
            }
            case zp_X:///Zero page with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus)+(my6502->reg_X);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                my6502->reg_Y= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_Y);
                my6502->clock+=4;
                break;
            }

            default:
                break;
        }
    }
    return 0;
}
/// @brief Logical shift right
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int LSR(cpu*my6502,bus*my_bus,mode cpu_mode){
    ///Check for BCD mode
    if(get_D_flag(my6502->reg_sta)==0){
        switch (cpu_mode) {
            case acc:///Accumulator mode which is the mode the result is stored directly into register A
            {
                uint8_t res=(my6502->reg_A)>>1;
                my6502->reg_A=res;
                set_flag(my6502,my_bus,my6502->reg_A);
                if((res&0x01)>0){
                    set_C_flag(my6502);
                }
                else{
                    clr_C_flag(my6502);
                }
                my6502->clock+=2;
                break;}
            case zp:///Zero page address mode, the result is stored in that address
            {
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,0,1);
                char result= fetch(my_bus);
                uint8_t temp=my6502->reg_A;
                ///We need to temporary store result into A register
                ///to avoid changing Overflow flag which this instruction
                ///never changes this flag
                my6502->reg_A=result>>1;
                set_flag(my6502,my_bus,result>>1);
                my6502->reg_A=temp;
                write(my_bus,addr,result,0);
                if((result&0x01)>0){
                    set_C_flag(my6502);
                }
                else{
                    clr_C_flag(my6502);
                }
                my6502->clock+=5;
                break;

            }
            case zp_X:///Zero page address mode with X index
            {
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr= fetch(my_bus)+my6502->reg_X;
                write(my_bus,addr,0,1);
                char result= fetch(my_bus);
                uint8_t temp=my6502->reg_A;
                ///We need to temporary store result into A register
                ///to avoid changing Overflow flag which this instruction
                ///never changes this flag
                my6502->reg_A=result>>1;
                set_flag(my6502,my_bus,result>>1);
                my6502->reg_A=temp;
                write(my_bus,addr,result,0);
                if((result&0x01)>0){
                    set_C_flag(my6502);
                }
                else{
                    clr_C_flag(my6502);
                }
                my6502->clock+=6;
                break;
            }
            case adr:///Absolute address mode
            {
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr_low= fetch(my_bus);
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr_hi= fetch(my_bus);
                uint16_t addr=(addr_hi<<8)|addr_low;
                write(my_bus,addr,0,1);
                char result= fetch(my_bus);
                uint8_t temp=my6502->reg_A;
                my6502->reg_A=result>>1;
                set_flag(my6502,my_bus,result>>1);
                my6502->reg_A=temp;
                write(my_bus,addr,result,0);
                if((result&0x01)>0){
                    set_C_flag(my6502);
                }
                else{
                    clr_C_flag(my6502);
                }
                my6502->clock+=6;
                break;
            }
            case adr_X:///Absolute address mode with X index
            {
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr_low= fetch(my_bus);
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr_hi= fetch(my_bus);
                uint16_t addr=(addr_hi<<8)|addr_low+my6502->reg_X;
                write(my_bus,addr,0,1);
                char result= fetch(my_bus);
                uint8_t temp=my6502->reg_A;
                my6502->reg_A=result>>1;
                set_flag(my6502,my_bus,result>>1);
                my6502->reg_A=temp;
                write(my_bus,addr,result,0);
                if((result&0x01)>0){
                    set_C_flag(my6502);
                }
                else{
                    clr_C_flag(my6502);
                }
                my6502->clock+=7;
                break;
            }
            default:
                break;

        }
    }
    return 0;
}
/// @brief No operation
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int NOP(cpu*my6502,bus*my_bus,mode cpu_mode){
    my6502->clock+=2;
    my6502->pc++;
    return 0;
}
/// @brief Or memory with accumulator
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int ORA(cpu*my6502,bus*my_bus,mode cpu_mode){
     ///Check for BCD mode
    ///This instruction can affect 4 flags: Negative, Overflow, Carry and Zero
    ///This instruction always stores results in register A (accumulator)
    ///First we need to check if the mode is binary or not
    int i=get_D_flag(my6502->reg_sta);
    if(i==0){
        ///if it's the binary mode
        /// Now we have to consider which address mode it is
        switch (cpu_mode)
        {
            ///Immediate mode: just or number directly to register A
            case imm:{
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);

                uint16_t result=(my6502->reg_A)| fetch(my_bus);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=2;

                break;
            }
                /// Absolute address mode
            case adr:{
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low);///Combine address
                write(my_bus,addr,0,1);///Tell the memory to get content of that address
                uint16_t result=fetch(my_bus)|(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=4;
                break;
            }
            case adr_Y:///Absolute address mode with Y index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_Y);///Combine address
                write(my_bus,addr,0,1);///Read data from address
                uint16_t result=fetch(my_bus)|(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                if(addr>0x00FF){
                    ///If the address is crossing Zero page
                    my6502->clock+=5;
                }
                else{
                    my6502->clock+=4;
                }
                break;
            }
            case adr_X:///Absolute Address mode with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_X);///Combine address
                write(my_bus,addr,0,1);///Read data from address
                uint16_t result=fetch(my_bus)|(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                if(addr>0x00FF){
                    ///If the address is crossing Zero page
                    my6502->clock+=5;
                }
                else{
                    my6502->clock+=4;
                }
                break;
            }
            case zp: ///Zero page address mode
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                uint16_t result= fetch(my_bus)|(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=3;
                break;
            }
            case zp_X:///Zero page with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus)+(my6502->reg_X);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                uint16_t result= fetch(my_bus)|(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=4;
                break;
            }
            case pre_ind_X:/// Indirect address mode with X index
            {
                ///This address mode has syntax as: ADC ($80,X)
                ///For ex: X=0x01, then the ADC will first find
                ///adress stored at 0x0081 and 0x0082
                ///Then it will take the content of that new found address
                ///Note this address is Little Endian and the value must be Zero page
                ///For ex: ADC ($0800,X) is invalid
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);
                uint16_t ind_addr_low= fetch(my_bus)+(my6502->reg_X);
                write(my_bus,ind_addr_low,0,1);
                uint16_t addr_low= fetch(my_bus);
                uint16_t ind_addr_hi= ind_addr_low+1;
                write(my_bus,ind_addr_hi,0,1);
                uint16_t addr_hi= fetch(my_bus);

                uint16_t addr=(addr_hi<<8)|(addr_low);
                write(my_bus,addr,0,1);
                uint16_t result= fetch(my_bus)|(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=6;
                break;
            }
            case pos_ind_Y:{///Post indirect address mode with Y index
                ///Syntax: ADC ($80),Y if Y=0x02
                ///First it will find address at 0x0080 and 0x0081
                ///If they are 0x12 and 0x13 then new indirect address
                ///will be 0x1312+0x02=0x1314 and it will take value at address 0x1314
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t ind_ind_addr= fetch(my_bus);///Indirect of indirect address
                write(my_bus,ind_ind_addr,0,1);
                uint16_t ind_addr_low= fetch(my_bus);
                write(my_bus,ind_ind_addr+1,0,1);
                uint16_t ind_addr_hi= fetch(my_bus);
                uint16_t addr=(ind_addr_hi<<8)|(ind_addr_low)+my6502->reg_Y;
                write(my_bus,addr,0,1);
                uint16_t result= fetch(my_bus)|(my6502->reg_A);
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                if(addr>0x00ff){
                    ///If address crossed the Zero page
                    my6502->clock+=6;
                }
                else{
                    my6502->clock+=5;
                }
                break;
            }
            default:
                break;
        }
    }
    return 0;
}
/// @brief Push accumulator to stack
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int PHA(cpu*my6502,bus*my_bus,mode cpu_mode){
    my6502->sp--;///Move stack pointer
    write(my_bus,my6502->sp,my6502->reg_A,0);//Push data to stack
    my6502->pc++;
    my6502->clock+=3;
    return 0;
}
/// @brief Push register status to the stack
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int PHP(cpu*my6502,bus*my_bus,mode cpu_mode){
    my6502->sp--;
    write(my_bus,my6502->sp,my6502->reg_sta,0);//Push data to stack
    my6502->pc++;
    my6502->clock+=3;
    return 0;
}
/// @brief Push register X to the stack
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int PHX(cpu*my6502,bus*my_bus,mode cpu_mode){
    my6502->sp--;
    write(my_bus,my6502->sp,my6502->reg_X,0);//Push data to stack
    my6502->pc++;
    my6502->clock+=3;
    return 0;
}
/// @brief Push register Y to the stack
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int PHY(cpu*my6502,bus*my_bus,mode cpu_mode){
    my6502->sp--;
    write(my_bus,my6502->sp,my6502->reg_Y,0);//Push data to stack
    my6502->pc++;
    my6502->clock+=3;
    return 0;
}
/// @brief Pull data from stack to accumulator
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int PLA(cpu*my6502,bus*my_bus,mode cpu_mode){
    write(my_bus,my6502->sp,0,1);//Get data from stack
    my6502->reg_A= fetch(my_bus);
    my6502->pc++;
    my6502->clock+=4;
    my6502->sp++;
    return 0;
}
/// @brief Pull data from stack to register status
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int PLP(cpu*my6502,bus*my_bus,mode cpu_mode){
    write(my_bus,my6502->sp,0,1);//Get data from stack
    my6502->reg_sta= fetch(my_bus);
    my6502->pc++;
    my6502->clock+=4;
    my6502->sp++;
    return 0;
}
/// @brief Pull data from stack to register X
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int PLX(cpu*my6502,bus*my_bus,mode cpu_mode){
    write(my_bus,my6502->sp,0,1);//Get data from stack
    my6502->reg_X= fetch(my_bus);
    my6502->pc++;
    my6502->clock+=4;
    my6502->sp++;
    return 0;
}
/// @brief Pull data from stack to register Y
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int PLY(cpu*my6502,bus*my_bus,mode cpu_mode){
     write(my_bus,my6502->sp,0,1);//Get data from stack
    my6502->reg_Y= fetch(my_bus);
    my6502->pc++;
    my6502->clock+=4;
    my6502->sp++;
    return 0;
}
/// @brief Rotation left 1 bit
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int ROL(cpu*my6502,bus*my_bus,mode cpu_mode){
    ///Check for BCD mode
    if(get_D_flag(my6502->reg_sta)==0){
        switch (cpu_mode) {
            case acc:///Accumulator mode which is the mode the result is stored directly into register A
            {
                char res=(my6502->reg_A<<1)| get_C_flag(my6502->reg_sta);
                uint16_t temp=my6502->reg_A<<1;
                my6502->reg_A=temp;///Trick to avoid setting overflow flag
                set_flag(my6502,my_bus,temp);
                my6502->reg_A=res;
                my6502->clock+=2;
                break;}
           
            case zp:///Zero page address mode, the result is stored in that address
            {
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,0,1);
                char num= fetch(my_bus);
                uint8_t temp=my6502->reg_A;
                char res=(num<<1)| get_C_flag(my6502->reg_sta);
                my6502->reg_A=num<<1;///Trick to avoid overflow flag is set
                set_flag(my6502,my_bus,num<<1);
                my6502->reg_A=temp;
                write(my_bus,addr,res,0);///Write back to the memory
                my6502->clock+=5;
                break;

            }
            case zp_X:///Zero page address mode with X index
            {
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr= fetch(my_bus)+my6502->reg_X;
                write(my_bus,addr,0,1);
                char num= fetch(my_bus);
                uint8_t temp=my6502->reg_A;
                char res=(num<<1)| get_C_flag(my6502->reg_sta);
                my6502->reg_A=num<<1;///Trick to avoid setting overflow flag
                set_flag(my6502,my_bus,num<<1);
                my6502->reg_A=temp;
                write(my_bus,addr,res,0);///Write back to memory
                my6502->clock+=6;
                break;
            }
            case adr:///Absolute address mode
            {
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr_low= fetch(my_bus);
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr_hi= fetch(my_bus);
                uint16_t addr=(addr_hi<<8)|addr_low;
                write(my_bus,addr,0,1);
                char num= fetch(my_bus);
                uint8_t temp=my6502->reg_A;
                char res=(num<<1)| get_C_flag(my6502->reg_sta);
                my6502->reg_A=num<<1;///Trick to avoid setting overflow flag
                set_flag(my6502,my_bus,num<<1);
                my6502->reg_A=temp;
                write(my_bus,addr,res,0);///Write back to memory

                my6502->clock+=6;
                break;
            }
            case adr_X:///Absolute address mode with X index
            {
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr_low= fetch(my_bus);
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr_hi= fetch(my_bus);
                uint16_t addr=(addr_hi<<8)|addr_low+my6502->reg_X;
                write(my_bus,addr,0,1);
                char num= fetch(my_bus);
                uint8_t temp=my6502->reg_A;
                char res=(num<<1)| get_C_flag(my6502->reg_sta);
                my6502->reg_A=num<<1;///Trick to avoid setting overflow flag
                set_flag(my6502,my_bus,num<<1);
                my6502->reg_A=temp;
                write(my_bus,addr,res,0);///Write back to memory

                my6502->clock+=7;
                break;
            }
            default:
                break;

        }
    }
    return 0;
}
/// @brief Rotate 1 bit right
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int ROR(cpu*my6502,bus*my_bus,mode cpu_mode){
    ///Check for BCD mode
    if(get_D_flag(my6502->reg_sta)==0){
        switch (cpu_mode) {
            case acc:///Accumulator mode which is the mode the result is stored directly into register A
            {
                char num=my6502->reg_A;
                char res=(my6502->reg_A>>1)| get_C_flag(my6502->reg_sta)<<7;
                uint16_t temp=my6502->reg_A>>1;
                my6502->reg_A=temp;///Trick to avoid setting overflow flag
                set_flag(my6502,my_bus,temp);
                if((num&0x01)>0){
                    set_C_flag(my6502);
                }else{
                    clr_C_flag(my6502);
                }
                my6502->reg_A=res;
                my6502->clock+=2;
                break;}

            case zp:///Zero page address mode, the result is stored in that address
            {
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,0,1);
                char num= fetch(my_bus);
                uint8_t temp=my6502->reg_A;
                char res=(num>>1)| get_C_flag(my6502->reg_sta)<<7;
                my6502->reg_A=num>>1;///Trick to avoid overflow flag is set
                set_flag(my6502,my_bus,num>>1);
                if((num&0x01)>0){
                    set_C_flag(my6502);
                }else{
                    clr_C_flag(my6502);
                }
                my6502->reg_A=temp;
                write(my_bus,addr,res,0);///Write back to the memory
                my6502->clock+=5;
                break;

            }
            case zp_X:///Zero page address mode with X index
            {
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr= fetch(my_bus)+my6502->reg_X;
                write(my_bus,addr,0,1);
                char num= fetch(my_bus);
                uint8_t temp=my6502->reg_A;
                char res=(num>>1)| get_C_flag(my6502->reg_sta)<<7;
                my6502->reg_A=num>>1;///Trick to avoid overflow flag is set
                set_flag(my6502,my_bus,num>>1);
                if((num&0x01)>0){
                    set_C_flag(my6502);
                }else{
                    clr_C_flag(my6502);
                }
                my6502->reg_A=temp;
                write(my_bus,addr,res,0);///Write back to memory
                my6502->clock+=6;
                break;
            }
            case adr:///Absolute address mode
            {
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr_low= fetch(my_bus);
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr_hi= fetch(my_bus);
                uint16_t addr=(addr_hi<<8)|addr_low;
                write(my_bus,addr,0,1);
                char num= fetch(my_bus);
                uint8_t temp=my6502->reg_A;
                char res=(num>>1)| get_C_flag(my6502->reg_sta)<<7;
                my6502->reg_A=num>>1;///Trick to avoid overflow flag is set
                set_flag(my6502,my_bus,num>>1);
                if((num&0x01)>0){
                    set_C_flag(my6502);
                }else{
                    clr_C_flag(my6502);
                }
                my6502->reg_A=temp;
                write(my_bus,addr,res,0);///Write back to memory

                my6502->clock+=6;
                break;
            }
            case adr_X:///Absolute address mode with X index
            {
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr_low= fetch(my_bus);
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t addr_hi= fetch(my_bus);
                uint16_t addr=(addr_hi<<8)|addr_low+my6502->reg_X;
                write(my_bus,addr,0,1);
                char num= fetch(my_bus);
                uint8_t temp=my6502->reg_A;
                char res=(num>>1)| get_C_flag(my6502->reg_sta)<<7;
                my6502->reg_A=num>>1;///Trick to avoid overflow flag is set
                set_flag(my6502,my_bus,num>>1);
                if((num&0x01)>0){
                    set_C_flag(my6502);
                }else{
                    clr_C_flag(my6502);
                }
                my6502->reg_A=temp;
                write(my_bus,addr,res,0);///Write back to memory

                my6502->clock+=7;
                break;
            }
            default:
                break;

        }
    }
    return 0;
}
/// @brief Return from interrupt
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int RTI(cpu*my6502,bus*my_bus,mode cpu_mode){
    ///Pop the status register first
    my6502->sp--;
    write(my_bus,my6502->sp,0,1);
    my6502->reg_sta= fetch(my_bus);
    ///Pop the address of program counter
    my6502->sp--;
    write(my_bus,my6502->sp,0,1);
    uint16_t addr_low= fetch(my_bus);
    my6502->sp--;
    write(my_bus,my6502->sp,0,1);
    uint16_t addr_hi= fetch(my_bus);
    uint16_t addr=(addr_hi<<8)|(addr_low);
    my6502->pc=addr;
    return 0;
}
/// @brief Jump from subroutine
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int RTS(cpu*my6502,bus*my_bus,mode cpu_mode){
     ///Pop the address of program counter
    my6502->sp--;
    write(my_bus,my6502->sp,0,1);
    uint16_t addr_low= fetch(my_bus);
    my6502->sp--;
    write(my_bus,my6502->sp,0,1);
    uint16_t addr_hi= fetch(my_bus);
    uint16_t addr=(addr_hi<<8)|(addr_low);
    my6502->pc=addr;
    return 0;
}
/// @brief Subtraction with carry
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int SBC(cpu*my6502,bus*my_bus,mode cpu_mode){
    ///This instruction can affect 4 flags: Negative, Overflow, Carry and Zero
    ///This instruction always stores results in register A (accumulator)
    ///First we need to check if the mode is binary or not
    int i=get_D_flag(my6502->reg_sta);
    if(i==0){
        ///if it's the binary mode
        /// Now we have to consider which address mode it is
        switch (cpu_mode)
        {
            ///Immediate mode: just add number directly to register A
            case imm:{
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);

                uint16_t result=(my6502->reg_A)- fetch(my_bus)-(1- get_C_flag(my6502->reg_sta));
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=2;

                break;
            }
                /// Absolute address mode
            case adr:{
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low);///Combine address
                write(my_bus,addr,0,1);///Tell the memory to get content of that address
                uint16_t result=(my6502->reg_A)- fetch(my_bus)-(1- get_C_flag(my6502->reg_sta));
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=4;
                break;
            }
            case adr_Y:///Absolute address mode with Y index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_Y);///Combine address
                write(my_bus,addr,0,1);///Read data from address
                uint16_t result=(my6502->reg_A)- fetch(my_bus)-(1- get_C_flag(my6502->reg_sta));
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                if(addr>0x00FF){
                    ///If the address is crossing Zero page
                    my6502->clock+=5;
                }
                else{
                    my6502->clock+=4;
                }
                break;
            }
            case adr_X:///Absolute Address mode with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_X);///Combine address
                write(my_bus,addr,0,1);///Read data from address
                uint16_t result=(my6502->reg_A)- fetch(my_bus)-(1- get_C_flag(my6502->reg_sta));
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                if(addr>0x00FF){
                    ///If the address is crossing Zero page
                    my6502->clock+=5;
                }
                else{
                    my6502->clock+=4;
                }
                break;
            }
            case zp: ///Zero page address mode
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                uint16_t result= (my6502->reg_A)- fetch(my_bus)-(1- get_C_flag(my6502->reg_sta));
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=3;
                break;
            }
            case zp_X:///Zero page with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus)+(my6502->reg_X);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                uint16_t result= (my6502->reg_A)- fetch(my_bus)-(1- get_C_flag(my6502->reg_sta));
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=4;
                break;
            }
            case pre_ind_X:/// Indirect address mode with X index
            {
                ///This address mode has syntax as: ADC ($80,X)
                ///For ex: X=0x01, then the ADC will first find
                ///adress stored at 0x0081 and 0x0082
                ///Then it will take the content of that new found address
                ///Note this address is Little Endian and the value must be Zero page
                ///For ex: ADC ($0800,X) is invalid
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);
                uint16_t ind_addr_low= fetch(my_bus)+(my6502->reg_X);
                write(my_bus,ind_addr_low,0,1);
                uint16_t addr_low= fetch(my_bus);
                uint16_t ind_addr_hi= ind_addr_low+1;
                write(my_bus,ind_addr_hi,0,1);
                uint16_t addr_hi= fetch(my_bus);

                uint16_t addr=(addr_hi<<8)|(addr_low);
                write(my_bus,addr,0,1);
                uint16_t result= (my6502->reg_A)- fetch(my_bus)-(1- get_C_flag(my6502->reg_sta));
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                my6502->clock+=6;
                break;
            }
            case pos_ind_Y:{///Post indirect address mode with Y index
                ///Syntax: ADC ($80),Y if Y=0x02
                ///First it will find address at 0x0080 and 0x0081
                ///If they are 0x12 and 0x13 then new indirect address
                ///will be 0x1312+0x02=0x1314 and it will take value at address 0x1314
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t ind_ind_addr= fetch(my_bus);///Indirect of indirect address
                write(my_bus,ind_ind_addr,0,1);
                uint16_t ind_addr_low= fetch(my_bus);
                write(my_bus,ind_ind_addr+1,0,1);
                uint16_t ind_addr_hi= fetch(my_bus);
                uint16_t addr=(ind_addr_hi<<8)|(ind_addr_low)+my6502->reg_Y;
                write(my_bus,addr,0,1);
                uint16_t result= (my6502->reg_A)- fetch(my_bus)-(1- get_C_flag(my6502->reg_sta));
                set_flag(my6502,my_bus,result);
                my6502->reg_A=result;
                if(addr>0x00ff){
                    ///If address crossed the Zero page
                    my6502->clock+=6;
                }
                else{
                    my6502->clock+=5;
                }
                break;
            }
            default:
                break;
        }
    }
    return 0;
}
/// @brief set carry flag
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int SEC(cpu*my6502,bus*my_bus,mode cpu_mode){
    set_C_flag(my6502);
    return 0;
}
/// @brief set decimal flag
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int SED(cpu*my6502,bus*my_bus,mode cpu_mode){
    set_D_flag(my6502);
    return 0;
}
/// @brief set interupt flag or disable interrupt
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int SEI(cpu*my6502,bus*my_bus,mode cpu_mode){
    set_I_flag(my6502);
    return 0;
}
/// @brief Store the content of Accumulator into memory address
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int STA(cpu*my6502,bus*my_bus,mode cpu_mode){
    int i=get_D_flag(my6502->reg_sta);
    if(i==0){
        ///if it's the binary mode
        /// Now we have to consider which address mode it is
        switch (cpu_mode)
        {

                /// Absolute address mode
            case adr:{
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low);///Combine address
                write(my_bus,addr,my6502->reg_A,0);///Write content to of that address

                my6502->clock+=4;
                break;
            }
            case adr_Y:///Absolute address mode with Y index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_Y);///Combine address
                write(my_bus,addr,my6502->reg_A,0);///Write content to of that address
                my6502->clock+=5;
                break;
            }
            case adr_X:///Absolute Address mode with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low)+(my6502->reg_X);///Combine address
                write(my_bus,addr,my6502->reg_A,0);///Write content to of that address
                my6502->clock+=5;
                break;
            }
            case zp: ///Zero page address mode
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,my6502->reg_A,0);///Write content to of that address
                my6502->clock+=3;
                break;
            }
            case zp_X:///Zero page with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus)+(my6502->reg_X);
                write(my_bus,addr,0,1);///Read the data from address in Zero page (0x0000-0x00FF)
                my6502->reg_A= fetch(my_bus);
                set_flag(my6502,my_bus,my6502->reg_A);
                my6502->clock+=4;
                break;
            }
            case pre_ind_X:/// Indirect address mode with X index
            {
                ///This address mode has syntax as: ADC ($80,X)
                ///For ex: X=0x01, then the ADC will first find
                ///adress stored at 0x0081 and 0x0082
                ///Then it will take the content of that new found address
                ///Note this address is Little Endian and the value must be Zero page
                ///For ex: ADC ($0800,X) is invalid
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);
                uint16_t ind_addr_low= fetch(my_bus)+(my6502->reg_X);
                write(my_bus,ind_addr_low,0,1);
                uint16_t addr_low= fetch(my_bus);
                uint16_t ind_addr_hi= ind_addr_low+1;
                write(my_bus,ind_addr_hi,0,1);
                uint16_t addr_hi= fetch(my_bus);

                uint16_t addr=(addr_hi<<8)|(addr_low);
                write(my_bus,addr,my6502->reg_A,0);///Write content to of that address
                my6502->clock+=6;
                break;
            }
            case pos_ind_Y:{///Post indirect address mode with Y index
                ///Syntax: ADC ($80),Y if Y=0x02
                ///First it will find address at 0x0080 and 0x0081
                ///If they are 0x12 and 0x13 then new indirect address
                ///will be 0x1312+0x02=0x1314 and it will take value at address 0x1314
                (my6502->pc)++;
                write(my_bus,my6502->pc,0,1);
                uint16_t ind_ind_addr= fetch(my_bus);///Indirect of indirect address
                write(my_bus,ind_ind_addr,0,1);
                uint16_t ind_addr_low= fetch(my_bus);
                write(my_bus,ind_ind_addr+1,0,1);
                uint16_t ind_addr_hi= fetch(my_bus);
                uint16_t addr=(ind_addr_hi<<8)|(ind_addr_low)+my6502->reg_Y;
                write(my_bus,addr,my6502->reg_A,0);///Write content to of that address
               my6502->clock+=6;
                break;
            }
            default:
                break;
        }
    }
    return 0;
}
/// @brief Store the content of X register into memory address
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int STX(cpu*my6502,bus*my_bus,mode cpu_mode){
    int i=get_D_flag(my6502->reg_sta);
    if(i==0){
        ///if it's the binary mode
        /// Now we have to consider which address mode it is
        switch (cpu_mode)
        {

                /// Absolute address mode
            case adr:{
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low);///Combine address
                write(my_bus,addr,my6502->reg_X,1);///Write content to the memory of that address
                my6502->clock+=4;
                break;
            }

            case zp: ///Zero page address mode
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,my6502->reg_X,1);///Write content to the memory of that address
                my6502->clock+=3;
                break;
            }
            case zp_Y:///Zero page with Y index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus)+(my6502->reg_Y);
                write(my_bus,addr,my6502->reg_X,1);///Write content to the memory of that address
                my6502->clock+=4;
                break;
            }

            default:
                break;
        }
    }
    return 0;
    
}
/// @brief Store the content of Y register into memory address
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int STY(cpu*my6502,bus*my_bus,mode cpu_mode){
    int i=get_D_flag(my6502->reg_sta);
    if(i==0){
        ///if it's the binary mode
        /// Now we have to consider which address mode it is
        switch (cpu_mode)
        {

                /// Absolute address mode
            case adr:{
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_low= fetch(my_bus);///Take the low address first beacause of Little Endian
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr_hi= fetch(my_bus);///Take the high address
                uint16_t addr=((uint16_t)(addr_hi<<8))|(addr_low);///Combine address
                write(my_bus,addr,my6502->reg_Y,0);///Write the content to the memory of that address
                my6502->clock+=4;
                break;
            }

            case zp: ///Zero page address mode
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus);
                write(my_bus,addr,my6502->reg_Y,0);///Write the content to the memory of that address
                my6502->clock+=3;
                break;
            }
            case zp_X:///Zero page with X index
            {
                (my6502->pc)++;
                write(my_bus,(my6502->pc),0,1);///Read the next address
                uint16_t addr= fetch(my_bus)+(my6502->reg_X);
                write(my_bus,addr,my6502->reg_Y,0);///Write the content to the memory of that address
                my6502->clock+=4;
                break;
            }

            default:
                break;
        }
    }
    return 0;
}

/// @brief Transfer from content of Accumulator to X register
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int TAX(cpu*my6502,bus*my_bus,mode cpu_mode){
    my6502->reg_X=my6502->reg_A;
    set_flag(my6502,my_bus,my6502->reg_A);
    my6502->clock+=2;
    return 0;
}
/// @brief Transfer from content of Accumulator to Y register
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int TAY(cpu*my6502,bus*my_bus,mode cpu_mode){
    my6502->reg_Y=my6502->reg_A;
    set_flag(my6502,my_bus,my6502->reg_A);
    my6502->clock+=2;
    return 0;
}
/// @brief Transfer content from Stack to register X
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int TSX(cpu*my6502,bus*my_bus,mode cpu_mode){
    uint8_t temp=my6502->reg_A;
    write(my_bus,my6502->sp,0,1);
    char res= fetch(my_bus);
    my6502->reg_A=res;
    my6502->reg_X=res;
    set_flag(my6502,my_bus,my6502->reg_A);
    my6502->reg_A=temp;
    my6502->clock+=2;
    return 0;
}
/// @brief Transfer content from X register to Accumulator
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int TXA(cpu*my6502,bus*my_bus,mode cpu_mode){
    my6502->reg_A=my6502->reg_X;
    my6502->clock+=2;
    set_flag(my6502,my_bus,my6502->reg_A);
    return 0;
}
/// @brief Transfer content from X register to Stack
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int TXS(cpu*my6502,bus*my_bus,mode cpu_mode){
    my6502->sp++;
    write(my_bus,my6502->sp,my6502->reg_X,0);
    my6502->clock+=2;
    return 0;
}
/// @brief Transfer content from Y register to accumulator
/// @param my6502 
/// @param my_bus 
/// @param cpu_mode 
/// @return 
int TYA(cpu*my6502,bus*my_bus,mode cpu_mode){
    my6502->reg_A=my6502->reg_Y;
    set_flag(my6502,my_bus,my6502->reg_A);
    my6502->clock+=2;
    return 0;
}

#endif
