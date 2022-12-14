//
// Created by Axurq on 17/5/2022.
//

#include <x86intrin.h>

#define V(a, b, c, d) _mm512_ternarylogic_epi32((a), (b), (c), (d))


void mix_linear2(__m512i *b0,__m512i *b1,__m512i *b2,__m512i *b3, __m512i *y, u_int32_t key) {
    __m512i x[32];
    x[0] = b0[0];
    x[1] = b0[1];
    x[2] = b0[2];
    x[3] = b0[3];
    x[4] = b0[4];
    x[5] = b0[5];
    x[6] = b0[6];
    x[7] = b0[7];
    x[8] = b1[0];
    x[9] = b1[1];
    x[10] = b1[2];
    x[11] = b1[3];
    x[12] = b1[4];
    x[13] = b1[5];
    x[14] = b1[6];
    x[15] = b1[7];
    x[16] = b2[0];
    x[17] = b2[1];
    x[18] = b2[2];
    x[19] = b2[3];
    x[20] = b2[4];
    x[21] = b2[5];
    x[22] = b2[6];
    x[23] = b2[7];
    x[24] = b3[0];
    x[25] = b3[1];
    x[26] = b3[2];
    x[27] = b3[3];
    x[28] = b3[4];
    x[29] = b3[5];
    x[30] = b3[6];
    x[31] = b3[7];


    x[12] = x[12] ^ x[4];
    x[13] = x[13] ^ x[21];
    x[17] = x[17] ^ x[9];
    x[11] = x[11] ^ x[27];
    x[4] = x[4] ^ x[28];
    x[21] = x[21] ^ x[5];
    x[0] = x[0] ^ x[24];
    x[9] = x[9] ^ x[1];
    x[14] = x[14] ^ x[6];
    x[24] = V(x[24], x[16], x[8], 0X96);
    x[6] = x[6] ^ x[22];
    x[18] = x[18] ^ x[26];
    x[22] = x[22] ^ x[30];
    x[26] = x[26] ^ x[10];
    x[23] = x[23] ^ x[31];
    x[31] = x[31] ^ x[15];
    x[16] = x[16] ^ x[31];
    x[30] = V(x[30], x[13], x[6], 0X96);    //y[14]
    x[5] = V(x[5], x[13], x[29], 0X96);
    x[13] = V(x[13], x[29], x[12], 0X96);    //y[ 5]
    x[29] = x[29] ^ x[4];
    x[4] = V(x[4], x[11], x[31], 0X96);
    x[11] = x[11] ^ x[19];
    x[19] = x[19] ^ x[23];
    x[28] = V(x[28], x[12], x[20], 0X96);
    x[15] = x[15] ^ x[7];
    x[12] = V(x[12], x[20], x[15], 0X96);
    x[20] = V(x[20], x[27], x[19], 0X96);
    x[27] = V(x[27], x[31], x[3], 0X96);
    x[19] = x[19] ^ x[18];
    x[3] = V(x[3], x[11], x[19], 0X96);    //y[19]
    x[11] = V(x[11], x[2], x[10], 0X96); //y[ 3]
    x[11] = x[11] ^ x[15];
    x[10] = V(x[10], x[18], x[9], 0X96);    //y[ 2]
    x[18] = V(x[18], x[2], x[17], 0X96);    //y[10]
    x[2] = x[2] ^ x[9];
    x[1] = V(x[1], x[17], x[25], 0X96);
    x[17] = V(x[17], x[25], x[16], 0X96);
    x[9] = V(x[9], x[8], x[23], 0X96);
    x[8] = V(x[8], x[23], x[0], 0X96);    //y[16]
    x[16] = V(x[16], x[0], x[23], 0X96);    //y[ 8]
    x[25] = x[25] ^ x[24];
    x[24] = x[24] ^ x[15];    //y[ 0]
    x[0] = V(x[0], x[31], x[24], 0X96);    //y[24]
    x[31] = V(x[31], x[7], x[22], 0X96);    //y[23]
    x[7] = x[7] ^ x[14];
    x[14] = V(x[14], x[21], x[30], 0X96);    //y[ 6]
    x[15] = V(x[15], x[23], x[7], 0X96);    //y[ 7]
    x[7] = V(x[7], x[23], x[6], 0X96);    //y[15]
    x[23] = V(x[23], x[6], x[31], 0X96);    //y[31]
    x[6] = V(x[6], x[5], x[14], 0X96);    //y[22]
    y[29] = V(x[5], x[29], _mm512_set1_epi32(-(((key) >> 29) & 1)), 0X96);
    x[22] = V(x[22], x[21], x[6], 0X96);    //y[30]
    x[29] = V(x[29], x[21], x[28], 0X96);    //y[13]
    x[21] = V(x[21], x[28], x[13], 0X96);    //y[21]
    x[12] = x[12] ^ x[27];                    //y[28]
    y[20] = V(x[28], x[20], _mm512_set1_epi32(-(((key) >> 20) & 1)), 0X96);
    y[12] = V(x[20], x[4], _mm512_set1_epi32(-(((key) >> 12) & 1)), 0X96);
    y[4] = V(x[4], x[12], _mm512_set1_epi32(-(((key) >> 4 ) & 1)), 0X96);
    x[19] = V(x[19], x[27], x[26], 0X96);    //y[11]
    x[27] = V(x[27], x[26], x[11], 0X96);    //y[27]
    x[2] = V(x[2], x[26], x[1], 0X96);    //y[18]
    x[26] = V(x[26], x[1], x[18], 0X96);    //y[26]
    x[1] = V(x[1], x[25], x[0], 0X96);    //y[25]
    y[17] = V(x[25], x[9], _mm512_set1_epi32(-(((key) >> 17) & 1)), 0X96);
    y[9] = V(x[9], x[17], _mm512_set1_epi32(-(((key) >> 9 ) & 1)), 0X96);
    y[1] = V(x[17], x[0], _mm512_set1_epi32(-(((key) >> 1 ) & 1)), 0X96);



    y[0] = x[24] ^ _mm512_set1_epi32(-(((key) >> 0 ) & 1));
    y[2] = x[10] ^ _mm512_set1_epi32(-(((key) >> 2 ) & 1));
    y[3] = x[11] ^ _mm512_set1_epi32(-(((key) >> 3 ) & 1));
    y[5] = x[13] ^ _mm512_set1_epi32(-(((key) >> 5 ) & 1));
    y[6] = x[14] ^ _mm512_set1_epi32(-(((key) >> 6 ) & 1));
    y[7] = x[15] ^ _mm512_set1_epi32(-(((key) >> 7 ) & 1));
    y[8] = x[16] ^ _mm512_set1_epi32(-(((key) >> 8 ) & 1));
    y[10] = x[18] ^ _mm512_set1_epi32(-(((key) >> 10) & 1));
    y[11] = x[19] ^ _mm512_set1_epi32(-(((key) >> 11) & 1));
    y[13] = x[29] ^ _mm512_set1_epi32(-(((key) >> 13) & 1));
    y[14] = x[30] ^ _mm512_set1_epi32(-(((key) >> 14) & 1));
    y[15] = x[7] ^ _mm512_set1_epi32(-(((key) >> 15) & 1));
    y[16] = x[8] ^ _mm512_set1_epi32(-(((key) >> 16) & 1));
    y[18] = x[2] ^ _mm512_set1_epi32(-(((key) >> 18) & 1));
    y[19] = x[3] ^ _mm512_set1_epi32(-(((key) >> 19) & 1));
    y[21] = x[21] ^ _mm512_set1_epi32(-(((key) >> 21) & 1));
    y[22] = x[6] ^ _mm512_set1_epi32(-(((key) >> 22) & 1));
    y[23] = x[31] ^ _mm512_set1_epi32(-(((key) >> 23) & 1));
    y[24] = x[0] ^ _mm512_set1_epi32(-(((key) >> 24) & 1));
    y[25] = x[1] ^ _mm512_set1_epi32(-(((key) >> 25) & 1));
    y[26] = x[26] ^ _mm512_set1_epi32(-(((key) >> 26) & 1));
    y[27] = x[27] ^ _mm512_set1_epi32(-(((key) >> 27) & 1));
    y[28] = x[12] ^ _mm512_set1_epi32(-(((key) >> 28) & 1));
    y[30] = x[22] ^ _mm512_set1_epi32(-(((key) >> 30) & 1));
    y[31] = x[23] ^ _mm512_set1_epi32(-(((key) >> 31) & 1));


}