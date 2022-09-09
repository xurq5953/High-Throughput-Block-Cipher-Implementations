//
// Created by Axurq on 20/5/2022.
//

#include <x86intrin.h>

void sbox(__m256i *x) {
    __m256i b[8];
    __m256i g[8];
    __m256i m[10];

    b[0] = x[0];
    b[1] = x[1];
    b[2] = x[2];
    b[3] = x[3];
    b[4] = x[4];
    b[5] = x[5];
    b[6] = x[6];
    b[7] = x[7];
//20
    g[7] = b[3] ^ b[1];
    m[5] = g[7] ^ b[2];
    m[6] = b[7] ^ b[4];
    m[7] = b[6] ^ m[5];
    g[5] = b[0] ^ m[7];
    m[1] = b[5] ^ m[5];
    g[4] = g[5] ^ m[1];
    g[3] = b[4] ^ g[4];
    m[9] = g[7] ^ m[6];
    g[1] = m[6] ^ g[3];
    g[6] = b[0] ^ m[9];
    m[2] = b[4] ^ b[2];
    g[0] = b[1] ^ g[4];
    m[4] = b[7] ^ b[2];
    g[2] = g[0] ^ m[4];
    m[0] = b[7] ^ b[1];
    m[8] = m[2] ^ m[0];
    m[3] = m[1] ^ m[9];
    m[5] = g[4] ^ g[6];
    g[7] = b[0];

//24
    b[0] = g[6] & g[2];
    b[1] = m[3] & m[2];
    b[2] = m[4] & m[5];

    b[7] = b[0] ^ b[1] ^ (m[9] & m[8]) ^ (m[6] | m[7]);
    b[6] = b[0] ^ b[2] ^ (g[3] & g[7]) ^ (m[2] | m[3]);
    b[5] = b[1] ^ (m[6] & m[7]) ^ (g[0] & g[4]) ^ (m[0] | m[1]);
    b[4] = b[1] ^ b[2] ^ (g[1] & g[5]) ^ (g[0] | g[4]);

//middle 15

    b[6] = b[6] ^ b[7];
    b[0] = b[4] & b[6] & b[7];
    b[5] = b[5] ^ b[0];
    b[4] = b[4] ^ b[6] & b[5];
    b[7] = b[7] ^ b[6] & b[4];
    b[6] = b[6] ^ _mm256_andnot_si256(b[4], b[7]);
    b[4] = b[4] ^ b[7] & b[5];
    b[5] = b[5] ^ b[6] & b[4];


//bottom  35

    b[3] = b[4] ^ b[6];
    b[2] = b[5] ^ b[7];
    b[1] = b[3] ^ b[2];
    b[0] = b[6] ^ b[7];


    g[3] = g[3] & b[4];
    m[4] = m[4] & b[2];
    g[1] = g[1] & b[6];

    g[2] = g[3] ^ (g[2] & b[5]);
    m[2] = m[4] ^ (m[2] & b[1]);
    m[6] = m[4] ^ (m[6] & b[3]);
    g[0] = g[1] ^ (g[0] & b[7]);
    m[0] = g[1] ^ (m[0] & b[0]);
    m[4] = b[4] ^ b[5];
    m[8] = g[3] ^ (m[8] & m[4]);

    g[5] = g[5] & b[6];
    m[5] = m[5] & b[2];
    g[7] = g[7] & b[4];


    g[6] = g[7] ^ (g[6] & b[5]);
    m[9] = g[7] ^ (m[9] & m[4]);
    m[3] = m[5] ^ (m[3] & b[1]);
    m[7] = m[5] ^ (m[7] & b[3]);
    g[4] = g[5] ^ (g[4] & b[7]);
    m[1] = g[5] ^ (m[1] & b[0]);

    //output  21

    g[1] = m[7] ^ m[1];
    g[3] = g[6] ^ g[4];
    g[5] = g[6] ^ m[3];
    m[4] = g[0] ^ g[5];

    b[7] = m[6] ^ m[8] ^ g[1];
    b[4] = m[9] ^ m[7] ^ b[7];
    b[5] = ~(m[2] ^ m[4]);
    b[0] = ~(g[3] ^ m[6] ^ m[0]);
    b[2] = g[2] ^ b[7] ^ m[4];
    x[6] = ~(g[1] ^ b[4]);
    x[1] = b[0] ^ g[1] ^ g[5];
    x[3] = g[3] ^ b[4];

    x[0] = b[0];
    x[2] = b[2];
    x[4] = b[4];
    x[5] = b[5];
    x[7] = b[7];

}