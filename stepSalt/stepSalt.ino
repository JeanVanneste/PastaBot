/**
 * Exemple de code pour un servomoteur, il fait faire des va-et-vient à la tête du servomoteur.
 */

 /* Inclut la lib Servo pour manipuler le servomoteur */
#include <Servo.h>

/* Créer un objet Servo pour contrôler le servomoteur */
Servo saltDispenser;

void setup() {
    
  // Attache le servomoteur à la broche D9
  saltDispenser.attach(9);
}

void loop() {
  dispenseSalt();
}

void dispenseSalt(){
     saltDispenser.write(180);
    delay(500);
    saltDispenser.write(0);
    delay(15000);
}
