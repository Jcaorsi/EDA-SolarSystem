# EDA #level1: Orbital simulation

## Integrantes del grupo y contribución al trabajo de cada integrante

* Juan Ignacio Caorsi: implementación de calculo de aceleración y creación de estructuras OrbitalBody, OrbitalSim.
* Ana Destefano: iniciación y dibujo de cuerpos celestes

## Verificación del timestep

Verificamos que la simulación funcione bien unos 100 años adelante y así fue, no se perdió el movimiento con el que debe funcionar tanto el sistema solar como los asteroides.

## Verificación del tipo de datos float

Las variables en la simulación son de tipo float ya que tienen suficiente presición para los cálculos que necesitamos realizar. Usar solo enteros no era viable y, aunque podríamos haber 
usado double, no se lograban mejoras significativas en todos los casos, exceptuando uno: la variable auxScalar de la función updateOrbitalSim. Esto se debe a que en esta almacenan operaciones 
con la constante gravitacional, que tiene presición double. Para las cuentas que incluyen esta constante, realizamos un casteo temporal, pues funciones como Vector3Scale tienen como 
argumento a un valor con presición float, por lo que para confirmar que incluso si ocurriera un casteo implícito, lo que hacemos es deliberado y no daña a la simulación.

Por otro lado, confirmamos que no ocurran operaciones invalidas, en particular, la división por 0. Esto podría llegar a pasar en el caso del cálculo de la fuerza de atracción entre un planeta y 
si mismo. Para evitarlo decidimos que lo mejor es devolver el vector nulo.

## Complejidad computacional con asteroides

Al colocar 90 asteroides graficados con esferas, la simulación dejaba de funcionar.

## Mejora de la complejidad computacional

Decidimos intentar representar a los asteroides como puntos y no esferas, pensando en que es algo 
significativamente más simple que el dibujo de cada una de las numerosas esferas. Una vez hecho esto,
se logró aumentar drásticamente el número máximo de esferas que soporta nuestra simulación.

También implementammos una función para el cálculo de la fuerza gravitatoria.

## Bonus points

Encontramos el easter egg, es el valor inicial de phi dentro de la función configureAsteroid. Con este, se logra que los asteroides comiencen su recorrido desde una recta y luego se dispersen. 
También modificamos la masa de Júpiter para que sea mil veces mayor y notamos que el sistema solar se desequilibra completamente, lo único que se mantiene "en orden" es Mercurio y el Sol.

