#include <stdio.h>
#include <math.h>

#define	MAX_STRING_SIZE  255


// Print an unsigned char as 6 binary digits
void printAs6BitBinary(unsigned char n) {
  for (int i=5; i>=0; i--) {
    if ((int)(n/(2<<i)) > 0) {
      printf("1");
      n = n - (2<<i);
    }
    else
      printf("0");
  }
  printf("\n");
}

// Print an unsigned char as 8 binary digits
void printAs8BitBinary(unsigned char n) {
  for (int i=7; i>=0; i--) {
    if ((int)(n/(2<<i)) > 0) {
      printf("1");
      n = n - (2<<i);
    }
    else
      printf("0");
  }
  printf("\n");
}


// Get up to 255 characters as input from the user (or piped in from another program).
// The first character is the number of characters to be read in
unsigned char getInputString(unsigned char *stringIn) {
	unsigned char numChars = getc(stdin);
	unsigned char c = '?';
	unsigned int  count = 0;
	while ((c != '\n') && (count<MAX_STRING_SIZE)) {
		c = getc(stdin);
		stringIn[count++] = c;
	}
	return numChars;
}

// Print out (or pipe out to another program) the converted string
void sendOutputString(unsigned char size, unsigned char *stringOut) {
	printf("%c", size);
	for (int i=0; i<size; i++)
		printf("%c", stringOut[i]);
	printf("%c", 0);
}

// Return true if the program was run with the debug option on (i.e., -d) and false otherwise
unsigned char isDebugMode(int argc, char *argv[]) {
	if (argc != 2)
		return 0;
	if ((argv[1][0] == '-') && (argv[1][1] == 'd'))
		return 1;
	return 0;
}



/*
  Function:  getBit
  Purpose:   retrieve value of bit at specified position
       in:   character from which a bit will be returned
       in:   position of bit to be returned
   return:   value of bit n in int c (0 or 1)
*/
int getBit(unsigned char c, int n)
{
  return (int)(c & (1<<n))/(1<<n) ;
}

/*
  Function:  setBit
  Purpose:   set specified bit to 1
       in:   character in which a bit will be set to 1
       in:   position of bit to be set to 1
   return:   new value of character c with bit n set to 1
*/
unsigned char setBit(unsigned char c, int n)
{
  return c|(1<<n);
}


/*
  Function:  clearBit
  Purpose:   set specified bit to 0
       in:   character in which a bit will be set to 0
       in:   position of bit to be set to 0
   return:   new value of character c with bit n set to 0
*/
unsigned char clearBit(unsigned char c, int n)
{
  return c & ~(1<<n);
}