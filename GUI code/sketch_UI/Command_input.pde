String text;
StringList input_commands;

void Submit(){
  //println("This is the text you typed");
  text = cp5.get(Textfield.class, "Textfield").getText();
  Textfield.clear();
  //println(text);
  add_textbox("User: "+text);
  Process_input(text);
}

void input_setup(){
  input_commands = new StringList();
  input_commands.append("");
  input_commands.append("toggle bluetooth");
  input_commands.append("help");
  input_commands.append("toggle stream  N");
  input_commands.append("toggle stream quality  N");
  input_commands.append("stand");
  input_commands.append("intimidate");
  input_commands.append("walk");
  input_commands.append("connect bluetooth");
}

void Process_input(String input_text){
  if((input_commands.get(1)).equals(input_text)){
    add_textbox("--======================-- ");
    add_textbox("--Bluetooth toggled");
    if (bluetooth_on == true){
      bluetooth_on = false;
      add_textbox("--Bluetooth is off");
    }
    else if (bluetooth_on == false){
      bluetooth_on = true;
      add_textbox("--Bluetooth is on");
    }
    add_textbox("--======================-- ");
  }
  else if ((input_commands.get(8)).equals(input_text)){
    add_textbox("--======================-- ");
    add_textbox("--Trying bluetooth connection");
    add_textbox("--Please wait");
    thread("connect_bluetooth");
    //if (CONNECT == -1){
    //  add_textbox("--Failed to connect");  
    //}
    //else if (CONNECT== -2){
    //  add_textbox("--Bluetooth is off");
    //}
    //else if (CONNECT == 1){
    //  add_textbox("--Trying bluetooth connection");
    //}
  }
    
  else if ((input_commands.get(5)).equals(input_text)){
    add_textbox("--======================-- ");
    add_textbox("--Standing");
    add_textbox("--======================-- ");
    primary.add_data(630);
    primary.add_data(630);
    primary.add_data(630);
  }
  
  else if ((input_commands.get(6)).equals(input_text)){
    add_textbox("--======================-- ");
    add_textbox("--Intimidating");
    add_textbox("--======================-- ");
    primary.add_data(620);
    primary.add_data(620);
    primary.add_data(620);
  }
  else if ((input_commands.get(7)).equals(input_text)){
    add_textbox("--======================-- ");
    add_textbox("--Walking");
    add_textbox("--======================-- ");
    primary.add_data(610);
    primary.add_data(610);
    primary.add_data(610);
  }
    
  else if ((input_commands.get(2)).equals(input_text)){
    add_textbox("--These are the possible commands:");
    add_textbox("--======================-- ");
    for(int i=1; i< input_commands.size(); i++){
      add_textbox("-- "+input_commands.get(i));
    }
    add_textbox("--======================--");
  }
  
  else if ((input_commands.get(0)).equals(input_text)){}
  
  //else if (Command3.equals(input_text)){
  //      add_textbox("--Stream toggled");
  //      if (stream == 1){
  //        stream =0;
  //        add_textbox("--Stream turned off");
  //      }
  //      else if (stream == 0){
  //        stream = 1;
  //        add_textbox("--Stream turned on");          
  //      }
  // }
  
  //  else if (Command4.equals(input_text)){
  //      add_textbox("--Stream quality toggled");
  //      if (stream_quality == 1){
  //        stream_quality =0;
  //        camURL = "http://192.168.0.45:8082/";
  //        add_textbox("--Stream quality low");
  //      }
  //      else if (stream_quality == 0){
  //        stream_quality =1;
  //        camURL = "http://192.168.0.45:8081/";
  //        add_textbox("--Stream quality high");          
  //      }
  //}
  
  else{
    String out = ("--Unknown Input: "+ input_text);
    add_textbox(out);
      
  }
  
}

void add_textbox(String input){
  String s = my_text_area.getText();
  s = (s + "\n\r" +input);
  my_text_area.setText(s); 
}
