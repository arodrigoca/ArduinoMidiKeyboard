import RPi.GPIO as GPIO
import subprocess
import os
import sys
import keyboard

def generator_up():

    keyboard.send("shift")

GPIO.setmode(GPIO.BCM)
GPIO.setup(4, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(17, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

GPIO.add_event_detect(4, GPIO.RISING, callback=my_callback, bouncetime=300)
GPIO.add_event_detect(17, GPIO.RISING, callback=my_callback, bouncetime=300)
