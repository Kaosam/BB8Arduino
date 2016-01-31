#include <PS3BT.h>
#include <usbhub.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

#define E1 2 //Enable Pin Motore 1
#define E2 4 //Enable Pin Motore 2
#define I1 3 //Control Pin 1 Motore 1
#define I2 6 //Control Pin 2 Motore 1
#define I3 7 //Control Pin 1 Motore 2
#define I4 5 //Control Pin 2 Motore 2

int stato_motori = 0; //Motori Spenti(0), Accesi(1)
int vel = 255;

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

void setup() {
   Serial.begin(115200);
   pinMode(E1, OUTPUT);
   pinMode(E2, OUTPUT);
   pinMode(I1, OUTPUT);
   pinMode(I2, OUTPUT);
   pinMode(I3, OUTPUT);
   pinMode(I4, OUTPUT);
   digitalWrite(I1, HIGH);
   digitalWrite(I2, LOW);
   digitalWrite(I3, HIGH);
   digitalWrite(I4, LOW);
   if (Usb.Init() == -1) {
   Serial.print(F("\r\nOSC did not start"));
   while (1); //halt     
   }
   Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}

void loop() {
 Usb.Task();
 
    if(stato_motori == 0) {
          analogWrite(E1, 0);
          analogWrite(E2, 0);
    } 
    
if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
   
   if(PS3.getAnalogHat(LeftHatY) >= 0 && PS3.getAnalogHat(LeftHatY) <= 117) {
      stato_motori = 1;
      vel = 255;
      vel = vel - (PS3.getAnalogHat(LeftHatY)*2);
      digitalWrite(I1, HIGH);
      digitalWrite(I2, LOW);
      digitalWrite(I3, HIGH);
      digitalWrite(I4, LOW);
      analogWrite(E1, vel);
      analogWrite(E2, vel);
      Serial.print(F("\r\nLeftHatY: "));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      Serial.print(F("\tVelocita': "));
      Serial.print(vel);
   }
   if(PS3.getAnalogHat(LeftHatY) >= 137 && PS3.getAnalogHat(LeftHatY) <= 255) {
      stato_motori = 1;
      vel = 0;
      vel = map(PS3.getAnalogHat(LeftHatY), 137, 255, 20, 255);
      digitalWrite(I1, LOW);
      digitalWrite(I2, HIGH);
      digitalWrite(I3, LOW);
      digitalWrite(I4, HIGH);
      analogWrite(E1, vel);
      analogWrite(E2, vel);
      Serial.print(F("\r\nLeftHatY: "));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      Serial.print(F("\tVelocita': "));
      Serial.print(vel);
   }
   
   if(PS3.getAnalogHat(LeftHatY) >= 117 && PS3.getAnalogHat(LeftHatY) <= 137) {
      stato_motori = 0;
      digitalWrite(E1, LOW);
      digitalWrite(E2, LOW);     
   }
   

    if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
      Serial.print(F("\r\nL2: "));
      Serial.print(PS3.getAnalogButton(L2));
      if (PS3.PS3Connected) {
        Serial.print(F("\tR2: "));
        Serial.print(PS3.getAnalogButton(R2));
      }
    }
    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
    
    else {
      
      if (PS3.getButtonClick(TRIANGLE))
        Serial.print(F("\r\nTriangle"));
        
      if (PS3.getButtonClick(CIRCLE)) 
        Serial.print(F("\r\nCircle"));
        
      if (PS3.getButtonClick(CROSS))
        Serial.print(F("\r\nCross"));
        
      if (PS3.getButtonClick(SQUARE))
        Serial.print(F("\r\nSquare"));

      if (PS3.getButtonClick(UP)) {
        Serial.print(F("\r\nUp"));
          digitalWrite(I1, HIGH);
          digitalWrite(I2, HIGH);
          digitalWrite(I3, HIGH);
          digitalWrite(I4, HIGH);
          digitalWrite(E1, LOW);
          digitalWrite(E2, LOW);
          stato_motori = 1;
          delay(1000);
          digitalWrite(I1, HIGH);
          digitalWrite(I2, LOW);
          digitalWrite(I3, HIGH);
          digitalWrite(I4, LOW);
          analogWrite(E1, 255);
          analogWrite(E2, 255);
      }
      
      if (PS3.getButtonClick(RIGHT)) {
        Serial.print(F("\r\nRight")); 
          digitalWrite(I1, HIGH);
          digitalWrite(I2, HIGH);
          digitalWrite(I3, HIGH);
          digitalWrite(I4, HIGH);
          digitalWrite(E1, LOW);
          digitalWrite(E2, LOW);
          stato_motori = 1;
          delay(1000);     
          digitalWrite(I1, HIGH);
          digitalWrite(I2, LOW);
          digitalWrite(I3, LOW);
          digitalWrite(I4, HIGH);
          analogWrite(E1, 255);
          analogWrite(E2, 255);
      }        
      
      if (PS3.getButtonClick(DOWN)) {
        Serial.print(F("\r\nDown"));
          digitalWrite(I1, HIGH);
          digitalWrite(I2, HIGH);
          digitalWrite(I3, HIGH);
          digitalWrite(I4, HIGH);
          digitalWrite(E1, LOW);
          digitalWrite(E2, LOW);
          stato_motori = 1;
          delay(1000);
          digitalWrite(I1, LOW);
          digitalWrite(I2, HIGH);
          digitalWrite(I3, LOW);
          digitalWrite(I4, HIGH);
          analogWrite(E1, 255);
          analogWrite(E2, 255);
      }
      
      if (PS3.getButtonClick(LEFT)) {
        Serial.print(F("\r\nLeft"));     
          digitalWrite(I1, HIGH);
          digitalWrite(I2, HIGH);
          digitalWrite(I3, HIGH);
          digitalWrite(I4, HIGH);
          digitalWrite(E1, LOW);
          digitalWrite(E2, LOW);
          stato_motori = 1;
          delay(1000); 
          digitalWrite(I1, LOW);
          digitalWrite(I2, HIGH);
          digitalWrite(I3, HIGH);
          digitalWrite(I4, LOW);
          analogWrite(E1, 255);
          analogWrite(E2, 255);  
      }    

      if (PS3.getButtonClick(L1)) 
        Serial.print(F("\r\nL1")); 
            
      if (PS3.getButtonClick(L3))
        Serial.print(F("\r\nL3"));
        
      if (PS3.getButtonClick(R1)) 
        Serial.print(F("\r\nR1")); 
              
      if (PS3.getButtonClick(R3))
        Serial.print(F("\r\nR3"));

      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect - "));
        PS3.printStatusString();
      }
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart "));
        if (stato_motori == 0) {
          stato_motori = 1;
          digitalWrite(I1, HIGH); 
          digitalWrite(I2, LOW);
          digitalWrite(I3, HIGH);
          digitalWrite(I4, LOW);
          analogWrite(E1, 255);
          analogWrite(E2, 255);
          Serial.print(stato_motori);
        }
        else {
          stato_motori = 0;  
          Serial.print(stato_motori);
        }
      }
    }
  }
}
