<a href="https://github.com/mcgurk/Controller_adapter_for_NES/raw/master/Images/Wii-Classic-Controller_Arduino_NES.jpg"><img src="https://github.com/mcgurk/Controller_adapter_for_NES/raw/master/Images/Wii-Classic-Controller_Arduino_NES.jpg" height="300"></a>

# Wii Classic Controller to NES.

Works with normal Arduino with Atmega328P (5V 16MHz). I used Arduino Pro Mini (Arduino Pro Mini doesn't include USB-port - needs USB-serial adapter for programming). Arduino Nano may be better option, because it includes USB-port.

Lag under 1ms.

Compatible with PAL (50Hz) and NTSC (60Hz) (NTSC support not tested).

Arduino Pro Mini, AMS1117 regulator, signal voltage converter and Wii Classic Controller altogether 28mA.

## Images

https://github.com/mcgurk/Controller_adapter_for_NES/raw/master/Images/2016-11-10%2011.08.51.jpg

https://github.com/mcgurk/Controller_adapter_for_NES/raw/master/Images/2016-11-10%2011.23.53.jpg

## Connections

### Wii Classic Controller (I2C)

<a href="https://c2.staticflickr.com/8/7263/7085452395_c6897a4f2d_b.jpg"><img src="https://c2.staticflickr.com/8/7263/7085452395_c6897a4f2d_b.jpg" height="200"></a>

Arduino Uno/Pro Mini (ATmega328P): SDA = A4, SCL = A5

Leonardo/Pro Micro (ATmega32u4): SDA = D2, SCL = D3 (With ATmega32u4 you have to use some other pins for NES) 

Officially Wii extension controllers are 3.3V.  Might work with 5V. I used level converter with 3.3V AMS1117 regulator. Search from Ebay with Logic Level Converter Module AMS1117 DC 5V to 3.3V

### NES-controller:

<a href="http://psmay.com/wp-content/uploads/2011/10/nes-controller-pinout.png"><img src="http://psmay.com/wp-content/uploads/2011/10/nes-controller-pinout.png" height="200"></a>

- Pin 8 NES data (D1) 
- Pin 2 NES latch (OUT 0)
- Pin 3 NES pulse (clock/CUP)

(Latch and pulse must be interrupt pins: https://www.arduino.cc/en/Reference/AttachInterrupt)

## Links

http://www.mit.edu/~tarvizo/nes-controller.html

https://www.arduino.cc/en/Reference/PortManipulation
