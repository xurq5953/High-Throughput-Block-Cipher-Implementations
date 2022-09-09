#include <iostream>
#include <x86intrin.h>
#include <string>
#include "encryptool.h"
#include <ctime>

using namespace std;


alignas(32) extern uint8_t text[];

__m256i *windows;

extern uint32_t roundkey[32];

__m256i new_x[32];


void sbox4(__m256i *b);


void linearLayer(__m256i *x);

void key_expansion();

void transpose_simultaneously(__m256i *A);

inline void output_text();

__m256i load_mask;
__m256i store_mask;

void init_data() {
    windows = (__m256i *) text;
    load_mask = _mm256_set_epi8(0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                                10, 11, 12, 13, 14, 15,
                                0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                                10, 11, 12, 13, 14, 15);
    store_mask = _mm256_set_epi8(12, 13, 14, 15, 8, 9, 10, 11,
                                 4, 5, 6, 7, 0, 1, 2, 3,
                                 12, 13, 14, 15, 8, 9, 10, 11,
                                 4, 5, 6, 7, 0, 1, 2, 3);
}


inline void format_bundle() {
    for (int i = 0; i < 128; ++i)
        windows[i] = _mm256_shuffle_epi8(windows[i], load_mask);

    transpose_simultaneously(windows);
}


inline void output_text() {
    transpose_simultaneously(windows);

    for (int i = 0; i < 128; ++i)
        windows[i] = _mm256_shuffle_epi8(windows[i], store_mask);

}


__m256i foo[32];

void encrypt() {

    int index0, index1, index2, index3;
    uint32_t temp, key;
    for (int round = 0; round < 32; ++round) {
        index0 = (round % 4) * 32;
        index1 = (index0 + 32) % 128;
        index2 = (index0 + 64) % 128;
        index3 = (index0 + 96) % 128;
        key = roundkey[round];
        for (int i = 0; i < 32; ++i) {
            foo[i] = _mm256_xor_si256(windows[index2 + i], windows[index3 + i]);
            new_x[i] = _mm256_xor_si256(foo[i], windows[index1 + i]);
            temp = (key >> i) & 1;
            new_x[i] = _mm256_xor_si256(new_x[i], _mm256_set1_epi32(-temp));
        }

        sbox4(new_x);
        sbox4(new_x+8);
        sbox4(new_x+16);
        sbox4(new_x+24);

        linearLayer(new_x);


        windows[index0] = _mm256_xor_si256(windows[index0], new_x[2]);
        windows[index0 + 1] = _mm256_xor_si256(windows[index0 + 1], new_x[19]);
        windows[index0 + 2] = _mm256_xor_si256(windows[index0 + 2], new_x[28]);
        windows[index0 + 3] = _mm256_xor_si256(windows[index0 + 3], new_x[5]);
        windows[index0 + 4] = _mm256_xor_si256(windows[index0 + 4], new_x[6]);
        windows[index0 + 5] = _mm256_xor_si256(windows[index0 + 5], new_x[23]);
        windows[index0 + 6] = _mm256_xor_si256(windows[index0 + 6], new_x[24]);
        windows[index0 + 7] = _mm256_xor_si256(windows[index0 + 7], new_x[9]);
        windows[index0 + 8] = _mm256_xor_si256(windows[index0 + 8], new_x[10]);
        windows[index0 + 9] = _mm256_xor_si256(windows[index0 + 9], new_x[11]);
        windows[index0 + 10] = _mm256_xor_si256(windows[index0 + 10], new_x[12]);
        windows[index0 + 11] = _mm256_xor_si256(windows[index0 + 11], new_x[21]);
        windows[index0 + 12] = _mm256_xor_si256(windows[index0 + 12], new_x[22]);
        windows[index0 + 13] = _mm256_xor_si256(windows[index0 + 13], new_x[7]);
        windows[index0 + 14] = _mm256_xor_si256(windows[index0 + 14], new_x[8]);
        windows[index0 + 15] = _mm256_xor_si256(windows[index0 + 15], new_x[25]);
        windows[index0 + 16] = _mm256_xor_si256(windows[index0 + 16], new_x[26]);
        windows[index0 + 17] = _mm256_xor_si256(windows[index0 + 17], new_x[3]);
        windows[index0 + 18] = _mm256_xor_si256(windows[index0 + 18], new_x[20]);
        windows[index0 + 19] = _mm256_xor_si256(windows[index0 + 19], new_x[13]);
        windows[index0 + 20] = _mm256_xor_si256(windows[index0 + 20], new_x[14]);
        windows[index0 + 21] = _mm256_xor_si256(windows[index0 + 21], new_x[31]);
        windows[index0 + 22] = _mm256_xor_si256(windows[index0 + 22], new_x[0]);
        windows[index0 + 23] = _mm256_xor_si256(windows[index0 + 23], new_x[17]);
        windows[index0 + 24] = _mm256_xor_si256(windows[index0 + 24], new_x[18]);
        windows[index0 + 25] = _mm256_xor_si256(windows[index0 + 25], new_x[27]);
        windows[index0 + 26] = _mm256_xor_si256(windows[index0 + 26], new_x[4]);
        windows[index0 + 27] = _mm256_xor_si256(windows[index0 + 27], new_x[29]);
        windows[index0 + 28] = _mm256_xor_si256(windows[index0 + 28], new_x[30]);
        windows[index0 + 29] = _mm256_xor_si256(windows[index0 + 29], new_x[15]);
        windows[index0 + 30] = _mm256_xor_si256(windows[index0 + 30], new_x[16]);
        windows[index0 + 31] = _mm256_xor_si256(windows[index0 + 31], new_x[1]);


        round++;
        key = roundkey[round];
        for (int i = 0; i < 32; ++i) {
            foo[i] = _mm256_xor_si256(foo[i], windows[index0 + i]);
            temp = (key >> i) & 1;
            foo[i] = _mm256_xor_si256(foo[i], _mm256_set1_epi32(-temp));
        }

        sbox4(foo);
        sbox4(foo+8);
        sbox4(foo+16);
        sbox4(foo+24);

        linearLayer(foo);

        windows[index1] = _mm256_xor_si256(windows[index1], foo[2]);
        windows[index1 + 1] = _mm256_xor_si256(windows[index1 + 1], foo[19]);
        windows[index1 + 2] = _mm256_xor_si256(windows[index1 + 2], foo[28]);
        windows[index1 + 3] = _mm256_xor_si256(windows[index1 + 3], foo[5]);
        windows[index1 + 4] = _mm256_xor_si256(windows[index1 + 4], foo[6]);
        windows[index1 + 5] = _mm256_xor_si256(windows[index1 + 5], foo[23]);
        windows[index1 + 6] = _mm256_xor_si256(windows[index1 + 6], foo[24]);
        windows[index1 + 7] = _mm256_xor_si256(windows[index1 + 7], foo[9]);
        windows[index1 + 8] = _mm256_xor_si256(windows[index1 + 8], foo[10]);
        windows[index1 + 9] = _mm256_xor_si256(windows[index1 + 9], foo[11]);
        windows[index1 + 10] = _mm256_xor_si256(windows[index1 + 10], foo[12]);
        windows[index1 + 11] = _mm256_xor_si256(windows[index1 + 11], foo[21]);
        windows[index1 + 12] = _mm256_xor_si256(windows[index1 + 12], foo[22]);
        windows[index1 + 13] = _mm256_xor_si256(windows[index1 + 13], foo[7]);
        windows[index1 + 14] = _mm256_xor_si256(windows[index1 + 14], foo[8]);
        windows[index1 + 15] = _mm256_xor_si256(windows[index1 + 15], foo[25]);
        windows[index1 + 16] = _mm256_xor_si256(windows[index1 + 16], foo[26]);
        windows[index1 + 17] = _mm256_xor_si256(windows[index1 + 17], foo[3]);
        windows[index1 + 18] = _mm256_xor_si256(windows[index1 + 18], foo[20]);
        windows[index1 + 19] = _mm256_xor_si256(windows[index1 + 19], foo[13]);
        windows[index1 + 20] = _mm256_xor_si256(windows[index1 + 20], foo[14]);
        windows[index1 + 21] = _mm256_xor_si256(windows[index1 + 21], foo[31]);
        windows[index1 + 22] = _mm256_xor_si256(windows[index1 + 22], foo[0]);
        windows[index1 + 23] = _mm256_xor_si256(windows[index1 + 23], foo[17]);
        windows[index1 + 24] = _mm256_xor_si256(windows[index1 + 24], foo[18]);
        windows[index1 + 25] = _mm256_xor_si256(windows[index1 + 25], foo[27]);
        windows[index1 + 26] = _mm256_xor_si256(windows[index1 + 26], foo[4]);
        windows[index1 + 27] = _mm256_xor_si256(windows[index1 + 27], foo[29]);
        windows[index1 + 28] = _mm256_xor_si256(windows[index1 + 28], foo[30]);
        windows[index1 + 29] = _mm256_xor_si256(windows[index1 + 29], foo[15]);
        windows[index1 + 30] = _mm256_xor_si256(windows[index1 + 30], foo[16]);
        windows[index1 + 31] = _mm256_xor_si256(windows[index1 + 31], foo[1]);
    }
}

