const int B1A = 3;  // Digital Pin 3 Black
const int B2A = 4;  // Digital Pin 4 White
const int A1A = 5;  // Digital Pin 5 Blue
const int A1B = 6;  // Digital Pin 6 Green
//Green and Blue left motor
//Black and white right motor
char BT_Data;  //Char value called Bluetooth data
int motorSpeed = 0;
void setup() {
  Serial.begin(9600);  //Start the Serial for RX and TX (UART) communication with the HC-05 Bluetooth Module
  pinMode(B1A, OUTPUT);
  pinMode(B2A, OUTPUT);
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
}
void backwards() {
  // (Pin 13 and 12 turning anticlockwise(Backwards) Blue and Green Right motor)
  digitalWrite(A1B, LOW);
  digitalWrite(A1A, HIGH);
  digitalWrite(B1A, LOW);
  digitalWrite(B2A, HIGH);
}
void forwards() {
  //(Pin 10 and 11  turning clockwise(forward)) colours are black and white Left motor)
  digitalWrite(A1B, HIGH);
  digitalWrite(A1A, LOW);
  digitalWrite(B1A, HIGH);
  digitalWrite(B2A, LOW);
}
void forward(int x) {
  //(Pin 10 and 11  turning clockwise(forward)) colours are black and white Left motor)
  analogWrite(A1B, x);
  analogWrite(A1A, 0);
  analogWrite(B1A, x);
  analogWrite(B2A, 0);
}
void right() {
  digitalWrite(A1B, HIGH);
  digitalWrite(A1A, LOW);
  digitalWrite(B1A, LOW);
  digitalWrite(B2A, HIGH);
}
void PWM_right(int x) {
  analogWrite(A1B, x*2);
  analogWrite(A1A, x);
  analogWrite(B1A, x);
  analogWrite(B2A, x*2);
}
void left() {
  digitalWrite(A1B, LOW);
  digitalWrite(A1A, HIGH);
  digitalWrite(B1A, HIGH);
  digitalWrite(B2A, LOW);
}
void stop_all() {
  digitalWrite(A1B, LOW);
  digitalWrite(A1A, LOW);
  digitalWrite(B1A, LOW);
  digitalWrite(B2A, LOW);
}
void exp(int x) {
  analogWrite(A1B, x);
  analogWrite(A1A, 0);
  // Gradually increase the motor speed
  for (motorSpeed = 0; motorSpeed <= 255; motorSpeed += 5) {
    analogWrite(A1A, motorSpeed);  // Set the left motor speed
    //analogWrite(A2B, 0);
    delay(100);  // Wait for 100 milliseconds
  }
  // Wait a bit before decreasing speed
  delay(1000);  // Wait for 1 second
  //Gradually decrease the motor speed
  for (motorSpeed = 255; motorSpeed >= 0; motorSpeed -= 5) {
    analogWrite(A1A, motorSpeed);  //Set the motor speed
    //analogWrite();
    delay(100);
  }
}
void loop() {
  if (Serial.available())  //Check if there is data on the serial port
  {
    BT_Data = Serial.read();  //read the serial data and store it in the global variable BT_Data
    switch (BT_Data) {
      case 'W':  // If we receive 'W' move forwards until otherwise
        forwards();
        //forward(speed);
        break;
      case 'A':  // If we receive 'A' move left until otherwise
        //left();
        speed_left();  //Call the function
        break;
      case 'D':  // If we receive 'D' move right until otherwise
        //right();
        speed_right();
        break;
      case 'S':  // If we receive 'S' move forwards until otherwise
        backwards();
        break;
    }
  }
}
//Case 0-3 for the left motor
void speed_left() {
  case '0':
    analogWrite(A1A, 0);
    analogWrite(A1B, 0);
    break;
  case '1':
    analogWrite(A1A, 32);  // Adjust PWM value for desired speed
    analogWrite(A1B, 0);
  case '2':
    analogWrite(A1A, 128);
    analogWrite(A1B, 0);
    // Adjust PWM value for desired speed
    break;
  case '3':
    analogWrite(A1A, 255);  // Maximum speed
    analogWrite(A1B, 0);
    break;
}
void speed_right() {
  //Case 4-7 right motor
  speed4 = case '4' : analogWrite(B1A, 0);
  analogWrite(B2A, 0);
  break;
  case '5':
    analogWrite(B1A, 32);
    analogWrite(B2A, 0);
    break;
  case '6':
    analogWrite(B1A, 128);
    analogWrite(B2A, 0);
    break;
  case '7':
    analogWrite(B1A, 255);
    analogWrite(B2A, 0);
    break;
  default:       //If we receive no characters or unrecognised stop all motors
    stop_all();  // Call the function to stop all motors
}