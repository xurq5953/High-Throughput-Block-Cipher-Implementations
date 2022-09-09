#include <x86intrin.h>

__m256i v1, v2;

inline __m256i SHR256n(const __m256i &v, int n) {
    v1 = _mm256_srli_epi64(v, n);
    v2 = _mm256_srli_si256(v, 8);
    v2 = _mm256_slli_epi64(v2, 64 - n);
    return _mm256_or_si256(v1, v2);
}

inline __m256i SHL256n(const __m256i &v, int n) {
    v1 = _mm256_slli_epi64(v, n);
    v2 = _mm256_slli_si256(v, 8);
    v2 = _mm256_srli_epi64(v2, 64 - n);
    return _mm256_or_si256(v1, v2);
}


void transpose_simultaneously(__m256i *A) {
    __m256i mask[7] = {
            _mm256_set1_epi64x(0x5555555555555555),
            _mm256_set1_epi64x(0x3333333333333333),
            _mm256_set1_epi64x(0x0f0f0f0f0f0f0f0f),
            _mm256_set1_epi64x(0x00ff00ff00ff00ff),
            _mm256_set1_epi64x(0x0000ffff0000ffff),
            _mm256_set1_epi64x(0x00000000ffffffff),
            _mm256_set_epi64x(0, -1, 0, -1)
    };
    int k, l;
    __m256i temp, temp1, temp2;
    for (int j = 0; j < 3; ++j) {
        k = 1 << j;
        for (int i = 0; i < 64; ++i) {
            l = 2 * i - (i % k);

            temp1 = _mm256_andnot_si256(mask[j], A[l]);
            temp2 = _mm256_andnot_si256(mask[j], A[l + k]);
            temp2 = SHR256n(temp2, k);
            temp = _mm256_or_si256(temp1, temp2);

            temp1 = _mm256_and_si256(mask[j], A[l + k]);
            temp2 = _mm256_and_si256(mask[j], A[l]);
            temp2 = SHL256n(temp2, k);
            A[l + k] = _mm256_or_si256(temp1, temp2);
            A[l] = temp;
        }
    }

    k = 8;
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % k);
        temp1 = _mm256_andnot_si256(mask[3], A[l]);
        temp2 = _mm256_andnot_si256(mask[3], A[l + k]);
        temp2 = _mm256_srli_si256(temp2, 1);
        temp = _mm256_or_si256(temp1, temp2);

        temp1 = _mm256_and_si256(mask[3], A[l + k]);
        temp2 = _mm256_and_si256(mask[3], A[l]);
        temp2 = _mm256_slli_si256(temp2, 1);
        A[l + k] = _mm256_or_si256(temp1, temp2);
        A[l] = temp;
    }


    k = 16;
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % k);
        temp1 = _mm256_andnot_si256(mask[4], A[l]);
        temp2 = _mm256_andnot_si256(mask[4], A[l + k]);
        temp2 = _mm256_srli_si256(temp2, 2);
        temp = _mm256_or_si256(temp1, temp2);

        temp1 = _mm256_and_si256(mask[4], A[l + k]);
        temp2 = _mm256_and_si256(mask[4], A[l]);
        temp2 = _mm256_slli_si256(temp2, 2);
        A[l + k] = _mm256_or_si256(temp1, temp2);
        A[l] = temp;
    }

    k = 32;
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % k);
        temp1 = _mm256_andnot_si256(mask[5], A[l]);
        temp2 = _mm256_andnot_si256(mask[5], A[l + k]);
        temp2 = _mm256_srli_si256(temp2, 4);
        temp = _mm256_or_si256(temp1, temp2);

        temp1 = _mm256_and_si256(mask[5], A[l + k]);
        temp2 = _mm256_and_si256(mask[5], A[l]);
        temp2 = _mm256_slli_si256(temp2, 4);
        A[l + k] = _mm256_or_si256(temp1, temp2);
        A[l] = temp;
    }

    k = 64;
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % k);
        temp1 = _mm256_andnot_si256(mask[6], A[l]);
        temp2 = _mm256_andnot_si256(mask[6], A[l + k]);
        temp2 = _mm256_srli_si256(temp2, 8);
        temp = _mm256_or_si256(temp1, temp2);

        temp1 = _mm256_and_si256(mask[6], A[l + k]);
        temp2 = _mm256_and_si256(mask[6], A[l]);
        temp2 = _mm256_slli_si256(temp2, 8);
        A[l + k] = _mm256_or_si256(temp1, temp2);
        A[l] = temp;
    }
}

