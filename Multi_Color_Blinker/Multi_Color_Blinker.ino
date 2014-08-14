/*     ---------------------------------------------------------
 *     |  Experimentation Kit for Arduino Example Code         |
 *     |  CIRC-RGB .: Colourful Light :. (RGB LED)             |
 *     ---------------------------------------------------------
 * 
 * We've blinked an LED and controlled eight in sequence now it's time to 
 * control colour. Using an RGB LED (actual 3 LEDs in a single housing)  
 * we can generate any colour our heart desires.
 *
 * (we'll also use a few programming shortcuts to make the code 
 * more portable/readable)
 */

#include <Servo.h>
Servo myServo1; 
int myServoPos = 0;
boolean GoingUp = true; 

//RGB LED pins
int ledDigitalOne[] = {10, 11, 12}; //the three digital pins of the digital LED 
                                   //9 = redPin, 10 = greenPin, 11 = bluePin

const boolean ON = LOW;     //Define on as LOW (this is because we use a common 
                            //Anode RGB LED (common pin is connected to +5 volts)
const boolean OFF = HIGH;   //Define off as HIGH

//Predefined Colors
const boolean RED[] = {ON, OFF, OFF};    
const boolean GREEN[] = {OFF, ON, OFF}; 
const boolean BLUE[] = {OFF, OFF, ON}; 
const boolean YELLOW[] = {ON, ON, OFF}; 
const boolean CYAN[] = {OFF, ON, ON}; 
const boolean MAGENTA[] = {ON, OFF, ON}; 
const boolean WHITE[] = {ON, ON, ON}; 
const boolean BLACK[] = {OFF, OFF, OFF}; 
const boolean FALSE = 0;
const boolean TRUE = 1;

//An Array that stores the predefined colors (allows us to later randomly display a color)
const boolean* COLORS[] = {RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, WHITE, BLACK};
//OK so this is an array of arrays (of pointers?)

boolean isLit = FALSE;
long previousMillis = 0;
long interval = 250; 
int ColorIndex = 0;

void setup(){
  for(int i = 0; i < 3; i++){
   pinMode(ledDigitalOne[i], OUTPUT);
   setColorByName(ledDigitalOne, BLACK);   //Set the three LED pins as outputs
  }
  myServo1.attach(9);
}

void loop(){
   unsigned long currentMillis = millis();
   if(currentMillis - previousMillis > interval) { // save the last time you blinked the LED 
     previousMillis = currentMillis;
     ChangeLEDState(); 
     for (int ii=0; ii<10; ii++){
     MoveServo(); 
     delay (10);
     }
   }
   
}

void ChangeLEDState(){
  if (isLit == FALSE){
    //SetRandomColor();
    SetNextColor();
    isLit = TRUE; 
  }
  else
  {
    setColorByName (ledDigitalOne, BLACK);
    isLit = FALSE; 
  }
}


/* Sets an led to any color
   led - a three element array defining the three color pins (led[0] = redPin, led[1] = greenPin, led[2] = bluePin)
   color - a three element boolean array (color[0] = red value (LOW = on, HIGH = off), color[1] = green value, color[2] =blue value)
*/
void setColor(int* led, boolean* color){
 for(int i = 0; i < 3; i++){
   digitalWrite(led[i], color[i]);
 }
 
}

/* A version of setColor that allows for using const boolean colors
*
*/
void setColorByName(int* led, const boolean* color){
  boolean tempColor[] = {color[0], color[1], color[2]};
  setColor(led, tempColor);
}


void SetRandomColor(){
  int rand = random() % 7; // There are 7 non-black colors in the array, after all.  
  setColorByName(ledDigitalOne, COLORS[rand]);  //Set the color of led one to a random color
}


void SetNextColor(){
  ColorIndex++; 
  ColorIndex = ColorIndex % 3; // There are 7 non-black colors in the array, after all.  
  setColorByName(ledDigitalOne, COLORS[ColorIndex]);  //Set the color of led one to a random color
}


void MoveServo(){
  if (myServoPos >= 180) {GoingUp = false;}
  if (myServoPos <= 0) {GoingUp = true;}
  if (GoingUp) {
    myServoPos += 1;                
  }else{
    myServoPos -= 1; 
  }
  myServo1.write(myServoPos); // tell servo to go to position in variable 'pos' 
} 
  
