const int potentiometer_one = A2;
const int potentiometer_two = A4;

const int button = 4;

const int led_green = 8;
const int led_yellow = 7;
const int led_red = 2;
const int led_blue = 12;


unsigned int button_state = 0;
unsigned int value_left;
unsigned int value_right;
unsigned int read_value_right;
unsigned int read_value_left;
unsigned int goal_value_left;
unsigned int goal_value_right;
unsigned int i;

void setup() {
  Serial.begin(9600);

  pinMode(led_green, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_blue, OUTPUT);
  pinMode(button, INPUT);
  pinMode(potentiometer_one, INPUT);
  pinMode(potentiometer_two, INPUT);
}

void blink_start() {

  led_map(1, 1 , 1);
  delay(100);
  led_map(0, 0, 0);
  delay(100);
  led_map(1, 1 , 1);
  delay(250);
  led_map(0, 0, 0);
  delay(100);
}

void led_map(int green, int yellow, int red) {

  if (green == 1) {
    digitalWrite(led_green, HIGH);
  }
  else {
    digitalWrite(led_green, LOW);
  }

  if (yellow == 1) {
    digitalWrite(led_yellow, HIGH);
  }
  else {
    digitalWrite(led_yellow, LOW);
  }

  if (red == 1) {
    digitalWrite(led_red, HIGH);
  }
  else {
    digitalWrite(led_red, LOW);
  }

}

void blink_wrong() {

  led_map(1, 1, 1);
  delay(500);

  led_map(0, 0, 0);
  delay(300);

  led_map(1, 1, 1);
  delay(500);

  led_map(0, 0, 0);
  delay(300);

  led_map(1, 1, 1);
  delay(500);

  led_map(0, 0, 0);
  delay(300);
}

void blink_victory() {
  led_map(0, 0 ,0);
  for (i = 0; i < 4; i++) {
    digitalWrite(led_green, HIGH);
    delay(100);
    digitalWrite(led_green, LOW);
    delay(100);
    digitalWrite(led_yellow, HIGH);
    delay(100);
    digitalWrite(led_yellow, LOW);
    delay(100);
    digitalWrite(led_red, HIGH);
    delay(100);
    digitalWrite(led_red, LOW);
    delay(100);
    digitalWrite(led_red, HIGH);
    delay(100);
    digitalWrite(led_red, LOW);
    delay(100);
    digitalWrite(led_yellow, HIGH);
    delay(100);
    digitalWrite(led_yellow, LOW);
    delay(100);
    digitalWrite(led_green, HIGH);
    delay(100);
    digitalWrite(led_green, LOW);
    delay(100);
  }
}

void game() {

  // Randomize goal value for left potentiometer
  goal_value_left = random(30, 260);

  // Randomize goal value for right potentiometer
  goal_value_right = random(30, 260);

  Serial.println(goal_value_left);
  Serial.println(goal_value_right);


  while (true) {
    read_value_right = analogRead(potentiometer_one);
    read_value_left = analogRead(potentiometer_two);
    value_left = map(read_value_left, 0, 1023, 0, 300);
    value_right = map(read_value_right, 0, 1023, 0, 300);
    digitalWrite(led_blue, LOW);

    // If both values are correct, light up all three main LEDs
    if ((value_left == goal_value_left) && (value_right == goal_value_right)) {
      led_map(1, 1, 1);
      Serial.println("Both OK");
    }
    // Otherwise, show some different combinations of LEDs
    else {
      if (value_left < (goal_value_left - 20) && value_right < (goal_value_right - 20)) {
        led_map(1, 0 ,1);
        Serial.println("Both LOW");
      }
      else if ((value_left > goal_value_left + 20) && (value_right > goal_value_right + 20)) {
        led_map(0, 1, 0);
        Serial.println("Both HIGH");
      }
      else if ((value_left < (goal_value_left - 20)) && (value_right > goal_value_right + 20)) {
        led_map(1, 1, 0);
        Serial.println("Left LOW, Right HIGH");
      }
      else if ((value_left > goal_value_left + 20) && (value_right < (goal_value_right - 20)) ) {
        led_map(0, 1, 1);
        Serial.println("Left HIGH, Right LOW");
      }
      else if ((value_left == goal_value_left) || (value_right == goal_value_right)) {
        led_map(0, 0, 0);
        digitalWrite(led_blue, HIGH);

      }
      else {
        led_map(0, 0 ,0);
      }
    }

    button_state = digitalRead(button);
    
    // When the player presses the button, check if they win or if they need to retry
    if (button_state == HIGH) {
      if (value_left == goal_value_left && value_right == goal_value_right) {
        blink_victory();
        blink_start();
        Serial.println("Correct! You win");
        delay(1000);
        break;
      }
      else {
        Serial.println("Wrong answer");
        blink_wrong();
        delay(500);
      }
    }
  }
  delay(500);
}

void loop() {
  button_state = digitalRead(button);
  
  // Do some blinking while waiting for a player
  while (button_state == 0) {
    button_state = digitalRead(button);
    Serial.println("Waiting for player...");
    digitalWrite(led_green, HIGH);
    delay(200);
    digitalWrite(led_green, LOW);
    delay(150);
    digitalWrite(led_yellow, HIGH);
    delay(200);
    digitalWrite(led_yellow, LOW);
    delay(150);
    digitalWrite(led_red, HIGH);
    delay(200);
    digitalWrite(led_red, LOW);
    delay(150);
  }
  Serial.println("Player found! Starting game...");
  blink_start();
  game();

}
