# EDA #level1: Orbital simulation

## Integrantes del grupo y contribución al trabajo de cada integrante

* Juan Ignacio Caorsi: implementación de calculo de aceleración y creación de estructuras OrbitalBody, OrbitalSim.
* Ana Destefano: iniciación y dibujo de cuerpos celestes

[completar]

## Verificación del timestep

Verificamos que la simulación funcione bien unos 100 años adelante y así fue, no se perdió el movimiento con el que debe funcionar tanto el sistema solar como los asteroides.

## Verificación del tipo de datos float

El tipo de dato de las variables con las que se trabaja que son float, se vio que tienen suficiente precisión, pues el trabajo con solo enteros no es 
posible para lograr la simulación deseada, y con variables tipo double no se logran mejoras significativas en todos los casos, exceptuando uno. 
Una variable llamada auxScalar en la función de updateOrbitalSim debe ser del tipo double pues 
en esta se almacenan operaciones que tienen a la constante gravitacional (un valor de presición double). Para las cuentas que incluyan a esta constante,
se realiza un casteo temporal pues funciones como Vector3Scale tienen como argumento a un valor con presición float para confirmar que incluso si
ocurriera un casteo implícito, lo que hacemos es deliberado y no daña a la simulación.

Por otro lado, confirmamos que no ocurran operaciones invalidas, en particular, la división por 0. En el caso del cálculo de la fuerza de atracción entre un planeta y si mismo, esto podría llegar a pasar. 
Por esto, consideramos que  bueno que se devolviera el vector nulo. 

## Complejidad computacional con asteroides

Primero, al colocar 90 asteroides graficados con esferas, la simulación dejaba de funcionar. Por esto, decidimos intentar representar a los asteroides como puntos y no esferas, pensando en que es algo 
significativamente más simple que el dibujo de cada una de las numerosas esferas. Una vez hecho esto, se logró aumentar drásticamente el número máximo de esferas que soporta nuestra simulación.

## Mejora de la complejidad computacional

Representar los asteroides como puntos 
Cálculo de la fuerza gravitatoria dentro de una función 

## Bonus points

Encontramos el easter egg, es el valor inicial de phi dentro de la función configureAsteroid, con este se logra que los asteroides comiencen su recorrido desde una recta y luego se dispersen. 
También modificamos la masa de júpiter para que sea mil veces mayor y notamos que el sistema solar se desequilibra completamente, lo único que se mantiene "en orden" es mercurio y el sol.

