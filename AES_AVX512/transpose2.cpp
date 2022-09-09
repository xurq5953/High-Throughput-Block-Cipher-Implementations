#include <x86intrin.h>

//对角线转置
extern __m512i v1, v2;

inline __m512i SHR512n(__m512i &v, int n) {
    v1 = _mm512_srli_epi64(v, n);
    v2 = _mm512_bsrli_epi128(v, 8);
    v2 = _mm512_slli_epi64(v2, 64 - n);
    return _mm512_or_si512(v1, v2);
}

inline __m512i SHL512n(__m512i &v, int n) {
    v1 = _mm512_slli_epi64(v, n);
    v2 = _mm512_bslli_epi128(v, 8);
    v2 = _mm512_srli_epi64(v2, 64 - n);
    return _mm512_or_si512(v1, v2);
}


void transpose_simultaneously2(__m512i *A) {

    int l;
    __m512i temp, temp1, temp2, mask;

    mask = _mm512_set1_epi64(0x5555555555555555);
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % 1);

        temp1 = _mm512_and_si512(mask, A[l]);
        temp2 = _mm512_and_si512(mask, A[l + 1]);
        temp2 = SHL512n(temp2, 1);
        temp = _mm512_or_si512(temp1, temp2);

        temp1 = _mm512_andnot_si512(mask, A[l + 1]);
        temp2 = _mm512_andnot_si512(mask, A[l]);
        temp2 = SHR512n(temp2, 1);
        A[l + 1] = _mm512_or_si512(temp1, temp2);
        A[l] = temp;
    }

    mask = _mm512_set1_epi64(0x3333333333333333);
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % 2);

        temp1 = _mm512_and_si512(mask, A[l]);
        temp2 = _mm512_and_si512(mask, A[l + 2]);
        temp2 = SHL512n(temp2, 2);
        temp = _mm512_or_si512(temp1, temp2);

        temp1 = _mm512_andnot_si512(mask, A[l + 2]);
        temp2 = _mm512_andnot_si512(mask, A[l]);
        temp2 = SHR512n(temp2, 2);
        A[l + 2] = _mm512_or_si512(temp1, temp2);
        A[l] = temp;
    }

    mask = _mm512_set1_epi64(0x0f0f0f0f0f0f0f0f);
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % 4);

        temp1 = _mm512_and_si512(mask, A[l]);
        temp2 = _mm512_and_si512(mask, A[l + 4]);
        temp2 = SHL512n(temp2, 4);
        temp = _mm512_or_si512(temp1, temp2);

        temp1 = _mm512_andnot_si512(mask, A[l + 4]);
        temp2 = _mm512_andnot_si512(mask, A[l]);
        temp2 = SHR512n(temp2, 4);
        A[l + 4] = _mm512_or_si512(temp1, temp2);
        A[l] = temp;
    }

    mask = _mm512_set1_epi64(0x00ff00ff00ff00ff);
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % 8);
        temp1 = _mm512_and_si512(mask, A[l]);
        temp2 = _mm512_and_si512(mask, A[l + 8]);
        temp2 = _mm512_bslli_epi128(temp2, 1);
        temp = _mm512_or_si512(temp1, temp2);

        temp1 = _mm512_andnot_si512(mask, A[l + 8]);
        temp2 = _mm512_andnot_si512(mask, A[l]);
        temp2 = _mm512_bsrli_epi128(temp2, 1);
        A[l + 8] = _mm512_or_si512(temp1, temp2);
        A[l] = temp;
    }


    mask = _mm512_set1_epi64(0x0000ffff0000ffff);
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % 16);

        temp1 = _mm512_and_si512(mask, A[l]);
        temp2 = _mm512_and_si512(mask, A[l + 16]);
        temp2 = _mm512_bslli_epi128(temp2, 2);
        temp = _mm512_or_si512(temp1, temp2);

        temp1 = _mm512_andnot_si512(mask, A[l + 16]);
        temp2 = _mm512_andnot_si512(mask, A[l]);
        temp2 = _mm512_bsrli_epi128(temp2, 2);
        A[l + 16] = _mm512_or_si512(temp1, temp2);
        A[l] = temp;
    }

    mask = _mm512_set1_epi64(0x00000000ffffffff);
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % 32);
        temp1 = _mm512_and_si512(mask, A[l]);
        temp2 = _mm512_and_si512(mask, A[l + 32]);
        temp2 = _mm512_bslli_epi128(temp2, 4);
        temp = _mm512_or_si512(temp1, temp2);

        temp1 = _mm512_andnot_si512(mask, A[l + 32]);
        temp2 = _mm512_andnot_si512(mask, A[l]);
        temp2 = _mm512_bsrli_epi128(temp2, 4);
        A[l + 32] = _mm512_or_si512(temp1, temp2);
        A[l] = temp;
    }

    mask = _mm512_set_epi64(0, -1, 0, -1, 0, -1, 0, -1);
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % 64);

        temp1 = _mm512_and_si512(mask, A[l]);
        temp2 = _mm512_and_si512(mask, A[l + 64]);
        temp2 = _mm512_bslli_epi128(temp2, 8);
        temp = _mm512_or_si512(temp1, temp2);

        temp1 = _mm512_andnot_si512(mask, A[l + 64]);
        temp2 = _mm512_andnot_si512(mask, A[l]);
        temp2 = _mm512_bsrli_epi128(temp2, 8);
        A[l + 64] = _mm512_or_si512(temp1, temp2);
        A[l] = temp;
    }
}

