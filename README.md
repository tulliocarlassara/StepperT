# StepperT

Semplice libreria per gestire in "rampa" un motore passo-passo
alimentato attraverso un driver step-direzione.

Per l'installazione in Arduino IDE:  
Sketch > Include Library > Add .ZIP Library...  
[StepperT.zip](StepperT/StepperT.zip)

Esempio di utilizzo:

```
#include "StepperT.h"

//definisci la variabile identificativa del motore ed assegna i pin di step e dir
StepperT stepMotor(2,3);

void setup() {
  //introduci velocità massima e accelerazione in step/s e step/s^2
  stepMotor.setParametri(5000,2000);
  //dai lo start fornendo numero passi e direzione 0 o 1
  stepMotor.start(50000,0);
}

void loop() {

}
```
# Stepper3T

Semplice libreria per gestire in "rampa" tre motori passo-passo
interpolati linearmente ed alimentati tramite driver step-direzione

Per l'installazione in Arduino IDE:  
Sketch > Include Library > Add .ZIP Library...  
[Stepper3T.zip](Stepper3T/Stepper3T.zip)

Esempio di utilizzo:

```
#include "Stepper3T.h"

//definisci la variabile identificativa del motore ed assegna i pin di step e dir
Stepper3T cnc(2,3,4,5,6,7);   //stepX, stepY, stepZ, dirX, dirY, dirZ

void setup() {
  cnc.setParametri(1000,300); //velocità massima e accelerazione in step/s e step/s^2
  cnc.start(10000,0,0,0,0,0); //passiX, passiY, passiZ, dirX, dirY, dirZ
}

void loop() {

}
```

