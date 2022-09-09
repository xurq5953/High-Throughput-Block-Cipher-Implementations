//
// Created by Axurq on 2022/4/13.
//

#define V(a, b, c, d) _mm512_ternarylogic_epi32((a), (b), (c), d)

#include <x86intrin.h>

void sbox2(__m512i *b) {
    __m512i g[8];
    __m512i m[10];

    g[7] = b[3] ^ b[1];
    m[6] = b[7] ^ b[4];
    m[7] = V(b[6], b[2], g[7], 0x96);
    g[5] = b[0] ^ m[7];
    m[1] = V(b[5], b[2], g[7], 0x96);
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

    b[0] = g[6] & g[2];
    b[1] = m[3] & m[2];

    b[7] = b[0] ^ b[1];
    b[7] = V(b[7], m[9], m[8], 0x78);
    b[7] = V(b[7], m[6], m[7], 0x1e);

    b[6] = V(b[0], m[4], m[5], 0x78);
    b[6] = V(b[6], g[3], g[7], 0x78);
    b[6] = V(b[6], m[2], m[3], 0x1e);

    b[5] = V(b[1], m[6], m[7], 0x78);
    b[5] = V(b[5], g[0], g[4], 0x78);
    b[5] = V(b[5], m[0], m[1], 0x1e);

    b[4] = V(b[1], m[4], m[5], 0x78);
    b[4] = V(b[4], g[1], g[5], 0x78);
    b[4] = V(b[4], g[0], g[4], 0x1e);


    b[6] = _mm512_xor_si512(b[6], b[7]);
    b[0] = _mm512_ternarylogic_epi32(b[4], b[6], b[7], 128);
    b[5] = _mm512_xor_si512(b[5], b[0]);
    b[4] = _mm512_ternarylogic_epi32(b[4], b[6], b[5], 0x78);
    b[7] = _mm512_ternarylogic_epi32(b[7], b[6], b[4], 0x78);
    b[6] = _mm512_ternarylogic_epi32(b[6], b[4], b[7], 0xd2);
    b[4] = _mm512_ternarylogic_epi32(b[4], b[7], b[5], 0x78);
    b[5] = _mm512_ternarylogic_epi32(b[5], b[6], b[4], 0x78);

    b[3] = _mm512_xor_si512(b[4], b[6]);
    b[2] = _mm512_xor_si512(b[5], b[7]);
    b[1] = _mm512_xor_si512(b[3], b[2]);
    b[0] = _mm512_xor_si512(b[6], b[7]);


    g[3] = _mm512_and_si512(g[3], b[4]);
    m[4] = _mm512_and_si512(m[4], b[2]);
    g[1] = _mm512_and_si512(g[1], b[6]);


    g[2] = _mm512_ternarylogic_epi32(g[3], g[2], b[5], 0x78);
    m[2] = _mm512_ternarylogic_epi32(m[4], m[2], b[1], 0x78);
    m[6] = _mm512_ternarylogic_epi32(m[4], m[6], b[3], 0x78);
    g[0] = _mm512_ternarylogic_epi32(g[1], g[0], b[7], 0x78);
    m[0] = _mm512_ternarylogic_epi32(g[1], m[0], b[0], 0x78);
    m[4] = _mm512_xor_si512(b[4], b[5]);//k
    m[8] = _mm512_ternarylogic_epi32(g[3], m[8], m[4], 0x78);

    g[5] = _mm512_and_si512(g[5], b[6]);
    m[5] = _mm512_and_si512(m[5], b[2]);
    g[7] = _mm512_and_si512(g[7], b[4]);


    g[6] = _mm512_ternarylogic_epi32(g[7], g[6], b[5], 0x78);
    m[9] = _mm512_ternarylogic_epi32(g[7], m[9], m[4], 0x78);
    m[3] = _mm512_ternarylogic_epi32(m[5], m[3], b[1], 0x78);
    m[7] = _mm512_ternarylogic_epi32(m[5], m[7], b[3], 0x78);
    g[4] = _mm512_ternarylogic_epi32(g[5], g[4], b[7], 0x78);
    m[1] = _mm512_ternarylogic_epi32(g[5], m[1], b[0], 0x78);

    g[1] = m[7] ^ m[1];
    g[3] = g[6] ^ g[4];
    g[5] = g[6] ^ m[3];
    b[7] = V(m[6], m[8], g[1], 0x96);
    b[4] = V(m[9], m[7], b[7], 0x96);
    b[5] = V(m[2], g[0], g[5], 0x69);
    b[0] = V(g[3], m[6], m[0], 0x69);
    b[2] = V(g[2], b[7], g[0], 0x96);
    b[2] = b[2] ^ g[5];
    b[6] = V(g[1], g[1], b[4], 0x81);
    b[1] = V(b[0], g[1], g[5], 0x96);
    b[3] = g[3] ^ b[4];


}