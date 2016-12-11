
long microMilli = 0;
void setup(){
   pinMode( 2, OUTPUT);
   pinMode( 3, OUTPUT);
   pinMode( 4, OUTPUT);
   pinMode( 5, OUTPUT);
   pinMode( 6, OUTPUT);
   pinMode( 7, OUTPUT);
   pinMode( 8, OUTPUT);
   pinMode( 9, OUTPUT);
   pinMode(10, OUTPUT);
   pinMode(11, OUTPUT);
   pinMode(12, OUTPUT);
   pinMode(13, OUTPUT);
   pinMode(A0, OUTPUT);
   pinMode(A1, OUTPUT);
   pinMode(A2, OUTPUT);
   pinMode(A3, OUTPUT);
   pinMode(A4, OUTPUT);
   pinMode(A5, OUTPUT);
   Serial.print("A0 "); Serial.println(A0);
   Serial.print("A1 "); Serial.println(A1);
   Serial.print("A5 "); Serial.println(A5);
   microMilli = micros();
}


long milli = 0;
long sec = 0;
long cntMilli = 0;
long cntCenti = 0;
long cntSec = 0;
long loopCnt = 0;
void loop(){
   long micro = micros();

   loopCnt++;
   digitalWrite(2, (loopCnt&1) ? HIGH : LOW);  // How fast do we go ?

   if (micro - microMilli < 200)
      return;
   microMilli += 200;
   digitalWrite(3+cntMilli, LOW);  // Increasing duty cycle on 3..7
   if ((milli%12) == 1) {
       // RC servo pulse from 1 .. 2 millis in a 12 milli period
       digitalWrite(14 + cntMilli, LOW); // RC servo control
       digitalWrite(19, LOW); // RC servo control
   }
   if (cntMilli++ < 5)
      return;
   cntMilli = 0;
   digitalWrite(3, HIGH);  // Increasing duty cycle on 3..7
   digitalWrite(4, HIGH);  // Increasing duty cycle on 3..7
   digitalWrite(5, HIGH);  // Increasing duty cycle on 3..7
   digitalWrite(6, HIGH);  // Increasing duty cycle on 3..7
   digitalWrite(7, HIGH);  // Increasing duty cycle on 3..7

   milli++;
   cntSec++;
   digitalWrite( 8, (milli&4) ? HIGH : LOW); // 125 Hz for stepper /16 ~>  8 steps/sec
   digitalWrite( 9, (milli&2) ? HIGH : LOW); // 250 Hz for stepper /16 ~> 16 steps/sec
   digitalWrite(10, (milli&1) ? HIGH : LOW); // 500 Hz for stepper /16 ~> 32 steps/sec

   if ((milli%12) == 0) {
      digitalWrite(14, HIGH); // RC servo control
      digitalWrite(15, HIGH); // RC servo control
      digitalWrite(16, HIGH); // RC servo control
      digitalWrite(17, HIGH); // RC servo control
      digitalWrite(18, HIGH); // RC servo control
      digitalWrite(19, HIGH); // RC servo control
   }


   if (cntSec < 1000)
      return;
   cntSec = 0;
   digitalWrite(11, (sec&4) ? HIGH : LOW); // Stepper dir. 1/8 Hz
   digitalWrite(12, (sec&2) ? HIGH : LOW); // Stepper dir. 1/4 Hz
   digitalWrite(13, (sec&1) ? HIGH : LOW); // Stepper dir. 1/2 Hz -- Also the LED
}
// vim: set ts=3 sw=3 et:
