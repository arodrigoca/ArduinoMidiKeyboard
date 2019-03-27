import serial
import mido

s = serial.Serial('/dev/ttyUSB0', 115200, timeout = None)
#print(mido.get_output_names())
mido.open_output()
outport = mido.open_output()
try:
    while True:

        message = s.read(3)
        msg_output = mido.Message.from_bytes(message)
        #print(msg_output)
        outport.send(msg_output)

except KeyboardInterrupt:

    s.close()
