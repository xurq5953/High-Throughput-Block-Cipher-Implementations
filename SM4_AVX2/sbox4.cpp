#include <x86intrin.h>

#define NOT(x) _mm256_xor_si256((x), _mm256_cmpeq_epi32((x), (x)))

void sbox4(__m256i *b) {
    __m256i g[8];
    __m256i m[10];
    __m256i k;

    m[6] = _mm256_xor_si256(b[0], b[2]);
    g[4] = _mm256_xor_si256(b[2], b[6]);
    m[1] = _mm256_xor_si256(b[7], g[4]);
    g[4] = ~(g[4]);
    m[4] = _mm256_xor_si256(b[1], b[5]);
    g[3] = _mm256_xor_si256(b[4], m[1]);
    m[0] = _mm256_xor_si256(b[3], m[6]);
    g[1] = _mm256_xor_si256(b[6], g[3]);
    m[2] = _mm256_xor_si256(b[6], m[4]);
    m[8] = _mm256_xor_si256(m[0], m[2]);
    g[0] = _mm256_xor_si256(m[0], g[1]);
    m[5] = NOT(_mm256_xor_si256(b[4], m[6]));
    m[9] = NOT(_mm256_xor_si256(b[1], m[8]));
    g[2] = _mm256_xor_si256(m[4], g[0]);
    g[6] = _mm256_xor_si256(g[4], m[5]);
    g[7] = _mm256_xor_si256(m[9], g[6]);
    m[3] = _mm256_xor_si256(m[1], m[9]);
    m[7] = _mm256_xor_si256(m[5], m[3]);
    g[5] = b[7];
    m[6] = b[6];


    b[0] = _mm256_and_si256(m[1], m[0]);
    b[1] = _mm256_or_si256(g[6], g[2]);
    b[2] = _mm256_and_si256(m[9], m[8]);
    b[2] = _mm256_xor_si256(b[2], _mm256_and_si256(g[4], g[0]));
    b[2] = _mm256_xor_si256(b[2], b[0]);
    b[3] = _mm256_and_si256(g[7], g[3]);
    b[3] = _mm256_xor_si256(b[3], _mm256_andnot_si256(g[5], g[1]));
    b[3] = _mm256_xor_si256(b[3], b[0]);

    b[4] = _mm256_or_si256(m[7], m[6]);
    b[7] = _mm256_and_si256(m[3], m[2]);
    b[7] = _mm256_xor_si256(b[7], b[4]);
    b[7] = _mm256_xor_si256(b[7], b[1]);
    b[7] = _mm256_xor_si256(b[7], b[3]);

    b[4] = _mm256_or_si256(g[7], g[3]);
    b[5] = _mm256_or_si256(m[3], m[2]);
    b[6] = _mm256_and_si256(m[5], m[4]);
    b[6] = _mm256_xor_si256(b[6], b[4]);
    b[6] = _mm256_xor_si256(b[6], b[5]);
    b[6] = _mm256_xor_si256(b[6], b[2]);

    b[5] = _mm256_or_si256(m[9], m[8]);
    b[5] = _mm256_xor_si256(b[5], b[3]);

    b[4] = _mm256_xor_si256(b[1], b[2]);



    b[6] = _mm256_xor_si256(b[6], b[7]);
    b[5] = _mm256_xor_si256(b[5], _mm256_and_si256(b[4], _mm256_and_si256(b[6], b[7])));
    b[4] = _mm256_xor_si256(b[4], _mm256_and_si256(b[6], b[5]));
    b[7] = _mm256_xor_si256(b[7], _mm256_and_si256(b[6], b[4]));
    b[6] = _mm256_xor_si256(b[6], _mm256_andnot_si256(b[4], b[7]));
    b[4] = _mm256_xor_si256(b[4], _mm256_and_si256(b[7], b[5]));
    b[5] = _mm256_xor_si256(b[5], _mm256_and_si256(b[6], b[4]));


    k = _mm256_xor_si256(b[4], b[5]);
    b[3] = _mm256_xor_si256(b[4], b[6]);
    b[2] = _mm256_xor_si256(b[5], b[7]);
    b[1] = _mm256_xor_si256(b[3], b[2]);
    b[0] = _mm256_xor_si256(b[6], b[7]);


    g[3] = _mm256_and_si256(g[3], b[4]);
    m[4] = _mm256_and_si256(m[4], b[2]);
    g[1] = _mm256_and_si256(g[1], b[6]);

    g[2] = _mm256_and_si256(g[2], b[5]);
    g[2] = _mm256_xor_si256(g[2], g[3]);
    m[8] = _mm256_and_si256(m[8], k);
    m[8] = _mm256_xor_si256(m[8], g[3]);
    m[2] = _mm256_and_si256(m[2], b[1]);
    m[2] = _mm256_xor_si256(m[2], m[4]);
    m[6] = _mm256_and_si256(m[6], b[3]);
    m[6] = _mm256_xor_si256(m[6], m[4]);
    g[0] = _mm256_and_si256(g[0], b[7]);
    g[0] = _mm256_xor_si256(g[0], g[1]);
    m[0] = _mm256_and_si256(m[0], b[0]);
    m[0] = _mm256_xor_si256(m[0], g[1]);


    g[5] = _mm256_andnot_si256(g[5], b[6]);
    m[5] = _mm256_and_si256(m[5], b[2]);
    g[7] = _mm256_and_si256(g[7], b[4]);

    g[6] = _mm256_and_si256(g[6], b[5]);
    g[6] = _mm256_xor_si256(g[6], g[7]);
    m[9] = _mm256_and_si256(m[9], k);
    m[9] = _mm256_xor_si256(m[9], g[7]);
    m[3] = _mm256_and_si256(m[3], b[1]);
    m[3] = _mm256_xor_si256(m[3], m[5]);
    m[7] = _mm256_and_si256(m[7], b[3]);
    m[7] = _mm256_xor_si256(m[7], m[5]);
    g[4] = _mm256_and_si256(g[4], b[7]);
    g[4] = _mm256_xor_si256(g[4], g[5]);
    m[1] = _mm256_and_si256(m[1], b[0]);
    m[1] = _mm256_xor_si256(m[1], g[5]);




    b[0] = _mm256_xor_si256(m[2], g[0]);
    b[3] = _mm256_xor_si256(g[4], b[0]);
    b[3] = _mm256_xor_si256(b[3], m[3]);
    b[1] = _mm256_xor_si256(g[6], m[3]);
    b[7] = _mm256_xor_si256(m[9], m[1]);

    b[2] = _mm256_xor_si256(b[0], b[1]);
    b[5] = _mm256_xor_si256(b[0], b[7]);
    b[4] = _mm256_xor_si256(m[8], m[6]);
    b[6] = ~(_mm256_xor_si256(b[3], b[4]));
    b[1] = _mm256_xor_si256(m[9], b[1]);
    b[1] = _mm256_xor_si256(b[1], m[7]);
    b[1] = _mm256_xor_si256(b[1], b[6]);
    b[3] = _mm256_xor_si256(g[2], b[3]);
    b[3] = ~(_mm256_xor_si256(b[3],g[0] ));
    b[0] = ~(_mm256_xor_si256(m[8], m[0]));
    b[7] = _mm256_xor_si256(b[7], b[3]);

}
