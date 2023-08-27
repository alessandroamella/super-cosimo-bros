# SuperCosimoBros

### Todo

-   Cambiare i testi in `src/asciiart/texts.hpp` da array a liste 2D (richiesta del cosy è usare solo strutture dati dinamiche)
-   Aggiungere piattaforme (pensa a struttura dati intelligente)
-   Fixa nemici che camminano fuori dalle piattaforme
-   Aggiungi nemici che sparano
-   Devi far spawnare più monete

SPIEGA suddivisione in stanze (LevelManager composto da lista di Room\* che vengono clonate da una lista)
La quantità di nemici nella stanza è lineare alla difficoltà
La quantità di powerup segue una funzione radice quadrata (perché è più difficile trovare powerup che nemici)
Da difficoltà 5 in poi i nemici sparano
Esci dal gioco con q
Controlli WASD, in shop = idem (compra = invio)
Entra in SHOP ogni 3 livelli
