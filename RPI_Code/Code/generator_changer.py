import time
import keyboard
from bluetooth import *
import subprocess

global volume
volume = 70

def init_keyboard():

    keyboard.press("shift")
    keyboard.release("shift")


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



subprocess.call("amixer sset 'Speaker' 70%", shell=True)
init_keyboard()

try:

    server_sock=BluetoothSocket( RFCOMM )
    server_sock.bind(("",PORT_ANY))
    server_sock.listen(1)

    port = server_sock.getsockname()[1]

    uuid = "94f39d29-7d6d-437d-973b-fba39e49d4ee"

    advertise_service( server_sock, "TestServer",
                       service_id = uuid,
                       service_classes = [ uuid, SERIAL_PORT_CLASS ],
                       profiles = [ SERIAL_PORT_PROFILE ],
    #                   protocols = [ OBEX_UUID ]
                        )

    print ("Waiting for connection on RFCOMM channel %d" % port)

    client_sock, client_info = server_sock.accept()
    print ("Accepted connection from ", client_info)

    while True:


        try:
            data = client_sock.recv(1024)
            if len(data) == 0: break
            command = data.decode("utf-8")
            if(command == "gen_up"):
                generator_up()

            elif(command == "gen_down"):
                generator_down()


            elif(command == "mute"):

                mute_command(mute)

            else:

                volume_change(command)

        except IOError:
            print("Client disconnected")
            client_sock, client_info = server_sock.accept()
            print ("Accepted connection from ", client_info)

        except KeyboardInterrupt:

            print ("disconnected")

            client_sock.close()
            server_sock.close()
            print ("all done")

            break

except KeyboardInterrupt:

    client_sock.close()
    server_sock.close()
