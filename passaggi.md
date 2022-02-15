# TTGO-Nes
Sono partito dal video che si trova sul link:
https://www.youtube.com/watch?v=1TspP-tZocc&ab_channel=%E7%84%A1%E9%99%90%E5%8D%87%E7%B4%9A
che mi rimanda alla repository:
https://github.com/channel2007/TTGO_FC 

Ho creato un progetto per PlatformIO copiando tutti i files di channel 2007.
Le dipendenze sono sul progetto "nofrendo" e "Arduino_GFX". Le ho trovate su queste repos:
https://github.com/moononournation/arduino-nofrendo
https://github.com/moononournation/Arduino_GFX
Così sono riuscito a compilare il programma e a scaricarlo sul target. Però non funziona 
e ricevo l'errore GUI: error: could not open SNSS file.   
La repository https://github.com/channel2007/TTGO_FC mi serve solo per i collegamenti iniziali.
e per il codice iniziale. Ho dovuto però cambiare il codice nel controller.cpp per fare andare i collegamenti.
I files binari già pronti non li ho usati (vedi tentativo a vuoto).

### Tentativo a vuoto
Siccome i conctrolli non hanno funzionato, 
ho provato a usare il tool per il flash download tool, come descritto nel video. Esso si trova su:
https://www.espressif.com/en/support/download/other-tools
Una volta scaricato (D:\Arduino\PlatformIO\TTyGo-NES\reference\flash_download_tool_3.9.2), 
si imposta la port com7 (o quella che al momento è attuale) e si preme ERASE.
Poi si caricano i quattro files del firmware. Nota bene che occorre anche l'offset del dove vanno caricati:
boot_app0.bin                    | 0xe000
bootloader_dio_80m.bin           | 0x1000
ttgo_t_display_fc_partitions.bin | 0x8000
ttgo_t_display_fc.bin            | 0x10000
Ora si può far partire il flash con START.
Anche questo step senza successo in quanto ricevo lo stesso errore. Per me è inutile questo passaggio,
in quanto quando carico il firmware da platform io esso va proprio a cancellare ed a riscrivere
proprio questi segmenti, quindi me li sostituisce con il software di questo progetto.
Non sono andato molto lontano con dei binari che non ho idea di quello che facciano e quali controlli 
sono necessari.

## Software compilazione e problemi
Tutti i files nella directory ./src sono necessari con l'esclusione di main2.cpp che ho usato 
per fare dei test sui pulsanti.
Le dipendenze "nofrendo" e "Arduino_GFX" li ho messi nella directory Lib. Ho preso semplicemente 
i master latest dei due rispettivi progetti su github. Essi compilano senza nessun problema.

I files  osd.c, sound.c e diaplay.cpp sono dei files di callback di nesemu 
Quando faccio con platform IO  "Upload Filesystem Image" ottengo questo
Flash will be erased from 0x00290000 to 0x003fffff...
La rom viene pescata all'interno di spdiff senza problemi e va messa nella sottodirectory data. 

Disabilitando l'audio e anche i controlli sono riuscito a vedere la schermata iniziale.
Il problema che avevo all'inizio era dovuto al fattto che i controlli erano settati male (hw_config.h)
e l'evento loadstate veniva lanciato di continuo. Nel mio TTGO non c'è nessun stato di gioco da caricare.

L'audio, quando l'ho abilitato non mi ha fatto andare il display, per cui l'ho disabilitato per il momento.
Per fare il trace nella console seriale basta usare la funzione nofrendo_log_printf() che manda 
l'outout di printf() in console.
I pulsanti UP/DOWN e LEFT/RIGHT sono settati assieme su GPIO 38 e 37 ma non danno il riscontro corretto.
Per cui ho creato il file main2.cpp per provare la risposta dei bottoni. Alla fine a forza di provare 
diversi collegamenti sono riuscito a trovare la combinazione giusta. Ogni input analogico dei GPIO 38 e 37
hanno 3 livelli: 0, 1879 e 4085. 0 è quando nessun tasto è premuto, gli altri due livelli è quando 
un tasto è premuto.


## Nes
Nello sviluppo di Nes c'è anche un forum: https://forums.nesdev.org/

