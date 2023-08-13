#include <iostream>

#define MAX_OUTPUT_DIGIT 64

int main() {
    // lookup table [2^n] for n = 1; n < 64
    float lookup_table[MAX_OUTPUT_DIGIT];
    lookup_table[0] = 1;
    for (short i = 1; i < MAX_OUTPUT_DIGIT; i++) {
        lookup_table[i] = 2 * lookup_table[i - 1];
    }
    while (true) {
        // decimal input
        long input_number;
        std::cout << "Decimal (base 10) input\t: ";
        std::cin >> input_number;
        // calculate the corresponding output digit by a linear-search through LT
        short output_digit = 1;
        for (short i = 1; i < MAX_OUTPUT_DIGIT; i++) {
            if (input_number < lookup_table[i]) {
                output_digit = i;
                break;
            }
        }
        // calculate and print the binary form output
        // calculation start from n-th LT based on previous for loop
        std::cout << "Binary (base 2) form\t: ";
        short bit[output_digit];
        for (short i = output_digit - 1; i >= 0; i--) {
            if (input_number >= lookup_table[i]) {
                input_number = input_number - lookup_table[i];
                bit[i] = 1;
                std::cout << bit[i];
            } else {
                bit[i] = 0;
                std::cout << bit[i];
            }
        }
        // We break the loop and the program end if we input 0
        // this could handle number only, not robust yet
        std::cout << "\nTry again? (1 OR 0)\t: ";
        std::cin >> input_number;
        if (input_number == 0) {
            break;
        }
    }
    return 0;
}
