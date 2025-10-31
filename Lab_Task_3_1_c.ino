void setup() {
  DDRB = 0b00100000;   // Configure PB5 as an output for the LED
}
void loop() {
  // Toggle the LED state using XOR: if PB5 is 0 → becomes 1 (ON); if 1 → becomes 0 (OFF)
  PORTB ^= 0b00100000;  
  delay(750); 
  // Toggle again after 750 ms to reverse the LED state
  PORTB ^= 0b00100000;  
  delay(750);
}
