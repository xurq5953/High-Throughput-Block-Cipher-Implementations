#include <x86intrin.h>



inline __m256i SHR256n(__m256i &v, int n) {
    __m256i v1, v2;
    v1 = _mm256_srli_epi64(v, n);
    v2 = _mm256_bsrli_epi128(v, 8);
    v2 = _mm256_slli_epi64(v2, 64 - n);
    return _mm256_or_si256(v1, v2);
}

inline __m256i SHL256n(__m256i &v, int n) {
    __m256i v1, v2;
    v1 = _mm256_slli_epi64(v, n);
    v2 = _mm256_bslli_epi128(v, 8);
    v2 = _mm256_srli_epi64(v2, 64 - n);
    return _mm256_or_si256(v1, v2);
}


void transpose_simultaneously(__m256i *A) {

    int l;
    __m256i temp, temp1, temp2, mask;

    mask = _mm256_set1_epi64x(0x5555555555555555);
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % 1);

        temp1 = _mm256_and_si256(mask, A[l]);//temp1 = A[l] & masks
        temp2 = _mm256_and_si256(mask, A[l + 1]); // temp2 = A[l+k] & masks
        temp2 = SHL256n(temp2, 1);
        temp = _mm256_or_si256(temp1, temp2);

        temp1 = _mm256_andnot_si256(mask, A[l + 1]);//temp1 = A[l + k] & ~masks
        temp2 = _mm256_andnot_si256(mask, A[l]);//temp2 = A[l] & ~masks
        temp2 = SHR256n(temp2, 1);
        A[l + 1] = _mm256_or_si256(temp1, temp2);
        A[l] = temp;
    }

    mask = _mm256_set1_epi64x(0x3333333333333333);
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % 2);

        temp1 = _mm256_and_si256(mask, A[l]);//temp1 = A[l] & masks
        temp2 = _mm256_and_si256(mask, A[l + 2]); // temp2 = A[l+k] & masks
        temp2 = SHL256n(temp2, 2);
        temp = _mm256_or_si256(temp1, temp2);

        temp1 = _mm256_andnot_si256(mask, A[l + 2]);//temp1 = A[l + k] & ~masks
        temp2 = _mm256_andnot_si256(mask, A[l]);//temp2 = A[l] & ~masks
        temp2 = SHR256n(temp2, 2);
        A[l + 2] = _mm256_or_si256(temp1, temp2);
        A[l] = temp;
    }

    mask = _mm256_set1_epi64x(0x0f0f0f0f0f0f0f0f);
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % 4);

        temp1 = _mm256_and_si256(mask, A[l]);//temp1 = A[l] & masks
        temp2 = _mm256_and_si256(mask, A[l + 4]); // temp2 = A[l+k] & masks
        temp2 = SHL256n(temp2, 4);
        temp = _mm256_or_si256(temp1, temp2);

        temp1 = _mm256_andnot_si256(mask, A[l + 4]);//temp1 = A[l + k] & ~masks
        temp2 = _mm256_andnot_si256(mask, A[l]);//temp2 = A[l] & ~masks
        temp2 = SHR256n(temp2, 4);
        A[l + 4] = _mm256_or_si256(temp1, temp2);
        A[l] = temp;
    }

    mask = _mm256_set1_epi64x(0x00ff00ff00ff00ff);
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % 8);
        temp1 = _mm256_and_si256(mask, A[l]);//temp1 = A[l] & masks
        temp2 = _mm256_and_si256(mask, A[l + 8]); // temp2 = A[l+k] & masks
        temp2 = _mm256_bslli_epi128(temp2, 1);
        temp = _mm256_or_si256(temp1, temp2);

        temp1 = _mm256_andnot_si256(mask, A[l + 8]);//temp1 = A[l + k] & ~masks
        temp2 = _mm256_andnot_si256(mask, A[l]);//temp2 = A[l] & ~masks
        temp2 = _mm256_bsrli_epi128(temp2, 1);
        A[l + 8] = _mm256_or_si256(temp1, temp2);
        A[l] = temp;
    }


    mask = _mm256_set1_epi64x(0x0000ffff0000ffff);
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % 16);

        temp1 = _mm256_and_si256(mask, A[l]);//temp1 = A[l] & masks
        temp2 = _mm256_and_si256(mask, A[l + 16]); // temp2 = A[l+k] & masks
        temp2 = _mm256_bslli_epi128(temp2, 2);
        temp = _mm256_or_si256(temp1, temp2);

        temp1 = _mm256_andnot_si256(mask, A[l + 16]);//temp1 = A[l + k] & ~masks
        temp2 = _mm256_andnot_si256(mask, A[l]);//temp2 = A[l] & ~masks
        temp2 = _mm256_bsrli_epi128(temp2, 2);
        A[l + 16] = _mm256_or_si256(temp1, temp2);
        A[l] = temp;
    }

    mask = _mm256_set1_epi64x(0x00000000ffffffff);
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % 32);
        temp1 = _mm256_and_si256(mask, A[l]);//temp1 = A[l] & masks
        temp2 = _mm256_and_si256(mask, A[l + 32]); // temp2 = A[l+k] & masks
        temp2 = _mm256_bslli_epi128(temp2, 4);
        temp = _mm256_or_si256(temp1, temp2);

        temp1 = _mm256_andnot_si256(mask, A[l + 32]);//temp1 = A[l + k] & ~masks
        temp2 = _mm256_andnot_si256(mask, A[l]);//temp2 = A[l] & ~masks
        temp2 = _mm256_bsrli_epi128(temp2, 4);
        A[l + 32] = _mm256_or_si256(temp1, temp2);
        A[l] = temp;
    }

    mask = _mm256_set_epi64x(0, -1, 0, -1);
    for (int i = 0; i < 64; ++i) {
        l = 2 * i - (i % 64);

        temp1 = _mm256_and_si256(mask, A[l]);//temp1 = A[l] & masks
        temp2 = _mm256_and_si256(mask, A[l + 64]); // temp2 = A[l+k] & masks
        temp2 = _mm256_bslli_epi128(temp2, 8);
        temp = _mm256_or_si256(temp1, temp2);

        temp1 = _mm256_andnot_si256(mask, A[l + 64]);//temp1 = A[l + k] & ~masks
        temp2 = _mm256_andnot_si256(mask, A[l]);//temp2 = A[l] & ~masks
        temp2 = _mm256_bsrli_epi128(temp2, 8);
        A[l + 64] = _mm256_or_si256(temp1, temp2);
        A[l] = temp;
    }
}

