#include <Arduino.h>
#include <Stepper.h>

#define SOL_PWM 6
#define PUL 10
#define DIR 11
#define ENA 12

#define FORWARD_SPEED 800
#define REVERSE_SPEED -800

#define ENDPOINT 1792000
Stepper myStepper(400,PUL, DIR);

  int POSITION = 0;
  int stepCount = 0;
  bool PULSE = false;


void setup() {

  Serial.begin(9600);
  pinMode(5, INPUT_PULLUP);
  pinMode(SOL_PWM, OUTPUT); 
  pinMode(ENA, OUTPUT);
  digitalWrite(ENA, HIGH);
  myStepper.setSpeed(15000);

  // put your setup code here, to run once:
}

void loop() {

  stepCount = 0;
  POSITION = 0;

  myStepper.step(REVERSE_SPEED);

  if(digitalRead(5) == 0){
    Serial.println("Zero point reached. ");
    Serial.println("Starting Air...");

    POSITION = 0;

    while(1){
      Serial.println(stepCount);
      myStepper.step(FORWARD_SPEED);
      stepCount += FORWARD_SPEED;

      if(stepCount > 50000){
        PULSE = true;
      }

      if(PULSE == true){
        if((stepCount % 50000) == 0){
        digitalWrite(SOL_PWM, HIGH);
        delay(100);
        digitalWrite(SOL_PWM, LOW);
        }
      }
      if(stepCount > ENDPOINT){
        Serial.println("END");
        digitalWrite(SOL_PWM, LOW);
        while(true){}
      }
    }


  }

}