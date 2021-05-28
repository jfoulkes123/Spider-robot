#include "mbed.h"
#include "FIFO.h"
#include <cstring>

//#include <string>

FIFO::FIFO(int FIFO_limit){
    this->_size = FIFO_limit;
    this->_current_end = 0;
    this->_state = -1;
    this->_data = new int[FIFO_limit];


}// setup

int FIFO::add_data(float input){
    int out_return = 1;
    if (_state != 1){
        budge_up();
        int temp = input *1000;
        this->_data[0] = temp;
        this->_current_end = this->_current_end +1;
        state_update();
        out_return = 1;
    }
    else {
        out_return = -1;
    }
    return out_return;
    


}

void FIFO::force_add(float input){
    budge_up();
    int temp = input *1000;
    this->_data[0] = temp;
    this->_current_end = this->_current_end +1;
    state_update();

}

float FIFO::pop(void){
    int out_return;
    if(_state!= -1){
        int temp = _data[_current_end-1];
        float tempf= temp/1000;
        out_return = tempf;
        _data[_current_end-1] = NULL;
        this->_current_end = this->_current_end -1;
    }
    else{
        out_return = -1;
    }
    state_update();
    return out_return;

}

float FIFO::read(int location){
    int temp = 0;
    float tempf;

    if (location > _current_end-1){
        temp = _data[_current_end-1];        
    }

    else if (location < 0){
        temp = _data[0];
    }

    else{
        temp = _data[location];
    }
    tempf = temp/1000;
    return tempf;
}


float FIFO::read_end(void){

    int temp = _data[_current_end-1];
    float tempf= temp/1000;
    return tempf;

}

int FIFO::size_return(void){
    return _size;
}

int FIFO::state_return(void){
    return _state;
}

int FIFO::end_loc_return(void){
    return _current_end;
}


void FIFO::purge(void){
    for(int i= _size; i>0; i--){
        _data[i-1] = NULL;
    }
    _current_end = 0;
    state_update();
}


void FIFO::budge_up(void){
    for(int i= _current_end; i>0; i--){
        _data[i] = _data[i-1];
    }
    _data[0] = NULL;
    _data[_size-1] = NULL;

}

void FIFO::state_update(void){
    if(_current_end >= _size){
        _state = 1;
        _current_end = _size;
    }
    else if(_current_end == 0){
        _state = -1;
    }
    else{
        _state = 0;
    }
}


