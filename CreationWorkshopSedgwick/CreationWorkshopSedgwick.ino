#include <Servo.h>

//****************************//
//You need to adjust this for your specific servo
const int ApertureOpen = 20;
const int ApertureClose = 100;
//****************************//

const int IO_LED = 11;
const int IO_Servo = 9;

const int IO_NOT_Enable = 7;
const int IO_MS1 = 6;
const int IO_MS2 = 5;
const int IO_MS3 = 4;
const int IO_Step = 1;
const int IO_NOT_Sleep = 2;
const int IO_NOT_Reset = 3;
const int IO_Direction = 0;




int Direction = 0; //1 Z+, 0 Z-
Servo servo; //servo controlled aperture

void setup()
{
  pinMode(IO_LED, OUTPUT);
  digitalWrite(IO_LED, 1);

  pinMode(IO_NOT_Enable, OUTPUT);
  digitalWrite(IO_NOT_Enable, 1);
  pinMode(IO_MS1, OUTPUT);
  digitalWrite(IO_MS1, 1);
  pinMode(IO_MS2, OUTPUT);
  digitalWrite(IO_MS2, 1);
  pinMode(IO_MS3, OUTPUT);
  digitalWrite(IO_MS3, 1);
  pinMode(IO_Step, OUTPUT);
  digitalWrite(IO_Step, 0);
  pinMode(IO_NOT_Sleep, OUTPUT);
  digitalWrite(IO_NOT_Sleep, 1);
  pinMode(IO_NOT_Reset, OUTPUT);
  digitalWrite(IO_NOT_Reset, 1);
  pinMode(IO_Direction, OUTPUT);
  digitalWrite(IO_Direction, 0);

  servo.attach(IO_Servo);
  servo.write(ApertureClose); //Close aperture

    //300, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200
  Serial.begin(9600);
  Direction = 1;
}

void loop()
{
  if (Serial.available() > 0)
  {
    int Byte = Serial.read();
    switch(Byte)
    {
    case 'E': //Enable Stepper Motor
      digitalWrite(IO_NOT_Enable, 0);
      //Serial.write('e');
      Serial.println('e');
      break;
    case 'D': //Disable Stepper Motor
      digitalWrite(IO_NOT_Enable, 1);
      //        Serial.write('d');
      Serial.println('d');
      break;
    case 'F': //Change Direction to forward (1)
      digitalWrite(IO_Direction, 1);
      //        Serial.write('f');
      Serial.println('f');
      break;
    case 'R': //Change Direction to Reverse (0)
      digitalWrite(IO_Direction, 0);
      //        Serial.write('r');
      Serial.println('r');
      break;
    case 'S': //Step the Stepper Motor
      digitalWrite(IO_Step, 1);
      delay(1);
      digitalWrite(IO_Step, 0);
      //        Serial.write('s');
      Serial.println('s');
      break;
    case 'L': // Lift function
      liftFunction();
      //        Serial.write('l');
      Serial.println('l');
      break;
    case 'H': // jog small forward
      jogSmallForward();
      Serial.println('h');
      break;
    case 'J': // jog medium forward
      jogMediumForward();
      Serial.println('j');
      break;
    case 'K': // jog large forward
      jogLargeForward();
      Serial.println('k');
      break;
    case 'Y': // jog small reverse
      jogSmallReverse();
      Serial.println('y');
      break;
    case 'U': // jog medium reverse
      jogMediumReverse();
      Serial.println('u');
      break;
    case 'I': // jog large reverse
      jogLargeReverse();
      Serial.println('i');
      break;
    case 'P': //Ping Teensy 2.0
      Serial.write('Sedgwick20130725');
      break;
    case 'O':
      servo.write(ApertureOpen); //Open Aperture
      //        Serial.write('O');
      Serial.println('o');
      break;
    case 'C':
      servo.write(ApertureClose); //Close Aperture
      //        Serial.write('C');
      Serial.println('c');
      break;
    case 'V':
      //        Serial.write('Sedgwick20130725');
      Serial.println('v');
      break;
    default:
      break;
    }
  }
}

void jogSmallReverse(){
  // Set direction reverse
  digitalWrite(IO_Direction, 0);

  // Step 71
  for(int i=0;i<71;i++){
    digitalWrite(IO_Step, 1);
    delay(1);
    digitalWrite(IO_Step, 0);
  }
}

void jogMediumReverse(){
  // Set direction reverse
  digitalWrite(IO_Direction, 0);

  // Step 142
  for(int i=0;i<142;i++){
    digitalWrite(IO_Step, 1);
    delay(1);
    digitalWrite(IO_Step, 0);
  }
}

void jogLargeReverse(){
  // Set direction reverse
  digitalWrite(IO_Direction, 0);

  // Step 284
  for(int i=0;i<284;i++){
    digitalWrite(IO_Step, 1);
    delay(1);
    digitalWrite(IO_Step, 0);
  }
}

void jogSmallForward(){
// Set direction forward
  digitalWrite(IO_Direction, 1);

  // Step 151 
  for(int i=0; i<76; i++){
    digitalWrite(IO_Step, 1);
    delay(1);
    digitalWrite(IO_Step, 0);
  }
}

void jogMediumForward(){
// Set direction forward
  digitalWrite(IO_Direction, 1);

  // Step 151 
  for(int i=0; i<151; i++){
    digitalWrite(IO_Step, 1);
    delay(1);
    digitalWrite(IO_Step, 0);
  }
}

void jogLargeForward(){
// Set direction forward
  digitalWrite(IO_Direction, 1);

  // Step 302 
  for(int i=0; i<302; i++){
    digitalWrite(IO_Step, 1);
    delay(1);
    digitalWrite(IO_Step, 0);
  }
}

void liftFunction(){
  //M1   \\\\Time Delay per byte is 1ms (Min for 9600bps)\r\n
  //F    \\\\Set direction to forward\r\n
  //S151 \\\\Step 121 steps a S1 is equal to S\r\n
  //T500 \\\\Time delay in milliseconds before the next command\r\n
  //M2   \\\\Time Delay per byte in ms is now 2ms\r\n
  //R    \\\\Reverse direction\r\n
  //S142 \\\\Step 109 steps"

  // Set direction forward
  digitalWrite(IO_Direction, 1);

  // Step 151 
  for(int i=0; i<151; i++){
    digitalWrite(IO_Step, 1);
    delay(1);
    digitalWrite(IO_Step, 0);
  }

  // 500 millisecond delay
  delay(500);
  // Set direction reverse
  digitalWrite(IO_Direction, 0);

  // Step 142
  for(int i=0;i<142;i++){
    digitalWrite(IO_Step, 1);
    delay(1);
    digitalWrite(IO_Step, 0);
  }

}

