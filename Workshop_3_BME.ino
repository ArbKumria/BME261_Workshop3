#include <Servo.h>

Servo myservo1;  // standard position servo
Servo myservo2;  // continuous-rotation servo

void setup() {
  Serial.begin(9600);
  myservo1.attach(11);  // Position servo on pin 11
  myservo2.attach(9);   // Continuous rotation servo on pin 9
  Serial.println("Setup complete. Ready for commands.");
}

void posServo() {
  if (Serial.available() > 0) {
    int angle = Serial.parseInt();
    while (Serial.available() > 0 && Serial.read() != '\n');
    if (angle >= 0 && angle <= 180) {
      myservo1.write(angle);
      Serial.print("Position servo: moved to ");
      Serial.print(angle);
      Serial.println(" degrees");
    } else {
      Serial.println("Invalid angle. Enter 0-180.");
    }
  }
}

void rotServo() {
  if (Serial.available() > 0) {
    int speed = Serial.parseInt();   // –100 … +100
    while (Serial.available() > 0 && Serial.read() != '\n');

    // 1) validate
    if (speed < -100 || speed > 100) {
      Serial.println("Invalid speed. Enter -100 to 100.");
      return;
    }

    // 2) stop on zero
    if (speed == 0) {
      myservo2.write(93);            // neutral
      Serial.println("Rotation servo: stopped");
      return;
    }

    // 3) invert mapping: –100→180°, +100→0°
    int angle = map(speed, -100, 100, 180, 0);
    myservo2.write(angle);

    // feedback
    Serial.print("Rotation servo: ");
    Serial.print(speed);
    Serial.print("% → angle ");
    Serial.print(angle);
    Serial.println("°");
  }
}
void loop() {
  // Uncomment to test one at a time:
  posServo(); // Currently Testing Position Servo 
  //rotServo();  // reading -100 to 100, mapping to 0–180
  delay(50);
}
