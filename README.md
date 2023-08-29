# GaetanoBros

Benvenuto in GaetanoBros!

In questo mini-videogame, il giocatore veste i panni di Gaetano, rappresentato da "**@**", e si troverà ad affrontare diversi ostacoli.

L'obiettivo? Sopravvivere il maggior numero di livelli possibile, senza venire ucciso dagli insidiosi nemici.

[Gameplay](https://drive.google.com/file/d/15I3-gYn0vnf0aKTg7Fa9XqAyP8_wu2ng/view?usp=sharing).

Di seguito vengono elencate le istruzioni e le specifiche generali del gioco.

## Indice

In questo file vengono presentati i seguenti aspetti del gioco:

-   The basics
-   Salute
-   Valuta
-   Shop
-   Powerups
-   Nemici
-   Difficoltà crescente

## The basics

Il gioco è suddiviso in stanze (o livelli), ognuno con una specifica mappa, nei quali il giocatore dovrà partire da un punto, e arrivare in un altro punto per poter passare alla prossima stanza.

Ogni stanza ha una mappa distinta presa casualmente da un insieme di mappe.

Quando il giocatore non ha più salute (venendo ferito dai nemici) la partita termina.

Lo scopo del gioco è di sopravvivere il maggior numero di stanze possibili.

### Comandi del giocatore

Il giocatore viene controllato da tastiera, e si muove a sinistra e destra usando rispettivamente i tasti "a" e "d", e salta premendo lo spazio.

Esso può muoversi più veloce se viene premuto anche "control" mentre si sta muovendo a sinistra o destra.

### Quit

Per uscire da una finestra del gioco basta premere il tasto "q".

Nel caso esso viene premuto nello shop, il giocatore viene portato al prossimo livello, altrimenti la finestra di gioco viene terminata.

### Tornare indietro

Durante una partita, il giocatore ha la possibilità di tornare nella stanza precedente se desidera.

In una stanza, basta che il protagonista entri nel punto di partenza della stanza (segnato da un riquadro blu), ed esso verrà ricondotto nel livello precedente (ed eventualmente nello shop).

### Game over

Quando il giocatore ha 0 hp, la partita termina e viene mostrata la schermata "Game Over", con il numero di stanze completate nella partita ed il grado difficoltà massimo dei livelli completati.

Premendo lo spazio verrà iniziata una nuova partita, dove il primo livello avrà una difficoltà uguale alla difficoltà dell'ultimo livello della partita precedente.

Se invece si desidera iniziare una nuova partita con difficoltà minima, basta riavviare il gioco.

## Salute

Il giocatore inizia la partita con 50 hp.

Il giocatore perde 10 hp se:

-   entra a contatto con un nemico
-   entra a contatto con un proiettile (sparato da un nemico)

Il giocatore può acquisire più vita tramite potenziamenti.

Il massimo di hp consentiti è 100 hp.

## Valuta

Nel gioco è presente una valuta. La partita inizia con 50 coins, e il giocatore può raccogliere altri coins nei livelli. Infatti, nei livelli si trovano delle hitboxes che possono contenere 5, 10, 15 o 20 coins. Il massimo numero di coins che il player può avere è 99.

I coins vengono utilizzati nello shop per comprare potenziamenti.

## Shop

Lo shop è il luogo dove il giocatore puó comprare i potenziamenti con la valuta. La pagina dello shop compare quando il giocatore inizia la partita, e dopo ogni tre stanze superate.

## Powerups

I potenziamenti sono degli "enhancements" che facilitano il giocatore nel completare i livelli. Essi si trovano in due luoghi:

-   Nei livelli, sotto forma di hitboxes.
-   Nello shop, dove possono essere comprati con la valuta.

Ci sono quattro generi di potenziamenti:

### Cuore

-   Effetto: Il giocatore guadagna 30 hp di salute
-   Simbolo ID: **+**
-   Costo in shop: 10 coins

### Fungo

-   Effetto: Il giocatore ha uno "scudo" fino alla prossima volta che viene ferito
-   Simbolo ID: **?**
-   Costo in shop: 15 coins
-   Durata: Finchè il giocatore non viene ferito
-   Design: **&**

### Stella

-   Effetto: Il giocatore è invincibile agli attacchi nemici e quando collide con un nemico, il nemico muore
-   Simbolo ID: **S**
-   Costo in shop: 35 coins
-   Durata: 10 secondi
-   Design: La **@** lampeggia

### Pistola

-   Effetto: Il giocatore può sparare ed uccidere i nemici (usando il tasto **E**)
-   Simbolo ID: **P**
-   Costo in shop: 40 coins
-   Durata: Finchè il giocatore non viene ferito
-   Design: La **@** diventa gialla

## Nemici

I nemici sono entità opposte al giocatore, controllate dal computer. Essi camminano avanti e indietro sulla piattaforma dove vengono generati.

Man mano che la difficoltà aumenta (vedi sottocapitolo "Difficoltà crescente") essi aumentano di quantità nei livelli, e acquisiscono l'abilità di sparare.

## Difficoltà crescente

Per ogni livello che passa, la difficoltà di completamento aumenta.

Nella prima partita, la difficoltà è equivalente al numero di stanze completate. Nelle partite seguenti, la difficoltà continua ad aumentare anche se il giocatore è morto.

Specifiche:

-   La quantità di nemici nella stanza è lineare alla difficoltà
-   Dal grado di difficoltà 5 in poi, i nemici sparano proiettili
-   La quantità di potenziamenti nei livello segue la funzione $$ y = - \sqrt{x} + 4 $$
    dove l'asse delle ascisse rappresenta il grado di difficoltà mentre l'asse delle ordinate rappresenta il numero di powerups nel livello.
    N.B: Ci sarà sempre almeno un powerup per ogni grado di difficoltà.

## Conclusione

Buon divertimento!

Credits: Alessandro Amella, Michele Garavani, Simone Ballo

Italia, Svizzera, 2023

---

---

# ALTRA ROBA (DA TOGLIERE)

### Todo

-   In teoria tutto funzia (in teoria)

### IMPORTANTISSIMO

A volte **SI BUGGA** quando fai dei salti strani, aka

1. Clippa attraverso i muri quando salti o atterri
2. Quando salti e atterri abbastanza veloce su un pavimento, ti teletrasporta in avanti
3. Quando ti strusci su una piattaforma a volte si freeza
4. I PROIETTILI SI SMINCHIANO A PASSARE DA DUE PIATTAFORME DIVERSE CON LA STESSA Y DUNQUE NON SPARARE MAI DA UNA PIATTAFORMA ALL'ALTRA

Dunque => **NON FARE ROBE STRANE DURANTE LA PRESENTAZIONE**. done qed.

### Per presentazione

-   SPIEGA suddivisione in stanze (LevelManager composto da lista di Room\* che vengono clonate da una lista)
-   La quantità di nemici nella stanza è lineare alla difficoltà
-   La quantità di powerup segue una funzione radice quadrata (perché è più difficile trovare powerup che nemici)
-   Da difficoltà 5 in poi i nemici sparano
-   Esci dal gioco con q
-   Controlli WASD, in shop = idem (compra = invio)
-   Entra in SHOP ogni 3 livelli
