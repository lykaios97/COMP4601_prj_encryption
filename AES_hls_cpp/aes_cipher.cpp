#include <ap_int.h>
#include <hls_stream.h>
#include <stdint.h>

typedef ap_uint<8> byte;
typedef ap_uint<32> word;

#define Nb 4 // Block size in 32-bit words (4 words = 16 bytes)
#define Nk 4  // Key length in 32-bit words (AES-128)
#define Nr 10 // Number of rounds

const byte sbox[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5,
    0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0,
    0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC,
    0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A,
    0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0,
    0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B,
    0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85,
    0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5,
    0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17,
    0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88,
    0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C,
    0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9,
    0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6,
    0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E,
    0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94,
    0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68,
    0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

const byte Rcon[11] = {
    0x00, 0x01, 0x02, 0x04, 0x08,
    0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
};

// byte gmul(byte a, byte b) {
//     byte p = 0;
//     for (int i = 0; i < 8; i++) {
//     #pragma HLS PIPELINE II=1
//         if (b & 1) p ^= a;
//         bool hi_bit = (a & 0x80) != 0;
//         a <<= 1;
//         if (hi_bit) a ^= 0x1b;
//         b >>= 1;
//     }
//     return p;
// }

byte xtime(byte x) {
    return (x << 1) ^ ((x & 0x80) ? 0x1b : 0);
}

byte gmul_fast(byte x, byte coeff) {
    switch (coeff) {
        case 0x01: return x;
        case 0x02: return xtime(x);
        case 0x03: return xtime(x) ^ x;
        default: return 0;
    }
}

void SubBytes(byte state[4][4]) {
    #pragma HLS inline
    for (int r = 0; r < 4; r++) {
    #pragma HLS unroll factor=2
        for (int c = 0; c < 4; c++) {
    #pragma HLS unroll factor=2
            state[r][c] = sbox[state[r][c]];
        }
    }
}

void ShiftRows(byte state[4][4]) {
    #pragma HLS INLINE
    // if resource usage is too high, remove these array partitions
    #pragma HLS ARRAY_PARTITION variable=state complete dim=0
    #pragma HLS ARRAY_PARTITION variable=state complete dim=1
    byte temp;

    temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;

    byte t1 = state[2][0];
    byte t2 = state[2][1];
    state[2][0] = state[2][2];
    state[2][1] = state[2][3];
    state[2][2] = t1;
    state[2][3] = t2;

    temp = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = state[3][0];
    state[3][0] = temp;
}

void MixColumns(byte state[4][4]) {
    #pragma HLS ARRAY_PARTITION variable=state complete dim=0
    #pragma HLS ARRAY_PARTITION variable=state complete dim=1
    for (int c = 0; c < 4; c++) {
    #pragma HLS unroll
        byte a[4], res[4];

        a[0] = state[0][c];
        a[1] = state[1][c];
        a[2] = state[2][c];
        a[3] = state[3][c];

        res[0] = gmul_fast(a[0], 0x02) ^ gmul_fast(a[1], 0x03) ^ a[2] ^ a[3];
        res[1] = a[0] ^ gmul_fast(a[1], 0x02) ^ gmul_fast(a[2], 0x03) ^ a[3];
        res[2] = a[0] ^ a[1] ^ gmul_fast(a[2], 0x02) ^ gmul_fast(a[3], 0x03);
        res[3] = gmul_fast(a[0], 0x03) ^ a[1] ^ a[2] ^ gmul_fast(a[3], 0x02);        

        a[0] = state[0][c];
        a[1] = state[1][c];
        a[2] = state[2][c];
        a[3] = state[3][c];
    }
}

void AddRoundKey(byte state[4][4], const word roundKey[4]) {
    #pragma HLS INLINE
    #pragma HLS ARRAY_PARTITION variable=state complete dim=0
    #pragma HLS ARRAY_PARTITION variable=state complete dim=1

    for (int j = 0; j < 4; j++) {
    #pragma HLS UNROLL
        for (int i = 0; i < 4; i++) {
    #pragma HLS UNROLL
            ap_uint<8> k = (roundKey[j] >> (24 - 8 * i)) & 0xFF;
            state[i][j] ^= byte(k);
        }
    }
}

word RotWord(word w) {
    return (w << 8) | (w >> 24);
}

word SubWord(word w) {
    word result;
    result.range(31, 24) = sbox[w.range(31, 24)];
    result.range(23, 16) = sbox[w.range(23, 16)];
    result.range(15, 8)  = sbox[w.range(15, 8)];
    result.range(7, 0)   = sbox[w.range(7, 0)];
    return result;
}

void KeyExpansion(const byte key[16], word w[44]) {
    for (int i = 0; i < Nk; i++) {
    #pragma HLS unroll
        w[i] = (word(key[4 * i]) << 24) |
               (word(key[4 * i + 1]) << 16) |
               (word(key[4 * i + 2]) << 8) |
               word(key[4 * i + 3]);
    }

    for (int i = Nk; i < Nb * (Nr + 1); i++) {
    #pragma HLS unroll
        word temp = w[i - 1];
        if (i % Nk == 0)
            temp = SubWord(RotWord(temp)) ^ (word(Rcon[i / Nk]) << 24);
        w[i] = w[i - Nk] ^ temp;
    }
}

void Cipher(byte in[16], byte out[16], const word w[]) {
    byte state[4][4];


    for (int i = 0; i < 16; i++) {
    #pragma HLS unroll
        state[i % 4][i / 4] = in[i];
    }

    AddRoundKey(state, &w[0]);

    #pragma PIPELINE II = 1
    for (int round = 1; round < Nr; round++) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, &w[round * Nb]);
    }

    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, &w[Nr * Nb]);

    for (int i = 0; i < 16; i++)
    #pragma HLS unroll
        out[i] = state[i % 4][i / 4];
}
