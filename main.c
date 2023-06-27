#include <stdio.h>
#include <math.h>
#include <string.h>
const int MAX = 100;
int conversion(char number);                       // Justin (DONE)
int StringToNumber(char[], int base, int newBase); // Justin (DONE)
void DecimalToBase(int number, int base);          // Justin (DONE)
int BinaryToDecimal(char[]);                       // Danny (DONE)                
void removeSpaces(char string[]);                  // Danny (DONE)
int getStringSize(char number[]);                  // Danny (DONE)
void reverseString(char s[]);                      // Danny (DONE)
int BinaryToOctal(int num);                        // Garrett (DONE)
int BinaryToHexadecimal(char number[]);            // Justin (DONE)
int OctalToBinary(int num);                        // Justin(DONE)
int OctalToDecimal(int num);                       // Garrett (DONE)
int OctalToHexadecimal(int num);                   // Garrett (DONE)
int HexadecimalToBinary(char number[]);            // Danny (DONE)
int HexadecimalToOctal(char number[]);             // Garrett (DONE)
int HexadecimalToDecimal(char number[]);           // Danny (DONE)

int main(void) {
  int number;
  int base;
  int newBase;
  char result[MAX];
  printf("Enter a number: ");
  fgets(result, MAX, stdin);

  printf("Enter the base of the number: ");
  scanf("%d", &base);

  printf("Enter the new base to convert to: ");
  scanf("%d", &newBase);

  number = StringToNumber(result, base, newBase);
  // printf("New Number: %d", number);

  return 0;
}

//Justin 
int conversion(char number) {
  int x;
  x = number - '0';
  return x;
}

//converts userinput into a value
int StringToNumber(char number[], int base, int newBase) {
  int size = 0;
  int check;
  char newNum[MAX];

  for (int i = 0; number[i] != '\0'; i++) {
    check = number[i];
    if (check >= 48 && check <= 57) {
      newNum[size] = number[i];
      size++;
    } else if (check >= 65 && check <= 70) {
      newNum[size] = number[i];
      size++;
    }
  }

  number[size] = '\0'; 
  int finalNumber = 0;
  for (int i = 0; number[i] != '\0'; i++) {
    finalNumber *= 10;
    finalNumber += conversion(number[i]);
  }

  //checks base to see what functions to call
  if (base == 2 && newBase == 8) {
    return BinaryToOctal(finalNumber);
  } else if (base == 2 && newBase == 10) {
    return BinaryToDecimal(number);
  } else if (base == 2 && newBase == 16) {
    return BinaryToHexadecimal(number);
  } else if (base == 2) {
    return BinaryToDecimal(number);
  }

  if (base == 8 && newBase == 2) {
    return OctalToBinary(finalNumber);
  } else if (base == 8 && newBase == 10) {
    return OctalToDecimal(finalNumber);
  } else if (base == 8 && newBase == 16) {
    return OctalToHexadecimal(finalNumber);
  } else if (base == 8) {
    return OctalToDecimal(finalNumber);
  }

  if (base == 10) {
    DecimalToBase(finalNumber, newBase);
  }

  if (base == 16 && newBase == 2) {
    return HexadecimalToBinary(number);
  } else if (base == 16 && newBase == 8) {
    return HexadecimalToOctal(number);
  } else if (base == 16 && newBase == 10) {
    return HexadecimalToDecimal(number);
  } else if (base == 16) {
    return HexadecimalToDecimal(number);
  }

  return finalNumber;
}

void DecimalToBase(int number, int base) {
  int i = 0;
  char remainder;
  char result[MAX];

  while (number != 0) {
    remainder = number % base + '0';
    if (number % base >= 10 && number % base <= 15) {
      remainder = ((number % base) + 55);
      result[i] = remainder;
    } else {
      remainder = number % base + '0';
      result[i] = remainder;
    }
    i++;
    number = number / base;
  }
  for (int k = 0; k < i; k++) {
    printf("%c", result[i - k - 1]);
  }
}

int OctalToBinary(int num){
  int temp = OctalToDecimal(num);
  DecimalToBase(temp, 2);
  // int remainder;
  // int BinNum[MAX];
  // int i = 0;
  // int printNum;

  // while (temp != 0) {
  //   remainder = temp % 2;
  //   BinNum[i] = remainder;
  //   i++;
  //   temp = temp/2;
  // }
  // BinNum[i] = '\0';

  // for (int k = 0; k < i; k++) {
  //   printf("%d", BinNum[i-k-1]);
  // }

 return 0; //placeholder
}

//Danny 
int BinaryToDecimal(char number[]) {
  //create an array with no spaces so we don't try to count those as possible n place values
  //get size of the no space string and reverse all numbers in it
  int decimal = 0;
  removeSpaces(number);
  int size = getStringSize(number);
  reverseString(number);
  number[size] = '\0';
  
  //square only values of '1' in the array based on the n place they're in 
  for (int i = 0; number[i] != '\0'; i++) {
    if(number[i] == '1'){
      decimal += pow(2, i);
    }
  }
  
  return decimal;
}

