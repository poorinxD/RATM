#include <Keyboard.h>
#include <Adafruit_NeoPixel.h>
#include <TimerEvent.h>


const int shockthresh = 30;
const int upperthresh =100;  
const char enterkey = KEY_RETURN;
const char lshift = KEY_LEFT_SHIFT;

//////// Change swear words ////////////////////
const int wlsize = 7;
const String swearlist[wlsize] = {"UR MOM GAY", 
                        "SUCK MY A** MF", 
                        "TANGINA MO",
                        "Babi kau",
                        "I HERE MAE YED",
                        "CAO NI MA",
                        "CYKA BLYAT"};
////////////////////////////////////////////////

Adafruit_NeoPixel pixels(8, 6, NEO_GRB + NEO_KHZ800);
TimerEvent ledtimer;
const unsigned int ledperiod = 420;
                              
void setup() {
  pinMode(A0,INPUT);
  //Serial.begin(9600); //PLOT debug
  Keyboard.begin();
  // wait keyboard
  ledtimer.set(ledperiod,ledrandom);
  pixels.begin();
  pixels.setBrightness(80);
  rainbow();
}

void loop() {
  int shock = analogRead(A0);
  int magnitude = abs(shock);
  //Serial.println(shock); //PLOT debug
  if(magnitude > shockthresh && magnitude < upperthresh){
    keyboardout();
    rainbow();
  }
  ledtimer.update();

}//end loop

//////////Funcs///////////////////////////////
void keyboardout(){
   int num = rand()%wlsize;
   Keyboard.press(lshift);
   Keyboard.press(enterkey);
   delay(50);
   Keyboard.releaseAll();
   Keyboard.print(swearlist[num]);
   delay(100);
   Keyboard.press(enterkey);
   delay(10);
   Keyboard.releaseAll();
   delay(10);
}

void ledrandom(){
  pixels.clear();
  int cr = random(0, 255);
  int cg = random(0, 255);
  int cb = random(0, 255);
  for( int i = 0; i<8; i++){
    pixels.setPixelColor(i, cr,cg,cb);
    pixels.show();
  }   
}

void rainbow() {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256*2) {
    for(int i=0; i<8; i++) { 
      int pixelHue = firstPixelHue + (i * 65536L / 8);
      pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    }
    pixels.show();
    delay(1);
  }
}
