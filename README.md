# EDA #level1: Orbital simulation

## Integrantes del grupo y contribución al trabajo de cada integrante

* Juan Ignacio Caorsi: implementación de calculo de aceleración y creación de estructuras OrbitalBody, OrbitalSim.
* Ana Destefano: iniciación y dibujo de cuerpos celestes

## Verificación del timestep

Probamos aumentar los dias que pasan por segundo de simulación y vemos que si doblamos la cantidad inicial (a 200 dias por segundo de simulación), todo el sistema se comienza a expandir, haciendo que los planetas se separen más del sol.
Si aumentamos esta cantidad aún más (por ejemplo, a 1000 dias), podremos ver que el sistema luego de cierto tiempo se destruye, los planetas salen disparados.
En cambio, si decrementamos la cantidad de días que pasan por segundo de simulación, la simulación se mantiene estable en un periodo de tiempo mucho más grande.

Finalmente decidimos mantener el timestep en 100 dias por segundo de simulación, pues es suficientemente preciso como también rápido, para que el usuario aprecie la mecánica de nuestro sistema solar.

## Verificación del tipo de datos float

Las variables en la simulación son de tipo float ya que tienen suficiente presición para los cálculos con numeros reales. Usar solo enteros no fue viable y, aunque podríamos haber 
usado double, no se lograban mejoras significativas en todos los casos, exceptuando uno: la variable auxScalar de la función updateOrbitalSim. Esto se debe a que en esta almacenan operaciones 
con la constante gravitacional, que tiene presición double. Para las cuentas que incluyen esta constante, realizamos un casteo temporal, pues funciones como Vector3Scale tienen como 
parametros del tipo float, por lo que para confirmar que incluso si ocurriera un casteo implícito, lo que hacemos es deliberado y no daña a la simulación.

Por otro lado, confirmamos que no ocurran operaciones invalidas, en particular, la división por 0. Esto podría llegar a pasar en el caso del cálculo de la fuerza de atracción entre un planeta y 
si mismo. Para evitarlo decidimos que lo mejor es devolver el vector nulo.

## Complejidad computacional con asteroides

Al colocar 90 asteroides graficados con esferas, la simulación dejaba de funcionar, allí estaba el cuello de botella gráfico.
Por otro lado, también consideramos que si calculabamos las fuerzas ejercidas sobre los asteroides entre si mismos, al colocar muchos,
la cantidad de cálculos necesarios se disparaba, y encontramos el segundo cuello de botella.


## Mejora de la complejidad computacional

Decidimos intentar representar a los asteroides como puntos y no esferas, pensando en que es algo 
significativamente más simple que el dibujo de cada una de las numerosas esferas. Una vez hecho esto,
se logró aumentar drásticamente el número máximo de esferas que soporta nuestra simulación.

Por otra parte, en cuanto al cuello de botella del cálculo de las fuerzas entre los asteroides, decidimos sacrificar cierto realismo para alcanzar un mejor rendimiento.
Para esto, definimos que tendríamos en cuenta la fuerza de atracción que había entre los asteroides y los planetas, y entre los asteroides y el sol y despreciaríamos la atracción entre los asteroides.

También implementammos una función para el cálculo de la fuerza gravitatoria.

## Bonus points

Encontramos el easter egg, es el valor inicial de phi dentro de la función configureAsteroid. Con este, se logra que los asteroides comiencen su recorrido desde una recta y luego se dispersen. 
También modificamos la masa de Júpiter para que sea mil veces mayor y notamos que el sistema solar se desequilibra completamente, lo único que se mantiene "en orden" es Mercurio y el Sol.
Logramos implementar la simulación del sistema Alpha Centauri, activable a partir de la definición de la constante ALPHASYSTEM en el archivo orbitalSim.cpp. 
Además, probamos ver qué pasaría si apareciera un agujero negro y pasara por el sistema solar. Notamos que pasa algo similar al caso de jupiter cuando lo hicimos 1000 veces más masivo, el sistema se desequilibra y pierde su forma usual.
## Aclaraciónes generales

Se decidió dejar al sol en el centro de la simulación y no calcular la atracción que los cuerpos ejercieron sobre el mismo, pues consideramos conveniente que si estamos simulando el sistema solar,
el hecho de que el sol se mantenga en el centro sería lo más esperable.




