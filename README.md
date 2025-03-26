# EDA #level1: Orbital simulation

## Integrantes del grupo y contribución al trabajo de cada integrante

* Juan Ignacio Caorsi: implementación de calculo de aceleración y creación de estructuras OrbitalBody, OrbitalSim.
* Ana Destefano: iniciación y dibujo de cuerpos celestes

[completar]

## Verificación del timestep

Verificamos que la simulación funcione bien unos 100 años adelante y así fue, no se perdió el movimiento con el que debe funcionar tanto el sistema solar como los asteroides.

## Verificación del tipo de datos float

[completar]

## Complejidad computacional con asteroides

Primero, al colocar 90 asteroides graficados con esferas, la simulación dejaba de funcionar. Por esto, decidimos intentar representar a los asteroides como puntos y no esferas, pensando en que es algo 
significativamente más simple que el dibujo de cada una de las numerosas esferas.

## Mejora de la complejidad computacional

Representar los asteroides como puntos 
Cálculo de la fuerza gravitatoria dentro de una función 

## Bonus points

Encontramos el easter egg, es el valor inicial de phi dentro de la función configureAsteroid, con este se logra que los asteroides comiencen su recorrido desde una recta y luego se dispercen. 
También modificamos la masa de júpiter para que sea mil veces mayor y notamos que el sistema solar se desequilibra completamente, lo único que se mantiene "en orden" es mercurio y el sol.

