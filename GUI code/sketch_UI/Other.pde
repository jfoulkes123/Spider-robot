PImage loading;
int feet;

void setup_gen(){
  background(255,255,255);
  loading = loadImage( "loading_3.png" );
  connection_lost = loadImage("connection_lost.jpg");
  image(loading,0,0,width,height);
  //background(255,255,255);
  primary = new FIFO(20);
  secondary = new FIFO(30);
  data_buffer = new FIFO(20);
  commands_setup();
  UI_setup();
  controller_setup();
  camera_setup();
  input_setup();
  connect_bluetooth();
  frameRate(10);
  create_back();
  display();
  
}

void data_control(){
  int DATA = int(data_buffer.pop_data());
  if (DATA != -1){
    if (DATA > 119 && DATA < 376){
      feet = int(DATA-120);
    }
    else if (DATA > 399 && DATA < 501){
      if (DATA < 450){
        current_r = (int(DATA-400))*2;  
      }
      else{
        current_l = (int(DATA-450))*2;  
      }
    }
  }
}

void deci_to_bin(int in, int[] out){

    for(int i=0; in>0; i++){    
    out[i]=in%2;    
    in= in/2;  
    }
}

void keyPressed(){
    if (keyCode == ENTER){
      if (Textfield.isFocus() == true){
        Submit();      
      }
    }
  
}
