#include <iostream>
#include <iomanip>
#include <cstring>
#include "ap_int.h"

typedef ap_uint<8> byte;
typedef ap_uint<32> word;

// AES function prototypes (from your AES source)
void KeyExpansion(const byte key[16], word w[44]);
void Cipher(byte in[16], byte out[16], const word w[]);

// Test vector: AES-128 example (FIPS-197 Appendix B)
const byte test_input[16] = {
    0x32, 0x43, 0xf6, 0xa8,
    0x88, 0x5a, 0x30, 0x8d,
    0x31, 0x31, 0x98, 0xa2,
    0xe0, 0x37, 0x07, 0x34
};

const byte test_key[16] = {
    0x2b, 0x7e, 0x15, 0x16,
    0x28, 0xae, 0xd2, 0xa6,
    0xab, 0xf7, 0x15, 0x88,
    0x09, 0xcf, 0x4f, 0x3c
};

const byte expected_output[16] = {
    0x39, 0x25, 0x84, 0x1d,
    0x02, 0xdc, 0x09, 0xfb,
    0xdc, 0x11, 0x85, 0x97,
    0x19, 0x6a, 0x0b, 0x32
};

int main() {
    byte output[16];
    word round_keys[44];

    // Generate round keys
    KeyExpansion(test_key, round_keys);

    // Run AES cipher
    Cipher((byte *)test_input, output, round_keys);

    // Output comparison
    bool pass = true;
    std::cout << "Encrypted output:\n";
    for (int i = 0; i < 16; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << (int)output[i] << " ";
        if (output[i] != expected_output[i]) {
            pass = false;
        }
    }
    std::cout << "\n\nTest " << (pass ? "PASSED âœ…" : "FAILED â�Œ") << std::endl;

    return 0;
}
