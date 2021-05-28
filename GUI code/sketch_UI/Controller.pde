ControlDevice cont;
ControlIO control;
int controller_connect;
float a_but,b_but,x_but,y_but;
float lx_stick = 50,ly_stick = 50,rx_stick,ry_stick;
float Dpad;
int l_bump,r_bump;


void controller_setup(){
  control = ControlIO.getInstance(this);
  cont = control.getMatchedDeviceSilent("xone_cont");
  if (cont == null) {
      println("No controller connected");
      controller_connect = 0;
      //System.exit(-1);
    }
  else{
    controller_connect = 1;
    println("controller connected");  
  }
  
  
}


public void getUserInput() {
  if (cont != null){
    //a_but = cont.getButton("A_button").getValue();
    //b_but = cont.getButton("B_button").getValue();
    //x_but = cont.getButton("X_button").getValue();
    //y_but = cont.getButton("Y_button").getValue();
    l_bump = int(map(cont.getButton("LB_button").getValue(), 0, 8, 0, 1));
    r_bump = int(map(cont.getButton("RB_button").getValue(), 0, 8, 0, 1));
    lx_stick = (map(cont.getSlider("LX_output").getValue(), -1, 1, 0, 99));
    if (lx_stick < 60 && lx_stick > 40){lx_stick = 50;}
    ly_stick = (map(cont.getSlider("LY_output").getValue(), -1, 1, 0, 99));
    if (ly_stick < 60 && ly_stick > 40){ly_stick = 50;}
    rx_stick = (map(cont.getSlider("RX_output").getValue(), -1, 1, 0, 99));
    ry_stick = (map(cont.getSlider("RY_output").getValue(), -1, 1, 0, 99));
    Dpad = cont.getHat("DPAD_output").getValue();
  }
}
