#include <avr/io.h>
#include <util/delay.h>

void setup() {
  // ===== Set LED pins as outputs =====
  DDRD |= (1 << PD6);  // OC0A / pin 6  / Timer0
  DDRB |= (1 << PB1);  // OC1A / pin 9  / Timer1
  DDRB |= (1 << PB3);  // OC2A / pin 11 / Timer2

  // ===== Timer0 setup =====
  TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1); // Fast PWM, clear OC0A on compare match
  TCCR0B = (1 << CS01); // Prescaler = 8, controls PWM frequency

  // ===== Timer1 setup =====
  TCCR1A = (1 << WGM10) | (1 << COM1A1); // 8-bit Fast PWM, clear OC1A on compare match
  TCCR1B = (1 << WGM12) | (1 << CS11);   // Fast PWM, prescaler = 8

  // ===== Timer2 setup =====
  TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2A1); // Fast PWM, clear OC2A on compare match
  TCCR2B = (1 << CS21); // Prescaler = 8, controls PWM frequency
}

void loop() {
  // ===== Gradually change PWM duty cycle =====
  for (uint8_t i = 0; i <= 255; i++) {
    OCR0A = (uint8_t)(i * 0.3); // LED on pin 6: up to ~30% brightness
    OCR1A = (uint8_t)(i * 0.5); // LED on pin 9: up to ~50% brightness
    OCR2A = (uint8_t)(i * 0.8); // LED on pin 11: up to ~80% brightness
    _delay_ms(10);              // Small delay for visible fading effect
  }

  _delay_ms(1000); // Wait 1 second before repeating the fade
}
