const int button_pin = 2;
const int led_pin = 7;

int button_state = 0;

void setup() {
  Serial.begin(9600);

  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT);
}

void loop() {
  button_state = digitalRead(button_pin);

  Serial.println(buttonState);
  if (buttonstate == HIGH) {
    digitalWrite(led_pin, HIGH);
  }
  else {
    digitalWrite(led_pin, LOW);
  }
}
