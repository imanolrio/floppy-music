# Making music with floppy drives

[Readme file in working progress]

This is an Star-Wars-inspired model created to make music by using two old floppy drives. A LED strip has also been added.

![Model image](/image/01_floppy_music_model.jpg)


# What do you need
You can do any variants you consider to the following. The parts I used are:
- Two old floppy drives. I bought them on ebay.
- A LED strip based on WS2801 controller. In my case, I bougth the following one, in the IP30 variant (the waterproof IP68 version is not needed), but any other should be OK as long as it uses the WS2801 controller and it works on 5V (12V variants also exist): https://es.aliexpress.com/item/32794195484.html?spm=a2g0s.9042311.0.0.7f1263c0XuWP32


The code of this project uses the following libraries:

- Adafruit WS2801: https://github.com/adafruit/Adafruit-WS2801-Library
- A deeply customized version of: https://github.com/SammyIAm/Moppy2
- Timer One library for Arduino: https://playground.arduino.cc/Code/Timer1/

The first one allows to control LED strips which are based on the WS2801 controller, either by using a GPIO-pin-based software SPI implementation or by using the native hardware SPI module if available. In this project, Arduino Nano is used, which is hardware SPI capable, so this last option will be used.