int HexadecimalToBinary(char number[]){
  //(1)creating an array to reference for hex values, load with coressponding hex values based on index value 0-15
  char hexKey[16];
  char numLoad = '0';
  char letterLoad = 'A';

  //load the hexKey array
  for (int i = 0; i < 16; i++){
    //for numbers 0-9 set number values
    if (i >= 0 && i < 10){
      hexKey[i] = numLoad;
      numLoad++;
    //for numbers 10-15 set letter values
    } else if (i >= 10 && i <= 15){
      hexKey[i] = letterLoad;
      letterLoad++;
    }
  }

  //(2)convert hex values to decimal

  //get size of the number given, create a new array with the numeric values of each hex value (set to size of HEX number)
  int size = getStringSize(number);
  int vals[size];

  //load the numeric values from hexKey's index values into the vals array in order
  for (int i = 0; i < size; i++){
    for (int x = 0; x < 16; x++){
      if (number[i] == hexKey[x]){
        vals[i] = x;
      }
    }
  }
  
  //(3) convert decimal values to binary
  int chunks = size; //number of binary chunks we'll need to output
  int end = chunks*4; //end of the array based on chunks
  int start = 0; //start of the array
  int cStart; //chunk start will be used to assign the array values in reverse
  int binary[end]; //array of all numeric 1 and 0 values
  int num; //the number we currently need to convert to binary
  int remainder;
  int count = 0; //counter that ensure we only create chunks of four 1's and 0's per hex value

  //for loop that creates every binary chunk 
  for (int i = 0; i < chunks; i++){
    count = 0; //count must start at 0 always
    num = vals[i]; //get the hex numeric value 

    //based on which chunk of binary we're going to create, start needs to begin at different values. Set them here
    if (start == 0){
      cStart = 3;
    } else if (start == 4){
      cStart = 7;
    } else if (start == 8){
      cStart = 11;
    } else if (start == 12) {
      cStart = 15;
    }

    //if value is 0, 1, 2, 3, 4, 5, 6, or 7 we can assume we need to fill certain default values which don't get filled with our while loop since the number reaches 0
    if(num < 8 && num > 4){
      binary[start] = 0;
    } else if (num < 4 && num > 2){
      binary[start] = 0;
      binary[start + 1] = 0;
      binary[start + 2] = 1;
      binary[start + 3] = 1;
    } else if (num < 2){
      binary[start] = 0;
      binary[start + 1] = 0;
      binary[start + 2] = 0;
      binary[start + 3] = 1;
    } else if (num < 1){
      binary[start] = 0;
      binary[start + 1] = 0;
      binary[start + 2] = 0;
      binary[start + 3] = 0;
    } else if (num == 4){
      binary[start] = 0;
      binary[start + 1] = 1;
      binary[start + 2] = 0;
      binary[start + 3] = 0;
    }

    //While loop that fills our binary number array with the current hex value's binary value. 
    //Uses the method from class: divide a numeric value by 2, store the remainders as our binary number. 
    //Only runs to fill a binary number with four total 1 or 0 values
    while(count < 4){
      //the numeric value updates as we divide, continue while the value is not 0
      //fill our binary array here with our remainders in reverse order using cStart 
      while(num > 0){
        remainder = num % 2;
        num = num/2;
        binary[cStart] = remainder;
        cStart--; 
      } 
      count++;
    }

    //increment the starting point of where to continue filling our binary array 
    start += 4;
  }

  // //for testing purposes print array, WILL BE REMOVED
  // for(int x = 0; x < end; x++){
  //   printf("Binary[%d]: %d\n", x, binary[x]);
  // }

  //GOOD
  //(4) convert our numeric array back to a string
  char result[end];
  result[end] = '\0';
  for (int a = 0; a < end; a++){
    if (binary[a] == 1){
      result[a] = '1';
    } else if (binary[a] == 0) {
      result[a] = '0';
    }
  }
  
  //print Final Result
  printf("\nBinary: ");
  for(int a = 0; a < 1; a++){
    for(int x = 0; result[x] != '\0'; x++){
      printf("%c", result[x]);
    }
    printf(" ");
  }
  
  printf("\n\n");
  return result; 
}

void removeSpaces(char string[]) {
  int n = 0;
  int size = getStringSize(string);
  for(int i = 0; i < size; i++){
    if(string[i] != 32){
      string[n++] = string[i];
    }
  }
  string[size] = '\0';
} 

