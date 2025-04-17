// Define pins for inputs and outputs
const int A_PIN = 2;    // First input
const int B_PIN = 3;    // Second input
const int CIN_PIN = 4;    // Carry in
const int SUM_PIN = 6;  // Sum output
const int COUT_PIN = 5; // Carry out

void setup() {
  // Initialize input pins
  pinMode(A_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  pinMode(CIN_PIN, OUTPUT);
  
  // Initialize output pins
  pinMode(SUM_PIN, INPUT);
  pinMode(COUT_PIN, INPUT);
  
  // Start serial communication for debugging (optional)
  Serial.begin(9600);

  digitalWrite(A_PIN, HIGH);  // Set A to LOW
  digitalWrite(B_PIN, LOW);  // Set B to LOW
  digitalWrite(CIN_PIN, LOW); // Set CIN to LOW
  
  int sum = digitalRead(SUM_PIN);  // Read SUM
  int cout = digitalRead(COUT_PIN); // Read COUT

    // Print the values to the serial monitor
    Serial.print("Sum: ");
    Serial.print(sum);
    Serial.print(" Carry Out: ");
    Serial.println(cout);

    delay(100);
    // Call the add16bits function with two 16-bit numbers
    int a = 4; // Example 16-bit number
    int b = 4; // Example 16-bit number
    int result = add16bits(a, b); // Call the function
    Serial.print("Result bin: ");
    Serial.println(result, BIN); // Print the result in binary
    Serial.print("Result dec: ");
    Serial.println(result, DEC); // Print the result in decimal
  
}

void loop() {
    

}

int add16bits(int a, int b) {
    int sum = 0;  // Initialize sum
    int cout = 0; // Initialize carry out
    
    for (int i = 0; i < 16; i++) {
        int bitA = (a >> i) & 1; // Extract the ith bit of a
        int bitB = (b >> i) & 1; // Extract the ith bit of b
        int cin = (i == 0) ? 0 : cout; // Carry in for the next bit
        int* result = add1bit(bitA, bitB, cin); // Call the add1bit function
        sum |= (result[0] << i); // Set the ith bit of sum
        cout = result[1]; // Update carry out
        delete[] result;  // Free the allocated memory
    }
    Serial.print("Final Sum: ");
    return sum; // Return the final sum
}

int* add1bit(int a, int b, int cin) {
  // Calculate sum and carry out
    digitalWrite(A_PIN, a);
    digitalWrite(B_PIN, b);
    digitalWrite(CIN_PIN, cin);

    delay(10); // Wait for the circuit to stabilize

    bool sum = digitalRead(SUM_PIN);  // Read SUM
    bool cout = digitalRead(COUT_PIN); // Read COUT
    int* result = new int[2]; // Create an array to hold sum and carry out
    result[0] = sum; // Store sum
    result[1] = cout; // Store carry out
    return result; // Return the result
}