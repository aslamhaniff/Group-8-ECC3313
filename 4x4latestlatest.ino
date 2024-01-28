int motor_lA = 10;
int motor_lB = 9;
int motor_enableA = 11;

int motor_rA = 4;
int motor_rB = 3;
int motor_enableB = 5;

int trigger_front = A0;
int echo_front = A1;

int trigger_left = A2;
int echo_left = A3;

int trigger_right = A4;
int echo_right = A5;

void setup() {
  pinMode(motor_lA, OUTPUT);
  pinMode(motor_lB, OUTPUT);
  pinMode(motor_enableA, OUTPUT);

  pinMode(motor_rA, OUTPUT);
  pinMode(motor_rB, OUTPUT);
  pinMode(motor_enableB, OUTPUT);

  pinMode(trigger_front, OUTPUT);
  pinMode(echo_front, INPUT);

  pinMode(trigger_left, OUTPUT);
  pinMode(echo_left, INPUT);

  pinMode(trigger_right, OUTPUT);
  pinMode(echo_right, INPUT);

  analogWrite(motor_enableA, 140);
  analogWrite(motor_enableB, 140);

  Serial.begin(9600);
}

void loop() {
  long duration_front, distance_front, duration_left, distance_left, duration_right, distance_right;

  // Calculating distance
  distance_front = getDistance(trigger_front, echo_front);
  distance_left = getDistance(trigger_left, echo_left);
  distance_right = getDistance(trigger_right, echo_right);

  Serial.print("Front = ");
  Serial.println(distance_front);
  Serial.print("Left = ");
  Serial.println(distance_left);
  Serial.print("Right = ");
  Serial.println(distance_right);
  delay(50);

   // If there's an obstacle in front
  if (distance_front <= 40) {
    // If there's enough space on the left, turn left
    if (distance_left > 30) {
      Stop();
      left();
      delay(300);  // Adjust the delay based on your requirements
      forward();
    }
    // If not, stop and turn right
    else {
      Stop();
      right();
      delay(300);  // Adjust the delay based on your requirements
    }
  }
  // If there's no obstacle on the right or left
  else if (distance_right > 20 && distance_left > 20) {
    // Move forward
    forward();
  }
  // If there's enough space on the left, turn left slightly
  else if (distance_left > 20) {
    // Turn left slightly
    left();
    delay(100);
    forward();
  }
  // Otherwise, just keep moving forward
  else {
    forward();
  }
}



long getDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

void forward() {
  digitalWrite(motor_lA, HIGH);
  digitalWrite(motor_lB, LOW);
  digitalWrite(motor_rA, HIGH);
  digitalWrite(motor_rB, LOW);
  // Check the front distance
  long distance_front = getDistance(trigger_front, echo_front);

  // If the front distance is less than a threshold, stop the robot
  if (distance_front < 40) {
    Stop();
  }
  delay(500);
}

void right() {
  digitalWrite(motor_lA, LOW);
  digitalWrite(motor_lB, HIGH);
  digitalWrite(motor_rA, HIGH);
  digitalWrite(motor_rB, LOW);
  analogWrite(motor_enableA, 200); // Increase motor speed
  analogWrite(motor_enableB, 200); // Increase motor speed
  delay(800);                       // Adjust the delay based on your requirements
  Stop();
}

void left() {
  digitalWrite(motor_lA, HIGH);
  digitalWrite(motor_lB, LOW);
  digitalWrite(motor_rA, LOW);
  digitalWrite(motor_rB, HIGH);
  analogWrite(motor_enableA, 200); // Increase motor speed
  analogWrite(motor_enableB, 200); // Increase motor speed
  delay(800);                       // Adjust the delay based on your requirements
  Stop();
}

void Stop() {
  digitalWrite(motor_lA, LOW);
  digitalWrite(motor_lB, LOW);
  digitalWrite(motor_rA, LOW);
  digitalWrite(motor_rB, LOW);
  delay(1000);
}
