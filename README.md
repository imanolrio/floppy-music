# floppy-music

[Readme file in working progress]



The code of this project uses the following libraries:

- Adafruit WS2801: https://github.com/adafruit/Adafruit-WS2801-Library
- A deeply customized version of: https://github.com/SammyIAm/Moppy2 

The first one allows to control LED strips which are based on the WS2801 controller, either by using a GPIO-pin-based software SPI implementation or by using the native hardware SPI module if available. In this project, Arduino Nano is used, which is hardware SPI capable, so this last option will be used.

In my case, I bougth the following LED strip in the IP30 variant (I didn't need the waterproof IP68 one), but any other should be OK as long as it uses the WS2801 controller: https://es.aliexpress.com/item/32794195484.html?spm=a2g0s.9042311.0.0.7f1263c0XuWP32

Another important detail is that in this project I am using a LED strip version which uses 5V (12V versions are also available).
