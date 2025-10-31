void setup() {
  DDRB |= 0b00100000;   // Set PB5 as an output for the LED
}

void loop() {
  PORTB |= 0b00100000;  // Turn the LED on using OR operation
  delay(750);
  PORTB &= 0b11011111;  // Turn the LED off using AND operation
  delay(750);
}
