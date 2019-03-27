import RPi.GPIO as GPIO
import subprocess
import os
import sys

GPIO.setmode(GPIO.BCM)
GPIO.setup(19, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(23, GPIO.OUT)
FNULL = open(os.devnull, 'w')

def start_sunvox(channel):

    subprocess.Popen("./sunvox_start.sh", stdout=FNULL, stderr=subprocess.STDOUT)


GPIO.output(23, 1)
channel = GPIO.wait_for_edge(19, GPIO.FALLING, bouncetime=300)
GPIO.output(23, 0)
start_sunvox(channel)
