# ArduinoMidiKeyboard
A little project to transform an old Casio to be MIDI capable.

Hi! In this repository it's the code from my newest project. I bought an olc Casio Tone Bank M-130, a very simple electric piano that had only the sounds coming from its very bad and cheap audio processor to convert it to a MIDI keyboard. The steps I followed to do this:

1-Bought the keyboard.

2-Figured out the input scan matrix, which I determined it to be a 9 rows 6 columns matrix (so 9 inputs and 6 outputs). I did this with a multimeter and the Arduino Keypad library. I plan to upload the exact method that I followed so you can do it too.

3-Tested all the keys were working using the Keypad library.

4-Completed the keys array that the Keypad library needs to work. For this, as my keyboard has 49 keys, I decided which MIDI note would map to each key. 49 keys keyboard usually have C2 as the lower note and C6 as the highest note. Then, I looked up the MIDI note table to see what MIDI note number corresponded to what note. I made a mistake and made the keys array with the lowest MIDI note being 36, which is C1. Because I noticed this after being done with the keys array, I fixed it by adding an octave (12) to the MIDI note (it is commented in the code).

5-Once I had that, I started coding the MIDI part. It was really simple, as MIDI library already has functions like send note off or on. My keyboard has only ON or OFF switches, so in this case MIDI velocity is set to 127 for all notes.

6-I wanted to use the USB interface for MIDI because it is very convenient. Not all sound cards have MIDI port (my case, Scarlett 2i2). I installed the Hairless MIDI software, that allows using a COM port as MIDI. To make it work, just added Serial.begin(115200) after the MIDI.begin(1) in the setup section.

8-Checked the Hairless MIDI program received MIDI notes from the keyboard.
