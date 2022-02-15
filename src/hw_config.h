#ifndef _HW_CONFIG_H_
#define _HW_CONFIG_H_

#define FSROOT "/fs"



// Uncomment one of below, ESP32 support SPIFFS SD_MMC and SD
/* SPIFFS */
#define FILESYSTEM_BEGIN SPIFFS.begin(false, FSROOT); FS filesystem = SPIFFS;
/* 1-bit SD mode SD_MMC, always retry once for begin() failed */
// #define FILESYSTEM_BEGIN (!SD_MMC.begin(FSROOT, true)) && (!SD_MMC.begin(FSROOT, true)); FS filesystem = SD_MMC;
/* 4-bit SD mode SD_MMC, always retry once for begin() failed */
//#define FILESYSTEM_BEGIN (!SD_MMC.begin(FSROOT, false)) && (!SD_MMC.begin(FSROOT, false)); FS filesystem = SD_MMC;
/* SD using default SPI settings */
//#define FILESYSTEM_BEGIN SD.begin(22 /* SS */, SPI, 8000000, FSROOT); FS filesystem = SD;
/* SD using custom SPI settings */
//#define FILESYSTEM_BEGIN SPIClass spi = SPIClass(HSPI); spi.begin(14, 2, 15, 13); SD.begin(13, spi, 8000000, FSROOT); FS filesystem = SD;
                                                         
// enable audio
#define HW_AUDIO
//#define HW_AUDIO_EXTDAC
// #define HW_AUDIO_EXTDAC_WCLK 21
// #define HW_AUDIO_EXTDAC_BCLK 22
// #define HW_AUDIO_EXTDAC_DOUT 19
#define HW_AUDIO_SAMPLERATE 22050

/* controller is GPIO */
#define HW_CONTROLLER_GPIO
#define HW_CONTROLLER_GPIO_UP_DOWN 38
#define HW_CONTROLLER_GPIO_LEFT_RIGHT 37
#define HW_CONTROLLER_GPIO_SELECT 27
#define HW_CONTROLLER_GPIO_START 39
#define HW_CONTROLLER_GPIO_A 32
#define HW_CONTROLLER_GPIO_B 33

#endif /* _HW_CONFIG_H_ */
