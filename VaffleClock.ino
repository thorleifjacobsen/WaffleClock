#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "./LCDBigNumbers.hpp"
#include "./melodies.h"


const int rs = 10, en = 8, d4 = 3, d5 = 2, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LCDBigNumbers bigNumberLCD(&lcd, BIG_NUMBERS_FONT_2_COLUMN_2_ROWS_VARIANT_1);

// Variable for which menu we are in, "main", "timerRunning", "adjustingTimer", "adjustingMelody" or "adjustingWaffels"
String menu = "main";

const int buttonPin = 9; // Button pin
const int buzzerPin = 7; // Buzzer pin
unsigned long timerStartMillis = 0;
byte  melodyIndex = 0; // Index of the melody to play
byte  maxMelodyIndex = 6;
int timerDuration = 40; // 2 minutes and 45 seconds initially
byte adjustPosition = 0; // Adjust position for timer adjustment (0-3)
char timeDisplay[6] = "00:20"; // Display buffer for time
word numberOfWaffels = 0;
// array for possible increments for waffels
int waffelIncrement[] = {1, 5, 10, -10, -5, -1};
word waffelIncrementIndex = 0;


// Constants to define press durations
const unsigned long shortPressTime = 50;    // 50 milliseconds
const unsigned long longPressTime = 1000;    // 1000 milliseconds
const unsigned long veryLongPressTime = 3000; // 3000 milliseconds
const unsigned long insanlyLongPressTime = 5000; // 5000 milliseconds
const unsigned long debounceDelay = 50;      // 50 milliseconds for debounce

// Variables to track button state changes
unsigned long lastDebounceTime = 0;           // the last time the output pin was toggled
int lastButtonState = HIGH;                   // the previous reading from the input pin
bool shortPressPlayed = false;
bool longPressPlayed = false;
bool veryLongPressPlayed = false;
bool insanlyLongPressPlayed = false;

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  bigNumberLCD.begin(); // Creates custom character used for generating big numbers

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  timerDuration = readIntFromEEPROM(0);

  if (timerDuration < 0) {
    writeIntIntoEEPROM(0, 5);
  }

  melodyIndex = EEPROM.read(2);
  if (melodyIndex < 1 || melodyIndex > maxMelodyIndex) {
    melodyIndex = 1;
    EEPROM.write(2, melodyIndex);
  }

  // Get number of waffels
  numberOfWaffels = readIntFromEEPROM(4);

  Serial.print("Melody index: ");
  Serial.println(melodyIndex);

  Serial.print("timerDuration: ");
  Serial.println(timerDuration);

  displayMainMenu();
}

void loop() {
  static unsigned long buttonPressedTime = 0;
  int reading = digitalRead(buttonPin);
  unsigned long currentMillis = millis();

  // Check for button state change and reset debounce timer
  if (reading != lastButtonState) {
    lastDebounceTime = currentMillis;
  }

  if ((currentMillis - lastDebounceTime) > debounceDelay) {
    if (reading == LOW) {
      if (buttonPressedTime == 0) {
        buttonPressedTime = currentMillis;
        shortPressPlayed = longPressPlayed = veryLongPressPlayed = insanlyLongPressPlayed = false; // Reset flags when button is pressed
      } else {
        unsigned long heldTime = currentMillis - buttonPressedTime;
        if (!shortPressPlayed && heldTime >= shortPressTime) {
          playMelody(0, buzzerPin); // Melody for short press
          shortPressPlayed = true;
        }
        if (!longPressPlayed && heldTime >= longPressTime) {
          playMelody(0, buzzerPin); // Melody for long press
          playMelody(0, buzzerPin); // Melody for long press
          longPressPlayed = true;
        }
        if (!veryLongPressPlayed && heldTime >= veryLongPressTime) {
          playMelody(0, buzzerPin); // Melody for very long press
          playMelody(0, buzzerPin); // Melody for very long press
          playMelody(0, buzzerPin); // Melody for very long press
          veryLongPressPlayed = true;
        }
        if (!insanlyLongPressPlayed && heldTime >= insanlyLongPressTime) {
          playMelody(0, buzzerPin); // Melody for very long press
          playMelody(0, buzzerPin); // Melody for very long press
          playMelody(0, buzzerPin); // Melody for very long press
          playMelody(0, buzzerPin); // Melody for very long press
          insanlyLongPressPlayed = true;
        }
      }
    } else if (reading == HIGH && buttonPressedTime >= shortPressTime) {
      unsigned long buttonHoldTime = currentMillis - buttonPressedTime;
      buttonPressedTime = 0; // Reset button press time
      handleButtonPress(buttonHoldTime); // Handle the press based on duration
    }
  }

  // Update display if a timer is running
  if (menu == "timerRunning") {
    updateTimerDisplay();
  }

  lastButtonState = reading; // Update the last button state for the next loop
}

