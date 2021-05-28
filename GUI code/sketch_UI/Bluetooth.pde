StringList commands;
boolean bluetooth_on,print = false;
boolean port_found = false;
int bluetooth_colour,bluetooth_connect,bluetooth_tally,b_disconnect_tally = 11;
int velocity;


Serial port;


void bluetooth_loop(){
    bluetooth_tally = bluetooth_tally+1;
    thread("data_control");
    
    if (bluetooth_tally > 3){
      bluetooth_tally =0;
      velocity = 700 + int(controlller_lY/10)+(int(controlller_lX/10)*10);
      println(velocity);
      //secondary.add_data(float(velocity));
      println("bluetooth");
      //bluetooth_send_receive();
      thread("bluetooth_send_receive");
    }  
}

void bluetooth_send_receive(){
    println("b");
    int data;
    send_data();
    println("r");
    data = receive_data();
    println("Data: "+data);
    if (data != 111 && data != 000 && data > 0 && data < 999){
      data_buffer.add_data(data);
    }
    else if (data == 000){
     
      if(b_disconnect_tally> 10){
         //bluetooth_connect = -1;
         //bluetooth_colour = 3;
      }
      else{
         b_disconnect_tally = b_disconnect_tally +1;  
      }
      
    }
    else if(data == -1){
    }
    else{
       b_disconnect_tally = 0;
       bluetooth_connect = 1; 
    }
    println("data: "+data);
  

  
}




void commands_setup(){  
  commands = new StringList();
  for (int x =0; x < 501;x++){
    commands.append("x"+x);
  }

}

int port_write(String inputString){
  int i;
  if (bluetooth_connect == 1){
    println("v");
    port.write(inputString);
    i =  1;
  }
  else{
    i =0;
  }
  return i;
}




String port_read(){
  String output;
  if (bluetooth_connect == 1 ){//|| bluetooth_connect == -1
    println("waiting");
    output = port.readString();
    println("done");
  }
  else {
    println("0");
    output = "0"; 
  }
  return output;
   
}
 
    
    
    
int receive_data(){
    //println("waiting");
   // while(true){
   if (bluetooth_connect==1 ){  //|| bluetooth_connect == -1
      String inBuffer = port.readString();
      //if (inBuffer.equals("null")){
      //  }
      //else{
      //  println(inBuffer);  
      //}
      println("1");
      if (commands.hasValue(inBuffer)){
        int[] nums = int(inBuffer.split(""));
        int num= ((nums[1]*100)+(nums[2]*10)+nums[3]);
        println(num);

        return num;
      }
      else {
        return 000;  
      }
   }
   return -1;
      

    //}
    
}
    
    
void data_emulator(int _tally){    
    println("tally:" + _tally);
    if(_tally % 50 == 0){
        secondary.add_data(211);
        println("added 211");
    }
    if(_tally% 30 == 0){
        secondary.add_data(341);
        println("added 341");
    }
    if(_tally% 100 == 0){
        primary.add_data(456);
        println("added 456");
    }
}


int send_data(){
    int out = 0;
    float data;
    if (bluetooth_connect==1 ){//|| bluetooth_connect == -1
      if(primary.end_loc_return()==0){
          //data = int(secondary.pop_data());
          //println("v");
          //port.write(65);
          out = port_write("x"+velocity);
          println("sent x"+velocity);
      }
      else{
          data = int(primary.pop_data());
          out = port_write("x"+data);
          println("sent x"+data);
      }
      
    }
    else{
      out = -1;  
    }
    return out;
}

int connect_bluetooth(){
  if(bluetooth_on == true){
    try {
      //if (port_found == true){
      //  println("stop");
      //  port.stop();
      //}
      port = new Serial(this, "COM5", 9600);
      println("port found");
      bluetooth_tally =0;
      b_disconnect_tally = 0;
      bluetooth_connect = 1;
      port_found = true;
      //It didn't execute
    }
    catch(Exception e) {
      println("port not found");
      bluetooth_connect = -1;
      //System.exit(-1);
    }  
  }
  else{
    println("bluetooth is off");
    
    bluetooth_connect= -2;  
  }
  if (print == true){
    if (bluetooth_connect == -1){
      add_textbox("--Failed to connect");  
    }
    else if (bluetooth_connect== -2){
      add_textbox("--Bluetooth is off");
    }
    else if (bluetooth_connect == 1){
      add_textbox("--Connected");
    }
    add_textbox("--======================-- ");
  }
  
  print = true;
  return bluetooth_connect;
}

void bluetooth_vis_update(){
  if (bluetooth_on == false){
    bluetooth_colour = 0;
  }
  else{
    if(bluetooth_connect == 1){
      bluetooth_colour = 1;
    }
    else if (bluetooth_connect == -1){
      bluetooth_colour = 3;
    }
    else{
      bluetooth_colour = 2;
    }    
  }
} 
