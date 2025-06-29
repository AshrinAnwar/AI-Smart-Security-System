//AI-Smart-Security-System
#define pirPin 2
#define ledPin 9
#define buzzerPin 8
  
bool aiControlEnabled = true;
bool silentMode = false;
String aiCommand = "";

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);

  Serial.println("AI-Controlled Smart Security System Initialized.");
  Serial.println("Commands: alert | silent | on | off");
}

void loop() {
  // --- Check for serial input ---
  if (Serial.available()) {
    aiCommand = Serial.readStringUntil('\n');
    aiCommand.trim();
    aiCommand.toLowerCase();

    if (aiCommand == "alert") {
      Serial.println("Manual Alert Triggered");
      digitalWrite(ledPin, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(10000);
      digitalWrite(ledPin, LOW);
      digitalWrite(buzzerPin, LOW);
    }
    else if (aiCommand == "silent") {
      Serial.println("Silent Mode ON");
      silentMode = true;
    }
    else if (aiCommand == "on") {
      Serial.println("System ON");
      aiControlEnabled = true;
      silentMode = false;
    }
    else if (aiCommand == "off") {
      Serial.println("System OFF");
      aiControlEnabled = false;
      digitalWrite(ledPin, LOW);
      digitalWrite(buzzerPin, LOW);
    }
  }

  // --- Motion detection logic ---
  if (aiControlEnabled) {
    int motion = digitalRead(pirPin);
    if (motion == HIGH) {
      Serial.println("Motion Detected!");

      digitalWrite(ledPin, HIGH);
      if (!silentMode) {
        digitalWrite(buzzerPin, HIGH);
      }

      delay(2000);

      digitalWrite(ledPin, LOW);
      digitalWrite(buzzerPin, LOW);
    }
  }

  delay(100);
}
