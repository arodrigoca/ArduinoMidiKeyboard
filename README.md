# ArduinoMidiKeyboard
A little project to transform an old Casio to be MIDI capable over USB. Im thinking about adding bluetooth to it, but not for now.

Note: in this tutorial, you will see that I use a software to create a virtual midi port. This is because my Arduino Mega is one of the cheaper ones, and have a different USB to Serial converter (CH340 chip in my case) which cannot be flashed with an HID capable firmware.
If you have an Arduino Mega with an 16u2 or 8u2 chip, you should be able to flash an HID capable firmware and thus, skip the additional software that I used. However, this last method has a disadvantage. If an HID firmware is installed, you won't be able to upload code to the Arduino until you go back to the old firmware. This is specially painful when debugging your project or updating it. My method allows you to upload new code whenever you want, let alone not having to deal with the firmware update.

Mega with 16u2/8u2 chip:

https://github.com/arodrigoca/ArduinoMidiKeyboard/blob/master/mega1.PNG

Mega with CH340 chip:

https://github.com/arodrigoca/ArduinoMidiKeyboard/blob/master/mega2.PNG


Hi! In this repository it's the code from my newest project. I bought an olc Casio Tone Bank M-130, a very simple electric piano that had only the sounds coming from its very bad and cheap audio processor to convert it to a MIDI keyboard. The steps I followed to do this:

1-Bought the keyboard.

2-Figured out the input scan matrix, which I determined it to be a 9 rows 6 columns matrix (so 9 inputs and 6 outputs). I did this with a multimeter and the Arduino Keypad library. I plan to upload the exact method that I followed so you can do it too.

3-Tested all the keys were working using the Keypad library.

4-Completed the keys array that the Keypad library needs to work. For this, as my keyboard has 49 keys, I decided which MIDI note would map to each key. 49 keys keyboard usually have C2 as the lower note and C6 as the highest note. Then, I looked up the MIDI note table to see what MIDI note number corresponded to what note. I made a mistake and made the keys array with the lowest MIDI note being 36, which is C1. Because I noticed this after being done with the keys array, I fixed it by adding an octave (12) to the MIDI note (it is commented in the code).

5-Once I had that, I started coding the MIDI part. It was really simple, as MIDI library already has functions like send note off or on. My keyboard has only ON or OFF switches, so in this case MIDI velocity is set to 127 for all notes.

6-I wanted to use the USB interface for MIDI because it is very convenient. Not all sound cards have MIDI port (my case, Scarlett 2i2). I installed the Hairless MIDI software, that allows using a COM port as MIDI. To make it work, just added Serial.begin(115200) after the MIDI.begin(1) in the setup section.

7-Checked the Hairless MIDI program received MIDI notes from the keyboard. It did.

8-Then, I installed the loopMIDI software. It allows to connect HairlessMIDI to any DAW or MIDI instrument program like synths. Just create a virtual port and then in Hairless select in MIDI out the port that you created before.

9-Tried in Cubase and it worked perfectly.

10-I wanted to add a pitch bend wheel, so I grabbed an old RC controller stick (It is just a potentiometer) and connected it to A0, 5v and GND in the Mega. Added some more code to make it work and it was done. I had to put some value margins as the potentiometer was not very good, but the result was good in the end.

Libraries or software used. Please consider supporting the people that made all this incredible code to make our lifes easier :)

Keypad - https://github.com/Chris--A/Keypad.git

MIDI -   https://github.com/FortySevenEffects/arduino_midi_library.git

Hairless Serial port to MIDI - http://projectgus.github.io/hairless-midiserial/

loopMIDI - https://www.tobias-erichsen.de/software/loopmidi.html