void reverseString(char s[]){
  int size = getStringSize(s);
  int c, i, j;
  
  for(i = 0, j = size-1; i < j; i++, j--){
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

int getStringSize(char number[]){
  int size = 0;
  for (int i = 0; number[i] != '\0'; i++) {
    size += 1;
  }
  
  return size;
}

//Garrett 
int OctalToHexadecimal(int octalNum){
  //long int binaryval = OctalToBinary(num);
  
  int i = 1;
  long binaryval = 0;
long int num = octalNum;
    long int dec_value = 0;
 
    // Initializing base value to 1, i.e 8^0
    int base = 1;
 
    int temp = num;
    while (temp) {
 
        // Extracting last digit
        int last_digit = temp % 10;
        temp = temp / 10;
 
        // Multiplying last digit with appropriate
        // base value and adding it to dec_value
        dec_value += last_digit * base;
 
        base = base * 8;
      }
  long decimal = dec_value;






  
  while (decimal != 0) {
    binaryval += (decimal % 2) * i;
    decimal /= 2;
    i *= 10;
  }


  long int hexadecimalval = 0, j = 1, remainder;
 
    
    while (binaryval != 0)
    {
        remainder = binaryval % 10;
        hexadecimalval = hexadecimalval + remainder * j;
        j = j * 2;
        binaryval = binaryval / 10;
    }
    printf("Equivalent hexadecimal value: %lX", hexadecimalval);
    return 0;
  
  

  
  
  return 0;
}
//Garrett
int OctalToDecimal(int number){
    long int num = number;
    long int dec_value = 0;
 
    // Initializing base value to 1, i.e 8^0
    int base = 1;
 
    int temp = num;
    while (temp) {
 
        // Extracting last digit
        int last_digit = temp % 10;
        temp = temp / 10;
 
        // Multiplying last digit with appropriate
        // base value and adding it to dec_value
        dec_value += last_digit * base;
 
        base = base * 8;
    }
    return dec_value;
}
//Garrett
int BinaryToOctal(int num){
  long int octalnum = 0, j = 1, remainder;
 
    
    while (num != 0)
    {
        remainder = num % 10;
        octalnum = octalnum + remainder * j;
        j = j * 2;
        num = num / 10;
    }
    printf("Equivalent octal value: %lo", octalnum);
    
  
  return octalnum; //placeholder
}                 

//Danny
int HexadecimalToDecimal(char number[]){
  //(1)creating an array to reference for hex values, load with coressponding hex values based on index value 0-15
  char hexKey[16];
  char numLoad = '0';
  char letterLoad = 'A';

  //load the hexKey array
  for (int i = 0; i < 16; i++){
    //for numbers 0-9 set number values
    if (i >= 0 && i < 10){
      hexKey[i] = numLoad;
      numLoad++;
    //for numbers 10-15 set letter values
    } else if (i >= 10 && i <= 15){
      hexKey[i] = letterLoad;
      letterLoad++;
    }
  }

  //(2)convert hex values to decimal

  //get size of the number given, create a new array with the numeric values of each hex value (set to size of HEX number)
  int size = getStringSize(number);
  int vals[size];
  reverseString(number);
  //load the numeric values from hexKey's index values into the vals array in order
  int valSize = 0;
  for (int i = 0; i < size; i++){
    for (int x = 0; x < 16; x++){
      if (number[i] == hexKey[x]){
        vals[i] = x;
        valSize++;
      }
    }
  }

  int decimal = 0;
  int base = 1;
  for (int i = 0; i < valSize; i++) {
    decimal += vals[i] * base;
    base *= 16;   
  }
printf("%d\n", decimal);
  return decimal;
}

//Garrett
int HexadecimalToOctal(char number[]){
  char hexKey[16];
  char numLoad = '0';
  char letterLoad = 'A';

  //load the hexKey array
  for (int i = 0; i < 16; i++){
    //for numbers 0-9 set number values
    if (i >= 0 && i < 10){
      hexKey[i] = numLoad;
      numLoad++;
    //for numbers 10-15 set letter values
    } else if (i >= 10 && i <= 15){
      hexKey[i] = letterLoad;
      letterLoad++;
    }
  }

  //(2)convert hex values to decimal

  //get size of the number given, create a new array with the numeric values of each hex value (set to size of HEX number)
  int size = getStringSize(number);
  int vals[size];
  reverseString(number);
  //load the numeric values from hexKey's index values into the vals array in order
  int valSize = 0;
  for (int i = 0; i < size; i++){
    for (int x = 0; x < 16; x++){
      if (number[i] == hexKey[x]){
        vals[i] = x;
        valSize++;
      }
    }
  }

  int decimal = 0;
  int base = 1;
  for (int i = 0; i < valSize; i++) {
    decimal += vals[i] * base;
    base *= 16;   
  }
  DecimalToBase(decimal, 8);
  

  
  return 0;
}

int BinaryToHexadecimal(char number[]){
  int temp = BinaryToDecimal(number);
  printf("%d\n", temp);
  DecimalToBase(temp, 16);
  // int remainder;
  // int HexNum[MAX];
  // int i = 0;
  // int printNum;

  // while (temp != 0) {
  //   remainder = temp;
  //      if (temp % 16 >= 10 && temp % 16 <= 15) {
  //        remainder = ((temp % 16) + 55);
  //        HexNum[i] = remainder;
  //       } else {
  //        remainder = temp % 16;
  //        HexNum[i] = remainder;
  //      }  
  //     i++;
  //     temp = temp/16;
  // }
  // HexNum[i] = '\0';

  // for (int k = 0; k < i; k++) {
  //   printf("%d", HexNum[i-k-1]);
  // }
  return 0; //placeholder
}