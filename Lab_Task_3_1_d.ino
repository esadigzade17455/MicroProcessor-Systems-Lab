void setup() {
  DDRB = 0b00100000;   // Configure PB5 as an output for the LED
}

void loop() {
  PORTB = (1 << 5);    // Turn the LED on by setting bit 5 high (0b00100000)
  delay(750);
  PORTB = (1 << 0);    // Turn the LED off since bit 5 is cleared (0b00000001)
  delay(750);
}
