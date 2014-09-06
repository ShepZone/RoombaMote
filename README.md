RoombaMote
==========
RoombaMote is a project designed to allow an Arduino to interface with late-model Roombas (in my case, the 550/551) to control them via a simple Infared remote. The parts are cheap and readily available, and it allows you to offer full control of it utilizing the remote.

Parts Needed
------------
- [DC Boarduino]
- [FTDI Serial USB Cable] (or other FTDI cable)
- Male Power Adapter [Terminal] - OR - [Alligator Clip] (only need one)
- [DC Switch]
- [IR Remote]
- [IR Receiver]
- Old PS/2 cable (with plug)
- Solder
- Soldering iron

Controls
--------
STOP/MODE
- Turns Roomba Control Mode on and off (Boarduino red LED is on when Control Mode is active, off when disabled)

When Control Mode is active, the following functions are enabled. Otherwise, they are disabled:

PLAY/PAUSE BUTTON:
- Starts/Stops vacuum motors (side brush, main brush, and vacuum)

UP/DOWN:
- Moves forward/backward

LEFT/RIGHT:
- On-the-spot turning

ENTER/SAVE:
- Stops all movement except for motors

**More to come!**

[DC Boarduino]:https://www.adafruit.com/products/72
[FTDI Serial USB Cable]:https://www.adafruit.com/products/70
[Terminal]:https://www.adafruit.com/products/369
[Alligator Clip]:https://www.adafruit.com/products/1329
[DC Switch]:https://www.adafruit.com/products/1125
[IR Remote]:https://www.adafruit.com/product/389
[IR Receiver]:https://www.adafruit.com/products/157
