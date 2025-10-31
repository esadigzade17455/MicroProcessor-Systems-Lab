void setup() {
  DDRB = 0b00100000; // Configure PB5 as an output for the LED
}

void loop() {
  PORTB = 0b00100000; // Turn the LED on by setting PB5 high
  delay(750);
  PORTB = 0b00000000; // Turn the LED off by clearing PB5
  delay(750);
}
