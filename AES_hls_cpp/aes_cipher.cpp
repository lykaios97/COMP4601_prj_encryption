#include <ap_int.h>
#include <hls_stream.h>
#include <stdint.h>

typedef ap_uint<8> byte;
typedef ap_uint<32> word;

#define Nb 4 // Block size in 32-bit words (4 words = 16 bytes)

// S-box table (partial, for brevity – you must populate the full table)
const byte sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, /* ... */ 0x16
};

byte gmul(byte a, byte b) {
#pragma HLS INLINE
    byte p = 0;
    for (int i = 0; i < 8; i++) {
        if (b & 1) p ^= a;
        bool hi_bit = (a & 0x80) != 0;
        a <<= 1;
        if (hi_bit) a ^= 0x1b;
        b >>= 1;
    }
    return p;
}

void SubBytes(byte state[4][4]) {
#pragma HLS INLINE
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
#pragma HLS UNROLL
            state[r][c] = sbox[state[r][c]];
}

void ShiftRows(byte state[4][4]) {
#pragma HLS INLINE
    byte tmp[4];

    // Row 1: shift left by 1
    for (int c = 0; c < 4; c++) tmp[c] = state[1][(c + 1) % 4];
    for (int c = 0; c < 4; c++) state[1][c] = tmp[c];

    // Row 2: shift left by 2
    for (int c = 0; c < 4; c++) tmp[c] = state[2][(c + 2) % 4];
    for (int c = 0; c < 4; c++) state[2][c] = tmp[c];

    // Row 3: shift left by 3
    for (int c = 0; c < 4; c++) tmp[c] = state[3][(c + 3) % 4];
    for (int c = 0; c < 4; c++) state[3][c] = tmp[c];
}

void MixColumns(byte state[4][4]) {
#pragma HLS INLINE
    for (int c = 0; c < 4; c++) {
        byte a[4], res[4];
        for (int r = 0; r < 4; r++) a[r] = state[r][c];

        res[0] = gmul(0x02, a[0]) ^ gmul(0x03, a[1]) ^ a[2] ^ a[3];
        res[1] = a[0] ^ gmul(0x02, a[1]) ^ gmul(0x03, a[2]) ^ a[3];
        res[2] = a[0] ^ a[1] ^ gmul(0x02, a[2]) ^ gmul(0x03, a[3]);
        res[3] = gmul(0x03, a[0]) ^ a[1] ^ a[2] ^ gmul(0x02, a[3]);

        for (int r = 0; r < 4; r++) state[r][c] = res[r];
    }
}

void AddRoundKey(byte state[4][4], const word roundKey[4]) {
#pragma HLS INLINE
    for (int c = 0; c < 4; c++) {
        word keyWord = roundKey[c];
        for (int r = 0; r < 4; r++)
            state[r][c] ^= (keyWord >> (24 - 8 * r)) & 0xFF;
    }
}

void Cipher(byte in[16], byte out[16], const word w[], int Nr) {
#pragma HLS INLINE off

    byte state[4][4];

    // Load input into state array
    for (int i = 0; i < 16; i++)
        state[i % 4][i / 4] = in[i];

    AddRoundKey(state, &w[0]);

    for (int round = 1; round < Nr; round++) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, &w[round * Nb]);
    }

    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, &w[Nr * Nb]);

    // Copy state to output
    for (int i = 0; i < 16; i++)
        out[i] = state[i % 4][i / 4];
}
