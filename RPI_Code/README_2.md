If you plan to use an Arduino that requieres the Serial to MIDI conversion on a Raspberry pi (Raspbian or Ubuntu Mate),you cannot use Hairless serial to MIDI because it´s not available for ARM architectures.

For this reason, I created a very short script that solves this problem. It uses mido, rtmidi and pyserial python libraries to convert the serial messages coming from the arduino to MIDI messages. Best of all, you don´t have to change anything in the Arduino code, so you can use your keyboard on a RPI and then use it on another PC.


Here is the procedure that you have to follow:

1-Connect the keyboard to your RPI

2-Use ls /dev/ on a terminal to find your keyboard. Depending on your Arduino, it can be listed in different ways. It could appear as ttyUSB0, ttyACM0, or another; but usually those 2 are the commons ones.

3-Give permissions to open the device. Change the /dev/xxx value to your value:
  
    sudo chmod 666 /dev/ttyUSB0
  
    cd /etc/udev/rules.d
  
    sudo touch my-newrule.rules
  
    sudo nano my-newrule.rules  <--this will open the file to edit. Copy this line inside and save your changes.
  
    KERNEL=="ttyUSB0", MODE="0666"

4-Now, it´s time to get all python dependencies:


    sudo apt-get update
    sudo apt-get install build-essential
    sudo apt-get install libasound2-dev
    sudo apt-get install libjack0
    sudo apt-get install libjack-dev
    sudo apt-get install python-pip3
    sudo apt-get install python-dev
    sudo pip3 install python-rtmidi
    sudo pip3 install pyserial
    sudo pip3 install mido

5-Now go to the serial_to_midi.py and look at this line:

    s = serial.Serial('/dev/ttyUSB0', 115200, timeout = None)
    
   Change your first parameter to match your device name.

6-Now, you can open a new terminal and open the python3 interpreter:

    python3
    
    >>>import mido
    >>>print(mido.get_output_names())
    
  This will give an array with all the available midi output ports that the script can use. In my case:
  
    ['Midi Through:Midi Through Port-0 14:0']
  
  The output that you will get, will be very simmilar to this one. If you get more than one element in the array, search for the        one containing Port-x 
   
  Then, go ahead and change this line of code:
  
    mido.open_output('Midi Through:Midi Through Port-0 14:0')
    
  Put the string that you got inside the array as parameter. This will tell mido to use this port to send messages.
 
 7-Save your file. Then, you can run the script by typing:
 
      python3 serial_to_midi.py
 
 And it should be done! You can uncomment the print(msg_output) to see what messages are being sent when you press on the keyboard.

8-Open your synth software and try to play the keyboard. It should work.
