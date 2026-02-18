const int ledPin = 18;
const int buttonPin = 4;

bool sessionActive = false;
bool lockout = false;
unsigned long sessionStartTime = 0;

const unsigned long MAX_SESSION_DURATION = 600000; // 10 minutes

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  bool buttonPressed = (digitalRead(buttonPin) == LOW);

// START SESSION 
  if (buttonPressed && !sessionActive && !lockout) {
    sessionActive = true;
    sessionStartTime = millis();
  }

// END SESSION: phone removed
  if (!buttonPressed && sessionActive) {
    sessionActive = false;  
  }

  // END SESSION: time limit reached
  if (sessionActive && millis() - sessionStartTime >= MAX_SESSION_DURATION) {
    sessionActive = false;
    lockout = true;
  }

  // CLEAR LOCKOUT: when phone removed
  if (!buttonPressed && lockout) {
    lockout = false;
  }

  // STATE
  if (sessionActive) {
    Serial.println("START");
    digitalWrite(ledPin, HIGH);
  } else {
    Serial.println("STOP");
    digitalWrite(ledPin, LOW);
  }
}
