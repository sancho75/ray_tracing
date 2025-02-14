# Progetto Raytracer in C

## Descrizione del Progetto
Questo progetto consiste nella realizzazione di un programma in linguaggio C per il rendering di un insieme di sfere tramite tecniche di ray tracing. Il programma genera un'immagine in formato PPM rappresentante la scena definita dall'utente in un file di testo.

## Struttura del Progetto
Il progetto è suddiviso nei seguenti file:

- `main.c`: File principale, gestisce il flusso del programma.
- `scene.c` e `scene.h`: Gestiscono la scena, la lettura dal file di input, la generazione dei raggi e il calcolo dei colori dei pixel.
- `ppm.c` e `ppm.h`: Funzioni per il salvataggio dell'immagine in formato PPM usando `mmap`.
- `constants.h`: Definizione dei valori del colore di sfondo.
- `Makefile`: Script per la compilazione automatica.

## Requisiti
- Compilatore GCC
- Libreria OpenMP per la parallelizzazione
- Libreria matematica (collegata con `-lm`)

## Compilazione
Per compilare il progetto:
```bash
make
```

## Esecuzione
Il programma accetta i seguenti argomenti da linea di comando:
```bash
./raytracer <file_scena> <file_output> <larghezza> <altezza>
```
Esempio:
```bash
./raytracer scene.txt output.ppm 1920 1080
```

## Formato del File di Scena
Il file di scena deve avere il seguente formato:
```
VP <viewport_width> <viewport_height> <viewport_distance>
BG <r> <g> <b>
OBJ_N <numero_di_sfere>
S <cx> <cy> <cz> <raggio> <r> <g> <b>
S <cx> <cy> <cz> <raggio> <r> <g> <b>
...
```

Esempio:
```
VP 1.777 1 1
BG 255 255 255
OBJ_N 2
S 0 0 -5 1 255 0 0
S 2 0 -6 0.5 0 255 0
```

## Esempi di Scene di Test
Sono forniti 5 esempi di scene per testare il programma:
- `scene1.txt`: Una sfera rossa grande al centro.
- `scene2.txt`: Due sfere affiancate, verde e blu.
- `scene3.txt`: Tre sfere, una più vicina e più piccola.
- `scene4.txt`: Tappeto di sfere colorate su sfondo grigio.
- `scene5.txt`: Piano (sfera grande) con 3 sfere colorate sopra.

## Visualizzazione del Risultato
Il file generato è in formato PPM (P6), visualizzabile con:
- ImageMagick: `display output.ppm`
- IrfanView (Windows)
- Convertitore online: [onlineconvertfree.com](https://onlineconvertfree.com/ppm-to-png/)

## Funzionalità Implementate
- Ray tracing base per intersezioni raggio-sfera
- Parallelizzazione con OpenMP
- Salvataggio immagine con `mmap`
- Lettura file di scena con `fscanf`

## Autore
Tchakounte Nzoumeni Yvan Landry (SM3201458)

