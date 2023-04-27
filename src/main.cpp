#include <Arduino.h>
#include <Stepper.h>

#define SOL_PWM 6
#define PUL 10
#define DIR 11
#define ENA 12
#define ORIGIN_LIMIT_SWITCH 5
#define ENDPOINT_LIMIT 1792000
#define SPEED_LIMIT 16000

int ENDPOINT = ENDPOINT_LIMIT;
int ROTATION_SPEED = 15000;
int FORWARD_SPEED = 800;
int REVERSE_SPEED = -800;
int POSITION = 0;
int stepCount = 0;
bool PULSE = false;

Stepper myStepper(400,PUL, DIR);

void setup() {

  Serial.begin(9600);
  pinMode(5, INPUT_PULLUP);
  pinMode(SOL_PWM, OUTPUT); 
  pinMode(ENA, OUTPUT);
  digitalWrite(ENA, HIGH);
  myStepper.setSpeed(15000);

  // put your setup code here, to run once:
}


//--------------------------------------------------------------

bool setEndPoint(int endpointStepCount){
  if((endpointStepCount > ENDPOINT_LIMIT) || (endpointStepCount <= 0))
  {
    return false;
  }
  else
  {
    ENDPOINT = endpointStepCount;
    return true;
  }

  return true;
}

//--------------------------------------------------------------

bool setSpeed(int speed){
  if((speed > SPEED_LIMIT) || (speed <= 0))
  {
    return false;
  }
  else
  {
    ROTATION_SPEED = speed;
    return true;
  }
}

//--------------------------------------------------------------

bool setReverseSpeed(int speed){

  return true;
}

//--------------------------------------------------------------

int returnToOrigin(){

  while(true)
  {
    myStepper.setSpeed(REVERSE_SPEED);

    if(digitalRead(ORIGIN_LIMIT_SWITCH) == LOW)
    {
      POSITION = 0;
      return 1;
    }
  }
}

//--------------------------------------------------------------



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