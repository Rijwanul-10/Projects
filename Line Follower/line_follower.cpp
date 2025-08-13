// Pin assignments
#define LEFT_SENSOR_PIN A0     // Left IR sensor
#define RIGHT_SENSOR_PIN A1    // Right IR sensor
#define LEFT_MOTOR_ENABLE 5    // PWM pin for left motor
#define LEFT_MOTOR_DIR 4       // Direction pin for left motor
#define RIGHT_MOTOR_ENABLE 6   // PWM pin for right motor
#define RIGHT_MOTOR_DIR 7      // Direction pin for right motor

#define THRESHOLD 500          // Threshold for sensor readings

void setup() {
  // Initialize sensor pins
  pinMode(LEFT_SENSOR_PIN, INPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT);

  // Initialize motor pins
  pinMode(LEFT_MOTOR_ENABLE, OUTPUT);
  pinMode(LEFT_MOTOR_DIR, OUTPUT);
  pinMode(RIGHT_MOTOR_ENABLE, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR, OUTPUT);

  // Start Serial Monitor for debugging
  Serial.begin(9600);
}

void loop() {
  // Read sensor values
  int leftSensorValue = analogRead(LEFT_SENSOR_PIN);
  int rightSensorValue = analogRead(RIGHT_SENSOR_PIN);

  // Print sensor values to Serial Monitor for debugging
  Serial.print("Left Sensor: ");
  Serial.print(leftSensorValue);
  Serial.print(" | Right Sensor: ");
  Serial.println(rightSensorValue);

  // Default behavior: move forward
  moveForward();  

  // Adjust movement if black line is detected
  if (leftSensorValue < THRESHOLD && rightSensorValue < THRESHOLD) {
    moveForward();  // Both sensors detect black
  } else if (leftSensorValue >= THRESHOLD && rightSensorValue < THRESHOLD) {
    turnRight();  // Turn right when left sensor detects white
  } else if (leftSensorValue < THRESHOLD && rightSensorValue >= THRESHOLD) {
    turnLeft();  // Turn left when right sensor detects white
  }
}

// Functions to control motor actions
void moveForward() {
  digitalWrite(LEFT_MOTOR_DIR, HIGH);
  digitalWrite(RIGHT_MOTOR_DIR, HIGH);
  analogWrite(LEFT_MOTOR_ENABLE, 150);  // Adjust speed (0-255)
  analogWrite(RIGHT_MOTOR_ENABLE, 150);
}

void turnRight() {
  digitalWrite(LEFT_MOTOR_DIR, HIGH);
  digitalWrite(RIGHT_MOTOR_DIR, LOW);
  analogWrite(LEFT_MOTOR_ENABLE, 150);
  analogWrite(RIGHT_MOTOR_ENABLE, 150);
}

void turnLeft() {
  digitalWrite(LEFT_MOTOR_DIR, LOW);
  digitalWrite(RIGHT_MOTOR_DIR, HIGH);
  analogWrite(LEFT_MOTOR_ENABLE, 150);
  analogWrite(RIGHT_MOTOR_ENABLE, 150);
}

void stopMotors() {
  analogWrite(LEFT_MOTOR_ENABLE, 0);
  analogWrite(RIGHT_MOTOR_ENABLE, 0);
}
