#include <avr/io.h>
#include <avr/interrupt.h>

// Counters to keep track of Timer0 and Timer2 interrupts
volatile uint8_t counter0 = 0;
volatile uint8_t counter2 = 0;

void setup() {
    // Set pins 9 (PB1), 11 (PB3) and 6 (PD6) as output for LEDs
    DDRB |= (1 << PB1) | (1 << PB3);
    DDRD |= (1 << PD6);

    // ===== Timer0 for pin 6 (PD6) =====
    TCCR0A = (1 << WGM01);              // Set Timer0 to CTC mode (clear timer on compare)
    TCCR0B = (1 << CS02) | (1 << CS00); // Prescaler 1024 to slow down the timer
    OCR0A = 200;                         // Compare value for Timer0 (adjusts blink speed)
    TIMSK0 |= (1 << OCIE0A);             // Enable Timer0 Compare Match A interrupt

    // ===== Timer1 for pin 9 (PB1) =====
    TCCR1A = (1 << COM1A0);              // Toggle OC1A (pin 9) on compare match
    TCCR1B = (1 << WGM12) | (1 << CS12); // CTC mode, prescaler 256
    OCR1A = 31000;                        // Compare value for Timer1 (controls blink speed)
       
    // ===== Timer2 for pin 11 (PB3) =====
    TCCR2A = (1 << WGM21);               // Set Timer2 to CTC mode
    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20); // Prescaler 1024
    OCR2A = 130;                          // Compare value for Timer2 (adjusts blink speed)
    TIMSK2 |= (1 << OCIE2A);              // Enable Timer2 Compare Match A interrupt

    sei(); // Enable global interrupts so ISRs can run
}

void loop() {
    // Main loop is empty because all LED toggling is handled by timers and interrupts
}

// ===== Timer0 Compare Match A ISR =====
ISR(TIMER0_COMPA_vect) {
    counter0++; // Count how many times the interrupt occurred
    if(counter0 >= 2) { // Toggle LED on PD6 every 2 interrupts ≈ 0.5 Hz
        PORTD ^= (1 << PD6); // Toggle the LED
        counter0 = 0;        // Reset counter
    }
}

// ===== Timer2 Compare Match A ISR =====
ISR(TIMER2_COMPA_vect) {
    counter2++; // Count Timer2 interrupts
    if(counter2 >= 2) { // Toggle LED on PB3 every 2 interrupts ≈ 2 Hz
        PORTB ^= (1 << PB3); // Toggle the LED
        counter2 = 0;        // Reset counter
    }
}
