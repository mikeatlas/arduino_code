
#include <Servo.h>  // servo library

Servo servo1;  // servo control object
const int buttonPin = 2;
const int servoPin = 9;
const int buzzerPin = 8;
const int redLedPin = 13; 
const int greenLedPin = 12; 
const int blueLedPin = 11; 
boolean servingFood;

void setup()
{
  servo1.attach(servoPin);
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  servingFood=false;
  servo1.write(0);
  delay(300);
}


void loop()
{ 
 runFoodServer();
}

void redLight(){
  digitalWrite(redLedPin, HIGH);
  digitalWrite(greenLedPin, LOW);
  digitalWrite(blueLedPin, LOW);    
}

void greenLight(){
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(blueLedPin, LOW);    
}

void yellowLight(){
  digitalWrite(redLedPin, HIGH);
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(blueLedPin, LOW);    
}

void buzzBuzzer(char note){
   int tf = toneFrequency(note);
   tone(buzzerPin, tf, 200);
   delay(200);
}

void runFoodServer(){
  greenLight();
  int buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && servingFood == false){

    yellowLight();
   
    buzzBuzzer('c');
    buzzBuzzer('a');
    buzzBuzzer('b');
   
    redLight();
    serveFood();
    yellowLight();
 
    buzzBuzzer('b'); 
    buzzBuzzer('a');
    buzzBuzzer('c');
    delay(3000);
  }
  greenLight();
}

void serveFood(){
   delay(10);
   servingFood = true;
   wiggle(3);
   fullRotation();
   servingFood = false;
}

void fullRotation(){
  servo1.write(0);
  delay(1000);
  servo1.write(180);
  delay(1000);
  servo1.write(0);
  delay(700);
}

void wiggle(int wiggles)
{
 for (int i=0; i<wiggles; i++){
  servo1.write(0);
  delay(400);
  servo1.write(45);
  delay(400);
 }
 servo1.write(0);
}

int toneFrequency(char note) 
{
  // This function takes a note character (a-g), and returns the
  // corresponding frequency in Hz for the tone() function.
  
  int i;
  const int numNotes = 8;  // number of notes we're storing
  
  // The following arrays hold the note characters and their
  // corresponding frequencies. The last "C" note is uppercase
  // to separate it from the first lowercase "c". If you want to
  // add more notes, you'll need to use unique characters.

  // For the "char" (character) type, we put single characters
  // in single quotes.

  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};
  
  // Now we'll search through the letters in the array, and if
  // we find it, we'll return the frequency for that note.
  
  for (i = 0; i < numNotes; i++)  // Step through the notes
  {
    if (names[i] == note)         // Is this the one?
    {
      return(frequencies[i]);     // Yes! Return the frequency
    }
  }
  return(0);  // We looked through everything and didn't find it,
              // but we still need to return a value, so return 0.
}

