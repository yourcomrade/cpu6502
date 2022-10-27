//
// Created by ADMIN on 16/10/2022.
//
#ifndef BUS_C
#define BUS_C
#include "../inc/bus.h"

#include "../inc/memory.h"

uint8_t fetch(bus*my_bus){
    my_bus->read=1;///Now we read data from bus
    return my_bus->data;
}
void write(bus*my_bus,uint16_t addr,uint8_t data,char read){
    my_bus->address=addr;
    my_bus->data=data;
    my_bus->read=read;
    if(read==1){
        my_bus->data= get_val(my_bus->my_ram,my_bus->address);
    }
    else{
        insert(my_bus->my_ram,my_bus->address,my_bus->data);
    }
}
#endif