# waveshare-epd3.7in
This is an Arduino-based driver for the Waveshare 3.7in EPD listed here: https://www.waveshare.com/product/displays/e-paper/epaper-2/3.7inch-e-paper-hat.htm

Unfortunately, only drivers available for this screen are through a Python script running on an RPi. For smaller microcontroller uses, this small library is a port of said Python implementation.

## Requirements
* SPI pins required
  * Software SPI might work also - not tested

## Tested platforms
* Arduino Pro Mini (ATMega328P)