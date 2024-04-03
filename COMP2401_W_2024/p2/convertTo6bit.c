#include <stdio.h>
#include <string.h>

#include "usefulTools.h"


int main(int argc, char *argv[]) {
  unsigned char stringIn[MAX_STRING_SIZE+1];
  unsigned char stringOut[MAX_STRING_SIZE+1];

  // Determine if debugging should be on or not
  unsigned char debug = isDebugMode(argc, argv);
	
  // Get the sentence from the user
  scanf("%[^\n]s", stringIn);
  unsigned char numBytesIn = strlen(stringIn);
 
  stringOut[numBytesIn] = '\0';

  // INSERT YOUR CODE HERE
  // Make sure that you store the resulting string into stringOut
  	
 for (int i = 0; i < numBytesIn; i++){
    if(stringIn[i] == 0 ||stringIn[i] == 10 || (stringIn[i] <= 63 && stringIn[i] >= 32)){
      stringOut[i] = stringIn[i];
    }else if (stringIn[i] == '@'){
      stringOut[i] = 30;
    }else if (stringIn[i] == ']'){
      stringOut[i] = 29;
    }else if (stringIn[i] == '['){
      stringOut[i] = 28;
    }else if (stringIn[i] >= 'a' && stringIn[i] <= 'i'){
      stringOut[i] = stringIn[i]-96;
    }else if (stringIn[i] >= 'j' && stringIn[i] <= 'z'){
      stringOut[i] = stringIn[i]-95;
    }else if (stringIn[i] >= 'A' && stringIn[i] <= 'I'){
      stringOut[i] = stringIn[i]-64;
    }else if (stringIn[i] >= 'J' && stringIn[i] <= 'Z'){
      stringOut[i] = stringIn[i]-63;
    }else{
      stringOut[i] = 31;
    }
  }

  // If debugging is on, display the converted string as 2 digit codes
  if (debug) {
    printf("%d bytes entered\n", numBytesIn);
    for (int i=0; i<=numBytesIn; i++)
      printf("%02d ", stringOut[i]);
    printf("\n");
  }
  
  // Output to the next program
  sendOutputString(numBytesIn, stringOut);
}


