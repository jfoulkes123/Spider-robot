//colours
color fontp = color(33,33,33);
color fonts = color(117,117,117);
color prim_light = color(207,216,220);
color accent = color(83,109,254);
color prim_dark = color(69,90,100);
color icon = color(255,255,255);
color divider = color(189,189,189);
color prim = color(96,125,139);


//image variables
PImage bluetooth_g,bluetooth_b,bluetooth_r,bluetooth_o;
PImage spider,direction;

//variables
boolean connect_circle_var = false;
float controlller_lY,controlller_lX;
int current_l,current_r;

//camera
Movie syn;
String camURL = "http://192.168.1.136:8081/";
PImage connection_lost;// = loadImage("connection_lost.jpg");
int cam_tally;
boolean camera_on= false;


//UI variables
ControlP5 cp5;
Knob Knob_left, Knob_right;
Slider slider_left,slider_right;
Textarea my_text_area;
Textfield Textfield;
Button button;



void UI_setup(){
  cp5 = new ControlP5(this);

    //colour order: non-active outline, background, active outline, font
  
  Textfield = cp5.addTextfield("Textfield")
                .setPosition(963,680)
                .setSize(236,37)
                .setAutoClear(true)
                .setColorForeground(prim)
                .setColorBackground(prim_light)
                .setFont(createFont("Calibri",15))
                .setColorActive(prim)
                .setColorValue(fontp)
                .setColorCursor(fonts)
                ;
  //colour order: non-active hover bachground, background, active background, font
  button = cp5.addButton("Submit")
              .setPosition(1199,680)
              .setSize(78,37)
              .setColorForeground(accent)
              .setColorBackground(accent)
              .setFont(createFont("Arial",18))
              .setColorActive(prim_dark)
              .setColorCaptionLabel(color(255,255,255))
              ;
  my_text_area = cp5.addTextarea("txt")
                    .setPosition(965,250)
                    .setSize(308,425)
                    .setLineHeight(20)
                    .setColorForeground(color(accent))
                    .setColorBackground(prim)
                    .setFont(createFont("Calibri",15))
                    .scroll(1)
                    .setScrollBackground(prim_dark)
                    .setScrollForeground(prim_light)
                    ;
   
  Knob_left = cp5.addKnob("Battery percentage left")
                 .setRange(0,100)
                 .setValue(50)
                 .setPosition(200,50)
                 .setRadius(70)
                 .setValue(0)
                 .setColorBackground(prim_dark)
                 .setColorForeground(accent)
                 .setFont(createFont("Arial",12))
                 .setColorCaptionLabel(color(255,255,255))
                 .lock()
                 ;
  Knob_right = cp5.addKnob("Battery percentage right")
                   .setRange(0,100)
                   .setValue(50)
                   .setPosition(650,50)
                   .setRadius(70)
                   .setValue(0)
                   .setColorBackground(prim_dark)
                   .setColorForeground(accent)
                   .setFont(createFont("Arial",12))
                   .setColorCaptionLabel(color(255,255,255))
                   .lock()
                   ;
  slider_left = cp5.addSlider("Current left")
                   .setRange(0,100)
                   .setPosition(100,30)
                   .setSize(20,150)
                   .setValue(0)
                   .setColorBackground(prim_dark)
                   .setFont(createFont("Arial",10))
                   .setColorCaptionLabel(color(255,255,255))
                   .setColorForeground(accent)
                   .lock()
                   ;
  slider_right = cp5.addSlider("Current right")
                    .setRange(0,100)
                    .setPosition(850,30)
                    .setSize(20,150)
                    .setValue(0)
                    .setColorBackground(prim_dark)
                    .setFont(createFont("Arial",10))
                    .setColorCaptionLabel(color(255,255,255))
                    .setColorForeground(accent)
                    .lock()
                    ; 
  
  
}

void camera_setup(){
  if (camera_on == true){
    syn = new Movie(this, camURL);
    syn.play();
    syn.read(); 
    if (syn.available()) {
        image(syn, 330, 250, 620, 460);
      }
    else{
        image(connection_lost,330, 250, 620, 460);
        } 
  }
  else{
    image(connection_lost,330, 250, 620, 460);
  } 
}

void cam(){
  if (camera_on == true){
    //println("cam");
    syn.play();
    syn.read(); 
    image(syn, 330, 250, 620, 460);
  //  if (syn.available()) {
  //     println("got cam");
  //     cam_tally =0;
  //      image(syn, 330, 250, 620, 460);
  //    }
  //  else{
  //      cam_tally = cam_tally+1;
  //      if (cam_tally > 40){
  //          image(connection_lost,330, 250, 620, 460);
  //      }
  //  }
  }
  else{
    image(connection_lost,330, 250, 620, 460);
  }
  
}

