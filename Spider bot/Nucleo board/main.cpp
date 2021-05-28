/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */


//import libraries
#include "mbed.h"
#include "platform/mbed_thread.h"
#include "FIFO.h"
#include "LEG.h"
#include "SERVO.h"
#include "Bluetooth.hpp"
#include "other_func.hpp"
#include "math.h"
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>



//serial ports
Serial serial2(PD_5,PD_6,9600);
Serial pc(USBTX,USBRX,9600);
Serial serial_arduino(PE_8,PE_7,38400);

//array of button inputs
DigitalIn button_in_left[]  = {PC_0,PC_3,PF_3,PF_5};
DigitalIn button_in_right[] = {PG_1,PD_0,PD_1,PG_0};

//fifo buffers
FIFO primary = FIFO(20);
FIFO secondry = FIFO(30);
FIFO data_buffer = FIFO(20);

//declaring threads
Thread thread_coms;
Thread thread_data;
Thread thread_data_out;
Thread thread_arduino;

//declaring mutex
Mutex data_out_mutex;
Mutex data_in_mutex;


//declaring variables
uint8_t postior =3;//0 = stand,1= walk,2 = intimidate, 3 = test;
int tally = 1;
int speed = 500;
uint8_t velocity = 0;
uint8_t side_speed;
uint8_t battery_R;
uint8_t battery_L;
int out = 0;

//declaring each legs parameters
int16_t para_1R[] = {-90,90,-90,90,-90,90};
int16_t para_2R[] = {-90,90,-90,90,-90,90};
int16_t para_3R[] = {-90,90,-90,90,-90,90};
int16_t para_4R[] = {-90,90,-90,90,-90,90};
int16_t para_1L[] = {-90,90,-90,90,-90,90};
int16_t para_2L[] = {-90,90,-90,90,-90,90};
int16_t para_3L[] = {-90,90,-90,90,-90,90};
int16_t para_4L[] = {-90,90,-90,90,-90,90};
uint16_t center_1R[] = {470,140,190};
uint16_t center_2R[] = {330,210,290};
uint16_t center_3R[] = {270,144,330};
uint16_t center_4R[] = {215,190,350};
uint16_t center_1L[] = {210,140,250};
uint16_t center_2L[] = {240,170,300};
uint16_t center_3L[] = {330,260,300};
uint16_t center_4L[] = {400,145,290};

LEG leg_1R = LEG(125, 100, 110, 180, 0, false, para_1R,center_1R);
LEG leg_2R = LEG(125, 100, 110, 180, 1, false, para_2R,center_2R);
LEG leg_3R = LEG(125, 100, 110, 180, 2, false, para_3R,center_3R);
LEG leg_4R = LEG(125, 100, 110, 180, 3, false, para_4R,center_4R);
LEG leg_1L = LEG(125, 100, 110, 180, 0, true, para_1L,center_1L);
LEG leg_2L = LEG(125, 100, 110, 180, 1, true, para_2L,center_2L);
LEG leg_3L = LEG(125, 100, 110, 180, 2, true, para_3L,center_3L);
LEG leg_4L = LEG(125, 100, 110, 180, 3, true, para_4L,center_4L);


//void stand(int wait_ms = 0);

void startup(){
    pc.printf("Hollow world\n\r");
    pc.printf("starting in...3\n\r");
    wait_us(1000000);
    pc.printf("2\n\r");
    wait_us(1000000);
    pc.printf("1\n\r");
    wait_us(1000000);
    pc.printf("Start\n\r");
    return;

}

void stand(int wait_ms){
    leg_1R.LEG_servo(-80, 0, 70);   
    wait_us(wait_ms*1000);
    leg_2R.LEG_servo(-45, 0, 70);//-45
    wait_us(wait_ms*1000);
    leg_3R.LEG_servo(0, 0, 70);
    wait_us(wait_ms*1000);
    leg_4R.LEG_servo(45, 0, 70);
    wait_us(wait_ms*1000);
    leg_1L.LEG_servo(80, -20, 60);   
    wait_us(wait_ms*1000);
    leg_2L.LEG_servo(45, -20, 60);//45
    wait_us(wait_ms*1000);
    leg_3L.LEG_servo(0, -20, 60);
    wait_us(wait_ms*1000);
    leg_4L.LEG_servo(-45, -20, 60);
    return;
}

