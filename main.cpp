#include <Arduino.h>

#define X_STEP_PIN 54
#define X_DIR_PIN 55
#define X_ENABLE_PIN 38
#define X_MIN_PIN 3

#define Y_STEP_PIN 60
#define Y_DIR_PIN 61
#define Y_ENABLE_PIN 56
#define Y_MIN_PIN 14

void go_home()
{
  Serial.println("Going home");
  //Set direction to go towards endstops
  digitalWrite(X_DIR_PIN, HIGH);
  digitalWrite(Y_DIR_PIN, LOW);

  // Keep stepping the motor until the endstop button is pressed
  for (int counter = 0; digitalRead(X_MIN_PIN) == false; counter++)
  {
    delay(1);
    digitalWrite(X_STEP_PIN, not digitalRead(X_STEP_PIN));
  }

  for (int counter = 0; digitalRead(Y_MIN_PIN) == false; counter++)
  {
    delay(1);
    digitalWrite(Y_STEP_PIN, not digitalRead(Y_STEP_PIN));
  }
}

void go_to_start_point()
{
  Serial.println("Going to start position");
  //Go to the bottom right of where the square will be
  for (int counter = 0; counter < 10000; counter++)
  {
    digitalWrite(X_DIR_PIN, LOW);
    digitalWrite(Y_DIR_PIN, HIGH);
    delay(1);
    digitalWrite(X_STEP_PIN, not digitalRead(X_STEP_PIN));
    digitalWrite(Y_STEP_PIN, not digitalRead(Y_STEP_PIN));
  }
}

void draw_square()
{
  Serial.println("Drawing square");
  //Draw right line (going upwards)
  for (int counter = 0; counter < 5000; counter++)
  {
    digitalWrite(Y_DIR_PIN, LOW);
    delay(1);
    digitalWrite(Y_STEP_PIN, not digitalRead(Y_STEP_PIN));
  }

  //Draw top line (going left)
  for (int counter = 0; counter < 5000; counter++)
  {
    digitalWrite(X_DIR_PIN, HIGH);
    delay(1);
    digitalWrite(X_STEP_PIN, not digitalRead(X_STEP_PIN));
  }

  //Draw left line (going down)
  for (int counter = 0; counter < 5000; counter++)
  {
    digitalWrite(Y_DIR_PIN, HIGH);
    delay(1);
    digitalWrite(Y_STEP_PIN, not digitalRead(Y_STEP_PIN));
  }

  //Draw bottom line (going right)
  for (int counter = 0; counter < 5000; counter++)
  {
    digitalWrite(X_DIR_PIN, LOW);
    delay(1);
    digitalWrite(X_STEP_PIN, not digitalRead(X_STEP_PIN));
  }
}

void draw_triangle()
{
  Serial.println("Drawing triangle");
  //Go diagonally (towards top-right)
  for (int counter = 0; counter < 2500; counter++)
  {
    digitalWrite(X_DIR_PIN, LOW);
    digitalWrite(Y_DIR_PIN, LOW);
    delay(1);
    digitalWrite(X_STEP_PIN, not digitalRead(X_STEP_PIN));
    digitalWrite(Y_STEP_PIN, not digitalRead(Y_STEP_PIN));
  }

  //Go diagonally (towards top-left)
  for (int counter = 0; counter < 2500; counter++)
  {
    digitalWrite(X_DIR_PIN, HIGH);
    digitalWrite(Y_DIR_PIN, LOW);
    delay(1);
    digitalWrite(X_STEP_PIN, not digitalRead(X_STEP_PIN));
    digitalWrite(Y_STEP_PIN, not digitalRead(Y_STEP_PIN));
  }

  //Go down (draw left [straight] line)
  for (int counter = 0; counter < 5000; counter++)
  {
    digitalWrite(Y_DIR_PIN, HIGH);
    delay(1);
    digitalWrite(Y_STEP_PIN, not digitalRead(Y_STEP_PIN));
  }
}

void go_to_centre()
{
  Serial.println("Going to centre");
  //Go to the centre of the workspace
  for (int counter = 0; counter < 5000; counter++)
  {
    digitalWrite(X_DIR_PIN, LOW);
    delay(1);
    digitalWrite(X_STEP_PIN, not digitalRead(X_STEP_PIN));
  }
  
  for (int counter = 0; counter < 8000; counter++)
  {
    digitalWrite(X_DIR_PIN, LOW);
    digitalWrite(Y_DIR_PIN, HIGH);
    delay(1);
    digitalWrite(X_STEP_PIN, not digitalRead(X_STEP_PIN));
    digitalWrite(Y_STEP_PIN, not digitalRead(Y_STEP_PIN));
  }

  digitalWrite(X_ENABLE_PIN, HIGH); //Disables the X axis stepper motor
  digitalWrite(Y_ENABLE_PIN, HIGH); //Disables the Y axis stepper motor
}

void move_to_next_point()
{
  Serial.println("Moving to next point");
  //Move to next point
  for (int counter = 0; counter < 1000; counter++)
  {
    digitalWrite(X_DIR_PIN, LOW);
    delay(1);
    digitalWrite(X_STEP_PIN, not digitalRead(X_STEP_PIN));
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);

  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);

  digitalWrite(X_ENABLE_PIN, LOW); //Enables the X axis stepper motor
  digitalWrite(Y_ENABLE_PIN, LOW); //Enables the Y axis stepper motor

  pinMode(X_MIN_PIN, INPUT_PULLUP); //Assigns a pull up resistor to the X-axis endstop button
  pinMode(Y_MIN_PIN, INPUT_PULLUP); //Assigns a pull up resistor to the Y-axis endstop button
}

void loop()
{
  delay(3000);
  go_home();            // 1
  go_to_start_point();  // 2
  draw_square();        // 3
  move_to_next_point(); // 4
  draw_triangle();      // 5
  go_to_centre();       // 6
}
