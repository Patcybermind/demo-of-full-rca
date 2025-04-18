// Define pins for inputs and outputs
const int A_PIN = 2;    // First input
const int B_PIN = 3;    // Second input
const int CIN_PIN = 4;  // Carry in
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
    
    // Start serial communication
    Serial.begin(9600);

    digitalWrite(A_PIN, HIGH);
    digitalWrite(B_PIN, LOW);
    digitalWrite(CIN_PIN, LOW);
    
    int sum = digitalRead(SUM_PIN);
    int cout = digitalRead(COUT_PIN);

    Serial.print("Sum: ");
    Serial.print(sum);
    Serial.print(" Carry Out: ");
    Serial.println(cout);

    delay(100);
    
    // Test with 32-bit numbers
    long a = 2147483647; // Max 32-bit signed integer
    long b = 1;
    long result = add32bits(a, b);
    Serial.print("Result bin: ");
    Serial.println(result, BIN);
    Serial.print("Result dec: ");
    Serial.println(result, DEC);
}

void loop() {
    long a = 0, b = 1; // Initialize Fibonacci with 32-bit numbers
    while (true) {
        long next = add32bits(a, b);
        if (next < a || next < b) {
            Serial.println("Rollover detected!");
            break;
        }
        Serial.print("Fibonacci: ");
        Serial.println(next, DEC);
        a = b;
        b = next;
        delay(100);
    }
    while (true) {
        // Do nothing, just wait
    }
}

long add32bits(long a, long b) {
    long sum = 0;  // Initialize sum
    int cout = 0;  // Initialize carry out
    
    for (int i = 0; i < 32; i++) {
        int bitA = (a >> i) & 1;  // Extract the ith bit of a
        int bitB = (b >> i) & 1;  // Extract the ith bit of b
        int cin = (i == 0) ? 0 : cout;  // Carry in for the next bit
        int* result = add1bit(bitA, bitB, cin);
        sum |= ((long)result[0] << i);  // Cast to long before shifting
        cout = result[1];
        delete[] result;
    }
    Serial.print("Final Sum: ");
    return sum;
}

int* add1bit(int a, int b, int cin) {
    digitalWrite(A_PIN, a);
    digitalWrite(B_PIN, b);
    digitalWrite(CIN_PIN, cin);

    delay(30); // Wait for the circuit to stabilize

    bool sum = digitalRead(SUM_PIN);
    bool cout = digitalRead(COUT_PIN);
    int* result = new int[2];
    result[0] = sum;
    result[1] = cout;
    return result;
}