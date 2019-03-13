If you plan to use an Arduino that requieres the Serial to MIDI conversion on a Raspberry pi (Raspbian or Ubuntu Mate),you cannot use Hairless serial to MIDI because it´s not available for ARM architectures.

For this reason, I created a very short script that solves this problem. It uses mido, rtmidi and pyserial python libraries to convert the serial messages coming from the arduino to MIDI messages. Best of all, you don´t have to change anything in the Arduino code, so you can use your keyboard on a RPI and then use it on another PC.


Here is the procedure that you have to follow:

1-Connect the keyboard to your RPI

2-Use ls /dev/ on a terminal to find your keyboard. Depending on your Arduino, it can be listed in different ways. It could appear as ttyUSB0, ttyACM0, or another; but usually those 2 are the commons ones.

3-Give permissions to open the device:
  
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
    
    
