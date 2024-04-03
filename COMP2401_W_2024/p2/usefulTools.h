#define	MAX_STRING_SIZE  255

// Print an unsigned char as 6 binary digits
void printAs6BitBinary(unsigned char n);

// Print an unsigned char as 8 binary digits
void printAs8BitBinary(unsigned char n);

// Get up to limit characters as input from the user (or piped in from another program)
unsigned char getInputString(unsigned char *stringIn);

// Print out (or pipe out to another program) the converted string
void sendOutputString(unsigned char numBytesOut, unsigned char *stringOut);

// Return true if the program was run with the debug option on (i.e., -d) and false otherwise
unsigned char isDebugMode(int argc, char *argv[]);



// Extra Fuction for bit manipiulation

int getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);