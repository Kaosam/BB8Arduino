#include <PS3BT.h> //Inizializzazione librerie
#include <usbhub.h>
#include <AFMotor.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

AF_DCMotor motor1(2); //Pin motori
AF_DCMotor motor2(4);
AF_DCMotor motor3(3);

int vel = 0; //Velocità motori PS3
int b = -1; //Dati ricevuti da Bluetooth
int vel2 = 0; //Velocità motori Bluetooth
int c= -1;

USB Usb; //Inizializzazione USB Shield
BTD Btd(&Usb);
PS3BT PS3(&Btd);

void setup() {
  Serial.begin(9600);
  Serial.flush();
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1);
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  SPI.begin();
}

void loop() {
  Usb.Task();

  // ------ COMANDI CONTROLLER PS3 ------ // 

  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {

    if (PS3.getAnalogHat(LeftHatX) > 150 || PS3.getAnalogHat(LeftHatX) < 105 ||
        PS3.getAnalogHat(LeftHatY) > 150 || PS3.getAnalogHat(LeftHatY) < 105) {
      
      if (PS3.getAnalogHat(LeftHatY) >= 0 && PS3.getAnalogHat(LeftHatY) < 105) {
        vel = map(PS3.getAnalogHat(LeftHatY), 105, 0, 120, 255); //AVANTI
        motor3.run(RELEASE); 
        motor1.setSpeed(vel); 
        motor1.run(FORWARD);
        motor2.setSpeed(vel); 
        motor2.run(FORWARD);
      }

      if (PS3.getAnalogHat(LeftHatY) > 150 && PS3.getAnalogHat(LeftHatY) <= 255) {
        vel = map(PS3.getAnalogHat(LeftHatY), 150, 255, 120, 255); //INDIETRO
        motor3.run(RELEASE); 
        motor1.setSpeed(vel); 
        motor1.run(BACKWARD);
        motor2.setSpeed(vel); 
        motor2.run(BACKWARD);   
      }
      
      Serial.print(F("\tLeftHatY: "));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      Serial.print(F("\tVelocita: "));
      Serial.print(vel);
      Serial.println();
    }

      if (PS3.getAnalogHat(RightHatX) > 150 || PS3.getAnalogHat(RightHatX) < 105 ||
          PS3.getAnalogHat(RightHatY) > 150 || PS3.getAnalogHat(RightHatY) < 105) {

        if (PS3.getAnalogHat(RightHatX) >= 0 && PS3.getAnalogHat(RightHatX) < 105) {     
          vel = map(PS3.getAnalogHat(RightHatX), 105, 0, 120, 255); //DESTRA
          motor3.setSpeed(vel); 
          motor3.run(FORWARD);
        }

       if (PS3.getAnalogHat(RightHatX) > 150 && PS3.getAnalogHat(RightHatX) <= 255) {
          vel = map(PS3.getAnalogHat(RightHatX), 150, 255, 120, 255); //SINISTRA 
          motor3.setSpeed(vel); 
          motor3.run(BACKWARD);
        }
      
      
      Serial.print(F("\tRightHatX: "));
      Serial.print(PS3.getAnalogHat(RightHatX));
      Serial.print(F("\tVelocita: "));
      Serial.print(vel);
      Serial.println();
    }

    if (PS3.getAnalogHat(LeftHatX) <= 150 && PS3.getAnalogHat(LeftHatX) >= 105 &&
        PS3.getAnalogHat(LeftHatY) <= 150 && PS3.getAnalogHat(LeftHatY) >= 105) {
      motor1.run(RELEASE); //STOP
      motor2.run(RELEASE);    
      motor3.run(RELEASE);  
      }
    }

    else {
      
      // ------ COMANDI con gestures ------ //
      b = Serial.read(); //Lettura dati da seriale
      if (b!=-1) {
        c = b;
      }
      if ((c> 42 && c <=84) || (c < 42 && c>=0)) {
        if (c>42 && c <=84) {
          vel = map(c, 43, 84, 120, 255); //avanti
          motor1.setSpeed(vel); 
          motor1.run(FORWARD);
          motor2.setSpeed(vel); 
          motor2.run(FORWARD);
        }
        if (c < 42 && c>=0) {
          vel = map(c, 41, 0, 120, 255); //indietro
          motor1.setSpeed(vel); 
          motor1.run(BACKWARD);
          motor2.setSpeed(vel); 
          motor2.run(BACKWARD);
        }
        Serial.println(vel);
      }
       else {
          motor1.run(RELEASE); //STOP
          motor2.run(RELEASE);  
          motor3.run(RELEASE);
        }
    }

    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
}
