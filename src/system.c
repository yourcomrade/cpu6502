//
// Created by ADMIN on 16/10/2022.
//
#ifndef SYSTEM_C
#define SYSTEM_C

#include <stddef.h>
#include "../inc/system.h"

#include <stdio.h>
const opcode *searching(unsigned char hex_opcode){
    int low=0, high=num_opcode-1;
    while((high-low)>1){
        int mid=(high+low)/2;
        if(my_opcode[mid].hexcode<hex_opcode){
            low=mid+1;
        }
        else{
            high=mid;
        }
    }
    if(my_opcode[low].hexcode==hex_opcode){
        return &my_opcode[low];
    }
    else if(my_opcode[high].hexcode==hex_opcode){
        return &my_opcode[high];
    }
    else{
        return NULL;
    }
}
void disassembler(char*file_name)
{
    FILE*fptr1= fopen(file_name,"rb");
    FILE*fptr2= fopen("disassembler_file.txt","a+");
    if(!fptr1){
        perror("\nCannot open binary file to read");
    }
    if(!fptr2){
        perror("\nCannot open text file for disassembler ");
    }
    unsigned char ins;
    char addr_val=0;

    opcode *prev=NULL;
    uint16_t address=0;
    fprintf(fptr2,"%s   %s   %s\n","Address","Hexdump","Assembly");
    while(fread(&ins, sizeof(char),1,fptr1)>0){
        opcode *my= searching(ins);
        switch (my->cpu_mode) {
            case imm:{
                char val=0;
                fread(&val, sizeof(char),1,fptr1);
                fprintf(fptr2,"%x   %x %x   %s #$%x\n",address,my->hexcode,val,my->ins,val);
                address+=2;
                break;
            }
            case zp:{
                char val=0;
                fread(&val, sizeof(char),1,fptr1);
                fprintf(fptr2,"%x   %x %x   %s $%x\n",address,my->hexcode,val,my->ins,val);
                address+=2;
                break;
            }
            case zp_X:{
                char val=0;
                fread(&val, sizeof(char),1,fptr1);
                fprintf(fptr2,"%x   %x %x   %s $%x,X\n",address,my->hexcode,val,my->ins,val);
                address+=2;
                break;
            }
            case zp_Y:{
                char val=0;
                fread(&val, sizeof(char),1,fptr1);
                fprintf(fptr2,"%x   %x %x   %s $%x,Y\n",address,my->hexcode,val,my->ins,val);
                address+=2;
                break;
            }
            case adr:{
                char val=0;
                fread(&val, sizeof(char),1,fptr1);
                char val1=0;
                fread(&val1, sizeof(char),1,fptr1);
                fprintf(fptr2,"%x   %x %x %x  %s $%x%x\n",address,my->hexcode,val,val1,my->ins,val1,val);
                address+=3;
                break;
            }
            case adr_X:{
                char val=0;
                fread(&val, sizeof(char),1,fptr1);
                char val1=0;
                fread(&val1, sizeof(char),1,fptr1);
                fprintf(fptr2,"%x   %x %x %x  %s $%x%x,X\n",address,my->hexcode,val,val1,my->ins,val1,val);
                address+=3;
                break;
            }
            case adr_Y:{
                char val=0;
                fread(&val, sizeof(char),1,fptr1);
                char val1=0;
                fread(&val1, sizeof(char),1,fptr1);
                fprintf(fptr2,"%x   %x %x %x  %s $%x%x,Y\n",address,my->hexcode,val,val1,my->ins,val1,val);
                address+=3;
                break;
            }
            case ind_adr:{
                char val=0;
                fread(&val, sizeof(char),1,fptr1);
                char val1=0;
                fread(&val1, sizeof(char),1,fptr1);
                fprintf(fptr2,"%x   %x %x %x  %s ($%x%x)\n",address,my->hexcode,val,val1,my->ins,val1,val);
                address+=3;
                break;
            }
            case pre_ind_X:{
                char val=0;
                fread(&val, sizeof(char),1,fptr1);
                fprintf(fptr2,"%x   %x %x   %s ($%x,X)\n",address,my->hexcode,val,my->ins,val);
                address+=2;
                break;
            }
            case pos_ind_Y:{
                char val=0;
                fread(&val, sizeof(char),1,fptr1);
                fprintf(fptr2,"%x   %x %x   %s ($%x),Y\n",address,my->hexcode,val,my->ins,val);
                address+=2;
                break;
            }
            case none:{
                fprintf(fptr2,"%x    %x      %s \n",address,my->hexcode,my->ins);
                address+=1;
                break;
            }
            default:
                break;
        }
    }
    fclose(fptr1);
    fclose(fptr2);

}
#endif