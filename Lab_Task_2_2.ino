void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud to display data on the Serial Monitor

  uint8_t R18;  // 8-bit variable to store the addition result since Serial.print() can't print registers directly

  asm volatile (
      "ldi r17, 5\n\t"      // Load 5 into register r17
      "ldi r18, 8\n\t"      // Load 8 into register r18
      "add r18, r17\n\t"    // Add r17 to r18 and store the result in r18
      "mov %0, r18\n\t"     // Move the result from r18 into the variable R18
      : "=r" (R18)          // Output operand: %0 maps to R18
      :                     // No input operands
      : "r17", "r18"        // Clobber list: informs compiler r17 and r18 are modified
  );

  Serial.print("Result = "); // Send the text "Result = " to the Serial Monitor
  Serial.println(R18);       // Send the value of R18 (the sum) to the Serial Monitor
}

void loop() {
  // Empty loop; code in setup() runs only once
}
