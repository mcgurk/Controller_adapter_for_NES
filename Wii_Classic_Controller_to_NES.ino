//Uno/Pro Mini: SDA = A4, SCL = A5
//Pro Micro: SDA = D2, SCL = D3
//ESP8266: SDA = D2, SCL = D1

//Pin 8 NES data (PORTB, bit 1) https://www.arduino.cc/en/Reference/PortManipulation
//must be interrupt pins: https://www.arduino.cc/en/Reference/AttachInterrupt
//Pin 2 NES latch
//Pin 3 NES pulse

//#define DEBUG
//#define DEBUG2

#include <Wire.h>

#define JOYSTICK_DATA_SIZE 6
uint8_t data[JOYSTICK_DATA_SIZE];

#define ADDRESS 0x52

void sendByte(int data, int location)  {  
  Wire.beginTransmission(ADDRESS);
  Wire.write(location);
  Wire.write(data);  
  Wire.endTransmission();
}

void sendZero()  {  
  Wire.beginTransmission(ADDRESS);
  Wire.write(0x00);  
  Wire.endTransmission();
}

volatile uint8_t counter = 0;

uint32_t frame_measured_duration = 0;
uint32_t framestart = 0;
uint32_t last_framestart = 0;
uint32_t readend = 0;
uint8_t PAL = 0;

volatile uint8_t btn0 = 1;
volatile uint8_t btn[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

void latch() {
  PORTB = btn0;
  counter = 0;
}

void pulse() {
  PORTB = btn[counter];
  counter++;
}


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  //pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  //pinMode(2, INPUT_PULLUP);
  //pinMode(3, INPUT_PULLUP);
  //pinMode(4, OUTPUT);
  //digitalWrite(4, HIGH);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  attachInterrupt(digitalPinToInterrupt(2), latch, RISING);
  //attachInterrupt(digitalPinToInterrupt(3), pulse, RISING);
  attachInterrupt(digitalPinToInterrupt(3), pulse, FALLING);

  Wire.begin();
  Wire.setClock(300000L);
  
  sendByte(0x55, 0xF0);
  sendByte(0x00, 0xFB);
  
  #if defined(DEBUG) || defined(DEBUG2)
  Serial.begin(115200);
  Serial.println("Start");
  Serial.println(micros());
  Serial.flush();
  #endif

  #if defined(DEBUG) || defined(DEBUG2)
  Serial.println(micros());
  Serial.flush();
  #endif

}


void loop() {

  // wait for latch signal
  while(!(PIND & B00000100)) {}

  framestart = micros();
  frame_measured_duration = framestart - last_framestart;
  last_framestart = framestart;
  if (frame_measured_duration > 19000 && frame_measured_duration < 21000) PAL = 1;
  if (frame_measured_duration > 16000 && frame_measured_duration < 17000) PAL = 0;

  #define PROCESSING_TIME 800
  // wait to moment where we can do all reading and processing before next latch signal
  if (PAL) delayMicroseconds(20000-PROCESSING_TIME); else delayMicroseconds(16666-PROCESSING_TIME);

  // ---------------------------------------------------------------------------------------------
  //  reading and processing: 708-728us (including frame duration calculation and PAL/NTSC check)
  // ---------------------------------------------------------------------------------------------
  
  sendZero();
  delayMicroseconds(200);
  
  Wire.requestFrom(ADDRESS, JOYSTICK_DATA_SIZE); //request data from wii classic
  uint8_t i = 0;
  while(Wire.available()) {
    data[i] = Wire.read();
    i++;
    if (i >= JOYSTICK_DATA_SIZE) break;
  }

  if(bitRead(data[5], 4)) btn0 = 1; else btn0 = 0; //a
  if(bitRead(data[5], 6)) btn[0] = 1; else btn[0] = 0; //b
  if(bitRead(data[4], 4)) btn[1] = 1; else btn[1] = 0; //select
  if(bitRead(data[4], 2)) btn[2] = 1; else btn[2] = 0; //start
  if(bitRead(data[5], 0)) btn[3] = 1; else btn[3] = 0; //up
  if(bitRead(data[4], 6)) btn[4] = 1; else btn[4] = 0; //down
  if(bitRead(data[5], 1)) btn[5] = 1; else btn[5] = 0; //left
  if(bitRead(data[4], 7)) btn[6] = 1; else btn[6] = 0; //right
  //http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Classic_Controller
  
  //detect if init is needed
  if (i < JOYSTICK_DATA_SIZE) {
    delay(100);
    sendByte(0x55, 0xF0);
    sendByte(0x00, 0xFB);
    #ifdef DEBUG
    Serial.println("Init!");
    #endif
  }

  readend = micros();

  #ifdef DEBUG2
  uint32_t temp = readend - framestart;
  Serial.println(temp);
  //Serial.println(frame_measured_duration);
  Serial.flush();
  #endif

  
  #ifdef DEBUG
  for (uint8_t i = 0; i < JOYSTICK_DATA_SIZE; i++) {
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  #endif

  #ifdef DEBUG
  delay(100); // used to see changes in the serial monitor easier.
  #endif
  

}
