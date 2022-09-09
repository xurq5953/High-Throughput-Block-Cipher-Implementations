#include <x86intrin.h>

void linearLayer(__m256i *x) {
    x[30] = _mm256_xor_si256(x[30], x[14]);
    x[14] = _mm256_xor_si256(x[14], x[22]);
    x[29] = _mm256_xor_si256(x[29], x[13]);
    x[25] = _mm256_xor_si256(x[25], x[17]);
    x[23] = _mm256_xor_si256(x[23], x[7]);
    x[26] = _mm256_xor_si256(x[26], x[18]);
    x[17] = _mm256_xor_si256(x[17], x[9]);
    x[16] = _mm256_xor_si256(x[16], x[14]);
    x[24] = _mm256_xor_si256(x[24], x[8]);
    x[8] = _mm256_xor_si256(x[8], x[0]);
    x[9] = _mm256_xor_si256(x[9], x[1]);
    x[20] = _mm256_xor_si256(x[20], x[28]);
    x[28] = _mm256_xor_si256(x[28], x[12]);
    x[7] = _mm256_xor_si256(x[7], x[31]);
    x[1] = _mm256_xor_si256(x[1], x[7]);
    x[18] = _mm256_xor_si256(x[18], x[10]);
    x[19] = _mm256_xor_si256(x[19], x[27]);
    x[7] = _mm256_xor_si256(x[7], x[29]);
    x[10] = _mm256_xor_si256(x[10], x[2]);
    x[2] = _mm256_xor_si256(x[2], x[8]);
    x[8] = _mm256_xor_si256(x[8], x[30]);
    x[29] = _mm256_xor_si256(x[29], x[5]);
    x[5] = _mm256_xor_si256(x[5], x[3]);
    x[30] = _mm256_xor_si256(x[30], x[6]);
    x[22] = _mm256_xor_si256(x[22], x[30]);
    x[27] = _mm256_xor_si256(x[27], x[11]);
    x[13] = _mm256_xor_si256(x[13], x[21]);
    x[5] = _mm256_xor_si256(x[5], x[11]);
    x[6] = _mm256_xor_si256(x[6], x[12]);
    x[0] = _mm256_xor_si256(x[0], x[14]);
    x[12] = _mm256_xor_si256(x[12], x[20]);
    x[14] = _mm256_xor_si256(x[14], x[28]);
    x[21] = _mm256_xor_si256(x[21], x[29]);
    x[30] = _mm256_xor_si256(x[30], x[20]);
    x[31] = _mm256_xor_si256(x[31], x[15]);
    x[11] = _mm256_xor_si256(x[11], x[19]);
    x[29] = _mm256_xor_si256(x[29], x[19]);
    x[20] = _mm256_xor_si256(x[20], x[18]);
    x[15] = _mm256_xor_si256(x[15], x[13]);
    x[19] = _mm256_xor_si256(x[19], x[17]);
    x[13] = _mm256_xor_si256(x[13], x[27]);
    x[28] = _mm256_xor_si256(x[28], x[26]);
    x[27] = _mm256_xor_si256(x[27], x[25]);
    x[17] = _mm256_xor_si256(x[17], x[23]);
    x[27] = _mm256_xor_si256(x[27], x[3]);
    x[6] = _mm256_xor_si256(x[6], x[4]);
    x[20] = _mm256_xor_si256(x[20], x[4]);
    x[3] = _mm256_xor_si256(x[3], x[19]);
    x[19] = _mm256_xor_si256(x[19], x[9]);
    x[23] = _mm256_xor_si256(x[23], x[15]);
    x[26] = _mm256_xor_si256(x[26], x[2]);
    x[11] = _mm256_xor_si256(x[11], x[9]);
    x[15] = _mm256_xor_si256(x[15], x[7]);
    x[25] = _mm256_xor_si256(x[25], x[1]);
    x[4] = _mm256_xor_si256(x[4], x[28]);
    x[28] = _mm256_xor_si256(x[28], x[10]);
    x[12] = _mm256_xor_si256(x[12], x[10]);
    x[10] = _mm256_xor_si256(x[10], x[26]);
    x[26] = _mm256_xor_si256(x[26], x[0]);
    x[0] = _mm256_xor_si256(x[0], x[24]);
    x[18] = _mm256_xor_si256(x[18], x[24]);
    x[9] = _mm256_xor_si256(x[9], x[25]);
    x[24] = _mm256_xor_si256(x[24], x[22]);
    x[25] = _mm256_xor_si256(x[25], x[31]);
    x[31] = _mm256_xor_si256(x[31], x[23]);
    x[23] = _mm256_xor_si256(x[23], x[21]);
    x[21] = _mm256_xor_si256(x[21], x[5]);
    x[22] = _mm256_xor_si256(x[22], x[6]);
    x[6] = _mm256_xor_si256(x[6], x[14]);
    x[26] = _mm256_xor_si256(x[26], x[16]);
    x[24] = _mm256_xor_si256(x[24], x[16]);
    x[16] = _mm256_xor_si256(x[16], x[8]);
    x[1] = _mm256_xor_si256(x[1], x[17]);
    x[14] = _mm256_xor_si256(x[14], x[30]);
    x[5] = _mm256_xor_si256(x[5], x[13]);
    x[13] = _mm256_xor_si256(x[13], x[29]);
    x[2] = _mm256_xor_si256(x[2], x[18]);
    x[19] = _mm256_xor_si256(x[19], x[27]);
    x[17] = _mm256_xor_si256(x[17], x[25]);
    x[8] = _mm256_xor_si256(x[8], x[24]);
    x[28] = _mm256_xor_si256(x[28], x[20]);
    x[18] = _mm256_xor_si256(x[18], x[26]);
    x[7] = _mm256_xor_si256(x[7], x[23]);
}
