import serial
import mido
import time


def init_serial():

    global s
    s = serial.Serial('/dev/ttyUSB0', 115200, timeout = None)


def check_connection():

    try:

        init_serial()

    except serial.serialutil.SerialException:

        print('MIDI device not connected. Retrying in 1 second')
        time.sleep(1)
        #check_connection()


def main():

    print('MIDI device is connected. Ready for input!')
    try:

        while True:

            message = s.read(3)
            msg_output = mido.Message.from_bytes(message)
            #print(msg_output)
            outport.send(msg_output)

    except KeyboardInterrupt:

        s.close()
        print('Closing program!')

    except serial.serialutil.SerialException:

        print('MIDI device has been disconnected. Attemping to reconnect...')
        s.close()
        check_connection()
        main()


check_connection()
#print(mido.get_output_names())
#mido.open_output()
outport = mido.open_output()
main()
