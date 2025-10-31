#include <avr/io.h>
#include <util/delay.h>

// ===== Setup function =====
void setup() {
  // ===== Output pins for LEDs =====
  DDRD |= (1 << PD6);  // OC0A / pin 6  / Timer0
  DDRB |= (1 << PB1);  // OC1A / pin 9  / Timer1
  DDRB |= (1 << PB3);  // OC2A / pin 11 / Timer2

  // ===== Input pin for button =====
  DDRB &= ~(1 << PB0); // Set PB0 as input
  PORTB |= (1 << PB0); // Enable internal pull-up resistor

  // ===== Timer0 setup =====
  TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1); // Fast PWM, clear OC0A on compare match
  TCCR0B = (1 << CS01); // Prescaler = 8

  // ===== Timer1 setup =====
  TCCR1A = (1 << WGM10) | (1 << COM1A1); // 8-bit Fast PWM, clear OC1A on compare match
  TCCR1B = (1 << WGM12) | (1 << CS11);   // Fast PWM, prescaler = 8

  // ===== Timer2 setup =====
  TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2A1); // Fast PWM, clear OC2A on compare match
  TCCR2B = (1 << CS21); // Prescaler = 8
}

// ===== Counter to track button presses =====
uint8_t press_count = 0;

// ===== Function to read button and handle debounce =====
uint8_t readButton() {
  static uint8_t prev = 1; // previous button state
  uint8_t current = (PINB & (1 << PB0)) ? 1 : 0; // current button state

  if (prev == 1 && current == 0) { // detect falling edge (button press)
    _delay_ms(30); // debounce delay
    if ((PINB & (1 << PB0)) == 0) { // confirm button is still pressed
      prev = current;
      return 1; // button press detected
    }
  }
  prev = current;
  return 0; // no new press
}

// ===== Main loop =====
void loop() {
  if (readButton()) { // if button pressed
    press_count++;                // increase counter
    if (press_count > 12) press_count = 1; // wrap around after 12 presses

    uint8_t level = ((press_count - 1) % 4) + 1; // determine brightness level (1-4)
    uint8_t brightness = (level * 64) - 1;       // brightness steps: 63, 127, 191, 255

    // Activate one LED at a time based on press_count
    if (press_count <= 4) {
      OCR0A = brightness;  // LED 1 active
      OCR1A = 0;
      OCR2A = 0;
    } else if (press_count <= 8) {
      OCR0A = 0;
      OCR1A = brightness;  // LED 2 active
      OCR2A = 0;
    } else {
      OCR0A = 0;
      OCR1A = 0;
      OCR2A = brightness;  // LED 3 active
    }
  }
}