void intimidate(){
    leg_1R.LEG_servo(-80, 70, 80);   
    leg_2R.LEG_servo(-45, -20, 60);
    leg_3R.LEG_servo(0, -20, 60);
    leg_4R.LEG_servo(45, -20, 60);
    leg_1L.LEG_servo(80, 70, 80);   
    leg_2L.LEG_servo(45, -20, 60);
    leg_3L.LEG_servo(0, -20, 60);
    leg_4L.LEG_servo(-45, -20, 60);
    return;

}

void data_out(void){
    while(1){
        out =0;
        uint8_t butt[8];
        for (int x = 0; x < 4;x++){
            butt[x] = button_in_right[3-x];
        }
        for (int x = 0; x < 4;x++){
            butt[x+4] = button_in_left[x];
        }
        for (int x= 0; x < 8; x++){
            out = out + ((pow(2,x))*butt[x]); 
        }
        //cout << "buttons:"<<butt[0]<<butt[1]<<butt[2]<<butt[3]<<butt[4]<<butt[5]<<butt[6]<<butt[7]<<endl;

        out = out+120;
        secondry.add_data(out);
        ThisThread::sleep_for(2000);
    }
}



// //uses data
// void data_output_2(int in_data){

//         if (in_data < 800 &&  in_data > 700){
//             float temp = (in_data - 700)/10;
//             temp = std::floor(temp);
//             pc.printf("%d\n\r",int(temp));
//         }
//         else if (in_data == 630){//stand
//             postior = 0;
//         }
//         else if(in_data == 620){//initimidate
//             postior = 2;
//         }
//         else if(in_data == 610){//walk
//             postior = 1;
//         }
//         else{
//             pc.printf("%d",in_data);
//         }



    
// }

void arduino(){

        char buffer[3];
        int input;
        //input =read_data(&pc, &serial_arduino);
        serial_arduino.scanf("%d",&input);
        //pc.printf("data\n\r");
        //buffer[3]= 0;
        //sscanf(buffer, "%d", &input);
        //pc.printf("data: %d", input);
        if (input < 1000 && input > -1){
            uint8_t current_r = input%100;
            secondry.add_data(int(current_r/2)+450);
            uint8_t current_l = (int(floor(input/100))*10+input%10);
           
            secondry.add_data(int(current_l/2)+400);
        }
        else{
            secondry.add_data(111);
        }
        return;
}



void data_control(){
    uint8_t i =0;
    while(1){
        //data_emulator(tally, &primary, &secondary,&pc);
        int data = read_data(&pc,&serial2);
        data_buffer.add_data(data);
        //int in_data = data_buffer.pop();
        //pc.printf("data received: %d\n\r",data);
        
        if (i > 5){
         arduino();
         i =0;
        }
        
        
        ThisThread::sleep_for(50);
        
        i++;
        // if (primary.end_loc_return()==0){
        //     if (secondary.end_loc_return()!=0){
        //         secondary.pop();
        //     }
        // }
        // else{
        //     primary.pop();
        // }
        //for(int x = 0; x < 10; x++){
        //pc.printf("sending data");
        
        pc.printf("sending data\n\r");
        send_data(&primary, &secondry, &pc, &serial2);

        //serial2.printf("x111");
        //}
        tally++;
        
    }
}



void data_output(){
    while(1){
        int in_data = data_buffer.pop();
        if(in_data != -1){
            if (in_data < 800 &&  in_data > 700){
                float temp = (in_data - 700)/10;
                side_speed = std::floor(temp);
                temp = (in_data - 700)-(side_speed*10);
                //pc.printf("temp: %f\n\r",temp);
                if (temp == 0){
                    
                }
                else if (temp > 6){
                    velocity = (temp-6)*-1;
                }
                else if (temp < 4){
                    velocity = (temp-4)*-1;
                }
                else{
                    velocity = 0;
                }
                //pc.printf("%d\n\r",int(temp));
            }
            else if (in_data == 630){//stand
                postior = 0;
            }
            else if(in_data == 620){//initimidate
                postior = 2;
            }
            else if(in_data == 610){//walk
                postior = 1;
            }
        }
        else{
            //pc.printf("empty\n\r");
        }
        ThisThread::sleep_for(50);

    }
}



