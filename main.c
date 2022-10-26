#include<stdio.h>
#include<stdlib.h>
#include "test/test_ins.h"
#include "inc/instruction.h"
#include "inc/memory.h"

#include "inc/bus.h"
int main(int arg,char **argc){
    //struct cpu my6502={0x0,0x0,0x0,0x0,0xff,0};
   // test_flag(&my6502);
  cpu my6502;
  bus my_bus;
  mem my_mem={NULL};
  init(&my_mem,&my6502,&my_bus);
    test_LDA(&my_bus,&my6502);
  return 0;
}