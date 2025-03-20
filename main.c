#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char key[] = "";

const char* reversestring(char str[]) {
    int len = strlen(str);
    int n;
    for (int i = 0; i < len / 2; i++) {
        n = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = n;
    }
    return str;
}

int ascii(char asciivalue) {
    return (int)asciivalue;
}

const char* binary(int num) {
    static char value[32];  
    int cont = 0, n;
    value[0] = '\0';
    while (num > 0) {
        n = num % 2;
        num /= 2;
        sprintf(value + strlen(value), "%d", n);
    }
    while (strlen(value) < 8) {  
        sprintf(value + strlen(value), "0");
    }
    return reversestring(value);
}

void base64(char key[]) {
    char prebinary[1000], binarys[100][7], base64_char[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";  
    prebinary[0] = '\0';
    int cont = 0, j = 0, binaryascii[100] = {0};  
    size_t length = strlen(key);

    // Convert the input string to binary
    for (int i = 0; i < length; i++) {
        strcat(prebinary, binary(ascii(key[i])));
    }
    strcat(prebinary, "00001010");  // Add newline character as binary (0x0A)

    int preblen = strlen(prebinary);
    
    // Break the binary string into 6-bit chunks
    for (int i = 0; i < preblen; i++) {
        binarys[cont][j] = prebinary[i]; 
        j++;
        
        if (j == 6) {
            binarys[cont][j] = '\0';
            cont++;
            j = 0;   
        }
    }

    // Padding the last binary chunk if needed
    for (int i = 0; i < strlen(binarys[cont]); i++) {
        if(binarys[cont][i] != '0' && binarys[cont][i] != '1') {
            binarys[cont][i] = '0';
        }
    }

    // Reverse the bits in each chunk and ensure it has 6 bits
    for (int i = 0; i <= cont; i++) {
        binarys[i][6] = '\0';
        reversestring(binarys[i]);
    }

    // Convert each 6-bit binary chunk to decimal and then to base64
    int cont24 = 0;
    for (int i = 0; i < cont; i++) {
        binaryascii[i] = 0; 
        for(int j = 5; j >= 0; j--) {
            if(binarys[i][j] == '1'){
                binaryascii[i] += pow(2, j);
            }
        }
        printf("\n%s\n", binarys[i]);
        cont24++;
        printf("%c", base64_char[binaryascii[i]]);
    }

    printf("\n\n\n");
    for(int i =0; i<cont; i++){
        printf("%c", base64_char[binaryascii[i]]);
    }
    if(cont24 > 0) {
        int remainder = cont24 % 4;
        if (remainder == 2) {
            printf("==");
        } else if (remainder == 1) {
            printf("=");
        }
    }
    printf("\n\n\n");
    
}

int main() {
    scanf("%[^\n]", key);  
    printf("\n");
    base64(key);  
    return 0;
}
