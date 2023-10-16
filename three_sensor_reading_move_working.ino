#define EMIT_PIN 11
#define L_PWM_PIN 10
#define L_DIR_PIN 16
#define R_PWM_PIN 9
#define R_DIR_PIN 15
#define FWD LOW
#define REV HIGH
 float DN_2;
 float DN_4;
 float W;
 int BiasPWM = 25;
int MaxTurnPWM = 35;
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
  delay(1500);
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
  }

  unsigned long t_start = micros();
  int SensorsStillReading = MaxSensors;

  while (SensorsStillReading > 0) {
    for (int n = 0; n < MaxSensors; n++) {
      if (digitalRead(SensorPins[n]) == LOW) {
        unsigned long t_end = micros();
        Rn[n] = t_end - t_start;
        SensorsStillReading--;
      }
    }
  }

  // Print sensor readings with labels
  for (int n = 0; n < MaxSensors; n++) {
    Serial.print(SensorLabels[n]);  // Use the sensor label
    Serial.print(" Reading: ");
    Serial.println(Rn[n]);
  }
 DN_2=Rn[0];
 DN_4=Rn[2];

   W = weightedMeasurement();
  // Calculate motor PWM values
  int LeftPWM = BiasPWM + (W * MaxTurnPWM);
  int RightPWM = BiasPWM - (W * MaxTurnPWM);
  setMotorPower(W);
}

 float weightedMeasurement() {
  // DN2 and DN4 are now read from the second program
  float Sum = DN_2 + DN_4;
  N1 = DN_2 / Sum;
  N3 = DN_4 / Sum;

  N1 *= 2.0; // Double Weighted
  N3 *= 2.0;

  float w = (N1 - N3);

  return w;
}
void setMotorPower(float k) {
  if (k > 0) {
    analogWrite(L_PWM_PIN, BiasPWM);
    analogWrite(R_PWM_PIN, MaxTurnPWM);
  } else if (k < 0) {
    analogWrite(L_PWM_PIN, MaxTurnPWM);
    analogWrite(R_PWM_PIN, BiasPWM);
  } else {
    analogWrite(L_PWM_PIN, BiasPWM);
    analogWrite(R_PWM_PIN, BiasPWM);
  }
}
  // Add a delay to slow down the readings (500 milliseconds)
 
  
