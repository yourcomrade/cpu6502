#ifndef BUS_H
#define BUS_H
#include<stdint.h>
#include "memory.h"
#include "cpu6502.h"
typedef struct bus{
    uint8_t data;//For accessing data
    uint16_t address;//For accessing address
    char read;//for signal
    ///Device connecting to bus
    cpu*my6502;
    mem*my_ram;
}bus;
uint8_t fetch(bus*my_bus);
void write(bus*my_bus,uint16_t addr,uint8_t data,char read);

#endif