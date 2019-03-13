import serial
import mido

s = serial.Serial('/dev/ttyUSB0', 115200, timeout = None)
#print(mido.get_output_names())
mido.open_output('Midi Through:Midi Through Port-0 14:0')
outport = mido.open_output()
try:
    while True:

        message = s.read(3)
        byte_1 = message[0]
        byte_2 = message[1]
        byte_3 = message[2]
        message = [byte_1, byte_2, byte_3]
        msg_output = mido.Message.from_bytes(message)
        #print(msg_output)
        outport.send(msg_output)

except KeyboardInterrupt:

    s.close()
