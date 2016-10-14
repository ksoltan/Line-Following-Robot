int portPin = A0;
int starboardPin = A1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(analogRead(portPin));
  Serial.print(",");
  Serial.println(analogRead(starboardPin));
  delay(100);
}
