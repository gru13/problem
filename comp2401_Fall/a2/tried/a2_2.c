#include <stdio.h>
#include <string.h>

#include<stdlib.h>

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

// extra function
signed char setByte(unsigned char, int, int);
void printByte(unsigned char);
int read_int_decode(unsigned char* );

int main()
{
	char str[8];
	int  choice;

	unsigned char pt[MAX_BUF];
	// unsigned char pt[MAX_BUF] = {'g', 'u', 'r', 'u', '\0'};
	unsigned char ct[MAX_BUF];
	unsigned char key = initKey();
	printByte(key);
	// printf("\n%d\n", key);
	int numBytes = strlen(pt);
	// printf("\n%d\n", numBytes);

	printf("\nYou may:\n");
	printf("  (1) Encrypt a message \n");
	printf("  (2) Decrypt a message \n");
	printf("  (0) Exit\n");
	printf("\n  what is your selection: ");
	scanf("%d", &choice);
	switch (choice) {
		case 1:
			printf("Enter the message to encrypt : \b");
			scanf("%[^\n]s", pt);
			encode(pt,ct,key,numBytes);
			printf("Encrypted message : \n");
			for(int i = 0;i<numBytes;i++){
				printf("%d\t", ct[i]);
			}
			printf("\n");
			break;

		case 2:
			printf("Enter the message to decrypt : ");
			numBytes = read_int_decode(ct);
            printf("%s", ct);
 			decode(ct, pt, key, numBytes);
            printf("%s", pt);
    		printf("the DEcrypted message : %s",pt);
			break;
		default:
			printf("exiting");
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

/*
  Function:  setByte
  Purpose:   set specified bit  in byte 0 or 1
       in:   Byte
       in:   bit
	   in:   n
   return:   new value
*/
signed char setByte(unsigned char byte, int n, int bit){
	if(bit == 0){
		return setBit(byte, n);
	}else{
		return clearBit(byte, n);
	}
}
/*
	this function initilaize the key via getting partial key
*/
unsigned char initKey()
{
	unsigned char key;
	do{
		printf("Enter a partialKey (1-15) :");
		scanf("%d", &key);
	}while(key <= 0 || key >15);
	// shift the least significant 4 bits to most significant bits by left shifting 4 bits
	key = key << 4;
	// ensure the key is 8 bits
	int j;

	for(int i = 7;i>=5;i--){
		j = (i-1) % 4;
		if(~getBit(key,i)){
			key = setBit(key, j);
		}else{
			key = clearBit(key,j);
		}
	}
	return key;
}

unsigned char cShiftLeft(unsigned char c){
    return (getBit(c,7) | (c<<1)) & 255;
}

unsigned char cShiftRight(unsigned char c){
    return (getBit(c,0)<<7 | c>>1) & 255;
}

/*
	this funcntion take unsigned char as input and print the binary form in std output
*/
void printByte(unsigned char k){
    for(int i = 7;i>=0;i--){
        printf("%d", getBit(k,i));
    }
}

unsigned char processKey(unsigned char key){
	key = cShiftLeft(key);
	key = cShiftLeft(key);

	if (key % 3 == 0){
		key = cShiftLeft(key);
	}

	return key;

}

unsigned char encryptByte(unsigned char pt, unsigned char key, unsigned char prev){
    unsigned char result = 0;
    int cur_bit;
    for(int i = 0;i<=7;i++){
        if(getBit(key,i)){
            prev = cShiftRight(prev);
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
            prev = cShiftRight(prev);
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
        // printf("%d\t", key);
        if(i == 0){
            ct[i] = encryptByte(pt[i],key,IV);
        }else{
            ct[i] = encryptByte(pt[i], key, ct[i-1]);
        }
        printf("%4s - %4s  ( %c - %c) (%d)\n",pt,ct, pt[i],ct[i],key);
    }
    printf("\n");
}

void decode(unsigned char* ct, unsigned char* pt, unsigned char key, int numBytes){
    unsigned char result[MAX_BUF];
    for(int i = 0;i<numBytes;i++){
        key = processKey(key);
        if(i == 0){
            pt[i] = decryptByte(ct[i], key,IV);
        }else{
            pt[i] = decryptByte(ct[i], key, ct[i-1]);
        }
        // printf("%4s - %4s ( %c - %c - %c)\n",ct,pt, ct[i], result[i],key);
    }
    printf("\n");
    // pt = result;
}


int read_int_decode(unsigned char* values) {
    int num_values = 0;
    unsigned int num;
    while (scanf("%u", &num) == 1 && num != -1 && num_values <MAX_BUF) {
        values[num_values++] = (unsigned char) num;
    }
    printf("Read %d values:\n", num_values);
    for (int i = 0; i < num_values; i++) {
        printf("%u ", values[i]);
    }
    printf("\n");
    return num_values;
}

