volatile uint8_t counter;  // Counter stored in SRAM; resets to 0 when power is lost
void setup() {
  Serial.begin(9600);  
  while (EECR & (1 << EEPE));   // Wait if EEPROM is still writing
  EEAR = 0;                     // Set EEPROM address to 0
  EECR |= (1 << EERE);          // Start EEPROM read
  counter = EEDR;               // Load value from EEPROM data register into counter
  DDRD &= ~(1 << PD2);          // Configure PD2 (button pin) as input 
  Serial.print("Starting counter from: ");
  Serial.println(counter);
}

void loop() {
  if (PIND & (1 << PD2)) {      // Check if button is pressed
    delay(250);                 // Simple debounce delay
    asm volatile(
      "lds r25, counter    \n\t"   // Load counter from SRAM into register r25
      "inc r25             \n\t"   // Increase r25 by 1
      "sts counter, r25    \n\t"   // Store updated value back into SRAM (counter)
    );
    // lds = load from SRAM to register  
    // sts = store from register to SRAM
    while (EECR & (1 << EEPE));   // Wait if EEPROM is busy
    EEAR = 0;                     // Set EEPROM address to 0
    EEDR = counter;               // Load new counter value into EEPROM data register
    EECR |= (1 << EEMPE);         // Enable master write
    EECR |= (1 << EEPE);          // Begin EEPROM write
    Serial.print("Counter: ");
    Serial.println(counter);
    while (PIND & (1 << PD2));    // Wait for button release
  }
}
