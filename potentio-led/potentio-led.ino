const int potentio_pin = A2;
const int led_1 = 8;
const int led_2 = 7;
const int led_3 = 2;

int read_value;
int write_value;
int mapped_value;

void setup() {
  Serial.begin(9600);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(potentio_pin, INPUT);
}

void loop() {
  read_value = analogRead(potentio_pin);
  mapped_value = map(read_value, 0, 1023, 0, 255);
  Serial.println("Potentiometer: ");
  Serial.println(mapped_value);
  if (mapped_value < 64) {
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, LOW);
  }
  if (mapped_value > 64 && mapped_value < 128) {
    digitalWrite(led_1, HIGH);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, LOW);
  }
  if (mapped_value > 128 && mapped_value < 192) {
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, HIGH);
    digitalWrite(led_3, LOW);
  }
  if (mapped_value > 192 && mapped_value < 240) {
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, HIGH);
  }
  if (mapped_value > 240) {
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, LOW);
    delay(100);
    digitalWrite(led_1, HIGH);
    delay(100);
    digitalWrite(led_2, HIGH);
    delay(100);
    digitalWrite(led_3, HIGH);
    delay(200);
  }

}
