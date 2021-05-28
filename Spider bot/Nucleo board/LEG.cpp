#include "mbed.h"
#include "LEG.h"
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <iostream>
#define PI 3.141592653589793238462643

LEG::LEG(float _L1, float _L2, float _L3,  int _ankle, int _position, bool _side, int16_t _para[], uint16_t _center[]){
    this->L1 = _L1;
    this->l2 = _L2;
    this->L3 = _L3;
    this->ankle = _ankle;
    this->side = _side;
    this->position = _position;
    for (int e = 0 ; e<6; e++){
        this->para[e] = _para[e];
    }
    for (int i = 0; i<3; i++){
        this->center[i] = _center[i];
    }
    this->servo_side._Min = this->para[0];
    this->servo_hip._Min = this->para[2];
    this->servo_knee._Min = this->para[4];

    this->servo_side._Max  = this->para[1];
    this->servo_hip._Max = this->para[3];
    this->servo_knee._Max = this->para[5];

    this->servo_side._Position = (this->position)*4;
    this->servo_hip._Position = ((this->position)*4)+1;
    this->servo_knee._Position = ((this->position)*4)+2;

    this->servo_side._Side = this->side;
    this->servo_hip._Side = this->side;
    this->servo_knee._Side = this->side;

    this->servo_side._Center = this->center[0];
    this->servo_hip._Center = this->center[1];
    this->servo_knee._Center = this->center[2];

}

void LEG::setup(void){
    servo_hip.setup();
    servo_knee.setup();
    servo_side.setup();
    cout<<"6"<<endl;
    return;
}

void LEG::LEG_servo(double q1, double q2, double q3){
    servo_side.setServo(q1);
    servo_hip.setServo(q2);
    servo_knee.setServo(q3);
    return;
}

// void LEG::cycle_data(float *pos_x, float *pos_y, float *pos_z, int _x, int _y, int _z, int x_rest, int y_rest, int z_rest, int start, int stop, float cycle_time, float total_dist, float increment,float angle){
//     int cycle;
//     for (int u = 0; u < 100; u++){
//          pos_x[u]=x_rest;
//          pos_y[u]=y_rest;
//          pos_z[u]=z_rest;
        
//     }
//     float x = _x,y = _z,z = _z;
//     if (start > stop){
//         cycle = (100 - start) + stop;
//     }
//     else{
//         cycle = stop - start;
//     }
//     float on_time = cycle_time * (cycle/100);
//     float dist_inc = total_dist/cycle;
//     //float pos[3][100];
//     pos_x[start] = x;
//     pos_y[start] = y;
//     pos_z[start] = z;
//     int i = start;
//     float theta = 90 - angle;
//     if (start  > stop){
//         for (i = 0; i < 100-start; i = i + increment){
//             //y=y+(increment*dist_inc);
//             //z=z+(increment*dist_inc);
//             for(int e = 0; e < increment; e++){
//                 pos_x[i+start+e]=x;
//                 pos_y[i+start+e]=y;
//                 pos_z[i+start+e]=z;
//             }
//             x=x+(increment*dist_inc);
//             if (x > _x+total_dist){
//                 x = _x+total_dist;
//             }
//         }
        
//         for (i = 0; i < stop; i = i + increment){
//             //y=y+(increment*dist_inc);
//             //z=z+(increment*dist_inc);
//             for(int e = 0; e < increment; e++){
//                 pos_x[i+e]=x;
//                 pos_y[i+e]=y;
//                 pos_z[i+e]=z;
//             }
//             x=x+(increment*dist_inc);
//             if (x > _x+total_dist){
//                 x = _x+total_dist;
//             }
//         }
        
//     }
//     else{
//         for (i = 0; i < stop- start; i = i + increment){
//             //y=y+(increment*dist_inc);
//             //z=z+(increment*dist_inc);
//             for(int e = 0; e < increment; e++){
//                 pos_x[i+start+e]=x;
//                 pos_y[i+start+e]=y;
//                 pos_z[i+start+e]=z;
//             }
//             x=x+(increment*dist_inc);
//             if (x > _x+total_dist){
//                 x = _x+total_dist;
//             }
//         }

//     }
//     int o;
//     int g = 0;
//     if (start > stop){
//         for (o = 0; (o < 8) && (o+stop < start); o ++){
//             pos_x[stop + o]=x;
//             pos_y[stop + o]=y;
//             pos_z[stop + o]=z;
//         }


//     }
//     else{
        
//         //while(1){
//         for (o = 0; (o < 10) && (o+stop != start); o ++){
//             //if (o+stop =! start){
//                 if ((stop + o) == 101 ){
//                     g = 0;
//                     pos_x[0]=x;
//                     pos_y[0]=y;
//                     pos_z[0]=z;
    
//                 }
//                 else if ((stop+o) > 101){
//                     pos_x[g]=x;
//                     pos_y[g]=y;
//                     pos_z[g]=z;
    
