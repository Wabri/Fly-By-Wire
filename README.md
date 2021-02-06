# Fly-by-wire

<small> **Progetto sistemi operativi 2019/2020 del corso di laurea in informatica Università degli studi di Firenze** </small>

* [Analisi del problema](#analisi)
* [Esecuzione del software](#esecuzione)

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

- [**PFC**](#pfc) corrispondente a 3 processi chiamati PFC1, PFC2 e PFC3
- [**Transducers**](#transducers) emulato da un processo chiamato trans
- [**Generatore Fallimenti**](#generatore-fallimenti) imitato da un processo chiamato FMAN (Failures manager)
- [**WES**](#wes) sarà relativo a un processo con lo stesso nome
- [**PFC Disconnect Switch**](#PFCDS) gestito dal processo PFCDS

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

### Transducers

Il processo trans deve:

- Acquisire ad ogni istante la velocità inviata da PFC1, PFC2 e PFC3
- Genera un log per ogni PFC: speedPFC1.log, speedPFC2.log  e speedPFC3.

Nel caso di fallimenti i dati non saranno inviati e il transducer non potrà analizzarli.

### Generatore Fallimenti

Il FMAN processo che agisce sui processi relativi al PFC:

- Ad ogni istante di tempo seleziona in modo casuale uno dei PFC
- Viene inviato al processo scelto:
    - con probabilità 0.01 invia un segnale SIGSTOP 
    - con probabilità 0.0001 invia un segnale SIGINT 
    - con probabilità 0.1 invia un segnale SIGCONT
    - con probabilità 0.1 invia un segnale SIGUSER1 che altera il valore del successivo calcolo della velocità, effettuando un left shift di 2 bits della velocità calcolata (dopo arrotondamento e cast a intero).
- Logga l'azione su un file failures.log

Si possono verificare anche più di uno degli eventi definiti sopra durante lo stesso istante di tempo. Considerando che i PFC devono saper ricevere i segnali sopra descritti.

### WES

Processo controllore dei PFC notificando eventuali problemi:

- Istante per istante, accede ai log generati dal processo trans
- Possono accadere 3 eventi:
    - Se tutti i log sono concordi allora segnala la correttezza con un OK
    - Se 2 sono concordi e 1 discorde viene inviato un messaggio di errore a PFCDS, indicando il processo discorde
    - Se tutti e 3 sono discordi invia un messaggio di EMERGENZA al PFCDS

Tutti i messaggi del WES sono stampati nello standard output e inseriti in un file di log chiamato status.log.

### PFCDS

Questo processo è un osservatore di quello che viene notificato dal WES reagendo ai messaggi che vengono inviati:

- In caso di errore:
    - Controlla lo stato del processo utilizzando l'istruzione kill che dice se il processo esiste o no, una volta scoperto lo stato del processo si può decidere se (le risoluzioni sotto sono opzionali): 
        - aggiustarlo, sbloccarlo o riavviarlo
        - ripartire a leggere nel punto giusto del file G18.txt, per fare questo è necessario mantenere in un file separato il numero di riga letta dai file
    - Loggare l'attività svolta nel log chiamato switch.log
- In caso di emergenza:
    - Termina l'applicazione

## Esecuzione

Il software sarà un client terminale eseguito in singola shell, con la possibilità di indicare il percorso del file G18.txt come parametro dell'eseguibile:

```Bash
fbf <percorso_assoluto_file>
```

L'esecuzione deve terminare quando viene letta l'ultima stringa GPGLL del file G18.txt dai PFC oppure a causa di un segnale di EMERGENZA invocato dal WES. I processi creati devono essere distrutti prima di terminare l'esecuzione.

Sono considerati opzionali i seguenti punti:

- Utilizzo Makefile per la compilazione
- Strutturazione dei file in folders: logs, bin, src e tmp
- Creazione delle directory definite sopra come parte integrante del processo di compilazione
- Riavvio dei 3 processi PFC al momento della ricezione del messaggio di EMERGENZA
- Inizializzazione delle probabilità definite per FMAN tramite macro

## Domande

- per l'inizializzazione delle probabilità si può usare anche un file di configurazione a parte?