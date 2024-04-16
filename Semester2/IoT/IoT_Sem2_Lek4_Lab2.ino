int motor_pin = 8; // PWM pin / the number of the motor pin


void initPwmTimer4(int percentageDutyCycle, int freq) 
{
  noInterrupts();
  TCCR4A = 0; // clear register
  TCCR4B = 0; // clear register
  TCNT4  = 0; // clear register

  // Mode 10: phase correct PWM with ICR4 as Top (= F_CPU/2/?)
  // OC4C as Non-Inverted PWM output
  ICR4   = (F_CPU/freq)/2;  // Timer/Counter4 - Input Capture Register
  OCR4C  = ICR4 * ((float)(percentageDutyCycle/100.0));        // Timer/Counter4 - Output Compare Register C
  TCCR4A = _BV(COM4C1) | _BV(WGM41);
  TCCR4B = _BV(WGM43) | _BV(CS40);
  interrupts();
}

void setup() {

  Serial.begin(9600);

  pinMode(motor_pin, OUTPUT); // initialize pin as an output:


  pinMode(A1, INPUT); // initialize pin as an input

  //set_duty_cycle(50);
  //initPwmTimer4(50, 25000);
}

void loop() {
  int val = analogRead(A1);
  val = map(val, 512, 1023, 0, 100);
  Serial.println(analogRead(A1));
  set_duty_cycle(val);
  delay(500);

}

// 
void set_duty_cycle(int percentage) {
  int dutyCycle = (float)(percentage/100.0) * 255.0;
  //int dutyCycle = (float)(0.5)*255.0;
  analogWrite(motor_pin, dutyCycle); // analogWrite values from 0 to 255

  Serial.println("");
  Serial.print("PWM works on pin ");
  Serial.print(motor_pin);
  Serial.print(". The duty cycle is ");
  Serial.print(percentage);
  Serial.println("%.");
  Serial.println(dutyCycle);
}