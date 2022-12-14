
#include <x86intrin.h>

#define V(a, b, c, d) _mm512_ternarylogic_epi32((a), (b), (c), (d))

void mixlinear(__m512i *b, __m512i *bundle) {
    __m512i x[32];
    x[0] = b[0];
    x[1] = b[1];
    x[2] = b[2];
    x[3] = b[3];
    x[4] = b[4];
    x[5] = b[5];
    x[6] = b[6];
    x[7] = b[7];
    x[8] = b[8];
    x[9] = b[9];
    x[10] = b[10];
    x[11] = b[11];
    x[12] = b[12];
    x[13] = b[13];
    x[14] = b[14];
    x[15] = b[15];
    x[16] = b[16];
    x[17] = b[17];
    x[18] = b[18];
    x[19] = b[19];
    x[20] = b[20];
    x[21] = b[21];
    x[22] = b[22];
    x[23] = b[23];
    x[24] = b[24];
    x[25] = b[25];
    x[26] = b[26];
    x[27] = b[27];
    x[28] = b[28];
    x[29] = b[29];
    x[30] = b[30];
    x[31] = b[31];

    x[30] = x[30] ^ x[14];
    x[14] = x[14] ^ x[22];
    x[29] = x[29] ^ x[13];
    x[25] = x[25] ^ x[17];
    x[23] = x[23] ^ x[7];
    x[26] = x[26] ^ x[18];
    x[17] = x[17] ^ x[9];
    x[16] = x[16] ^ x[14];
    x[9] = x[9] ^ x[1];
    x[20] = x[20] ^ x[28];
    x[1] = V(x[1], x[7], x[31], 0x96);
    x[7] = V(x[7], x[31], x[29], 0x96);
    x[18] = x[18] ^ x[10];
    x[19] = x[19] ^ x[27];
    x[10] = x[10] ^ x[2];
    x[24] = x[24] ^ x[8];
    x[2] = V(x[2], x[8], x[0], 0x96);
    x[8] = V(x[8], x[0], x[30], 0x96);
    x[22] = V(x[22], x[30], x[6], 0X96);
    x[30] = V(x[30], x[6], x[20], 0X96);//y[28]
    x[27] = x[27] ^ x[11];
    x[6] = V(x[6], x[12], x[4], 0X96);
    x[28] = x[28] ^ x[12];
    x[31] = x[31] ^ x[15];
    x[15] = V(x[15], x[13], x[21], 0x96);
    x[13] = V(x[13], x[21], x[27], 0x96);
    x[21] = V(x[21], x[29], x[5], 0x96);
    x[29] = V(x[29], x[5], x[19], 0x96);  //y[27]
    x[5] = V(x[5], x[3], x[11], 0X96);
    x[12] = V(x[12], x[20], x[10], 0X96);  //y[10]
    x[20] = V(x[20], x[18], x[4], 0X96);//y[18]
    x[27] = V(x[27], x[25], x[3], 0X96); //y[25]
    x[3] = V(x[3], x[19], x[17], 0X96); //y[17]
    x[11] = V(x[11], x[19], x[9], 0X96);//y[9]
    x[19] = V(x[19], x[17], x[9], 0X96);
    x[4] = V(x[4], x[28], x[26], 0x96); //y[26]
    x[0] = x[0] ^ x[14];
    x[14] = x[14] ^ x[28];
    x[28] = V(x[28], x[26], x[10], 0x96);
    x[10] = V(x[10], x[26], x[2], 0x96);  //y[8]
    x[26] = V(x[26], x[2], x[0], 0x96);
    x[0] = x[0] ^ x[24];   //y[22]
    x[9] = V(x[9], x[25], x[1], 0x96);   //y[7]
    x[25] = V(x[25], x[1], x[31], 0x96);  //y[15]
    x[31] = V(x[31], x[23], x[15], 0x96);  //y[21]
    x[1] = V(x[1], x[17], x[23], 0x96);  //y[31]
    x[17] = V(x[17], x[23], x[25], 0x96);  //y[23]
    x[23] = V(x[23], x[15], x[21], 0x96);  //y[5]
    x[15] = x[15] ^ x[7];//y[29]
    x[21] = x[21] ^ x[5];  //y[11]
    x[26] = x[26] ^ x[16];  //y[16]
    x[2] =   V(x[2] , x[18] , x[24] , 0x96);  //y[0]
    x[18] = V(x[18] , x[24] , x[26], 0x96);  //y[24]
    x[24] = V(x[24], x[22], x[16], 0x96);  //y[6]
    bundle[12] = V(bundle[12], x[22], x[6], 0x96);
    bundle[4] = V(bundle[4], x[6], x[14], 0x96);
    bundle[30] = V(bundle[30], x[8], x[16], 0x96);
    bundle[20] = V(bundle[20], x[14], x[30], 0x96);
    bundle[3] = V(bundle[3], x[13], x[5], 0x96);
    bundle[19] = V(bundle[19], x[13], x[29], 0x96);
    bundle[1] = V(bundle[1], x[19], x[27], 0x96);
    bundle[14] = V(bundle[14], x[8], x[24], 0x96);
    bundle[2] = V(bundle[2], x[28], x[20], 0x96);
    bundle[13] = V(bundle[13],x[7], x[23], 0x96);


    bundle[0]  ^= x[2];
    bundle[5]  ^= x[23];
    bundle[6]  ^= x[24];
    bundle[7]  ^= x[9];
    bundle[8]  ^= x[10];
    bundle[9]  ^= x[11];
    bundle[10] ^= x[12];
    bundle[11] ^= x[21];
    bundle[15] ^= x[25];
    bundle[16] ^= x[26];
    bundle[17] ^= x[3];
    bundle[18] ^= x[20];
    bundle[21] ^= x[31];
    bundle[22] ^= x[0];
    bundle[23] ^= x[17];
    bundle[24] ^= x[18];
    bundle[25] ^= x[27];
    bundle[26] ^= x[4];
    bundle[27] ^= x[29];
    bundle[28] ^= x[30];
    bundle[29] ^= x[15];
    bundle[31] ^= x[1];
}
