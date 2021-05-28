#include "mbed.h"
#include "SERVO.h"
#include <iostream>


I2C _i2c(PB_9,PB_8);


SERVO::SERVO(int Min, int Max, int Position, bool side, int center)

{
    this->_Min = (75+((Min+90)*2.63888888));
    this->_Max = (75+((Max+90)*2.63888888));
    this->_Position = Position;
    this->_Side = side;   
    this->_Center = center;

}// setup


void SERVO::write8(uint8_t address, uint8_t data)
{
    char cmd[2];
    cmd[0] = address;
    cmd[1] = data;
    
    if (_Side == true){
        _i2c.write(addr8bit_l, cmd, 2);
    }
    else{
        _i2c.write(addr8bit_r, cmd, 2);
    }
}
 
char SERVO::read8(char address)
{
    if(_Side == true){
        retVal = _i2c.write(addr8bit_l, &address, 1); 
        char rtn;
        retVal = _i2c.read(addr8bit_l, &rtn, 1);
        return rtn;
    }
    else{ 
        retVal = _i2c.write(addr8bit_r, &address, 1); 
        char rtn;
        retVal = _i2c.read(addr8bit_r, &rtn, 1);
        return rtn;
    }

}

void SERVO::reset(void)
{
    write8(PCA9685_MODE1, 0x0);
}

void SERVO::setPrescale(uint8_t prescale) 
{
    uint8_t oldmode = read8(PCA9685_MODE1);
    uint8_t newmode = (oldmode & 0x7F) | 0x10; // sleep
    write8(PCA9685_MODE1, newmode); // go to sleep
    ThisThread::sleep_for(5) ; 
    write8(PCA9685_PRESCALE, prescale); // set the prescaler
    write8(PCA9685_MODE1, oldmode); 
    ThisThread::sleep_for(5) ; 
    write8(PCA9685_MODE1, oldmode | 0xa1);
}

void SERVO::setPWMFreq(float freq)
{
    float prescaleval = 25000000;
    prescaleval /= 4096;
    prescaleval /= freq;
    uint8_t prescale = floor(prescaleval  + 0.5) - 1;
    setPrescale(prescale);
}

// function to set servo number (0-15) on and off count values 
// Range 0-4095 count for 1 ms = 205 count for 2 ms = 410
void SERVO::setServoOnOff(uint8_t num, uint16_t on, uint16_t off)
{
    char cmd[5] ;   // 
    cmd[0] = TIMING_BLOCK_START + (4 * num) ; // address of the low byte of servo 
    cmd[1] = on;                     // low byte of on value 
    cmd[2] = (on >> 8);              // high byte of on 
    cmd[3] = off;                    // low byte of off  
    cmd[4] = (off >> 8);             // high byte of off 
    if(_Side == true){
        retVal = _i2c.write(addr8bit_l, cmd, 5);     // write the address and 4 bytes   
    }
    else{ 
        retVal = _i2c.write(addr8bit_r, cmd, 5);     // write the address and 4 bytes   
    }
    return;

}

void SERVO::setup(void){
    if(_Side == true){
        _i2c.frequency(400000) ; // set the bus frequency 
        reset() ;
        cout<<"12345"<<endl;
        setPWMFreq(50.0) ;
    }
    else{
        _i2c.frequency(400000) ; // set the bus frequency 
        reset() ;
        cout<<"12345"<<endl;
        setPWMFreq(50.0) ;
    }
}

void SERVO::setServo(float angle){
    // if(angle > _Max){
    //     angle = _Max; 
    // }
    // else if (angle < _Min){
    //     angle = _Min;
    // }
    int num = ((((angle)*2.466666))+(_Center));
    setServoOnOff(_Position, 0, num);
    return;
}

void SERVO::setServo_default(int num){
    setServoOnOff(_Position, 0, num);
    return;
}

float SERVO::num_to_angle(int num){
    float angle = ((num-_Center)/2.466666666);
    return angle;    
}

