#include <iostream>

// return the modulo 16
int mod16(int *a) {
    return (*a)/16;
}

// return the remainder of a division by 16
int rem16(int *a) {
    return (*a) - ((*a)/16)*16;
}

// convert decimal 10 to hexadecimal 16
void decToHex(int *a, int *r, int *i) {
    r[3 - *i] = rem16(a);
    *a = mod16(a);
    (*i)++;
    if (*a > 16) {
        decToHex(a, r, i);
    } else {
        r[3 - *i] = *a;
    }
}

// to find number base16 to string hexadecimal representation
void hexToStrHex(int *r, char *hex) {
    for (short i = 0; i < 4; i++) {
        switch (r[i]) {
            case 0:
                hex[i] = '0';
                break;
            case 1:
                hex[i] = '1';
                break;
            case 2:
                hex[i] = '2';
                break;
            case 3:
                hex[i] = '3';
                break;
            case 4:
                hex[i] = '4';
                break;
            case 5:
                hex[i] = '5';
                break;
            case 6:
                hex[i] = '6';
                break;
            case 7:
                hex[i] = '7';
                break;
            case 8:
                hex[i] = '8';
                break;
            case 9:
                hex[i] = '9';
                break;
            case 10:
                hex[i] = 'A';
                break;
            case 11:
                hex[i] = 'B';
                break;
            case 12:
                hex[i] = 'C';
                break;
            case 13:
                hex[i] = 'D';
                break;
            case 14:
                hex[i] = 'E';
                break;
            case 15:
                hex[i] = 'F';
                break;
            default:
                break;
        }
    }
}

int main() {
    while (true) {
        int decimal_input = 0;
        int hex16[4] = {0, 0, 0, 0};
        char str_hex[4] = {'0', '0', '0', '0'};
        int i = 0;
        
        // take input in form of decimal number
        printf("Decimal input (0 - 65535)\t: ");
        scanf("%d", &decimal_input);
        
        // pass input to get Hex representation, will be assigned to hex16 -- a base16 representation
        decToHex(&decimal_input, hex16, &i);
        
        // convert base16 (hex16) to Str Hex (str_hex) --> 0-9,A,B,C,D,E,F
        hexToStrHex(hex16, str_hex);

        // print to console
        printf("hex\t\t: %d %d %d %d\n", hex16[0], hex16[1], hex16[2], hex16[3]);
        printf("string hex\t: %c %c %c %c\n", str_hex[0], str_hex[1], str_hex[2], str_hex[3]);

        // passing 0 will break from this while and exit main program
        printf("Try with other number? (1 for yes || 0 for no)\t: ");
        scanf("%d", &decimal_input);
        if (decimal_input == 0) {
            break;
        }
    }

    return 0;
}
