import RPi.GPIO as GPIO
import subprocess
import os
import socket
import sys

GPIO.setmode(GPIO.BCM)
GPIO.setup(9, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(24, GPIO.OUT)
FNULL = open(os.devnull, 'w')


def shutdown_system(channel):

    subprocess.Popen("sudo poweroff", shell=True)


channel = GPIO.wait_for_edge(9, GPIO.FALLING, bouncetime=300)
shutdown_system(channel)
GPIO.output(24, 0)
