class FIFO{
  
//variables

int _size;
int _current_end;
int _state;
int[] _data;



//constructor

  FIFO(int FIFO_limit){
      _size = FIFO_limit;
      _current_end = 0;
      _state = -1;
      _data = new int [FIFO_limit]; 
      //for(int e = 0;  e < FIFO_limit; e++){
      //    _data[e] =0;
      //}
  
  }

//functions
  
  int add_data(float input){
      int out_return = 1;
      if (_state != 1){
          budge_up();
          int temp = int(input *1000);
          _data[0] = temp;
          _current_end = _current_end +1;
          state_update();
          out_return = 1;
      }
      else {
          out_return = -1;
      }
      return out_return;
      
  
  
  }
  
  void force_add(float input){
    budge_up();
    int temp = int(input *1000);
    _data[0] = temp;
    _current_end = _current_end +1;
    state_update();

  }


  float pop_data(){
    int out_return;
    if(_state!= -1){
        int temp = _data[_current_end-1];
        float tempf= temp/1000;
        out_return = int(tempf);
        _data[_current_end-1] = 0;
        _current_end = _current_end -1;
    }
    else{
        out_return = -1;
    }
    state_update();
    return out_return;

  } 
  
  float read(int location){
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
  
  
   float read_end(){

    int temp = _data[_current_end-1];
    float tempf= temp/1000;
    return tempf;

  }

  int size_return(){
    return _size;
  }

  int state_return(){
    return _state;
  }

  int end_loc_return(){
    return _current_end;
  } 
  
  void purge(){
    for(int i= _size; i>0; i--){
        _data[i-1] = 0;
    }
    _current_end = 0;
    state_update();
  }


  void budge_up(){
    for(int i= _current_end; i>0; i--){
        _data[i] = _data[i-1];
    }
    _data[0] = 0;
    _data[_size-1] = 0;

  }
  
  
  void state_update(){
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
  
  
  
  
}
