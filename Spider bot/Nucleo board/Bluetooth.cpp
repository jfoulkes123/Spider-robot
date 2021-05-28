
#include"mbed.h"
#include"FIFO.h"
#include <iostream>


void data_emulator(int _tally, FIFO* _primary, FIFO* _secondry, Serial* _pc){
        if(_tally % 50 == 0){
            _secondry->add_data(211);
            //_pc->printf("added 211\n\r");
        }
        if(_tally% 30 == 0){
            _secondry->add_data(341);
            //_pc->printf("added 341\n\r");
        }
        if(_tally% 100 == 0){
            _primary->add_data(456);
            //_pc->printf("added 456\n\r");
        }
}


void send_data(FIFO* _primary, FIFO* _secondry,Serial* _pc, Serial* _serial2){
    int data;
    //_pc->printf("2\n\r");
    if(_primary->end_loc_return()==0){
        if (_secondry->end_loc_return()==0){
            _serial2->printf("x111");
            //_pc->printf("Sent x111\n\r");
        }
        else{
            data = _secondry->pop();
            //cout<<"secondary"<<endl;
            _serial2->printf("x%d",data);
            cout << "xs" <<data<<endl;
            //_pc->printf("Sent x%d\n\r",data);
        }
    }
    else{
        data = _primary->pop();
        _serial2->printf("x%d",data);
        cout << "xp" <<data<<endl;
        //_pc->printf("Sent x%d\n\r",data);
        }

}

int read_data(Serial* _pc,Serial* _serial2){
    char buffer[4];
    int input;
    _serial2->gets(buffer,sizeof(buffer)+1);
    if (buffer[0] == 'x' || buffer[1] == 'x' || buffer[2] == 'x' || buffer[3] == 'x' ){
        char a = buffer[0];
        int y = 0;
        while(a != 'x' or y >(sizeof(buffer)+1)){
            y = y+1;
            a = buffer[y];   
        }
        int x=0;
        y++;
        char buff[3];
        while (x < 3){
            buff[x]=buffer[y];
            if (y+1 > 3){
                y= 0;
            }
            else{
                y=y+1;
            }
            x=x+1;
        }
        sscanf(buff, "%d", &input);
        return input;
        //data.add_data(input);
    }
    else{
        return 0;
    }    
}
