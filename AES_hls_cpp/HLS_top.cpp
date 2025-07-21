#include <ap_int.h>

typedef ap_uint<8> byte;
typedef ap_uint<32> word;

// AES core function declaration
void Cipher(byte in[16], byte out[16], const word w[]);

// Minimal top-level wrapper
extern "C" {
void aes_top(byte in[16], byte out[16], const word w[44]) {
#pragma HLS INTERFACE mode=s_axilite port=return
#pragma HLS INTERFACE mode=s_axilite port=in
#pragma HLS INTERFACE mode=s_axilite port=out
#pragma HLS INTERFACE mode=s_axilite port=w
    // No pragmas for optimization � basic interface
    Cipher(in, out, w); // AES-128 = 10 rounds
}
}
