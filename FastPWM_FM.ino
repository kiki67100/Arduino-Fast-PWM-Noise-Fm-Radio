/* A sketch that creates a 4MHz fast PWM and then modulates
 * upon it a simplistic version of the infamous riff from smoke on the water.
 * The signal can be heard as AM modulation in many frequencies up to 1.76 or
 * more gigahertz. Just connect a wire to the output pin and fire up your SDR.
 *
 * Marios Andreopoulos
 * GPL v3 License
 * 
 * Thanks to Marios Andreopoulos
 * Source : https://withinspecifications.30ohm.com/2014/03/09/Fast-PWM-EMI/
 *
 *  Create a about 96 MHZ Electromagnic Wave From Arduino can be listen from any FM RADIO
 */

#include <avr/io.h>
#include <util/delay.h>
#define DELAY 30000 // pause after each chord, usec

// Some basic chord frequencies. Think of the as ratio guides.
//    E4 = 330Hz
//    G4 = 392Hz
//    A4 = 440Hz
//    Bb4 = 466Hz

int main(void)
{
  pinMode(3, OUTPUT); // output pin for OCR2B

  // Set fast PWM
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS20);
  OCR2A = 3;
  OCR2B = 0;

  while (1) {
    // The riff is E G A / E G Bb A / E G A / G E

    E(); G(); A();
    _delay_us(DELAY);
    E(); G(); Bb(); A();
    _delay_us(DELAY);
    E(); G(); A();
    _delay_us(DELAY);
    G(); E();
    _delay_us(500000);

  }
}

void E()
{
  // A note's duration should be about 1 sec.
  // Freq * Period = 1, thus 1515usec = 1/330Hz.
  // Accordingly we calculate the other chords' periods as well. The code
  // below seems like it will give a duration  of 1 sec but instead gives
  // a duration of about 0.6sec which is nice too. What happens is that my
  // _delay_us() function is faster normal for some reason.
  for (int duration = 0; duration <= 330; duration++)
    {
      _delay_us(1515);
      if ( OCR2B < 3 )
        OCR2B += 1;
      else
        OCR2B = 0;
    }
  _delay_us(DELAY);
}

void G()
{
  for (int duration = 0; duration <= 392; duration++)
    {
      _delay_us(1275);
      if ( OCR2B < 3 )
        OCR2B += 1;
      else
        OCR2B = 0;
    }
  _delay_us(DELAY);
}

void A()
{
  for (int duration = 0; duration <= 440; duration++)
    {
      _delay_us(1136);
      if ( OCR2B < 3 )
        OCR2B += 1;
      else
        OCR2B = 0;
    }
  _delay_us(DELAY);
}
void Bb()
{
  for (int duration = 0; duration <= 466; duration++)
    {
      _delay_us(1072);
      if ( OCR2B < 3 )
        OCR2B += 1;
      else
        OCR2B = 0;
    }
  _delay_us(DELAY);
}