
#include <QuadDisplay.h>
#define PN 0x04

#define NEGLOG  0

int istate;
int ii,iio;
int tt1, tt2;
unsigned long t1, t2;
int pin = 2;
uint8_t pDisp0;    // point

/*@brief 
 * Initialize pins and interruptions
 */
void setup(void)
{
//    pinMode(2, INPUT);
//    pinMode(13, OUTPUT);
    ii = 0; // set initial Value of counter to 0.
    iio = 0; // set initail Value of old-counter to 0
    tt1 = 0;
    tt2 = 0;

    DDRB |= 0x31; // output PB0(pin8)-Display, PB4(pin12) and PB5(pin13);
    PORTB &=~0x31;
    DDRD &= ~PN; 
    PORTD &= ~PN;

    pDisp0 = 8;        // pointer to number of PD4 (pin04) defined as output for Display

    sei();                    // Enable global interrupts
//    digitalWrite(2, HIGH);    // Enable pullup resistor
//    EIMSK |= (1 << INT0);     // Enable external interrupt INT0
//    EICRA |= (1 << ISC01);    // Trigger INT0 on falling edge
//    attachInterrupt(digitalPinToInterrupt(pin), blinks, CHANGE); 
}
                              //
/*@brief 
 * Main cycle
 */
void loop(void)
{
  istate = PIND & PN;
  
  if ( istate == PN){
//    t1 = micros();
    t1 = millis();
    PORTB |= 0x20;
    while (istate == PN){
      istate = PIND & PN;
    }
    if ( istate != PN){
//      t2 = micros();
      t2 = millis();
      if (ii< 10) ii++;
      tt1 = (int)(t2-t1);
      tt2 = (tt2 * iio + tt1) / ii;
      if (iio < 9) iio = ii - 1;
      displayInt(pDisp0,tt1);
      delay(20);
      PORTB &= ~0x20;
    }
  }
//  PORTB &= ~0x20;
//  delay(10);
}
                              //
// Interrupt Service Routine attached to INT0 vector
//ISR(EXT_INT0_vect)
void blinks()
{
  istate = PINB & 0x10;
  
  if ( istate == 0x10){
//    t1 = micros();
    PORTB &= ~0x10;
  } else {
    PORTB |= 0x10;
  }
}


