import processing.serial.*;
import processing.video.*;
import controlP5.*;
import net.java.games.input.*;
import org.gamecontrolplus.*;
import org.gamecontrolplus.gui.*;

FIFO primary;
FIFO secondary;
FIFO data_buffer;

void setup(){
  size(1280,720);
  setup_gen();
  
}




void draw(){
  bluetooth_loop();
  display(); 
}
