# TTGO-Nes Cup Version
This is a PlatformIO software project for my TTGO with a Nes emulator.
It works with sound, integrated TTGO display and 8 buttons controls.

![Image Device](https://github.com/aaaasmile/TTGO-Nes-Cup/blob/a4d762e6691bbad3c06a60935f21f4182d078c36/doc/img400.png)

## Build and run
Simply clone this repository and compile it with Platform IO and Visual Code.
All needed libraries are included in the project.
Before you start playing, you have to upload one nes file. This project only start the first
game placed into the SPIF TTGO file system. The Nes file should be copied into the data directory and then
with the Platform IO command "Upload Filesystem Image" uploaded to the target.
If you want to change the game, you put it into the data folder and then "Upload Filesystem Image" again.

## Software
It was difficult for me to understand the video below because it was not working. 
In that video there are some firmware update, arduino project and schema that doesn't work for me.
The first thing was to check all control events. For this I have used the file main2.cpp.
Then I have fixed the file controller.cpp. The next step was sound.c file. Here the TTGO is used 
with its internal DAC. Here is the final hardware configuration for my bread board:

    #define HW_AUDIO
    #define HW_AUDIO_SAMPLERATE 22050
    #define HW_CONTROLLER_GPIO
    #define HW_CONTROLLER_GPIO_UP_DOWN 38
    #define HW_CONTROLLER_GPIO_LEFT_RIGHT 37
    #define HW_CONTROLLER_GPIO_SELECT 27
    #define HW_CONTROLLER_GPIO_START 39
    #define HW_CONTROLLER_GPIO_A 32
    #define HW_CONTROLLER_GPIO_B 33

## Nes file
Check the Data folder in this repository https://github.com/channel2007/TTGO_FC/esp32-nofrendo/data/ 
to get a nes example file. It was also the repository that I used to start with this project.

## Credits
https://www.youtube.com/watch?v=1TspP-tZocc&ab_channel=%E7%84%A1%E9%99%90%E5%8D%87%E7%B4%9A

https://github.com/moononournation/arduino-nofrendo

https://github.com/moononournation/Arduino_GFX