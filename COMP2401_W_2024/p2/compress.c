#include <stdio.h>
#include <string.h>

#include "usefulTools.h"


int main(int argc, char *argv[]) {
  unsigned char stringIn[MAX_STRING_SIZE+1];
  unsigned char stringOut[MAX_STRING_SIZE+1];

  // Determine if debugging should be on or not
  unsigned char debug = isDebugMode(argc, argv);
	
  // Get the sentence from the user
  unsigned char numBytesIn = getInputString(stringIn);

  // Convert to new ASCII values
  unsigned char numBytesOut;

  // INSERT YOUR CODE HERE
  // Make sure that you: 
  //    1. Store the result string into stringOut
  //    2. Set the numBytesOut value to the number of bytes you wrote to stringOut

  // this is bit counter for ouput string
  int o = 7;
  // this is bit counter for input string
  int i = 5;
  //controling the loop
  int l = 0,b;
  while(l<numBytesIn*6){
    b = getBit(stringIn[l/6],i); 

    if(b == 1){
      stringOut[l/8] = setBit(stringOut[l/8],o);
    }else{
      stringOut[l/8] = clearBit(stringOut[l/8],o);
    }
    i--;o--;
    if(i<0){
      i = 5;
    }
    if(o<0){
      o = 7;
    }
    l++;
  }
  numBytesOut = (unsigned char)(l/8);
  if(l%8 != 0){numBytesOut++;}

  
  
  // If debugging is on, display the compression ratio as well as the
  // compressed string as sequences of 8-bit binary values
  if (debug) {
    printf("Compression ratio = %1.1f%%\n\n", 100*(float)(numBytesOut/(float)numBytesIn));
    printf("Before compression:\n");
    for (int i=0; i<numBytesIn; i++)
      printAs6BitBinary(stringIn[i]);
    printf("\n");
	
    printf("After compression:\n");
    for (int i=0; i<numBytesOut; i++)
      printAs8BitBinary(stringOut[i]);
    printf("\n");
		
    printf("Here is the resulting string:\n");
  }

  // Output to the next program
  sendOutputString(numBytesOut, stringOut);
}