//                 }
//                 else{
                    
//                     pos_x[stop + g]=x;
//                     pos_y[stop + g]=y;
//                     pos_z[stop + g]=z;
//                 }
//                 g++;
//             //}
//         }
//     }
//     return;
// }
void LEG::cycle(int16_t &x, int16_t &y, int16_t &z, int a, int xstart, int ystart, int zstart, int xstop, int ystop, int zstop, int start, int stop){
    bool in = false;
    float cycle, temp;
    if (stop > start){
        if (a> start && a <stop){
            in = true;
        }
        if(in == true){
            cycle  = stop-start;
            temp = a - start;
            float incx = (xstop-xstart)/cycle;
            float incy = (ystop-ystart)/cycle;
            float incz = (zstop-zstart)/cycle;
            x = int(xstart + incx*temp);
            y = int(ystart + incy*temp);
            z = int(zstart + incz*temp);
            
        }
        else{
            cycle = 100-stop+start;
            float incx = (xstop-xstart)/cycle;
            float incy = (ystop-ystart)/cycle;
            float incz = (zstop-zstart)/cycle;
            if(a<stop){
                temp = 100 - stop;
                x = xstop - incx*temp;
                y = ystop - incy*temp;
                z = zstop - incz*temp;
            }
            else{
                temp = a - stop;
                x = xstop - incx*temp;
                y = ystop - incy*temp;
                z = zstop - incz*temp;                
            }
        }
    }
    else{
        if (a> start xor a<stop){
            in = true;
        }
        if(in == true){
            cycle = 100 - start+stop;
            float incx = (xstop-xstart)/cycle;
            float incy = (ystop-ystart)/cycle;
            float incz = (zstop-zstart)/cycle;
            if(a<start){
                temp = 100 - start + a;
                x = xstart+incx*temp;
                y = ystart+incy*temp;
                z = zstart+incz*temp;
            }
            else{
                temp = a - start;
                x = xstart+incx*temp;
                y = ystart+incy*temp;
                z = zstart+incz*temp;
            }
        }
        else{
            cycle = start - stop;
            temp = a - stop;
            float incx = (xstop-xstart)/cycle;
            float incy = (ystop-ystart)/cycle;
            float incz = (zstop-zstart)/cycle;
            x = xstop - incx*temp;
            y = ystop - incy*temp;
            z = zstop - incz*temp;
        }
        
    }
}

void LEG::cycle_data_new(float* pos_x_output, float* pos_y_output, float* pos_z_output,int16_t _x_start, int16_t _y_start, int16_t _z_start,int16_t _x_stop,int16_t _y_stop,int16_t _z_stop, int16_t x_rest, int16_t y_rest, int16_t z_rest, uint8_t start, uint8_t stop){

    uint16_t cycle;
    for (int u = 0; u < 100; u++){
         pos_x_output[u]=x_rest;
         pos_y_output[u]=y_rest;
         pos_z_output[u]=z_rest;
        
    }
    float x = _x_start,y = _y_start,z = _z_start;
    if (start > stop){
        cycle = (100 - start) + stop;
    }
    else{
        cycle = stop - start;
    }
    //float on_time = cycle_time * (cycle/100);
    float dist_inc_x = (_x_stop-_x_start)/cycle;
    float dist_inc_y = (_y_stop-_y_start)/cycle;
    float dist_inc_z = (_z_stop-_z_start)/cycle;
    //float pos[3][100];
    pos_x_output[start] = x;
    pos_y_output[start] = y;
    pos_z_output[start] = z;
    int i = start;

    if (start  > stop){
        for (i = 0; i < 100-start; i++){
            pos_x_output[i+start]=x;
            pos_y_output[i+start]=y;
            pos_z_output[i+start]=z;
            y=y+(dist_inc_y);
            z=z+(dist_inc_z);
            x=x+(dist_inc_x);
            if (_x_start < _x_stop){
                if (x > _x_stop){
                    x = _x_stop;
                }
            }
            else{
                if (x < _x_stop){
                    x = _x_stop;
                }
            }
            if (_y_start < _y_stop){
                if (y > _y_stop){
                    y = _y_stop;
                }
            }
            else{
                if (y < _y_stop){
                    y = _y_stop;
                }
            }
            if (_z_start < _z_stop){
                if (z > _z_stop){
                    z = _z_stop;
                }
            }
            else{
                if (z < _z_stop){
                    z = _z_stop;
                }
            }


        }
        
        for (i = 0; i < stop; i++){
            pos_x_output[i]=x;
            pos_y_output[i]=y;
            pos_z_output[i]=z;
            y=y+(dist_inc_y);
            z=z+(dist_inc_z);
            x=x+(dist_inc_x);
            if (x > _x_stop){
                x = _x_stop;
            }
            if (y > _y_stop){
                y = _y_stop;
            }
            if (z > _z_stop){
                z = _z_stop;
            }


        }
        
    }
    else{
        for (i = 0; i < stop- start; i++){
            pos_x_output[i+start]=x;
            pos_y_output[i+start]=y;
            pos_z_output[i+start]=z;
            y=y+(dist_inc_y);
            z=z+(dist_inc_z);
            x=x+(dist_inc_x);
            if (_x_start < _x_stop){
                if (x > _x_stop){
                    x = _x_stop;
                }
            }
            else{
                if (x < _x_stop){
                    x = _x_stop;
                }
            }
            if (_y_start < _y_stop){
                if (y > _y_stop){
                    y = _y_stop;
                }
            }
            else{
                if (y < _y_stop){
                    y = _y_stop;
                }
            }
            if (_z_start < _z_stop){
                if (z > _z_stop){
                    z = _z_stop;
                }
            }
            else{
                if (z < _z_stop){
                    z = _z_stop;
                }
            }

        }

    }
    int o;
    int g = 0;
    if (start > stop){
        for (o = 0; (o < 8) && (o+stop < start); o ++){
            pos_x_output[stop + o]=x;
            pos_y_output[stop + o]=y;
            pos_z_output[stop + o]=z;
        }


    }
    else{
        
        //while(1){
        for (o = 0; (o < 10) && (o+stop != start); o ++){
            //if (o+stop =! start){
                if ((stop + o) == 101 ){
                    g = 0;
                    pos_x_output[0]=x;
                    pos_y_output[0]=y;
                    pos_z_output[0]=z;
    
                }
                else if ((stop+o) > 101){
                    pos_x_output[g]=x;
                    pos_y_output[g]=y;
                    pos_z_output[g]=z;
    
                }
                else{
                    
                    pos_x_output[stop + g]=x;
                    pos_y_output[stop + g]=y;
                    pos_z_output[stop + g]=z;
                }
                g++;
            //}
        }
    }
    return;
}


