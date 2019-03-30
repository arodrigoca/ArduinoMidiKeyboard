import time
import keyboard
from bluetooth import *
import subprocess

global volume
volume = 70

def init_keyboard():

    keyboard.press("shift")
    keyboard.release("shift")


def config_bt():

    global server_sock
    server_sock=BluetoothSocket( RFCOMM )
    server_sock.bind(("",PORT_ANY))
    server_sock.listen(1)

    global port
    port = server_sock.getsockname()[1]

    uuid = "94f39d29-7d6d-437d-973b-fba39e49d4ee"

    advertise_service( server_sock, "SampleServer",
                       service_id = uuid,
                       service_classes = [ uuid, SERIAL_PORT_CLASS ],
                       profiles = [ SERIAL_PORT_PROFILE ])


def generator_up():

    print("Gen Up")
    keyboard.send("ctrl+UP")


def generator_down():

    print("Gen Down")
    keyboard.send("ctrl+DOWN")


def volume_change(command):

    print("Volume up command")
    volume_cmd = "amixer sset 'Speaker' " + command + "%"
    volume = command
    print(volume)
    subprocess.call(volume_cmd, shell=True)


def mute_command(mute):

    print("Mute button")

    if(mute.mute == False):
        subprocess.call("amixer sset 'Speaker' mute", shell=True)
        mute.mute = True

    else:
        subprocess.call("amixer sset 'Speaker' unmute", shell=True)
        mute.mute = False
        print("Unmuted")



def start_bt():

    print("Waiting for connection on RFCOMM channel %d" % port)
    global client_sock, client_info
    client_sock, client_info = server_sock.accept()

    print("Accepted connection from ", client_info)
    class mute_object:

        def __init__(self):
            self.mute = False

    mute = mute_object()

    while True:
        data = client_sock.recv(1024)
        if len(data) == 0: break
        #print("received [%s]" % data)
        #print(data.decode("utf-8"))
        command = data.decode("utf-8")
        if(command == "gen_up"):
            generator_up()

        elif(command == "gen_down"):
            generator_down()


        elif(command == "mute"):

            mute_command(mute)

        else:

            volume_change(command)



subprocess.call("amixer sset 'Speaker' 70%", shell=True)
init_keyboard()
config_bt()

try:
    start_bt()

except IOError:

    client_sock.close()
    start_bt()


except KeyboardInterrupt:

    client_sock.close()
    server_sock.close()
