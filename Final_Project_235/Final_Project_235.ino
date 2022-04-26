#include <Adafruit_NeoPixel.h>

int numofPixels=60;
int npPin=3;
Adafruit_NeoPixel strip(numofPixels, npPin);

int ledPosition=0;

boolean switchColor=true;

//position
int index=0;

//global variable for the led number for n in colorsweep
int num=0;

int prevButtonState;
int prevButtonState2;
int buttonState;
int buttonPin=12;
int state=0;

int buttonState2;
int buttonPin2=11;

unsigned long startTime= millis();
unsigned long endTime= millis();
int interval=40;

uint32_t blue = strip.Color(0,0,255);
uint32_t white = strip.Color(0,255,255);
uint32_t blue2 = strip.Color(0,0,255);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
strip.begin();
//strip.clear();
strip.setBrightness(255);

}

void loop() {
    prevButtonState = buttonState;
  buttonState = debounce(buttonPin, prevButtonState);

  prevButtonState2 = buttonState2;
  buttonState2 = debounce(buttonPin2, prevButtonState2);

  //Serial.println(buttonState);
  Serial.println(buttonState);

  //toggle if statement

  if (buttonState == HIGH && prevButtonState == LOW) {
    state = 1;
  }
    if (buttonState2 == HIGH && prevButtonState2 == LOW) {
      state = 2;
    }
//    if (state < 0) {
//      state = 2;
//    }

switch (state) {

    case 0:
      strip.clear();
      strip.show();
      break;

    //make all blue
    case 1:
      strip.setPixelColor(index,0,0,255);
strip.show();

endTime=millis();

if(endTime-startTime> interval){
  startTime=millis();
  ledPosition +=1;


  if (ledPosition> strip.numPixels()){
   ledPosition=0;
  }

for(int i =0; i< strip.numPixels();i++){

  if(i == ledPosition){
    strip.setPixelColor(i,0,0,255);
    
  }
}

  for(int  i = 0; i < strip.numPixels();i++){
    if( i != ledPosition){
      strip.setPixelColor(i,0,0,0);
    }
  }
  
}
      
      strip.show();
      break;//make
  
    case  2:
      endTime=millis();


if(endTime-startTime>= interval){
  num++;
  colorSweep(blue, white, blue2, num);
  strip.show();
  startTime=millis();
  
}
 strip.show();
      break;
}
}


void colorSweep(uint32_t aColor1,  uint32_t aColor2, uint32_t aColor3, int n){

uint32_t c1;
uint32_t c2;
uint32_t c3;

if(n%3==0){
  c1 = aColor1;
  c2= aColor2;
  c3= aColor3;

}

if(n%3==1){
  c1 = aColor3;
  c2= aColor1;
  c3= aColor2;
}

if(n%3==2){
  c1 = aColor2;
  c2= aColor3;
  c3= aColor1;
}

for(int i =0; i <strip.numPixels();i++){
 int  n=i;
    if(n%3==0){
  strip.setPixelColor(i,c1);
  strip.show();
}

else if (n%3==1){
  strip.setPixelColor(i,c2);
  strip.show();
}

else if(n%3==2){
strip.setPixelColor(i,c3);
strip.show();
}
}
}
     





boolean debounce(int aButPin, boolean aPrevState) {
  // get the bouncy reading of the button
  boolean aButtonState = digitalRead(aButPin);

  // if the button state is different from what it
  // was last frame, then delay so it doesn't read
  // while the button is bouncing
  if (aButtonState != aPrevState) {
    delay(15);
  }

  return aButtonState;
}
