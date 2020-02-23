# Making music with floppy drives

[Readme file in working progress]

This is an Star-Wars-inspired model created to make music by using two old floppy drives, and a LED strip has also been added. To control the floppy drives, I deeply customized and integrated the [Moppy project](https://github.com/SammyIAm/Moppy2), and I used the [Adafruit 2801](https://github.com/adafruit/Adafruit-WS2801-Library) library to control the LED strip. You can see a video of the final result [here](https://youtu.be/pWgEK_t-BJY).

![Model image](/image/01_floppy_music_model.jpg)


# What do you need
The parts I used are the following:
- Two old floppy drives. I bought them on [eBay](https://www.ebay.com/).
- A LED strip based on WS2801 controller. In my case, I used a IP30 variant (the waterproof IP68 version is not needed), but any other should be OK as long as it uses the WS2801 controller and it works on 5V (12V variants also exist). I bought it on [Aliexpress](https://es.aliexpress.com/item/32794195484.html?spm=a2g0s.9042311.0.0.7f1263c0XuWP32)
- Arduino Nano. Kind of old, but it is powerful enough for this purpose. You can use any other Arduino variant with minimal changes in the code. I bought it on [eBay](https://www.ebay.com/).
- A 5V power supply with enough output current. I bought a 5A one to be sure, on [Amazon](https://www.amazon.es/gp/product/B013QWW4DO/).
- A black methacrylate board. You can find it in most DIY stores.
- A Darth Vader funko figure, just for decoration.

To compile the code, you need to have the [Arduino IDE](https://www.arduino.cc/en/main/software) installed, as well as the [Timer One](https://playground.arduino.cc/Code/Timer1/) library, which is used to generate interruptions.

If you are using another variant of Arduino instead of Nano, make sure it supports hardware SPI. If not, you will need to change the code to call the software SPI implementing functions of WS2801 library, which should not be a big deal anyway.




