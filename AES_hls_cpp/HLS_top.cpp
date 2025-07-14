#include <ap_int.h>

typedef ap_uint<8> byte;
typedef ap_uint<32> word;

void Cipher(byte in[16], byte out[16], const word w[], int Nr);

// Top-level function for HLS
extern "C" {
void aes_top(byte in[16], byte out[16], const word w[44]) {
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL
#pragma HLS INTERFACE s_axilite port=w      bundle=CTRL
#pragma HLS INTERFACE s_axilite port=out    bundle=CTRL
#pragma HLS INTERFACE s_axilite port=in     bundle=CTRL

    Cipher(in, out, w, 10); // AES-128
}
}
