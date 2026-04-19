// Arduino C++

const int doorPin = 2;
const int motionPin = 3;
const int resetPin = 4;
const int armPin = 5;

const int normalLed = 8;
const int alarmLed = 9;

int alarmLatched = 0;

bool entryActive = false;
unsigned long doorOpenTime = 0;
const unsigned long gracePeriod = 5000; // Allow 5s grace period in case door is left open

bool doorPreviouslyClosed = true;

void setup() {
  pinMode(doorPin, INPUT);
  pinMode(motionPin, INPUT);
  pinMode(resetPin, INPUT_PULLUP);
  pinMode(armPin, INPUT);

  pinMode(normalLed, OUTPUT);
  pinMode(alarmLed, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int doorState = digitalRead(doorPin);
  int motionState = digitalRead(motionPin);
  int resetState = digitalRead(resetPin);
  int armState = digitalRead(armPin);

  unsigned long currentTime = millis();

  // ALARM RESET (highest priority)
  if (resetState == LOW) {
    alarmLatched = 0;
    entryActive = false;
  }

  
  // ALARM DISARMED MODE
  if (armState == LOW) {
    alarmLatched = 0;
    entryActive = false;

    digitalWrite(alarmLed, LOW);
    digitalWrite(normalLed, HIGH);

    return; // this skips rest of logic when
  }

  ////////////////////////////////////////
  // ALARM ARMED-MODE MAIN LOGIC BLOCK ///
  ////////////////////////////////////////

  // Detect door opening event
  if (doorState == HIGH && doorPreviouslyClosed) {
    entryActive = true;
    doorOpenTime = currentTime;
    doorPreviouslyClosed = false;
  }

  // Detect door closing
  if (doorState == LOW) {
    doorPreviouslyClosed = true;
  }

  // Immediate intrusion: motion while door closed
  if (doorState == LOW && motionState == HIGH) {
    alarmLatched = 1;
  }

  // During grace period
  if (entryActive) {
    bool graceExpired = (currentTime - doorOpenTime) > gracePeriod;

    // Motion during grace
    if (motionState == HIGH) {
      alarmLatched = 1;
    }

    // Grace expired without disarming
    if (graceExpired) {
      alarmLatched = 1;
      entryActive = false; // End of grace period
    }
  }

  // =========================
  // OUTPUT CONTROL
  // =========================
  digitalWrite(normalLed, LOW);
  digitalWrite(alarmLed, LOW);

  if (alarmLatched == 1) {
    digitalWrite(alarmLed, HIGH);
  } else if (doorState == LOW) {
    digitalWrite(normalLed, HIGH);
  }

  // Serial Monitor for Debug and event tracking
  Serial.print("ARM: ");
  Serial.print(armState);
  Serial.print(" | Door: ");
  Serial.print(doorState);
  Serial.print(" | Motion: ");
  Serial.print(motionState);
  Serial.print(" | Entry: ");
  Serial.print(entryActive);
  Serial.print(" | Alarm: ");
  Serial.println(alarmLatched);

  delay(200);
}