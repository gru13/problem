#include "defs.h"

int randomInt(int max);
void viewEscape(char*);

// Mostprobale outcome chosser
int  ProbableOutcome(int* arrP,int* arrA, int len);

int main(int argc, char *argv[])
{
  if(argc == 1){
    runEscape();
  }else{
    viewEscape(argv[1]);
  }
  return(0);
}

int randomInt(int max)
{
  return(rand() % max);
}


int  ProbableOutcome(int* arrP,int* arrA, int len){
  int maxIndex = -1;
  int maxValue = -1;
  int aP[len];
  for (int i = 0; i < len;i++){
    aP[i] = arrP[i] * randomInt(10);
    if(aP[i] > maxValue){
      maxValue = aP[i];
      maxIndex = i;
    }
  }

  // return arrA[maxIndex];
  return maxIndex;
}


void viewEscape(char *ip){
  char message[MAX_BUFF];
  int viewSocket;
  setupClientSocket(&viewSocket,ip);
  while(1){
    rcvData(viewSocket,message);
    if(strcmp(message,"quit") == 0){
      break;
    }
    system("clear");
    printf("%s\n",message);
    usleep(OUTPUT_INTERVAL);
  }
  return;
}