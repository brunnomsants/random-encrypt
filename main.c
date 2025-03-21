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

void base64(char phrase[]) {
    char prebinary[1000], binarys[100][7], base64_char[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";  
    prebinary[0] = '\0';
    int cont = 0, j = 0, binaryascii[100] = {0};  
    size_t length = strlen(phrase);
    

    for (int i = 0; i < length; i++) {
        strcat(prebinary, binary(ascii(phrase[i])));
    }
    strcat(prebinary, "00001010");  

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
        reversestring(binarys[i]);
    }

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

void hexdecimal(char phrase[]){
    int firstletter, secondletter;
    
    size_t length = strlen(phrase);
    for (int i = 0; i < length; i++) {
        firstletter = ascii(phrase[i])/16;
        secondletter = ascii(phrase[i])%16;
        printf("%d", firstletter);
        if(secondletter<10){
            printf("%d", secondletter);
        }else{
            switch(secondletter){
                case 10:
                    printf("A");
                    break;
                case 11:
                    printf("B");
                    break;
                case 12:
                    printf("C");
                    break;
                case 13:
                    printf("D");
                    break;
                case 14:
                    printf("E");
                    break;
                case 15:
                    printf("F");
                    break;
            }
        }

    }

}



int main() {
    scanf("%[^\n]", key);  
    printf("\n");
    hexdecimal(key);  
    return 0;
}
