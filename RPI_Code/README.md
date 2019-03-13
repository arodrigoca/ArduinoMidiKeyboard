If you plan to use an Arduino that requieres the Serial to MIDI conversion on a Raspberry pi (Raspbian or Ubuntu Mate),you cannot use Hairless serial to MIDI because it´s not available for ARM architectures.

For this reason, I created a very short script that solves this problem. It uses mido, rtmidi and pyserial python libraries to convert the serial messages coming from the arduino to MIDI messages.


Here is the procedure that you have to follow:



