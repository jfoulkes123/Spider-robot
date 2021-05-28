#ifndef LEG_H
#define LEG_H

#include "mbed.h"
#include "SERVO.h"
#include <cstdint>

class LEG{

    private:
    float L1;
    float l2;
    float L3;
    int ankle;
    int position;
    bool side;
    int para[6];
    int center[3];


    public:
    SERVO servo_side = SERVO(para[0],para[1],(position*4),side,center[0]);
    SERVO servo_hip = SERVO(para[2],para[3],(position*4+1),side,center[1]);
    SERVO servo_knee = SERVO(para[4],para[5],(position*4+2),side,center[2]);
    LEG(float _L1, float _L2, float _L3, int _ankle, int _position, bool _side, int16_t _para[], uint16_t _center[]);
    void setup(void);
    void ikunc(float x, float y, float z,double* _q1, double* _q2, double* _q3);
    void ikunc_new(float x, float y, float z, double *_q1, double *_q2, double *_q3);
    void LEG_servo(double q1, double q2, double q3);
    //void cycle_data(float* pos_x, float* pos_y, float* pos_z,float _x, float _y, float _z, int x_rest, int y_rest, int z_rest, int start, int stop, float cycle_time, float total_dist, float increment, float angle);
    void cycle(int16_t &x, int16_t &y, int16_t &z,int a, int xstart, int ystart, int zstart, int xstop, int ystop, int zstop, int start, int stop);
    void cycle_data_new(float* pos_x_output, float* pos_y_output, float* pos_z_output,int16_t _x_start, int16_t _y_start, int16_t _z_start,int16_t _x_stop,int16_t _y_stop,int16_t _z_stop, int16_t x_rest, int16_t y_rest, int16_t z_rest, uint8_t start, uint8_t stop);
    //void limp(void);
    //void angle_to_coord(float q1, float q2, float q3, float *_x, float *_y, float *_z);
    float cosd(float d);
    float sind(float d);
    void fkunc(int q1,int q2,int q3, float &x, float &y,float &z);

};


#endif
