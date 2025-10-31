void setup() {
  Serial.begin(9600); // Start serial communication
  uint8_t result;  // Stores the subtraction result
  uint8_t sreg;    // Stores SREG after the operation
  asm volatile (
    "ldi r16, 50\n\t"      // Load 50 into r16
    "ldi r17, 200\n\t"     // Load 200 into r17
    "sub r16, r17\n\t"     // Subtract r17 from r16; result wraps to 106, SREG flags updated (Z=0, C=1)
    "in __tmp_reg__, __SREG__\n\t"  // Copy SREG to r0 (__tmp_reg__)
    "mov %1, __tmp_reg__\n\t"       // Move r0 (SREG) into output variable sreg
    "mov %0, r16\n\t"               // Move r16 (subtraction result) into output variable result
    : "=r"(result), "=r"(sreg)     // Output operands
    :                               // No input operands
    : "r16", "r17"                  // Clobbered registers
  );

  bool Z = (sreg & (1 << 1));   // Extract Z flag (bit 1) from SREG
  bool C = (sreg & (1 << 0));   // Extract C flag (bit 0) from SREG
  Serial.print("Result = ");
  Serial.println(result);        // Print subtraction result (wrapped value 106)
  Serial.print("SREG (bin) = "); 
  Serial.println(sreg, BIN);    // Print SREG in binary
  Serial.print("Z (zero) = ");
  Serial.println(Z);             // Print Z flag value (0)
  Serial.print("C (carry/borrow) = ");
  Serial.println(C);             // Print C flag value (1)
}

void loop() {
  
}
