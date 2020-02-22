# Making music with floppy drives

[Readme file in working progress]

This is an Star-Wars-inspired model created to make music by using two old floppy drives. A LED strip has also been added.

![Model image](/image/01_floppy_music_model.jpg)


# What do you need
The parts I used are the following:
- Two old floppy drives. I bought them on [ebay](https://www.ebay.com/).
- A LED strip based on WS2801 controller. In my case, I bougth the following one, in the IP30 variant (the waterproof IP68 version is not needed), but any other should be OK as long as it uses the WS2801 controller and it works on 5V (12V variants also exist): 
[Aliexpress](https://es.aliexpress.com/item/32794195484.html?spm=a2g0s.9042311.0.0.7f1263c0XuWP32)
- Arduino Nano. Kind of old, but it is powerful enough for this purpose. I bought it on [ebay](https://www.ebay.com/). You can use any other Arduino variant with minimal changes in the code.
- A 5V power supply with enough output current. I bought a 5A one to be sure, on [Amazon](https://www.amazon.es/gp/product/B013QWW4DO/).
- A black methacrylate board. You can find it in most DIY stores.
- A Darth Vader funko figure, just for decoration.

The code of this project uses the following libraries:

- [Adafruit 2801](https://github.com/adafruit/Adafruit-WS2801-Library)
- A deeply customized version of [Moppy project](https://github.com/SammyIAm/Moppy2)
- [Timer One](https://playground.arduino.cc/Code/Timer1/) for Arduino 

The first one allows to control LED strips which are based on the WS2801 controller, either by using a GPIO-pin-based software SPI implementation or by using the native hardware SPI module if available. In this project, Arduino Nano is used, which is hardware SPI capable, so this last option will be used.