void handleButtonPress(unsigned long buttonHoldTime) {

  // Short click
  if (buttonHoldTime >= shortPressTime && buttonHoldTime < longPressTime) {
    Serial.println("Short Click");
    if (menu == "main") {
      timerStartMillis = millis();
      menu = "timerRunning";
      lcd.clear();
    } else if (menu == "timerRunning") {
      // Do nothing if timer is already running and button is pressed
    } else if (menu == "adjustingTimer") {
      Serial.println("Adjusting timer increment!");
      incrementAdjustPosition();
    } else if (menu == "adjustingMelody") {
      Serial.println("Adjusting melody increment!");
      incrementMelody();
    } else if (menu == "adjustingWaffels") {
      incrementWaffels(waffelIncrement[waffelIncrementIndex]);
    }
  }
  // Long Press
  else if (buttonHoldTime >= longPressTime && buttonHoldTime < veryLongPressTime) {
    // Medium Click
    Serial.println("Medium Click");
    if (menu == "timerRunning") {
      displayMainMenu();
    } else if (menu == "adjustingTimer") {
      // Move to next adjustment position or exit adjusting mode
      adjustPosition = (adjustPosition + 1) % 4;
      showAdjustingTimer();
    } else if (menu == "main") {
      showAdjustMelody();
    } else if (menu == "adjustingMelody") {
      // play the tone
      playMelody(melodyIndex, buzzerPin);
    } else if (menu == "adjustingWaffels") {
      waffelIncrementIndex = (waffelIncrementIndex + 1) % 6;
      showAdjustingWaffels();
    }
  }
  // Very Long Press
  else if (buttonHoldTime >= veryLongPressTime && buttonHoldTime < insanlyLongPressTime) {

    Serial.println("Long Click");

    // If timer is running then we go back to main menu
    if (menu == "timerRunning") {
      displayMainMenu();
    } else if (menu == "adjustingTimer") {
      // Save
      parseTimeDisplayToDuration(); // Update timerDuration based on adjusted time
      writeIntIntoEEPROM(0, timerDuration);
      Serial.print("Writing: ");
      Serial.println(timerDuration);
      lcd.noBlink();
      displayMainMenu();
    } else if (menu == "adjustingMelody") {
      EEPROM.update(2, melodyIndex);
      lcd.noBlink();
      displayMainMenu();
    } else if (menu == "adjustingWaffels") {
      writeIntIntoEEPROM(4, numberOfWaffels);
      lcd.noBlink();
      displayMainMenu();
    } else {
      // If we are in main menu we adjust timer
      adjustPosition = 0; // Reset adjustment position
      int minutesLeft = timerDuration / 60;
      int secondsLeft = timerDuration % 60;
      sprintf(timeDisplay, "%02d:%02d", minutesLeft, secondsLeft);
      showAdjustingTimer();
    }
  }
  // Insanly Long Press
  else if (buttonHoldTime >= insanlyLongPressTime) {
    Serial.println("Insanly Long Click");
    if (menu == "timerRunning") {
      displayMainMenu();
    } else if (menu == "adjustingTimer" || menu == "adjustingMelody" || menu == "adjustingWaffels") {
      // Cancel adjustment and return to main menu
      melodyIndex = EEPROM.read(2);
      numberOfWaffels = readIntFromEEPROM(4);
      lcd.noBlink();
      displayMainMenu();
    } else {
      showAdjustingWaffels();
    }
  }
}

