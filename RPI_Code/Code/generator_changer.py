import RPi.GPIO as GPIO
import time
import keyboard

def generator_up():

    keyboard.send("ctrl+UP")


def generator_up():

    keyboard.send("trl+DOWN")

GPIO.setmode(GPIO.BCM)
GPIO.setup(4, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(17, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

GPIO.add_event_detect(4, GPIO.RISING, callback=generator_up, bouncetime=300)
GPIO.add_event_detect(17, GPIO.RISING, callback=generator_down, bouncetime=300)

while True:
    time.sleep(0.01)
