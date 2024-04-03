#include <stdio.h>
#include <string.h>

#include "usefulTools.h"


int main(int argc, char *argv[]) {
  unsigned char stringIn[MAX_STRING_SIZE];
  unsigned char stringOut[MAX_STRING_SIZE];

  // Determine if debugging should be on or not
  unsigned char debug = isDebugMode(argc, argv);

  // Get the sentence from the user
  unsigned char numBytesIn = getInputString(stringIn);

  unsigned char numBytesOut;

  // stringOut[0] = stringIn[0]>>2;
  // numBytesOut = numBytesIn;


  // INSERT YOUR CODE HERE
  // Make sure that you: 
  //    1. Store the result string into stringOut
  //    2. Set the numBytesOut value to the length of stringOut
  // this is bit counter for ouput string
  int o = 5;
  // this is bit counter for input string
  int i = 7;
  //controling the loop
  int l = 0,b;
  while(l<numBytesIn*8){
    b = getBit(stringIn[l/8],i); 

    if(b == 1){
      stringOut[l/6] = setBit(stringOut[l/6],o);
    }else{
      stringOut[l/6] = clearBit(stringOut[l/6],o);
    }
    i--;o--;
    if(i<0){
      i = 7;
    }
    if(o<0){
      o = 5;
    }
    l++;
  }
  numBytesOut = (unsigned char)(l/6);
  if(l%6 != 0){numBytesOut++;}



	
  // If debugging is on, display the expanded string as sequences of 8-bit binary values
  if (debug) {
    printf("Input bytes = %d\n\n", numBytesIn);
    printf("Output bytes = %d\n\n", numBytesOut);
    printf("Expansion ratio = %1.1f%%\n\n", 100*(float)(numBytesOut/(float)numBytesIn));
    printf("Before expansion:\n");
    for (int i=0; i<numBytesIn; i++)
      printAs8BitBinary(stringIn[i]);
    printf("\n");
	
    printf("After expansion:\n");
    for (int i=0; i<numBytesOut; i++)
      printAs6BitBinary(stringOut[i]);
    printf("\n");
		
    printf("Here is the resulting string:\n");
  }

  // Output to the next program
  sendOutputString(numBytesOut, stringOut);
}
