#include <Joystick.h>
#include <Keyboard.h>

// Pins for the potentiometer/switch combo
#define potAnalogPin A1
#define potSwitchPin 9

/*
 * BUTTON DIAGRAM
 * +--------+
 * |  1  2  |
 * |  3  4  |
 * |  5  6  |
 * +--------+
 */
// Pins for the buttons
#define button1Pin 2
#define button2Pin 7
#define button3Pin 14
#define button4Pin 8
#define button5Pin 16
#define button6Pin 4

// Pins for the LED
#define ledBPin 5

// Pin for the 2 position switch
#define switchPin 15

void setup()
{
  pinMode(potAnalogPin, INPUT);
  pinMode(potSwitchPin, INPUT_PULLUP);
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
  pinMode(button4Pin, INPUT_PULLUP);
  pinMode(button5Pin, INPUT_PULLUP);
  pinMode(button6Pin, INPUT_PULLUP);
  pinMode(switchPin, INPUT_PULLUP);

  pinMode(ledBPin, OUTPUT);

  Serial.begin(9600);
  Joystick.begin();
  Keyboard.begin();
}

const int pinToButtonMap = potAnalogPin;

// Value used in 'temp()' to test and find the value for 'potMinMapVal'
int minPotVal = 1023;

// Potentiometer variables
int potAnalogVal, potMappedVal, potSwitchVal;
int potMinMapVal = 800;

// Button variables
int button1Val, button2Val, button3Val, button4Val, button5Val, button6Val;

// Switch variable
int switchVal;

// Party mode variables
bool isPartyMode, ledBState;
int triggerCount, ledCount;

void loop()
{
  // Read all the input pins
  potAnalogVal = analogRead(potAnalogPin);
  potSwitchVal = !digitalRead(potSwitchPin);
  button1Val   = !digitalRead(button1Pin);
  button2Val   = !digitalRead(button2Pin);
  button3Val   = !digitalRead(button3Pin);
  button4Val   = !digitalRead(button4Pin);
  button5Val   = !digitalRead(button5Pin);
  button6Val   = !digitalRead(button6Pin);
  switchVal    = !digitalRead(switchPin);
  

  /* Uncomment the next line to test and find the value for 'potMinMapVal' */
  // temp();

  // Code for the 'throttle' input on the controller
  if(potSwitchVal)
  {
    potMappedVal = map(potAnalogVal,1023,potMinMapVal,0,255);
  }
  else
  {
    if(potAnalogVal < 1023)
    {
      potMappedVal = 255;
    }
    else
    {
      potMappedVal = 0;
    }
  }
  Joystick.setThrottle(potMappedVal);

  /*
   * BUTTON DIAGRAM
   * +--------+
   * |  1  2  |
   * |  3  4  |
   * |  5  6  |
   * +--------+
   * 
   * The controller has 32 buttons that can be pressed, indexed 0-31
   * e.g. to press the button shown as 20, you use 'Joystick.setButton(19, buttonXVal);'
   * 
   * To send keyboard input from a button, you can just send it a character
   * e.g. 'writeWhenPressed(char, buttonXVal);'
   * 
   * For standard characters on a keyboard, you use single quotes surounding one character
   * e.g. 'A', 'g', '9', '*'
   * 
   * There are special keyboard modifiers that you can use as well
   * e.g. KEY_PAGE_UP, KEY_DOWN_ARROW, KEY_LEFT_SHIFT
   * For a full list of keyboard modifiers, check here: https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
   * 
   */
  // Code for the buttons
  if(switchVal)
  {
    /* Switch in the UP position */
    
    //   Send controller button input
    Joystick.setButton(0, button1Val);
    Joystick.setButton(1, button2Val);
    // Joystick.setButton(2, button3Val);
    Joystick.setButton(3, button4Val);
    Joystick.setButton(4, button5Val);
    Joystick.setButton(5, button6Val);

    //   Send keyboard input
    // writeKeyWhenPressed('A', button1Val);
    // writeKeyWhenPressed(KEY_PAGE_DOWN, button2Val);
    writeKeyWhenPressed(KEY_F4, button3Val);
    // writeKeyWhenPressed('a', button4Val);
    // writeKeyWhenPressed(KEY_CAPS_LOCK, button5Val);
    // writeKeyWhenPressed(KEY_DOWN_ARROW, button6Val);
  }
  else
  {
    /* Switch in the DOWN position */
    
    // Send controller button input
    Joystick.setButton(6, button1Val);
    Joystick.setButton(7, button2Val);
    Joystick.setButton(8, button3Val);
    Joystick.setButton(9, button4Val);
    Joystick.setButton(10, button5Val);
    Joystick.setButton(11, button6Val);

    //   Send keyboard input
    // writeKeyWhenPressed(KEY_PAGE_UP, button1Val);
    // writeKeyWhenPressed(KEY_PAGE_DOWN, button2Val);
    // writeKeyWhenPressed('A', button3Val);
    // writeKeyWhenPressed('a', button4Val);
    // writeKeyWhenPressed(KEY_CAPS_LOCK, button5Val);
    // writeKeyWhenPressed(KEY_DOWN_ARROW, button6Val);
  }

  // Party mode counter
  if(!switchVal && !potSwitchVal && button1Val && button2Val)
  {
    triggerCount++;
    if(triggerCount > 500)
    {
      isPartyMode = !isPartyMode;
      triggerCount = 0;
    }
  }
  else
  {
    triggerCount = 0;
  }

  if(isPartyMode)
  {
    /* What happens when it's party mode */
    ledCount++;
    if(ledCount > 5)
    {
      ledBState = !ledBState;
      ledCount = 0;
    }
  }
  else
  {
    /* What happens when it's NOT party mode */
    ledBState = false;
  }

  digitalWrite(ledBPin, ledBState);
}

// Function to press a key when a given button is pressed

void writeKeyWhenPressed(char key, int buttonVal)
{
  if(buttonVal)
  {
    Keyboard.press(key);
  }
  else
  {
    Keyboard.release(key);
  }
}

// Fucntion to print out the minimum value the potentiometer has recorded
void temp()
{
  if (potAnalogVal < minPotVal)
  {
    minPotVal = potAnalogVal;
  }
  Serial.println(minPotVal);
}
