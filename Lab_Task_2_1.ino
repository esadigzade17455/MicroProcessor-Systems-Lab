void setup() {
    DDRB |= (1 << DDB5);   // Configure PB5 (pin 13, built-in LED) as an output
    DDRD &= ~(1 << DDD2);  // Configure PD2 (pin 2, button) as an input
}

void loop() {
    if (PIND & (1 << PIND2)) {       // Detect if the button is being pressed
        PORTB ^= (1 << PORTB5);      // Toggle the LED state
        delay(200);                  // Wait for 200 milliseconds
    }
}
