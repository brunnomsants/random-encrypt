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
    char prebinary[1000], binarys[100][7], base64_char[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";  
    prebinary[0] = '\0';
    int cont = 0, j = 0, binaryascii[100] = {0};  
    size_t length = strlen(key);

    for (int i = 0; i < length; i++) {
        strcat(prebinary, binary(ascii(key[i])));
    }
    
    int preblen = strlen(prebinary);
    
    for (int i = 0; i < preblen; i++) {
        binarys[cont][j] = prebinary[i]; 
        j++;
        
        if (j == 6) {
            binarys[cont][j] = '\0';
            cont++;
            j = 0;   
        }
    }
    
    for (int i = 0; i < strlen(binarys[cont]); i++) {
        if(binarys[cont][i] != '0' && binarys[cont][i] != '1') {
            binarys[cont][i] = '0';
        }
    }

    for (int i = 0; i <= cont; i++) {
        binarys[i][6] = '\0';
    }

    for (int i = 0; i <= cont; i++) {
        reversestring(binarys[i]);
    }

    // Convert binary to base64
    for (int i = 0; i <= cont; i++) {
        binaryascii[i] = 0; 
        for(int j = 5; j >= 0; j--) {
            if(binarys[i][j] == '1'){
                binaryascii[i] += pow(2, j);
            }
        }
        printf("================\n%s\n%d\n%c\n", binarys[i], binaryascii[i], base64_char[binaryascii[i]]);
    }

    printf("================\n");
}

int main() {
    scanf("%[^\n]", key);  
    base64(key);  
    return 0;
}
