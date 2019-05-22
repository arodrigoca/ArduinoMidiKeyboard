#!/bin/bash
dbus-launch jackd -P70 -p16 -t2000 -dalsa -dhw:Device -p256 -n3 -r44100 -s &> logs/jack_log.log &
sleep 4
/home/pi/sunvox/sunvox/linux_arm_armhf_raspberry_pi/sunvox &
sleep 8
a2jmidid -e &> logs/a2jmidi.log &
sleep 3
jack_connect a2j:'UNO_AND_MIDI [20] (capture)':' UNO_AND_MIDI MIDI 1' SunVox:Keyboard1 &> logs/jack_connect.log
sleep 4
python3 synth_ready_led.py &
