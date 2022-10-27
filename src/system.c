//
// Created by ADMIN on 16/10/2022.
//
#ifndef SYSTEM_C
#define SYSTEM_C

#include <stddef.h>
#include "../inc/system.h"
#include "opcode.c"
#include <stdio.h>
const opcode *searching(char hex_opcode){
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
    FILE*fptr= fopen(file_name,"rb");
    if(!fptr){
        perror("\nCannot open binary file to read");
    }
}
#endif