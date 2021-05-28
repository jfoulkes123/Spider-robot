#ifndef SERVO_H
#define SERVO_H

#include "mbed.h"

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE
#define TIMING_BLOCK_START 0x06


class SERVO{

    public:
    SERVO(int Min, int Max, int Position,bool side, int center);
    void setup(void);
    void setServo(float angle);
    void setServo_default(int num);
    float num_to_angle(int num);
    int _Center;
    int _Min;
    int _Max;
    int _Position;
    int _Side;

    protected:

    PinName _SDA;
    PinName _SCL;
    int addr8bit_r = 0x40 << 1;     // default 8-bit I2C address, 0x80 
    int addr8bit_l = 0x41 << 1;
    uint8_t retVal;
    void write8(uint8_t address, uint8_t data);
    char read8(char address);
    void reset(void);
    void setPrescale(uint8_t prescale);
    void setPWMFreq(float freq);
    void setServoOnOff(uint8_t num, uint16_t on, uint16_t off);


};

#endif
