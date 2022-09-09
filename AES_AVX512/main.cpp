#include <iostream>
#include <x86intrin.h>
#include <string>
#include <ctime>
#include <cstring>


alignas(64) extern uint8_t text[];

__m512i *bundle;
__m512i *bundle2;

void sbox2(__m512i *b);

void key_expansion();

extern uint32_t roundkey[44];

inline void output_text();

void transpose_simultaneously2(__m512i *A);

void transpose_simultaneously3(__m512i *A);

uint8_t *idata;


#define  SBOX(a) \
        sbox2((a));\
        sbox2((a) + 8);\
        sbox2((a) + 16);\
        sbox2((a) + 24);\
        sbox2((a) + 32);\
        sbox2((a) + 40);\
        sbox2((a) + 48);\
        sbox2((a) + 56);\
        sbox2((a) + 64);\
        sbox2((a) + 72);\
        sbox2((a) + 80);\
        sbox2((a) + 88);\
        sbox2((a) + 96);\
        sbox2((a) + 104);\
        sbox2((a) + 112);\
        sbox2((a) + 120)\



void init_data() {
    bundle = (__m512i *) aligned_alloc(64, 8192);
    memcpy(bundle, text, 4096);
    memcpy(bundle + 64, text, 4096);
    idata = (uint8_t *) bundle;
    bundle2 = (__m512i *) aligned_alloc(64, 8192);
}


inline void format_bundle() {
    transpose_simultaneously3(bundle);

}

inline void output_text() {
    transpose_simultaneously3(bundle);
}


void mix_linear2(__m512i *b0,__m512i *b1,__m512i *b2,__m512i *b3, __m512i *y, u_int32_t key);

