#include <x86intrin.h>

__m512i v1, v2;

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


void transpose_simultaneously(__m512i *A) {
    __m512i mask[7] = {
            _mm512_set1_epi64(0x5555555555555555),
            _mm512_set1_epi64(0x3333333333333333),
            _mm512_set1_epi64(0x0f0f0f0f0f0f0f0f),
            _mm512_set1_epi64(0x00ff00ff00ff00ff),
            _mm512_set1_epi64(0x0000ffff0000ffff),
            _mm512_set1_epi64(0x00000000ffffffff),
            _mm512_set_epi64(0, -1, 0, -1, 0, -1, 0, -1)
    };
    int k, l;
    __m512i temp, temp1, temp2;
    for (int j = 0; j < 3; ++j) {
        k = 1 << j;
        for (int i = 0; i < 64; ++i) {
            l = 2 * i - (i % k);

            temp1 = _mm512_andnot_si512(mask[j], A[l]);
            temp2 = _mm512_andnot_si512(mask[j], A[l + k]);
            temp2 = SHR512n(temp2, k);
            temp = _mm512_or_si512(temp1, temp2);

            temp1 = _mm512_and_si512(mask[j], A[l + k]);
            temp2 = _mm512_and_si512(mask[j], A[l]);
            temp2 = SHL512n(temp2, k);
            A[l + k] = _mm512_or_si512(temp1, temp2);
            A[l] = temp;
        }
    }

    k = 8;
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % k);
        temp1 = _mm512_andnot_si512(mask[3], A[l]);
        temp2 = _mm512_andnot_si512(mask[3], A[l + k]);
        temp2 = _mm512_bsrli_epi128(temp2, 1);
        temp = _mm512_or_si512(temp1, temp2);

        temp1 = _mm512_and_si512(mask[3], A[l + k]);
        temp2 = _mm512_and_si512(mask[3], A[l]);
        temp2 = _mm512_bslli_epi128(temp2, 1);
        A[l + k] = _mm512_or_si512(temp1, temp2);
        A[l] = temp;
    }


    k = 16;
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % k);
        temp1 = _mm512_andnot_si512(mask[4], A[l]);
        temp2 = _mm512_andnot_si512(mask[4], A[l + k]);
        temp2 = _mm512_bsrli_epi128(temp2, 2);
        temp = _mm512_or_si512(temp1, temp2);

        temp1 = _mm512_and_si512(mask[4], A[l + k]);
        temp2 = _mm512_and_si512(mask[4], A[l]);
        temp2 = _mm512_bslli_epi128(temp2, 2);
        A[l + k] = _mm512_or_si512(temp1, temp2);
        A[l] = temp;
    }

    k = 32;
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % k);
        temp1 = _mm512_andnot_si512(mask[5], A[l]);
        temp2 = _mm512_andnot_si512(mask[5], A[l + k]);
        temp2 = _mm512_bsrli_epi128(temp2, 4);
        temp = _mm512_or_si512(temp1, temp2);

        temp1 = _mm512_and_si512(mask[5], A[l + k]);
        temp2 = _mm512_and_si512(mask[5], A[l]);
        temp2 = _mm512_bslli_epi128(temp2, 4);
        A[l + k] = _mm512_or_si512(temp1, temp2);
        A[l] = temp;
    }

    k = 64;
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % k);
        temp1 = _mm512_andnot_si512(mask[6], A[l]);
        temp2 = _mm512_andnot_si512(mask[6], A[l + k]);
        temp2 = _mm512_bsrli_epi128(temp2, 8);
        temp = _mm512_or_si512(temp1, temp2);

        temp1 = _mm512_and_si512(mask[6], A[l + k]);
        temp2 = _mm512_and_si512(mask[6], A[l]);
        temp2 = _mm512_bslli_epi128(temp2, 8);
        A[l + k] = _mm512_or_si512(temp1, temp2);
        A[l] = temp;
    }
}

