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


	



  // INSERT YOUR CODE HERE
  // Make sure that you store the resulting string into stringOut

  for (int i = 0; i < numBytesIn; i++){
      if(stringIn[i] == 0 ||stringIn[i] == 10 || (stringIn[i] <= 63 && stringIn[i] >= 32)){
        stringOut[i] = stringIn[i];
      }else if (stringIn[i] == 30){
        stringOut[i] = '@';
      }else if (stringIn[i] == 29){
        stringOut[i] = ']';
      }else if (stringIn[i] == 28){
        stringOut[i] = '[';
      }else if (stringIn[i] >= 1 && stringIn[i] <= 9){
        stringOut[i] = stringIn[i]+64;
      }else if (stringIn[i] >= 11 && stringIn[i] <= 27){
        stringOut[i] = stringIn[i]+63;
      }else{
        stringOut[i] = '_';
      }
  }  
  // If debugging is on, display the converted string as 2 digit codes
  if (debug) {
    for (int i=0; i<=numBytesIn; i++)
      printf("%02d ", stringOut[i]);
    printf("\n");
  }
  
  // Output the final string
  printf("%s\n",stringOut);
}


