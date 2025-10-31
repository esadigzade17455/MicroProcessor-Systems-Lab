void setup() {
  Serial.begin(9600); 

  uint8_t sum;      // Variable to store the calculated total
  uint8_t counter;  // Variable to act as the counter
  uint8_t limit;    // Variable defining the maximum counter value

  asm volatile(
    "clr %[sum]           \n\t"   // Set sum to 0
    "ldi %[counter], 1    \n\t"   // Load 1 into the counter
    "ldi %[limit], 11     \n\t"   // Load 11 into limit (loop runs until counter = 10)

    "loop%=:              \n\t"   // Create a local label named 'loop'
    "add %[sum], %[counter]\n\t"  // Add counter value to sum
    "inc %[counter]       \n\t"   // Increase counter by 1
    "cp  %[counter], %[limit]\n\t"// Compare counter with limit
    "brne loop%=          \n\t"   // If not equal, jump back to 'loop'; stop when equal

    : [sum]     "=r"(sum),      // Output variable mappings
      [counter] "+r"(counter),  
      [limit]   "+r"(limit)
    :                           // No input operands
    : "cc"                      // Indicates condition flags were modified
  );
  Serial.print("1+2+3+4+5+6+7+8+9+10= ");
  Serial.println(sum);  // Print numeric result (55)
}

void loop() {

}