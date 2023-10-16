# define EMIT_PIN    11    // Documentation says 11.
# define LS_MID_PIN 20 
# define LS_LEFT_PIN 18
# define LS_RIGHT_PIN 21


float results_LEFT; // An array of MAX_SAMPLES length
float results_MID;
float results_RIGHT;
void setup() {

  // Set some initial pin modes and states
  pinMode( EMIT_PIN, INPUT ); // Set EMIT as an input (off)
  pinMode( LS_MID_PIN, INPUT );     // Set line sensor pin to input
   pinMode( LS_LEFT_PIN, INPUT );
    pinMode( LS_RIGHT_PIN, INPUT );

  // Start Serial, wait to connect, print a debug message.
  Serial.begin(9600);
  delay(1500);
  Serial.println("**RESET**");

} // End of setup()


void loop() {

  pinMode( EMIT_PIN, OUTPUT );
  digitalWrite( EMIT_PIN, HIGH );
  pinMode( LS_MID_PIN, OUTPUT );
  digitalWrite( LS_MID_PIN, HIGH );
    pinMode( LS_LEFT_PIN, OUTPUT );
  digitalWrite( LS_LEFT_PIN, HIGH );
    pinMode( LS_RIGHT_PIN, OUTPUT );
  digitalWrite( LS_RIGHT_PIN, HIGH );
  delayMicroseconds( 10 );
  


  
  pinMode( LS_MID_PIN, INPUT);
  unsigned long start_time_M = micros();
  while( digitalRead(LS_MID_PIN) == HIGH ) {
      // Do nothing here (waiting).
  }
  unsigned long end_time_M = micros();
  pinMode( EMIT_PIN, INPUT );
  unsigned long elapsed_time_M = end_time_M - start_time_M;
  results_MID = (float)elapsed_time_M;

  pinMode( LS_LEFT_PIN, INPUT);
  unsigned long start_time_L = micros();
  while( digitalRead(LS_LEFT_PIN) == HIGH ) {
      // Do nothing here (waiting).
  }
  unsigned long end_time_L = micros();
  pinMode( EMIT_PIN, INPUT );
  unsigned long elapsed_time_L = end_time_L - start_time_L;
  results_LEFT = (float)elapsed_time_L;

  pinMode( LS_RIGHT_PIN, INPUT);
  unsigned long start_time_R = micros();
  while( digitalRead(LS_RIGHT_PIN) == HIGH ) {
      // Do nothing here (waiting).
  }
  unsigned long end_time_R = micros();
  pinMode( EMIT_PIN, INPUT );
  unsigned long elapsed_time_R = end_time_R - start_time_R;
  results_RIGHT = (float)elapsed_time_R;
  
  delay(200);

  Serial.println ("Left" );
  Serial.println (results_LEFT);
  Serial.println ("Mid" );
  Serial.println (results_MID);
  Serial.println ("Right" );
  Serial.println (results_RIGHT);
  

      delay(100);
  }



// End of loop()