void LEG::ikunc(float x, float y, float z, double *_q1, double *_q2, double *_q3){

    double x2,y2,z2;
    double L0 = 50, L02 = 50*50;
    double L12,L22,L32,L2,l22;
    double temp;
    double q1r,q2r,q3r,q1;
    double angle;

    q1 = atan((abs(y)/abs(x)))*(180.0000/PI);
    q1r = 90-atan((abs(y)/abs(x)))*(180.0000/PI);

    double _x = abs(x) - (50.0000*sind(q1r));
    double _y = abs(y) - (50.0000*cosd(q1r));
    
    x2 = _x*_x;
    z2 =z*z;
    y2 = _y*_y;
    double x_temp = sqrt((x2)+(y2));
    double x2_temp = x_temp*x_temp;
    
    l22 = l2*l2;
    L12 = L1 * L1;
    L32 = L3 * L3;
    temp = 2*l2*L3*(cosd(ankle));
    L2 = L32+l22-(temp);
    L2 = sqrt(L2);
    
    L22 = L2 * L2;
    angle = acos((l22+L22-L32)/(2*l2*L2));
    q3r = -acos((x2_temp+z2-L12-L22)/(2*L1*L2));
    q2r = atan(z/x_temp)-(atan((L2*sin(q3r))/(L1+(L2*cos(q3r))) ) );

    *_q3 = -1*((q3r*(180.0000/PI))+(angle*(180.0000/PI)));
    *_q2 = -1*(q2r*(180.00000/PI));
    *_q1 = q1;
    return;

}

void LEG::ikunc_new(float x, float y, float z, double *_q1, double *_q2, double *_q3){
    double q1_a,q1_b, q2, q3;
    double out =1;
    ikunc(x,y,z,&q1_a,&q2,&q3);
    q1_b = 180 - q1_a;

    if (x > 0){
            out = q1_a;
    }
    else{
        out = q1_b;
    }
    if(y < 0){
        out = out *-1;
    }
    *_q1 = out;
    *_q2 = q2;
    *_q3 = q3;
    return;
}

float LEG::cosd(float d){
  float out = cos(d*(PI/180));
  return out;
}

float LEG::sind(float d){
  float out = sin(d*(PI/180));
  return out;    
}

void LEG::fkunc(int q1,int q2,int q3, float &x, float &y,float &z){
    q2= q2*-1;
    float L0 = 50;
    float qa = 90-q3+q2;
    float temp = (L0 + (cosd(q2)*L1) + (sind(qa)*(l2+L3)));
    y = temp * sind(q1);
    x = temp * cosd(q1);
    z = (sind(q2)*L1) - (cosd(qa)*(l2+L3));
    return;
}


// void LEG::limp(void){
//     servo_hip.setServo_default(1);
//     servo_knee.setServo_default(1);
//     servo_side.setServo_default(1);
//     return;
// }

// void LEG::angle_to_coord(float q1, float q2, float q3, float *_x, float *_y, float *_z){
//     return;
// }
