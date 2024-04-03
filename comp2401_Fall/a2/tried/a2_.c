#include <stdio.h>
#include <string.h>

#define MAX_BUF  256
#define IV 0b11001011

unsigned char initKey();
unsigned char processKey(unsigned char);

void encode(unsigned char*, unsigned char*, unsigned char, int);
void decode(unsigned char*, unsigned char*, unsigned char, int);

unsigned char encryptByte(unsigned char, unsigned char, unsigned char);
unsigned char decryptByte(unsigned char, unsigned char, unsigned char);
unsigned char cShiftRight(unsigned char);
unsigned char cShiftLeft(unsigned char);

int readBytes(unsigned char*, int);
unsigned char getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);


int main()
{
  char str[8];
  int  choice;
  int exit;// for exiting the infinte loop
  int len;// current len of pt will be stored here
  unsigned char pt[MAX_BUF];
  unsigned char ct[MAX_BUF];
  unsigned char key = initKey();

  printf("\nYou may:\n");
  printf("  (1) Encrypt a message \n");
  printf("  (2) Decrypt a message \n");
  printf("  (0) Exit\n");
  printf("\n  what is your selection: ");
  // fgets(str, sizeof(str), stdin);
  // sscanf(str, "%d", &choice);
  scanf("%d",&choice);


  switch (choice) {
    case 1:
      len = readBytes(pt, MAX_BUF);
      printf("%s",pt);
      break;

    case 2:
      printf("2");
      break;

    default:
      printf("3");
      break;
  }

  return(0);
}
/*
  Function:  readBytes
  Purpose:   reads characters from the standard output
      out:   the buffer containing the bytes read
       in:   the capacity of the buffer (maximum size)
   return:   the number of bytes actually read from the user
*/
int readBytes(unsigned char* buffer, int max)
{
  int num = 0;

  fgets((char*)buffer, max, stdin);
  num = strlen((char*)buffer) - 1;
  buffer[num] = '\0';

  return num;
}

/*
  Function:  getBit
  Purpose:   retrieve value of bit at specified position
       in:   character from which a bit will be returned
       in:   position of bit to be returned
   return:   value of bit n in character c (0 or 1)
*/
unsigned char getBit(unsigned char c, int n)
{
  return (c & (1<<n))/(1<<n) ;
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

unsigned char cShiftLeft(unsigned char c){
    return (getBit(c,7) | (c<<1)) & 255;
}

unsigned char cShiftRight(unsigned char c){
    return (getBit(c,0)<<7 | c>>1) & 255;
}

void printByte(unsigned char k){
    printf("\n");
    for(int i = 7;i>=0;i--){
        printf("%d", getBit(k,i));
    }
    printf("\n");
}

unsigned char processKey(unsigned char key){
    key = cShiftLeft(key);
    key = cShiftLeft(key);
    if(key%3==0){
        key = cShiftLeft(key);
    }
    return key;
}

unsigned char encryptByte(unsigned char pt, unsigned char key, unsigned char prev){
    unsigned char result = 0;
    int cur_bit;
    for(int i = 0;i<=7;i++){
        if(getBit(key,i)){
            printByte(prev);
            prev = cShiftRight(prev);
            printf("\nf");
            printByte(prev);
        }else{
            printf("\nw\n");
        }
        cur_bit = getBit(pt,i) ^ getBit(prev,7-i);
        // printf("\n%d %d %d\n",getBit(pt,i) , getBit(prev,7-i) ,getBit(pt,i) ^ getBit(prev,7-i));
        if(cur_bit){
            result = setBit(result,i);
        }
    }
    return result;
}

unsigned char decryptByte(unsigned char ct, unsigned char key, unsigned char prev){
        unsigned char result = 0;
    int cur_bit;
    for(int i = 0;i<=7;i++){
        if(getBit(key,i)){
            printByte(prev);
            prev = cShiftRight(prev);
            printf("\nf");
            printByte(prev);
        }else{
            printf("\nw\n");
        }
        cur_bit = getBit(ct,i) ^ getBit(prev,7-i);
        // printf("\n%d %d %d\n",getBit(pt,i) , getBit(prev,7-i) ,getBit(pt,i) ^ getBit(prev,7-i));
        if(cur_bit){
            result = setBit(result,i);
        }
    }
    return result;
}

void encode(unsigned char*pt, unsigned char* ct, unsigned char key, int numBytes){
    for(int i = 0;i<numBytes;i++){
        key = processKey(key);
        if(i == 0){
            ct[i] = encryptByte(pt[i],key,IV);
        }else{
            ct[i] = encryptByte(pt[i], key, ct[i-1]);
        }
    }
}

void decode(unsigned char* ct, unsigned char* pt, unsigned char key, int numBytes){
    for(int i = 0;i<numBytes;i++){
        key = processKey(key);
        if(i == 0){
            pt[i] = decryptByte(ct[i],key,IV);
        }else{
            pt[i] = decryptByte(ct[i], key, pt[i-1]);
        }
    }
}

unsigned char initKey(){
    unsigned partialKey = 0b00000000;
    do{
        printf("\nEnter the partial Key(1-15) : ");
        scanf("%d", &partialKey);
    }while(partialKey <= 0 || partialKey > 15);
    partialKey = (unsigned char)partialKey;
    partialKey = partialKey<<4;
    for(int i = 7;i>=4;i--){
        int j = (i-1)%4;// j => secondary bit
        // printf("%d-%d\n", i,j);
        if(getBit(partialKey,i) == 1){
            partialKey = clearBit(partialKey,j);
            // printf("1 %d\n",getBit(partialKey,j));
        }else{
            partialKey = setBit(partialKey,j);
            // printf("0 %d\n",getBit(partialKey,j));
        }

    }
    return partialKey;
}