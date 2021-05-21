// Pins for the LED
#define ledRPin 3
#define ledGPin 5
#define ledBPin 6

void setup()
{
  pinMode(ledRPin, OUTPUT);
  pinMode(ledGPin, OUTPUT);
  pinMode(ledBPin, OUTPUT);  
}

void loop()
{
  setColor(255, 0, 0);  // red
  delay(1000);
  setColor(0, 255, 0);  // green
  delay(1000);
  setColor(0, 0, 255);  // blue
  delay(1000);
  setColor(255, 255, 0);// yellow
  delay(1000);  
  setColor(80, 0, 80);  // purple
  delay(1000);
  setColor(0, 255, 255);// aqua
  delay(1000);
}

void setColor(int red, int green, int blue)
{
  analogWrite(ledRPin, red);
  analogWrite(ledGPin, green);
  analogWrite(ledBPin, blue);  
}
