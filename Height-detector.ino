#include <HCSR04.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD and Ultrasonic sensor
LiquidCrystal_I2C lcd(0x27, 16, 2);
HCSR04 distanceSensor(2,3);

// Global variables
float distance;
float boxHeight = 210.0;
int buzzerPin = 8;
int heightInCm;

// Function prototypes
void setup();
void loop();
void printInstructions();
void printHeight();
void printWeight(float heightInMeters, float heightInCm);

void setup() {
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    pinMode(buzzerPin, OUTPUT);
    printInstructions();
}

void loop() {
    distance = distanceSensor.dist();
    Serial.println(distance);
    delay(2000);

    if (distance < 65) {
        printHeight();
        delay(1000);
        tone(buzzerPin, 1000);
        delay(1000);
        noTone(buzzerPin);
        
 // Calculate suggested weight and BMI based on height
        float heightInMeters = (boxHeight - distance) / 100.0; 
// Convert box height from cm to meters
        printWeight(heightInMeters);
        delay(5000);
    }
       printInstructions(); 
}

void printInstructions() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Stand under the");
    lcd.setCursor(0, 1);
    lcd.print("sensor!");
}

void printHeight() {
    float heightInCm = boxHeight - distance;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Height:");
    lcd.setCursor(8, 0);
    lcd.print(heightInCm, 1);
    lcd.setCursor(14, 0);
    lcd.print("cm");
    delay(5000);
}

void printWeight(float heightInMeters)
{
 // Calculate suggested weight based on BMI range (18.5 - 24.9)
    float minBMI = 18.5;
    float maxBMI = 24.9;
    float minWeight = minBMI * (heightInMeters * heightInMeters);
    float maxWeight = maxBMI * (heightInMeters * heightInMeters);
lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Weight:");
    lcd.setCursor(0, 1);
    lcd.print(minWeight, 1); 
// Display suggested minimum weight in kilogram
    lcd.print("-");
    lcd.print(maxWeight, 1); 
// Display suggested maximum weight in kilogram
    lcd.setCursor(10, 1);
    lcd.print("kg");
    delay(5000);
    setup();
}
// Krysthille Anne Tambis