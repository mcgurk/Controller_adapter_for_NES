# Controller_adapter_for_NES

Wii Classic Controller to NES.

Works with normal Arduino with Atmega328P (5V 16MHz). I used Arduino Pro Mini.

Lag under 1ms.

## Connections

### Wii Classic Controller
```
// Uno/Pro Mini: SDA = A4, SCL = A5
// Pro Micro: SDA = D2, SCL = D3
// ESP8266: SDA = D2, SCL = D1
```
Officially Wii extension controllers are 3.3V. I used 3.3V voltage converter. Might work with 5V.

Very handy level converter with 3.3V AMS1117 regulator. Search from Ebay with Logic Level Converter Module AMS1117 DC 5V to 3.3V

### NES-controller:
```
// Pin 8 NES data (PORTB, bit 1) https://www.arduino.cc/en/Reference/PortManipulation
// Latch and pulse must be interrupt pins: https://www.arduino.cc/en/Reference/AttachInterrupt
// Pin 2 NES latch
// Pin 3 NES pulse
```

## Links

http://www.mit.edu/~tarvizo/nes-controller.html
