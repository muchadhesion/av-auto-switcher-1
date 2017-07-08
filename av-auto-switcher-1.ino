
#include <IRremote.h>

IRsend irsend;

// Enter (integer) send-code on Serial and will be replayed on IR sender on PIN 3

// RC5 http://lirc.sourceforge.net/remotes/rc-5/RC-5-extented
// # Bit   0    1   2   3    4    5    6    7    8    9    10   11   12   13
// #     | S |~C6 | T | A4 | A3 | A2 | A1 | A0 | C5 | C4 | C3 | C2 | C1 | C0 |

// http://lirc.10951.n7.nabble.com/Marantz-RC5-22-bits-Extend-Data-Word-possible-with-lircd-conf-semantic-td9784.html
// BIT 0  1    2    3  4  5  6  7        8  9  10 11 12 13 14 15 16 17 18 19
// START,~C6,TOGGLE,S4,S3,S2,S1,S0,PAUSE,C5,C4,C3,C2,C1,C0,D5,D4,D3,D2,D1,D0 

#define OPT_JACK_PIN A0  // 3 pins, Vout, +5v and GND
#define TEST_PIN 7  // INPUT_PULLUP - switch - GND
#define IR_SEND_PIN 3 // IR tx - resistor 220k - GND

// Optical reads at 1023 when off.  Averages at 400-900 during playback.
// Wobbles around 400 when disconnected
#define OPT_JACK_HIGH_LOW_TRIGGER 1015

int optJackPrev = 0;
int optJackMovingAverage = 0;

int movingAverage(int currentAvg, int new_sample)
{
  #define ALPHA 0.8
  float ma_new = ALPHA * new_sample + (1-ALPHA) * currentAvg;
  return (int) ma_new;
}


void onOptJackData()
{
  Serial.println("onOptJackData");
  // # Bit   0    1   2   3    4    5    6    7    8    9    10   11   12   13
  // #     | S |~C6 | T | A4 | A3 | A2 | A1 | A0 | C5 | C4 | C3 | C2 | C1 | C0 |
  // CD select
 
  // .c TSSS SSCC CCCC  
  //  1 0100 0011 1111  // 143f  CD // s=20 0x14 c=63 0x3f x=na
  //  1 0101 0011 1111  // 153f  CD,
  //  1 1101 0011 1111  // 1d3f  CD Toogle
  // 11 0101 0011 1111  // send(153f) rec; 

  irsend.sendRC5(0x153f, 12); // assumes IR_SEND_PIN=3

}

void onOptJackNoData()
{
  Serial.println("onOptJackNoData");
}

void setup() {
  // init
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TEST_PIN, INPUT_PULLUP);

  // Pre-load triggers and averages with current readings
  int optJackPrev = analogRead( OPT_JACK_PIN );
  optJackMovingAverage = optJackPrev;
}

void loop() {
  // put your main code here, to run repeatedly:

  if ( digitalRead(TEST_PIN) != HIGH ) // configured as PULLUP
  {
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
    onOptJackData();
  } else {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  }

  int optJackSensorValue = analogRead(A0);
  optJackMovingAverage = movingAverage(optJackMovingAverage, optJackSensorValue);
  Serial.print("\t");   Serial.println(optJackMovingAverage);

  if ((optJackMovingAverage <= OPT_JACK_HIGH_LOW_TRIGGER) && optJackPrev > OPT_JACK_HIGH_LOW_TRIGGER)
  {
    onOptJackData();
  } else if ((optJackMovingAverage > OPT_JACK_HIGH_LOW_TRIGGER) && optJackPrev <= OPT_JACK_HIGH_LOW_TRIGGER)
  {
    onOptJackNoData();
  }

  optJackPrev = optJackMovingAverage;
  
  delay(150);
}

