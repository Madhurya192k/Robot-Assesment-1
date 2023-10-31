#define EMIT_PIN 11
#define L_PWM_PIN 10
#define L_DIR_PIN 16
#define R_PWM_PIN 9
#define R_DIR_PIN 15
#define FWD LOW
#define REV HIGH
 float DN_2;
 float DN_4;
 float DN_3;
 float W;
 float N[3];
 int BiasPWM = 18;
int MaxTurnPWM = 20;
float N1;
float N3;
const int MaxSensors = 3;  // Define the number of line sensors
int SensorPins[MaxSensors] = {18, 20, 21};  // Define sensor pins
unsigned long Rn[MaxSensors];  // Array to store sensor readings

// Define labels for the sensors
const char* SensorLabels[MaxSensors] = {"Left", "Middle", "Right"};

void setup() {
  pinMode (EMIT_PIN, INPUT);

  // Set OUTPUT pins HIGH to charge sensors
  for (int n = 0; n < MaxSensors; n++) {
    pinMode(SensorPins[n], INPUT);
  }

  Serial.begin(9600);
  delay(2000);
}

void loop() {
  pinMode(EMIT_PIN, OUTPUT);
  digitalWrite(EMIT_PIN, HIGH);

  for (int n = 0; n < MaxSensors; n++) {
    pinMode(SensorPins[n], OUTPUT);
    digitalWrite(SensorPins[n], HIGH);
  }

 delayMicroseconds(10);

  // Set INPUT pins for sensor readings
  for (int n = 0; n < MaxSensors; n++) {
    pinMode(SensorPins[n], INPUT);
  

  unsigned long t_start = micros();
 
    
      while(digitalRead(SensorPins[n]) == HIGH) {}
        unsigned long t_end = micros();
        Rn[n] = t_end - t_start;
        
      }
    
  

  // Print sensor readings with labels
  for (int n = 0; n < MaxSensors; n++) {
    Serial.print(SensorLabels[n]);  // Use the sensor label
    Serial.print(" Reading: ");
    Serial.println(Rn[n]);
  }
 DN_2=Rn[0];
 DN_4=Rn[2];
 DN_3=Rn[1];

 int check= OnLine(DN_2,DN_3,DN_4);
 if (check==1)
 {setMotorPower(0.0, 0.0);
 delayMicroseconds(1000);

  //delay(500);
  //Code to turn the motor aroung by 180 degrees and this may take 3-4 seconds. That has to be taken into account too./
  turn(-18,18);
  }
  
  if (check==2)
  {
    setMotorPower(0.0,0.0);
    delayMicroseconds(1000);
    turn(18,-18);
    }
    
  
 
 else
 {

   W = weightedMeasurement();
   Serial.println ("Weighted value");
   Serial.println(W);
  // Calculate motor PWM values
  float LeftPWM = BiasPWM + (W * MaxTurnPWM);
  float RightPWM = BiasPWM - (W * MaxTurnPWM);
  
  setMotorPower(LeftPWM, RightPWM);
}
}
 


 float weightedMeasurement() {
  // DN2 and DN4 are now read from the second program
  float Sum = DN_2 + DN_4;
  for(int i=0;i<3;i++)
  {
    N[i]=Rn[i]/Sum;
    N[i]=N[i]*2.0;
  
  }
  Serial.println(N[0]);
  Serial.println(N[1]);
  float w = (N[0] - N[2]);

  return w;
}
void setMotorPower(float LeftPWM, float RightPWM) {
 analogWrite(L_PWM_PIN, abs(LeftPWM));
 analogWrite(R_PWM_PIN, abs(RightPWM));
}
int OnLine(float k, float l, float m)
{
  if (k<1300&&l<1300&&m<1300)
  return 1;
  if (k<1300&&l<1300&&m>1300)
  return 2;
 
  else
  return 4;
}
void turn(int val1, int val2)
{
  analogWrite (L_PWM_PIN, val1);
  analogWrite (R_PWM_PIN, val2);

}
