#include <SoftwareSerial.h>

//Create software serial object to communicate with A6
SoftwareSerial mySerial(3, 2); //A6 Tx & Rx is connected to Arduino #3 & #2


int window = 4;
int window_state = 0;
void setup() {
 pinMode(window, INPUT);
 Serial.begin(9600);

   //Begin serial communication with Arduino and A6
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, i t will back to OK
  updateSerial();
}

void loop() {
  
window_state = digitalRead(window);
//Serial.println(window_state);

if(window_state == 0){
  Serial.println("Beware");
  Make_call();
  delay(1000);
  }
 else{
  Serial.println("Closed closed");
  }
}
//update Serial function
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}

//on window alert
void Make_call(){
    mySerial.println("ATD+250791406284"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
  updateSerial();
  delay(20000); // wait for 20 seconds...
  mySerial.println("ATH"); //hang up
  updateSerial();
  }