void updateTimerDisplay() {
  int remainingTime = timerDuration - (millis() - timerStartMillis) / 1000;
  if (remainingTime <= 0) {
    // Increment and store in EEPROM
    numberOfWaffels++;
    writeIntIntoEEPROM(4, numberOfWaffels);

    // Generate string    
    String numStr = String(numberOfWaffels);
    String baseStr = "FERDIG";
    
    // Create the initial string with a single space (default)
    String fullStr = numStr + " " + baseStr;
    int len = fullStr.length();
  
    // Calculate spaces to center the text
    int spaces = (16 - len) / 2;
    
    // Build the string with leading spaces for centering
    String displayStr = "";
    for(int i = 0; i < spaces; i++) {
      displayStr += " ";
    }
  
    // Add the formatted string with an extra space if the length is odd
    if ((18 - len) % 2 != 0) {
      fullStr = numStr + "  " + baseStr;  // Adding two spaces instead of one
    }
    
    displayStr += fullStr;

    lcd.clear();
    lcd.print(" VAFFEL  NUMMER ");
    lcd.setCursor(0, 1);
    lcd.print(displayStr);
    playMelody(melodyIndex, buzzerPin);
    delay(2000);
    displayMainMenu();
  } else {
    int minutesLeft = remainingTime / 60;
    int secondsLeft = remainingTime % 60;

    sprintf(timeDisplay, "%02d:%02d", minutesLeft, secondsLeft);
    bigNumberLCD.setBigNumberCursor(0, 0); // row specification is redundant here for a 4 row font :-)
    bigNumberLCD.print(F(ONE_COLUMN_SPACE_STRING ONE_COLUMN_SPACE_STRING)); // print a number string
    bigNumberLCD.print(timeDisplay);
  }
}

void showAdjustingTimer() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Endre nedtelling:");
  lcd.setCursor(0, 1);
  lcd.print(timeDisplay);
  // Blink or highlight the digit being adjusted
  lcd.setCursor(adjustPosition + (adjustPosition > 1 ? 1 : 0), 1); // Adjust for ':' in display
  lcd.blink(); // Make the LCD cursor blink on the position being adjusted
  menu = "adjustingTimer";
}

void incrementAdjustPosition() {
  // Increments the digit in the current adjustPosition
  // Rolls over if necessary (e.g., '9' becomes '0')
  if (adjustPosition == 0) { // Adjusting tens of minutes
    timeDisplay[adjustPosition] = incrementDigit(timeDisplay[adjustPosition], '0', '9');
  } else if (adjustPosition == 1) { // Adjusting minutes
    timeDisplay[adjustPosition] = incrementDigit(timeDisplay[adjustPosition], '0', '9');
  } else if (adjustPosition == 2) { // Adjusting tens of seconds
    timeDisplay[adjustPosition + 1] = incrementDigit(timeDisplay[adjustPosition + 1], '0', '5'); // Seconds tens can only go up to '5'
  } else if (adjustPosition == 3) { // Adjusting seconds
    timeDisplay[adjustPosition + 1] = incrementDigit(timeDisplay[adjustPosition + 1], '0', '9');
  }
  showAdjustingTimer(); // Refresh display to show updated time
}

char incrementDigit(char digit, char minVal, char maxVal) {
  digit++;
  if (digit > maxVal) {
    digit = minVal;
  }
  if (digit > maxVal || digit < minVal) {
    digit = 0;
  }
  return digit;
}

void parseTimeDisplayToDuration() {
  // Convert the timeDisplay string to seconds and store in timerDuration
  int mins = (timeDisplay[0] - '0') * 10 + (timeDisplay[1] - '0');
  int secs = (timeDisplay[3] - '0') * 10 + (timeDisplay[4] - '0');
  timerDuration = mins * 60 + secs;
}

void showAdjustMelody() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Velg alarm lyd:");
  lcd.setCursor(0, 1);
  lcd.print(melodyIndex);
  // Blink or highlight the digit being adjusted
  lcd.setCursor(adjustPosition, 1); // Adjust for ':' in display
  lcd.blink(); // Make the LCD cursor blink on the position being adjusted
  menu = "adjustingMelody";
}

void incrementMelody() {
  melodyIndex = (melodyIndex % maxMelodyIndex) + 1;
  showAdjustMelody();
}

void showAdjustingWaffels() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vaffler: (" + String(waffelIncrement[waffelIncrementIndex]) + ")");
  lcd.setCursor(0, 1);
  lcd.print(numberOfWaffels);
  lcd.blink();
  menu = "adjustingWaffels";
}

void incrementWaffels(word num) {
  numberOfWaffels = numberOfWaffels + num;
  showAdjustingWaffels();
}

void displayMainMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Kleine Karer");
  lcd.setCursor(0, 1);
  lcd.print("  VaffelKlokke");
  menu = "main";
}

int readIntFromEEPROM(int address)
{
  byte byte1 = EEPROM.read(address);
  byte byte2 = EEPROM.read(address + 1);
  return (byte1 << 8) + byte2;
}

void writeIntIntoEEPROM(int address, int number)
{
  EEPROM.update(address, number >> 8);
  EEPROM.update(address + 1, number & 0xFF);
}
