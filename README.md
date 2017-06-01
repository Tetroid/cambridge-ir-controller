cambridge-ir-controller
===

Description
---
Send IR commands to cambridge audio 651A through the IR jack input from network.
First approach is to create an arduino web server that receive HTTP requests and convert them into IR commands.

How it works
---

This sketch is based on the library irremote.h for Arduino. for more information see the Github [here](https://github.com/z3t0/Arduino-IRremote). The board I've used is Arduino Uno R3 + Ethernet shield. As the ATmega on this board is ATmega328, it means that the signal output is the pin 3 in my case.

The arduino board is running a web server on port 80 which parse parameters of http GET requests. Syntax must be of type  "http://IP_ADDRESS/?COMMAND".

Regarding the command sent in parameter, the appropriate IR signal will be sent. I've included a conversion table for Cambridge Audio 651A IR codes so as to have them in the right hex formatting. They are availlable [here](http://newarchive.cambridgeaudio.com/media/azur651a_ircodes-1354625353.pdf). RC5 protocol ([see wikipedia](https://en.wikipedia.org/wiki/RC-5)) is encoded on 14 bits.

An example below for "source 1" :
System address can be converted into 5 bits : 16 => 10000
Command can be converted into 6 bits : 2 => 000010
Then we add start bit (1) field bit (1) toggle bit (0 or 1) at beginning and convert to hex : 0xC02

Given that Cambridge Audio 651A has a IR input port, you can directly use a jack cable and avoid occlusion problems using a LED emitter. Ground is linked to GND pin, head pin is linked to signal pin (pin 3 for Arduino Uno) with a serial resistor.

Possible evolution is to use a cheaper arduino pro mini 3v3 board and link it to a raspberry pi zero. This will allow to have a more advanced wed server (relying on node.js for example) and pass commands to Arduino through TTL.

Licence
---
This project is under MIT License, copyright (c) 2017 Jean-Baptiste GUYARD

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
