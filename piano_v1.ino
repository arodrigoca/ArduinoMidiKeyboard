
#include <Keypad.h>
#include <MIDI.h>

int lastPitchValue;
bool pastBend;

MIDI_CREATE_DEFAULT_INSTANCE();

const byte ROWS = 9;
const byte COLS = 6;
char keys[ROWS][COLS] = {
{48,49,50,51,52,53},
{60,61,62,63,64,65},
{66,67,68,69,70,71},
{72,73,74,75,76,77},
{78,79,80,81,82,83},
{84,0,0,0,0,0},
{54,55,56,57,58,59},
{42,43,44,45,46,47},
{36,37,38,39,40,41}
};
byte rowPins[ROWS] = {38, 36, 34, 32, 30, 28, 26, 24, 22}; //digital pins on the MEGA
byte colPins[COLS] = {50, 48, 46, 44, 42, 40};


Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String msg; //for debugging


void setup() {
    lastPitchValue = 403; //rest position reading of my potentiometer
    pastBend = false; //to keep track of the bend. This allows the code to know when you started a bend and when you finished so the code doesn't send a: no pitch change message all the time
    pinMode(A0, INPUT); //input pin for the potentiometer
    MIDI.begin(1);
    Serial.begin(115200); //for Hairless software
}


void loop() {

    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
                int midinote = kpd.key[i].kchar; //convert the midi note to int from char
                
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED: //this messages are for debugging so they are not necessary.
                    //msg = " PRESSED.";
                    MIDI.sendNoteOn(midinote+12, 127, 1); //12 is an octave shift (I developed all the code so C1 was the lowest note. With this, it is C2 instead).
                break;
                    case RELEASED:
                    //msg = " RELEASED.";
                    MIDI.sendNoteOff(midinote+12, 127, 1);
                break;
                }
                //Serial.print("Key ");
                //Serial.print(kpd.key[i].kchar);
                //int aux = kpd.key[i].kchar;
                //Serial.println(aux);
                //Serial.println(msg);
            }
        }
    }

    //pitch bend code

    int value = analogRead(A0);
  //Serial.println(value);
    if(value > 415 || value < 390){ //my potentiometer is not very good, the value read in the resting position varies a little bit
      if(value >= 560){
        value = 560;
      }else if(value <= 153){
        value = 153;
      }
    
      value = map(value,158,566,-8190,8190);
      if(abs(value - lastPitchValue) >= 100){
        MIDI.sendPitchBend(value, 1);
        pastBend = true;
        lastPitchValue = value;
      }
    }else if(pastBend == true){ //if the stick is back on the resting position, just send 1 MIDI message to return the pitch to normal state
      MIDI.sendPitchBend(0, 1);
      pastBend = false;
  }
}  
