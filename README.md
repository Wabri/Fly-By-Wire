# Fly-by-wire

<small> **Progetto sistemi operativi 2019/2020 del corso di laurea in informatica Università degli studi di Firenze** </small>

* [Analisi del problema](#analisi)

## Analisi

L'obiettivo del progetto è quello di costruire una architettura stilizzata, rivisitata e difforme, di un sistema Fly-By-Wire.

Il [fly by wire](https://en.wikipedia.org/wiki/Fly-by-wire) è un sistema che sostituisce i tradizionali comandi di volo diretti con un sistema di comando elettronico digitale. 

Per poter acquisire dati verrà usato il sistema di comunicazione dati [nmea](http://aprs.gids.nl/nmea/) utilizzato soprattutto in nautica e nella comunicazione di dati gps. Il progetto si basa su dati raccolti da un *GARMIN G18* in ambiente aperto. Questo sistema definisce delle così dette sentences che hanno una loro corretta interpretazione:

-  $GPBOD = Bearing, origin to destination
-  $GPBWC = Bearing and distance to waypoint, great circle
-  $GPGGA = Global Positioning System Fix Data
-  $GPGLL = Geographic position, latitude / longitude
-  $GPGSA = GPS DOP and active satellites 
-  $GPGSV = GPS Satellites in view
-  $GPHDT = Heading, True
-  $GPR00 = List of waypoints in currently active route
-  $GPRMA = Recommended minimum specific Loran-C data
-  $GPRMB = Recommended minimum navigation info
-  $GPRMC = Recommended minimum specific GPS/Transit data
-  $GPRTE = Routes
-  $GPTRF = Transit Fix Data
-  $GPSTN = Multiple Data ID
-  $GPVBW = Dual Ground / Water Speed
-  $GPVTG = Track made good and ground speed
-  $GPWPL = Waypoint location
-  $GPXTE = Cross-track error, Measured
-  $GPZDA = Date & Time

Per definire una distanza è necessario definire una coppia di dati ed eseguire una conversione, considerando che lo sviluppo di questo progetto è richiesto in linguaggio c la libreria che dovremmo usare sarà [math.h](http://www.cplusplus.com/reference/cmath/).

È consigliato l'utilizzo dei metri durante i vari calcoli per non rischiare di perdere cifre significative, inoltre GPGLL (posizione geografica latitudine longitudine, vedi la lista sopra) fornisce un valore come 4424.8422, ma molti algoritmi vogliono una sintassi quale 44.248422. 

I componenti che utilizzeremo saranno 5:

- **PFC** corrispondente a 3 processi chiamati PFC1, PFC2 e PFC3
- **Transducers** emulato da un processo chiamato trans
- **Generatore Fallimenti** imitato da un processo chiamato FMAN (Failures manager)
- **WES** sarà relativo a un processo con lo stesso nome
- **PFC** Disconnect Switch gestito dal processo PFCDS

In totale sarà quindi necessario gestire 7 processi. Andiamo a determinare le funzionalità di ogni singolo componente.

### PFC

Il comportamento funzionale di questi 3 componenti è il seguente:

- Acquisisce un nuovo record NMEA GPGLL dal file in input (nel nostro caso G18.txt)
- Estrae le coordinate
- Calcola la distanza percorsa rispetto alle coordinate acquisite
- Conseguentemente calcola la velocità attuale (all’avvio, la velocità è 0)
- Comunica la velocità elaborata a Transducers, tramite le seguenti modalità:
    - PFC1 comunica tramite una socket
    - PFC2 comunica tramite una pipe
    - PFC3 comunica tramite scrittura su un file condiviso
