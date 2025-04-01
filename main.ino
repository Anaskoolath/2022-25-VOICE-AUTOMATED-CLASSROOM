#include <SoftwareSerial.h>

#include "DFRobot_DF2301Q.h"

// Define Voice Module pins

#define DF2301Q_RX 10 // Arduino receives data from DF2301Q

#define DF2301Q_TX 11 // Arduino transmits data to DF2301Q

// Define inbuilt LED pin

#define LED_PIN 13

// Initialize SoftwareSerial for DF2301Q

SoftwareSerial dfSerial(DF2301Q_RX, DF2301Q_TX);

// Initialize DF2301Q UART object

DFRobot_DF2301Q_UART voiceModule(&dfSerial);

void setup() {

 // Initialize Serial Monitor for debugging

 Serial.begin(115200);

 // Initialize SoftwareSerial for DF2301Q

 dfSerial.begin(9600);

 // Configure LED pin as OUTPUT
pinMode(LED_PIN, OUTPUT);

 digitalWrite(LED_PIN, LOW); // Ensure LED is OFF initially

 // Initialize the voice recognition module

 while (!voiceModule.begin()) {

 Serial.println("Failed to communicate with Voice Module. Check connections.");

 delay(3000);

 }

 Serial.println("Voice Module initialized successfully!");

 // Play wake-up audio as confirmation (optional)

 voiceModule.playByCMDID(1); // Adjust command ID for wake-up audio if needed

}

void loop() {

 // Fetch command ID from the voice module

 uint8_t CMDID = voiceModule.getCMDID();

 // Debugging: Print the recognized command ID to Serial Monitor

 if (CMDID != 0) {

 Serial.print("Recognized Command ID: ");

 Serial.println(CMDID);

 }

 // Control the inbuilt LED based on command ID
switch (CMDID) {

 case 103: // Turn ON the inbuilt LED

 digitalWrite(LED_PIN, HIGH); // LED ON

 Serial.println("Inbuilt LED ON");

 break;

 case 104: // Turn OFF the inbuilt LED

 digitalWrite(LED_PIN, LOW); // LED OFF

 Serial.println("Inbuilt LED OFF");

 break;

 default:

 if (CMDID != 0) {

 Serial.println("Unrecognized Command ID");

 }

 break;

 }

 delay(300); // Small delay to stabilize

}