void encrypt() {
    uint32_t key;
    key = roundkey[0];
    for (int i = 0; i < 32; ++i)
        bundle[i] ^= _mm512_set1_epi32(-((key >> (i)) & 1));
    key = roundkey[1];
    for (int i = 0; i < 32; ++i)
        bundle[i + 32] ^= _mm512_set1_epi32(-((key >> (i)) & 1));
    key = roundkey[2];
    for (int i = 0; i < 32; ++i)
        bundle[i + 64] ^= _mm512_set1_epi32(-((key >> (i)) & 1));
    key = roundkey[3];
    for (int i = 0; i < 32; ++i)
        bundle[i + 96] ^= _mm512_set1_epi32(-((key >> (i)) & 1));


    for (int round = 1; round < 9; ++round) {

        SBOX(bundle);

        key = roundkey[round * 4];
        mix_linear2(bundle, bundle + 40, bundle + 80, bundle + 120, bundle2, key);
        key = roundkey[round * 4 + 1];
        mix_linear2(bundle + 32, bundle + 72, bundle + 112, bundle + 24, bundle2 + 32, key);
        key = roundkey[round * 4 + 2];
        mix_linear2(bundle + 64, bundle + 104, bundle + 16, bundle + 56, bundle2 + 64, key);
        key = roundkey[round * 4 + 3];
        mix_linear2(bundle + 96, bundle + 8, bundle + 48, bundle + 88, bundle2 + 96, key);

        round++;

        SBOX(bundle2);

        key = roundkey[round * 4];
        mix_linear2(bundle2, bundle2 + 40, bundle2 + 80, bundle2 + 120, bundle, key);
        key = roundkey[round * 4 + 1];
        mix_linear2(bundle2 + 32, bundle2 + 72, bundle2 + 112, bundle2 + 24, bundle + 32, key);
        key = roundkey[round * 4 + 2];
        mix_linear2(bundle2 + 64, bundle2 + 104, bundle2 + 16, bundle2 + 56, bundle + 64, key);
        key = roundkey[round * 4 + 3];
        mix_linear2(bundle2 + 96, bundle2 + 8, bundle2 + 48, bundle2 + 88, bundle + 96, key);
    }

    SBOX(bundle);

    key = roundkey[36];
    mix_linear2(bundle, bundle + 40, bundle + 80, bundle + 120, bundle2, key);
    key = roundkey[37];
    mix_linear2(bundle + 32, bundle + 72, bundle + 112, bundle + 24, bundle2 + 32, key);
    key = roundkey[38];
    mix_linear2(bundle + 64, bundle + 104, bundle + 16, bundle + 56, bundle2 + 64, key);
    key = roundkey[39];
    mix_linear2(bundle + 96, bundle + 8, bundle + 48, bundle + 88, bundle2 + 96, key);

    SBOX(bundle2);

    key = roundkey[40];
    bundle[0] = bundle2[0] ^ _mm512_set1_epi32(-((key >> 0) & 1));
    bundle[1] = bundle2[1] ^ _mm512_set1_epi32(-((key >> 1) & 1));
    bundle[2] = bundle2[2] ^ _mm512_set1_epi32(-((key >> 2) & 1));
    bundle[3] = bundle2[3] ^ _mm512_set1_epi32(-((key >> 3) & 1));
    bundle[4] = bundle2[4] ^ _mm512_set1_epi32(-((key >> 4) & 1));
    bundle[5] = bundle2[5] ^ _mm512_set1_epi32(-((key >> 5) & 1));
    bundle[6] = bundle2[6] ^ _mm512_set1_epi32(-((key >> 6) & 1));
    bundle[7] = bundle2[7] ^ _mm512_set1_epi32(-((key >> 7) & 1));
    bundle[8] = bundle2[40] ^ _mm512_set1_epi32(-((key >> 8) & 1));
    bundle[9] = bundle2[41] ^ _mm512_set1_epi32(-((key >> 9) & 1));
    bundle[10] = bundle2[42] ^ _mm512_set1_epi32(-((key >> 10) & 1));
    bundle[11] = bundle2[43] ^ _mm512_set1_epi32(-((key >> 11) & 1));
    bundle[12] = bundle2[44] ^ _mm512_set1_epi32(-((key >> 12) & 1));
    bundle[13] = bundle2[45] ^ _mm512_set1_epi32(-((key >> 13) & 1));
    bundle[14] = bundle2[46] ^ _mm512_set1_epi32(-((key >> 14) & 1));
    bundle[15] = bundle2[47] ^ _mm512_set1_epi32(-((key >> 15) & 1));
    bundle[16] = bundle2[80] ^ _mm512_set1_epi32(-((key >> 16) & 1));
    bundle[17] = bundle2[81] ^ _mm512_set1_epi32(-((key >> 17) & 1));
    bundle[18] = bundle2[82] ^ _mm512_set1_epi32(-((key >> 18) & 1));
    bundle[19] = bundle2[83] ^ _mm512_set1_epi32(-((key >> 19) & 1));
    bundle[20] = bundle2[84] ^ _mm512_set1_epi32(-((key >> 20) & 1));
    bundle[21] = bundle2[85] ^ _mm512_set1_epi32(-((key >> 21) & 1));
    bundle[22] = bundle2[86] ^ _mm512_set1_epi32(-((key >> 22) & 1));
    bundle[23] = bundle2[87] ^ _mm512_set1_epi32(-((key >> 23) & 1));
    bundle[24] = bundle2[120] ^ _mm512_set1_epi32(-((key >> 24) & 1));
    bundle[25] = bundle2[121] ^ _mm512_set1_epi32(-((key >> 25) & 1));
    bundle[26] = bundle2[122] ^ _mm512_set1_epi32(-((key >> 26) & 1));
    bundle[27] = bundle2[123] ^ _mm512_set1_epi32(-((key >> 27) & 1));
    bundle[28] = bundle2[124] ^ _mm512_set1_epi32(-((key >> 28) & 1));
    bundle[29] = bundle2[125] ^ _mm512_set1_epi32(-((key >> 29) & 1));
    bundle[30] = bundle2[126] ^ _mm512_set1_epi32(-((key >> 30) & 1));
    bundle[31] = bundle2[127] ^ _mm512_set1_epi32(-((key >> 31) & 1));

    key = roundkey[41];
    bundle[32] = bundle2[32] ^ _mm512_set1_epi32(-((key >> 0) & 1));
    bundle[33] = bundle2[33] ^ _mm512_set1_epi32(-((key >> 1) & 1));
    bundle[34] = bundle2[34] ^ _mm512_set1_epi32(-((key >> 2) & 1));
    bundle[35] = bundle2[35] ^ _mm512_set1_epi32(-((key >> 3) & 1));
    bundle[36] = bundle2[36] ^ _mm512_set1_epi32(-((key >> 4) & 1));
    bundle[37] = bundle2[37] ^ _mm512_set1_epi32(-((key >> 5) & 1));
    bundle[38] = bundle2[38] ^ _mm512_set1_epi32(-((key >> 6) & 1));
    bundle[39] = bundle2[39] ^ _mm512_set1_epi32(-((key >> 7) & 1));
    bundle[40] = bundle2[72] ^ _mm512_set1_epi32(-((key >> 8) & 1));
    bundle[41] = bundle2[73] ^ _mm512_set1_epi32(-((key >> 9) & 1));
    bundle[42] = bundle2[74] ^ _mm512_set1_epi32(-((key >> 10) & 1));
    bundle[43] = bundle2[75] ^ _mm512_set1_epi32(-((key >> 11) & 1));
    bundle[44] = bundle2[76] ^ _mm512_set1_epi32(-((key >> 12) & 1));
    bundle[45] = bundle2[77] ^ _mm512_set1_epi32(-((key >> 13) & 1));
    bundle[46] = bundle2[78] ^ _mm512_set1_epi32(-((key >> 14) & 1));
    bundle[47] = bundle2[79] ^ _mm512_set1_epi32(-((key >> 15) & 1));
    bundle[48] = bundle2[112] ^ _mm512_set1_epi32(-((key >> 16) & 1));
    bundle[49] = bundle2[113] ^ _mm512_set1_epi32(-((key >> 17) & 1));
    bundle[50] = bundle2[114] ^ _mm512_set1_epi32(-((key >> 18) & 1));
    bundle[51] = bundle2[115] ^ _mm512_set1_epi32(-((key >> 19) & 1));
    bundle[52] = bundle2[116] ^ _mm512_set1_epi32(-((key >> 20) & 1));
    bundle[53] = bundle2[117] ^ _mm512_set1_epi32(-((key >> 21) & 1));
    bundle[54] = bundle2[118] ^ _mm512_set1_epi32(-((key >> 22) & 1));
    bundle[55] = bundle2[119] ^ _mm512_set1_epi32(-((key >> 23) & 1));
    bundle[56] = bundle2[24] ^ _mm512_set1_epi32(-((key >> 24) & 1));
    bundle[57] = bundle2[25] ^ _mm512_set1_epi32(-((key >> 25) & 1));
    bundle[58] = bundle2[26] ^ _mm512_set1_epi32(-((key >> 26) & 1));
    bundle[59] = bundle2[27] ^ _mm512_set1_epi32(-((key >> 27) & 1));
    bundle[60] = bundle2[28] ^ _mm512_set1_epi32(-((key >> 28) & 1));
    bundle[61] = bundle2[29] ^ _mm512_set1_epi32(-((key >> 29) & 1));
    bundle[62] = bundle2[30] ^ _mm512_set1_epi32(-((key >> 30) & 1));
    bundle[63] = bundle2[31] ^ _mm512_set1_epi32(-((key >> 31) & 1));
    key = roundkey[42];
    bundle[64] = bundle2[64] ^ _mm512_set1_epi32(-((key >> 0) & 1));
    bundle[65] = bundle2[65] ^ _mm512_set1_epi32(-((key >> 1) & 1));
    bundle[66] = bundle2[66] ^ _mm512_set1_epi32(-((key >> 2) & 1));
    bundle[67] = bundle2[67] ^ _mm512_set1_epi32(-((key >> 3) & 1));
    bundle[68] = bundle2[68] ^ _mm512_set1_epi32(-((key >> 4) & 1));
    bundle[69] = bundle2[69] ^ _mm512_set1_epi32(-((key >> 5) & 1));
    bundle[70] = bundle2[70] ^ _mm512_set1_epi32(-((key >> 6) & 1));
    bundle[71] = bundle2[71] ^ _mm512_set1_epi32(-((key >> 7) & 1));
    bundle[72] = bundle2[104] ^ _mm512_set1_epi32(-((key >> 8) & 1));
    bundle[73] = bundle2[105] ^ _mm512_set1_epi32(-((key >> 9) & 1));
    bundle[74] = bundle2[106] ^ _mm512_set1_epi32(-((key >> 10) & 1));
    bundle[75] = bundle2[107] ^ _mm512_set1_epi32(-((key >> 11) & 1));
    bundle[76] = bundle2[108] ^ _mm512_set1_epi32(-((key >> 12) & 1));
    bundle[77] = bundle2[109] ^ _mm512_set1_epi32(-((key >> 13) & 1));
    bundle[78] = bundle2[110] ^ _mm512_set1_epi32(-((key >> 14) & 1));
    bundle[79] = bundle2[111] ^ _mm512_set1_epi32(-((key >> 15) & 1));
    bundle[80] = bundle2[16] ^ _mm512_set1_epi32(-((key >> 16) & 1));
    bundle[81] = bundle2[17] ^ _mm512_set1_epi32(-((key >> 17) & 1));
    bundle[82] = bundle2[18] ^ _mm512_set1_epi32(-((key >> 18) & 1));
    bundle[83] = bundle2[19] ^ _mm512_set1_epi32(-((key >> 19) & 1));
    bundle[84] = bundle2[20] ^ _mm512_set1_epi32(-((key >> 20) & 1));
    bundle[85] = bundle2[21] ^ _mm512_set1_epi32(-((key >> 21) & 1));
    bundle[86] = bundle2[22] ^ _mm512_set1_epi32(-((key >> 22) & 1));
    bundle[87] = bundle2[23] ^ _mm512_set1_epi32(-((key >> 23) & 1));
    bundle[88] = bundle2[56] ^ _mm512_set1_epi32(-((key >> 24) & 1));
    bundle[89] = bundle2[57] ^ _mm512_set1_epi32(-((key >> 25) & 1));
    bundle[90] = bundle2[58] ^ _mm512_set1_epi32(-((key >> 26) & 1));
    bundle[91] = bundle2[59] ^ _mm512_set1_epi32(-((key >> 27) & 1));
    bundle[92] = bundle2[60] ^ _mm512_set1_epi32(-((key >> 28) & 1));
    bundle[93] = bundle2[61] ^ _mm512_set1_epi32(-((key >> 29) & 1));
    bundle[94] = bundle2[62] ^ _mm512_set1_epi32(-((key >> 30) & 1));
    bundle[95] = bundle2[63] ^ _mm512_set1_epi32(-((key >> 31) & 1));
    key = roundkey[43];
    bundle[96 ] = bundle2[96] ^ _mm512_set1_epi32(-((key >> 0) & 1));
    bundle[97 ] = bundle2[97] ^ _mm512_set1_epi32(-((key >> 1) & 1));
    bundle[98 ] = bundle2[98] ^ _mm512_set1_epi32(-((key >> 2) & 1));
    bundle[99 ] = bundle2[99] ^ _mm512_set1_epi32(-((key >> 3) & 1));
    bundle[100] = bundle2[100] ^ _mm512_set1_epi32(-((key >> 4) & 1));
    bundle[101] = bundle2[101] ^ _mm512_set1_epi32(-((key >> 5) & 1));
    bundle[102] = bundle2[102] ^ _mm512_set1_epi32(-((key >> 6) & 1));
    bundle[103] = bundle2[103] ^ _mm512_set1_epi32(-((key >> 7) & 1));
    bundle[104] = bundle2[8] ^ _mm512_set1_epi32(-((key >> 8) & 1));
    bundle[105] = bundle2[9] ^ _mm512_set1_epi32(-((key >> 9) & 1));
    bundle[106] = bundle2[10] ^ _mm512_set1_epi32(-((key >> 10) & 1));
    bundle[107] = bundle2[11] ^ _mm512_set1_epi32(-((key >> 11) & 1));
    bundle[108] = bundle2[12] ^ _mm512_set1_epi32(-((key >> 12) & 1));
    bundle[109] = bundle2[13] ^ _mm512_set1_epi32(-((key >> 13) & 1));
    bundle[110] = bundle2[14] ^ _mm512_set1_epi32(-((key >> 14) & 1));
    bundle[111] = bundle2[15] ^ _mm512_set1_epi32(-((key >> 15) & 1));
    bundle[112] = bundle2[48] ^ _mm512_set1_epi32(-((key >> 16) & 1));
    bundle[113] = bundle2[49] ^ _mm512_set1_epi32(-((key >> 17) & 1));
    bundle[114] = bundle2[50] ^ _mm512_set1_epi32(-((key >> 18) & 1));
    bundle[115] = bundle2[51] ^ _mm512_set1_epi32(-((key >> 19) & 1));
    bundle[116] = bundle2[52] ^ _mm512_set1_epi32(-((key >> 20) & 1));
    bundle[117] = bundle2[53] ^ _mm512_set1_epi32(-((key >> 21) & 1));
    bundle[118] = bundle2[54] ^ _mm512_set1_epi32(-((key >> 22) & 1));
    bundle[119] = bundle2[55] ^ _mm512_set1_epi32(-((key >> 23) & 1));
    bundle[120] = bundle2[88] ^ _mm512_set1_epi32(-((key >> 24) & 1));
    bundle[121] = bundle2[89] ^ _mm512_set1_epi32(-((key >> 25) & 1));
    bundle[122] = bundle2[90] ^ _mm512_set1_epi32(-((key >> 26) & 1));
    bundle[123] = bundle2[91] ^ _mm512_set1_epi32(-((key >> 27) & 1));
    bundle[124] = bundle2[92] ^ _mm512_set1_epi32(-((key >> 28) & 1));
    bundle[125] = bundle2[93] ^ _mm512_set1_epi32(-((key >> 29) & 1));
    bundle[126] = bundle2[94] ^ _mm512_set1_epi32(-((key >> 30) & 1));
    bundle[127] = bundle2[95] ^ _mm512_set1_epi32(-((key >> 31) & 1));

}


int main() {
    init_data();
    key_expansion();
    format_bundle();
    encrypt();
    output_text();


    unsigned long long time = 0x200000;


    unsigned long long Mbits = (time >> 4); //  (>>20) * 512 * 128
    clock_t start, end;
    start = clock();
    for (long i = 0; i < time; ++i) {
         transpose_simultaneously3(bundle);
        encrypt();
         transpose_simultaneously3(bundle);
    }
    end = clock();
    double elapsed = (double) (end - start) / CLOCKS_PER_SEC;
    double speed_time = Mbits / elapsed;
    printf("\n----------Elapsed Timing is %f\n Encrypt speed is %f Mb/s\n", elapsed, speed_time);


    unsigned long long bytes = time << 13;
    startCycles();
    for (long i = 0; i < time; ++i)
        encrypt();
    unsigned long long cycles = stopWithPrintCycles();
    printf("Encrypt speed is %f cycles/bytes\n", (double) cycles / bytes);

    free(bundle);
    free(bundle2);
    // free(idata);
    return 0;
}
