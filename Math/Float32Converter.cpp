#include <iostream>

#define MAX_EXP_POW 128
#define MAX_BINARY_DIGIT 16
#define MAX_OUTPUT_DIGIT 32
#define EXP_BITS 8
#define FRACT_BITS 23

// take reference of input, output bit, and lookup-table, to calculate corresponding bits
void fungsiIntToBin(unsigned short *input_number, unsigned short *bit, float *lookup_table) {
    // calculate and print the binary form output, start from 16-th LT
    for (short i = MAX_BINARY_DIGIT - 1; i >= 0; i--) {
        if (*input_number >= lookup_table[i]) {
            *input_number = *input_number - lookup_table[i];
            bit[i] = 1;
            std::cout << bit[i];
        } else {
            bit[i] = 0;
            std::cout << bit[i];
        }
    }
}

// this concatenate bit_1 and bit_2 to single bit_f32
void fungsiConcat2Bin(unsigned short *bit_1, unsigned short *bit_2, unsigned short *bit_f32) {
    // use for loop twice to concatenate two 16bit into single 32bit
    for (short i = 1; i <= MAX_BINARY_DIGIT; i++) {
        bit_f32[i - 1] = bit_1[MAX_BINARY_DIGIT - i];
    }
    for (short i = MAX_BINARY_DIGIT + 1; i <= MAX_OUTPUT_DIGIT; i++) {
        bit_f32[i - 1] = bit_2[MAX_OUTPUT_DIGIT - i];
    }
}

// for displaying each bit (value) in an array
void displayBits32(unsigned short *bits) {
    for (short i = 0; i < MAX_OUTPUT_DIGIT; i++) {
        std::cout << bits[i];
    }
}

// this will extract 32-bit into 3 part
// 1. sign bit (f32[0]),
// 2. exponent bits (f32[1:8]), and
// 3. fraction bits (f32[9:31])
void extractBits(unsigned short *f32, unsigned short *sign, unsigned short *exp, unsigned short *fract) {
    *sign = f32[0];
    for (short i = 0; i < EXP_BITS; i++) {
        exp[i] = f32[i + 1];
    }
    for (short i = 0; i < FRACT_BITS; i++) {
        fract[i] = f32[i + 9];
    }
}

// this convert 8-bit from exp_bits and return decimal representation of that
short calculateExp(unsigned short *exp_bits, float *lookup_table) {
    long buffer = 0;
    for (short i = 1; i <= EXP_BITS; i++) {
        buffer = buffer + exp_bits[i - 1] * lookup_table[EXP_BITS - i];
    }
    return buffer;
}

// to calculate third opperand -- fraction part
float calculateVal3(unsigned short *fract_bits, float *lookup_table) {
    float buffer = 0;
    for (short i = 1; i <= FRACT_BITS; i++) {
        buffer = buffer + fract_bits[i - 1] * lookup_table[i];
    }
    buffer = buffer + 1;
    return buffer;
}

int main() {
    // lookup table 2^n for n >= 0 s.d. n < 128, also for 2^-n
    float lookup_table[MAX_EXP_POW], lookup_table2[MAX_EXP_POW];
    lookup_table[0] = 1;
    lookup_table2[0] = 1;
    for (short i = 1; i < MAX_EXP_POW; i++) {
        lookup_table[i] = 2 * lookup_table[i - 1];
        lookup_table2[i] = 1 / lookup_table[i];
    }

    while (true) {
        // 2 integer input (0 s.d. 65535)
        // input may come from a pair of register or whatever
        unsigned short input_1, input_2;
        std::cout << "\nInput must be an integer in range [0, 65535]\n";
        std::cout << "Input 1\t: ";
        std::cin >> input_1;
        std::cout << "Input 2\t: ";
        std::cin >> input_2;

        // just pass them without calculation
        if (input_1 == 0 && input_2 == 0) {
            std::cout << "Hasil konversi Float32\t: 0";
            goto pass;
        }

        // make variables for each input and then pass to fungsiIntToBin
        // binary form will be returned into bit_1 and bit_2
        unsigned short bit_1[MAX_BINARY_DIGIT], bit_2[MAX_BINARY_DIGIT];
        std::cout << "Binary (base 2) form: ";
        std::cout << "\n\tInput 1\t\t: ";
        fungsiIntToBin(&input_1, &bit_1[0], &lookup_table[0]);
        std::cout << "\n\tInput 2\t\t: ";
        fungsiIntToBin(&input_2, &bit_2[0], &lookup_table[0]);

        // concatenate bit_1 and bit_2 to bit_float32 then print them to console
        unsigned short bit_float32[MAX_OUTPUT_DIGIT];
        fungsiConcat2Bin(&bit_1[0], &bit_2[0], &bit_float32[0]);
        std::cout << "\nFloat32 binnary form\t: ";
        displayBits32(&bit_float32[0]);

        // extract bit_float32 into 3 parts: sign_bit, exp_bit, fract_bits
        unsigned short sign_bit, exp_bits[EXP_BITS], fract_bits[FRACT_BITS];
        extractBits(&bit_float32[0], &sign_bit, &exp_bits[0], &fract_bits[0]);

        // calculate exponent from exp bits
        short exp;
        exp = calculateExp(&exp_bits[0], &lookup_table[0]);

        // calculate val1 for (-1)^sign
        // calculate val2 for 2^(exp - 127) using LT
        // calculate val3 for fractal part using calculateVal3 function
        float val1, val2, val3;

        sign_bit == 0 ? val1 = 1 : val1 = - 1;

        exp = exp - 127;
        if (exp == 128) {
            std::cout << "\nHasil konversi Float32\t: NaN";
            goto pass;
        } else if (exp >= 0) {
            val2 = lookup_table[exp];
        } else {
            val2 = lookup_table2[- exp];
        }

        val3 = calculateVal3(&fract_bits[0], &lookup_table2[0]);

        // HASIL AKHIR || FINAL VALUE
        float final_value;
        final_value = val1 * val2 * val3;
        std::cout << "\nHasil konversi Float32\t: " << final_value;

        pass:
        // We break the loop and the program end if we input 0
        // this could handle number only, not robust yet
        std::cout << "\n\nUlangi konversi? (1 untuk Ya OR 0 untuk Tidak): ";
        std::cin >> input_1;
        if (input_1 == 0) {
            break;
        }
    }
    
    return 0;
}