void display(){
    connection_circle();
    getUserInput();
    direction(lx_stick,ly_stick,l_bump,r_bump,int(Dpad));
    bluetooth_vis_update();
    bluetooth_disp(bluetooth_colour);
    spider(feet);
    meters(8,50,current_l,current_r);
    cam();
}

void create_back(){
  background(divider);
  stroke(divider);
  fill(prim_light);
  strokeWeight(6);
  rect(0,0,960,240,10);
  rect(960,0,320,240,10);
  rect(320,240,640,480,10);
  fill(prim);
  rect(960,240,320,480,10);
  rect(0,240,320,480,10);
  fill(accent);
  rect(320,240,640,480,10);

}

void spider(int i){
     int in = i;
     int arr[] = {0,0,0,0,0,0,0,0}; 
     if (i > 255){in = 255;}
     if (i < 0){in = 0;}
     deci_to_bin(in, arr);
     //println("arr: "+arr[0]+arr[1]+arr[2]+arr[3]+arr[4]+arr[5]+arr[6]+arr[7]);
     spider = loadImage("spider_diagram.png");
     noStroke();
     fill(prim_light);
     rect(348,6,253,228);
     strokeWeight(3);
     stroke(divider);
     fill(accent);
     if (arr[4] == 1){
     circle(425,32,30);
     }
     if (arr[3] == 1){
     circle(535,32,30);
     }
     if (arr[5] == 1){
     circle(400,75,30);
     }
     if (arr[2] == 1){
     circle(555,75,30);
     }
     if (arr[6] == 1){
     circle(400,175,30);
     }
     if (arr[1] == 1){
     circle(555,175,30);
     }
     if (arr[7] == 1){
     circle(425,213,30);
     }
     if (arr[0] == 1){
     circle(535,213,30);
     }
     image (spider,380,20,200,200); 
}

  
void connection_circle(){
  stroke(divider);
  strokeWeight(3);
  if (connect_circle_var==true){
    fill(0,255,0);  
  }
  else{
    fill(255,0,0);
  }
  circle(30,270,20);
  connect_circle_var =! connect_circle_var;
}


void direction(float x,float y,int rotL,int rotR, int dpad){
  float valx,valy;
  
  if (x > 100){x=100;}
  if (y > 100){y=100;}
  if (x < 0){x=0;}
  if (y < 0){y=0;}
  strokeWeight(0);
  fill(prim_light);
  rect(970,6,2289,228);
  direction = loadImage("direction_cut_out.png");
  fill(accent);
  strokeWeight(3);
  stroke(divider);
  if (rotL == 1){
  circle(1050,55,60);
  }
  if (rotR == 1){
  circle(1190,55,60);
  }
  //centre    1118,126
  if (dpad == 2){
    y = 0;
    
  }
  else if (dpad == 6){
    y = 99;
  }
  if (dpad == 4){
    x = 99;
  }
  else if (dpad == 8){
    x = 0;
  }
  controlller_lX =x;
  controlller_lY = y;
  if (y < 10){controlller_lY = 10;}
  valx =(x/100)*140;
  valy = (y/100)*140;
  image (direction,1000,0,240,240);
  strokeWeight(1);
  stroke(divider);
  circle((1050+valx),(56+valy),20);
}

void meters(int L, int R, float Lc, float Rc){
  noStroke();
  fill(prim_light);
  rect(60,20,120,180);
  rect(820,20,120,180);
  Knob_left.setValue(L);
  Knob_right.setValue(R);
  slider_left.setValue(Lc);
  slider_right.setValue(Rc);

  if (L < 10){
    Knob_left.setColorForeground(color(255,0,0));  
  }
  
  if (R < 10){
    Knob_right.setColorForeground(color(255,0,0));  
  }
  
  if (Lc > 80){
    slider_left.setColorForeground(color(255,0,0));  
  }
  
  if (Rc > 80){
    slider_right.setColorForeground(color(255,0,0));  
  }
}

void bluetooth_disp(int i){
  bluetooth_b = loadImage("bluetooth blue.png");
  bluetooth_r = loadImage("bluetooth red.png");
  bluetooth_g = loadImage("bluetooth green.png");
  bluetooth_o = loadImage("bluetooth orange.png");
  if (i==0){
    image(bluetooth_r,85, 300, 100, 150);
  }
  else if (i ==1){
    image(bluetooth_b,85, 300, 100, 150);
  }
  else if (i==2){
    image(bluetooth_g,85, 300, 100, 150);
  }
  else if (i==3){
    image(bluetooth_o,85, 300, 100, 150);
  }
  else{
    image(bluetooth_o,85, 300, 100, 150);
  }
}



  
  
  
  
