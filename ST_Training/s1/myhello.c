#include <stdio.h>

typedef union 
{
    struct 
    {
        __uint8_t bit0:1;
        __uint8_t bit1:1;
        __uint8_t bit2:1;
        __uint8_t bit3:1;
        __uint8_t bit4:1;
        __uint8_t bit5:1;
        __uint8_t bit6:1;
        __uint8_t bit7:1;
    }Bit;

    __uint8_t Byte;
    
}register_t;

int main(){
    printf("\n> sizeof(register_t) =%ld\n",sizeof(register_t));
    return 0;
}
