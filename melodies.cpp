#include <Arduino.h>
#include "melodies.h"

void playMelody(int melodyNumber, int buzzerPin) {

  switch(melodyNumber) {

    case 0:
      tone(buzzerPin, 1480);
      delay(144);
      noTone(buzzerPin);
      break; 
     
    case 1: // Zelda Secret Unlocked
      tone(buzzerPin, 1480);
      delay(144);
      noTone(buzzerPin);
    
      tone(buzzerPin, 1397);
      delay(144);
      noTone(buzzerPin);
    
      tone(buzzerPin, 1175);
      delay(144);
      noTone(buzzerPin);
    
      tone(buzzerPin, 988);
      delay(144);
      noTone(buzzerPin);
    
      tone(buzzerPin, 784);
      delay(144);
      noTone(buzzerPin);
    
      tone(buzzerPin, 1245);
      delay(144);
      noTone(buzzerPin);
    
      tone(buzzerPin, 1568);
      delay(144);
      noTone(buzzerPin);
    
      tone(buzzerPin, 1976);
      delay(294);
      noTone(buzzerPin);
      break;  
      
    case 2: // Norwegian Anthem
      tone(buzzerPin, 698);
      delay(750);
      noTone(buzzerPin);
    
      tone(buzzerPin, 622);
      delay(250);
      noTone(buzzerPin);
    
      tone(buzzerPin, 587);
      delay(500);
      noTone(buzzerPin);
    
      tone(buzzerPin, 523);
      delay(500);
      noTone(buzzerPin);
    
      tone(buzzerPin, 466);
      delay(500);
      noTone(buzzerPin);
    
      tone(buzzerPin, 523);
      delay(500);
      noTone(buzzerPin);
    
      tone(buzzerPin, 587);
      delay(500);
      noTone(buzzerPin);
    
      tone(buzzerPin, 622);
      delay(500);
      noTone(buzzerPin);
    
      tone(buzzerPin, 698);
      delay(750);
      noTone(buzzerPin);
    
      tone(buzzerPin, 784);
      delay(250);
      noTone(buzzerPin);
    
      tone(buzzerPin, 698);
      delay(501);
      noTone(buzzerPin);
    
      tone(buzzerPin, 622);
      delay(500);
      noTone(buzzerPin);
    
      tone(buzzerPin, 587);
      delay(1000);
      noTone(buzzerPin);
      break;
      
    case 3: // Nokia Tune
      tone(buzzerPin, 1319);
      delay(125);
      noTone(buzzerPin);
    
      tone(buzzerPin, 1175);
      delay(133);
      noTone(buzzerPin);
    
      tone(buzzerPin, 740);
      delay(245);
      noTone(buzzerPin);
    
      tone(buzzerPin, 831);
      delay(247);
      noTone(buzzerPin);
    
      tone(buzzerPin, 1109);
      delay(115);
      noTone(buzzerPin);
    
      tone(buzzerPin, 988);
      delay(143);
      noTone(buzzerPin);
    
      tone(buzzerPin, 587);
      delay(276);
      noTone(buzzerPin);
    
      tone(buzzerPin, 659);
      delay(296);
      noTone(buzzerPin);
    
      tone(buzzerPin, 988);
      delay(139);
      noTone(buzzerPin);
    
      tone(buzzerPin, 880);
      delay(168);
      noTone(buzzerPin);
    
      tone(buzzerPin, 554);
      delay(315);
      noTone(buzzerPin);
    
      tone(buzzerPin, 659);
      delay(484);
      noTone(buzzerPin);
    
      tone(buzzerPin, 880);
      delay(981);
      noTone(buzzerPin);     
      break;

    case 4: // O jul med din glede
      tone(buzzerPin, 262);
      delay(300);
      noTone(buzzerPin);
      
      tone(buzzerPin, 392);
      delay(600);
      noTone(buzzerPin);
      
      tone(buzzerPin, 392);
      delay(300);
      noTone(buzzerPin);
      
      tone(buzzerPin, 392);
      delay(300);
      noTone(buzzerPin);
      
      tone(buzzerPin, 330);
      delay(600);
      noTone(buzzerPin);
      
      tone(buzzerPin, 262);
      delay(300);
      noTone(buzzerPin);
      
      tone(buzzerPin, 262);
      delay(300);
      noTone(buzzerPin);
      
      tone(buzzerPin, 440);
      delay(600);
      noTone(buzzerPin);
      
      tone(buzzerPin, 440);
      delay(300);
      noTone(buzzerPin);
      
      tone(buzzerPin, 440);
      delay(300);
      noTone(buzzerPin);
      
      tone(buzzerPin, 392);
      delay(900);
      noTone(buzzerPin);
      
      tone(buzzerPin, 392);
      delay(300);
      noTone(buzzerPin);
      
      tone(buzzerPin, 523);
      delay(600);
      noTone(buzzerPin);
      
      tone(buzzerPin, 392);
      delay(300);
      noTone(buzzerPin);
      
      tone(buzzerPin, 349);
      delay(300);
      noTone(buzzerPin);
      
      tone(buzzerPin, 330);
      delay(600);
      noTone(buzzerPin);
      
      tone(buzzerPin, 392);
      delay(300);
      noTone(buzzerPin);
      
      tone(buzzerPin, 330);
      delay(300);
      noTone(buzzerPin);
      
      tone(buzzerPin, 294);
      delay(1200);
      noTone(buzzerPin);
      
      tone(buzzerPin, 262);
      delay(900);
      noTone(buzzerPin);
      break;

    case 5: // Mario Bros
      tone(buzzerPin, 659);
      delay(100);
      noTone(buzzerPin);

      delay(50);

      tone(buzzerPin, 659);
      delay(100);
      noTone(buzzerPin);

      delay(50*3);

      tone(buzzerPin, 659);
      delay(100);
      noTone(buzzerPin);

      delay(50*3);

      tone(buzzerPin, 523);
      delay(100);
      noTone(buzzerPin);

      delay(50);

      tone(buzzerPin, 659);
      delay(100);
      noTone(buzzerPin);

      delay(50*3);

      tone(buzzerPin, 784);
      delay(100);
      noTone(buzzerPin);

      delay(50*7);

      tone(buzzerPin, 392);
      delay(100);
      noTone(buzzerPin);
      break;
    
    default: // Glory Glory  Man United
      tone(buzzerPin, 349);
      delay(750);
      noTone(buzzerPin);
    
      tone(buzzerPin, 311);
      delay(250);                                                                                                                       
      noTone(buzzerPin);
    
      tone(buzzerPin, 294);
      delay(375);
      noTone(buzzerPin);
    
      tone(buzzerPin, 294);
      delay(125);
      noTone(buzzerPin);
    
      tone(buzzerPin, 466);
      delay(375);
      noTone(buzzerPin);
    
      tone(buzzerPin, 523);
      delay(125);
      noTone(buzzerPin);
    
      tone(buzzerPin, 587);
      delay(1000);
      noTone(buzzerPin);
    
      tone(buzzerPin, 466);
      delay(1000);
      noTone(buzzerPin);
    
      tone(buzzerPin, 392);
      delay(750);
      noTone(buzzerPin);
    
      tone(buzzerPin, 440);
      delay(250);
      noTone(buzzerPin);
    
      tone(buzzerPin, 466);
      delay(375);
      noTone(buzzerPin);
    
      tone(buzzerPin, 440);
      delay(125);
      noTone(buzzerPin);
    
      tone(buzzerPin, 466);
      delay(375);
      noTone(buzzerPin);
    
      tone(buzzerPin, 392);
      delay(125);
      noTone(buzzerPin);
    
      tone(buzzerPin, 349);
      delay(1000);
      noTone(buzzerPin);
    
      tone(buzzerPin, 294);
      delay(1000);
      noTone(buzzerPin);
    
      tone(buzzerPin, 349);
      delay(750);
      noTone(buzzerPin);
    
      tone(buzzerPin, 311);
      delay(250);
      noTone(buzzerPin);
    
      tone(buzzerPin, 294);
      delay(375);
      noTone(buzzerPin);
    
      tone(buzzerPin, 349);
      delay(125);
      noTone(buzzerPin);
    
      tone(buzzerPin, 466);
      delay(375);
      noTone(buzzerPin);
    
      tone(buzzerPin, 523);
      delay(125);
      noTone(buzzerPin);
    
      tone(buzzerPin, 587);
      delay(1000);
      noTone(buzzerPin);
    
      tone(buzzerPin, 466);
      delay(500);
      noTone(buzzerPin);
    
      tone(buzzerPin, 466);
      delay(500);
      noTone(buzzerPin);
    
      tone(buzzerPin, 523);
      delay(500);
      noTone(buzzerPin);
    
      tone(buzzerPin, 523);
      delay(500);
      noTone(buzzerPin);
    
      tone(buzzerPin, 466);
      delay(500);
      noTone(buzzerPin);
    
      tone(buzzerPin, 440);
      delay(500);
      noTone(buzzerPin);
    
      tone(buzzerPin, 466);
      delay(1500);
      noTone(buzzerPin);
  }
}