inline void decrypt() {
    uint32_t d_rk[32];
    for (int i = 0; i < 32; i++)
        d_rk[i] = roundkey[31 - i];
    memcpy(&roundkey[0], d_rk, 32 * sizeof(uint32_t));

    format_bundle();
    encrypt();
    output_text();
}


int main() {
    init_data();
    key_expansion();
    format_bundle();
    encrypt();
    output_text();
    cout << endl << "encrypt:" << endl;
    for (size_t i = 0; i < 128; i++) {
        if (i % 16 == 0 && i != 0) printf("\n");
        printf("%#x ", text[i]);
    }
    decrypt();
    cout << endl << "decrypt:" << endl;
    for (size_t i = 0; i < 128; i++) {
        if (i % 16 == 0 && i != 0) printf("\n");
        printf("%#x ", text[i]);
    }

    unsigned long long time = 0x200000;


    unsigned long long Mbits = (time >> 5); //  (>>20) * 256 *128
    clock_t start, end;
    start = clock();
    for (long i = 0; i < time; ++i){
        encrypt();
    }
    end = clock();
    double elapsed = (double) (end - start) / CLOCKS_PER_SEC;
    double speed_time = Mbits / elapsed;
    printf("\n----------Elapsed Timing is %f\n Encrypt speed is %f Mb/s\n", elapsed, speed_time);


     unsigned long long bytes = time << 12;
     startCycles();
     for (long i = 0; i < time; ++i)
         encrypt();
     unsigned long long cycles = stopWithPrintCycles();
     printf("Encrypt speed is %f cycles/bytes\n", (double) cycles / bytes);

    return 0;
}