void read_terminal(void){
    while(1){
        char buff[10];
        pc.printf("Enter direction\n\r");
        pc.scanf("%s", buff);
        if (strcmp("forward",buff) == 0){
            pc.printf("forward\n\r");
            velocity = 1;
        }
        else if (strcmp("backwards",buff) == 0){
            pc.printf("backwards\n\r");
            velocity = -1;
        }
        else if (strcmp("stop", buff) == 0) {
            pc.printf("stop\n\r");
            velocity = 0;
        }
        else if (strcmp("fast", buff) == 0) {
            pc.printf("fast\n\r");
            speed = 100;
        }
        else if (strcmp("slow", buff) == 0) {
            pc.printf("slow\n\r");
            speed = 500;
        }

        else {
            pc.printf("unknown input\n\r");
        }
    }
}




int main()
{

    //create cycles
    startup();
    //setup each leg
    leg_1L.setup();
    leg_2L.setup();
    leg_3L.setup();
    leg_4L.setup();
    leg_1R.setup();
    leg_2R.setup();
    leg_3R.setup();
    leg_4R.setup();
   // stand(3000);
    //double q1,q2,q3;
    // leg_4R.ikunc_new(120, -120, -250, &q1, &q2, &q3);
    // pc.printf("q1: %f, q2: %f, q3: %f\n\r",q1,q2,q3);

    stand(0);// initial stance
    
    
    // float x1Rpos[100],y1Rpos[100],z1Rpos[100];
    // float x1Lpos[100],y1Lpos[100],z1Lpos[100];
    // float x2Rpos[100],y2Rpos[100],z2Rpos[100];
    //float x2Lpos[100],y2Lpos[100],z2Lpos[100];
    //float x3Rpos[100],y3Rpos[100],z3Rpos[100];
    //float x3Lpos[100],y3Lpos[100],z3Lpos[100];
    //float x4Rpos[100],y4Rpos[100],z4Rpos[100];
    //float x4Lpos[100],y4Lpos[100],z4Lpos[100];
    //leg_1R.cycle_data_new(x1Rpos, y1Rpos, z1Rpos,60 , 60, -250, 60, 210, -250, 42, 243, 53, 0, 68);
    //leg_1L.cycle_data_new(x1Lpos, y1Lpos, z1Lpos,60 , 60, -250, 60, 210, -250, 42, 243, 53, 40, 10);
    //leg_2R.cycle_data_new(x2Rpos, y2Rpos, z2Rpos,60 , 60, -250, 60, 210, -250, 42, 243, 53, 40, 10); //150,0, -250, 150,150,-250, 150, 0, -250, 70, 90
    //leg_2L.cycle_data_new(x2Lpos, y2Lpos, z2Lpos,150 ,0 , -250, 150,150, -250, 30, 0  , 50, 50, 20);
    //leg_3L.cycle_data_new(x3Lpos, y3Lpos, z3Lpos,60 , 60, -250, 60, 210, -250, 42, 243, 53, 40, 10);
    //leg_3R.cycle_data_new(x3Rpos, y3Rpos, z3Rpos,60 , 60, -250, 60, 210, -250, 42, 243, 53, 40, 10);
    //leg_4L.cycle_data_new(x4Lpos, y4Lpos, z4Lpos,60 , 60, -250, 60, 210, -250, 42, 243, 53, 40, 10);
    //leg_4R.cycle_data_new(x4Rpos, y4Rpos, z4Rpos,60 , 60, -250, 60, 210, -250, 42, 243, 53, 40, 10);
    int n = 50;
    thread_data.start(data_output);
    thread_coms.start(data_control);
    thread_data_out.start(data_out);
    //intimidate();
    // pc.printf("\n\rxpos: ");
    // for (int x = 0; x < 100 ; x++){
    //     pc.printf("%f ,",x2Rpos[x]);
    // }
    // pc.printf("\n\rypos: ");
    // for (int x = 0; x < 100 ; x++){
    //     pc.printf("%f ,",y2Rpos[x]);
    // }
    // pc.printf("\n\rzpos: ");
    // for (int x = 0; x < 100 ; x++){
    //     pc.printf("%f ,",z2Rpos[x]);
    // }
    // pc.printf("\n\rxpos: ");
    // for (int x = 0; x < 100 ; x++){
    //     pc.printf("%f ,",x2Lpos[x]);
    // }
    // pc.printf("\n\rypos: ");
    // for (int x = 0; x < 100 ; x++){
    //     pc.printf("%f ,",y2Lpos[x]);
    // }
    // pc.printf("\n\rzpos: ");
    // for (int x = 0; x < 100 ; x++){
    //     pc.printf("%f ,",z2Lpos[x]);
    // }
    pc.printf("\n\r");

    double l1a,l1b,l1c;
    double l2a,l2b,l2c;
    double l3a,l3b,l3c;
    double l4a,l4b,l4c;
    double r1a,r1b,r1c;
    double r2a,r2b,r2c;
    double r3a,r3b,r3c;
    double r4a,r4b,r4c;
    int16_t r1x,r1y,r1z;
    int16_t r2x,r2y,r2z;
    int16_t r3x,r3y,r3z;
    int16_t r4x,r4y,r4z;
    int16_t l1x,l1y,l1z;
    int16_t l2x,l2y,l2z;
    int16_t l3x,l3y,l3z;
    int16_t l4x,l4y,l4z;

    //leg_2L.LEG_servo(0, 0, 0);
    while (1){
        
        if (postior == 0){
            stand(0);
            LED_display(1);
            pc.printf("standing\n\r");
            ThisThread::sleep_for(100);
        }
        else if(postior== 2){
            intimidate();
            LED_display(3);
            pc.printf("intimidating\n\r");
            ThisThread::sleep_for(100);
        }
        else if(postior == 1){
           
            if(n > 99){n =99;}
            if(n<0){n =0;};
            LED_display(2);
            leg_1L.cycle(l1x, l1y, l1z,n ,60 , 60, -250, 60, 210, -250, 0, 68);//70
            leg_2L.cycle(l2x, l2y, l2z,n ,150,0, -250, 150,150,-250,50, 20);//70
            leg_3L.cycle(l3x, l3y, l3z,n ,150,0, -250, 150,150,-250, 10, 80);//70
            leg_4L.cycle(l4x, l4y, l4z,n ,60 , 60, -250, 60, 210, -250, 72, 42);//70
            leg_1R.cycle(r1x, r1y, r1z,n ,60 , 60, -250, 60, 210, -250,40,10);//70
            leg_2R.cycle(r2x, r2y, r2z,n ,150,0, -250, 150,150,-250,90,60);//70
            leg_3R.cycle(r3x, r3y, r3z,n ,150,0, -250, 150,150,-250, 70, 40);//70
            leg_4R.cycle(r4x, r4y, r4z,n ,60 , 60, -250, 60, 210, -250, 26,96);//70
            leg_1R.ikunc_new(r1x, r1y, r1z, &r1a, &r1b, &r1c);
            leg_2R.ikunc_new(r2x, r2y, r2z, &r2a, &r2b, &r2c);
            leg_3R.ikunc_new(r3x, r3y, r3z, &r3a, &r3b, &r3c);
            leg_4R.ikunc_new(r4x, r4y, r4z, &r4a, &r4b, &r4c);
            leg_1L.ikunc_new(l1x, l1y, l1z, &l1a, &l1b, &l1c);
            leg_2L.ikunc_new(l2x, l2y, l2z, &l2a, &l2b, &l2c);
            leg_3L.ikunc_new(l3x, l3y, l3z, &l3a, &l3b, &l3c);
            leg_4L.ikunc_new(l4x, l4y, l4z, &l4a, &l4b, &l4c);
            pc.printf("array: %d\n\r",n);
            //pc.printf("q1: %f, q2: %f, q3: %f\n\r",-q1,-q2,q3);
            //pc.printf("a1: %f, a2: %f, a3: %f\n\r",a1,-a2,a3);
            leg_1R.LEG_servo(-r1a, -r1b, r1c);
            leg_2R.LEG_servo(-r2a, -r2b, r2c);
            leg_3R.LEG_servo(r3a, -r3b, r3c);
            leg_4R.LEG_servo(r4a, -r4b, r4c);
            leg_1L.LEG_servo(l1a, -l1b, l1c);
            leg_2L.LEG_servo(l2a, -l2b, l2c);
            leg_3L.LEG_servo(-l3a, -l3b, l3c);
            leg_4L.LEG_servo(-l4a, -l4b, l4c);
            
            //leg_2R.LEG_servo(-r2a, -r2b, r2c);
            ThisThread::sleep_for(100);

            n = n - velocity;
            if (n > 99){
                n =0;
            }
            if (n < -1){
                n = 99;
            }

        }
        else if(postior == 3){
            pc.printf("standing\n\r");
            stand(0);
            ThisThread::sleep_for(100);
        }

    }
}