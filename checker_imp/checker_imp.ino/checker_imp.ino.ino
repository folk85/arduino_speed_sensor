int ts = 15; // Set the base width of the impulse
int tw = 7;
int t1,t2;
long tr;
int t_frames[] ={2000,1000,500,200,100,25}; // Set Times of period
int8_t i; 

void setup() {
  // put your setup code here, to run once:
  DDRB |= 0x20; // output PB5(pin13)-LED;
  PORTB &=~0x20;
  DDRD |= 0x80; // output PD7(pin7)-SIGNAL;
  PORTD &=~0x80;

  t1 = ts - tw;
  t2 = ts + tw + 1;
  i = 5; // set initial value 2 to get impulse with 2 Hz
  
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  PORTB |= 0x20; // set HIGH for pin8 and pin13;
  PORTD |= 0x80; // set HIGH for pin7 and pin13;
  delayMicroseconds(ts);
//  delay(ts);
  PORTD &= ~0x80; // set LOW for pin8;
  delay(10);
  PORTB &= ~0x20; // set LOW for pin13;
  delay(t_frames[i]-10);
}
