#include "mbed.h"
#include <cmath>
#include "other_func.hpp"
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

int bin_to_deci(int* in){
    int out;
    for (int x= 0; x < sizeof(in); x++){
        out = out + ((pow(2,x))*in[x]); 
    }
    return out;
    
}


void LED_display(int i){
    switch(i)
    {
        case 1:
            led1 = 1;
            led2 = 0;
            led3 = 0;
            break;
        case 2:
            led1 = 0;
            led2 = 1;
            led3 = 0;
            break;
        case 3:
            led1 = 0;
            led2 = 0;
            led3 = 1;
            break;

    }

}






