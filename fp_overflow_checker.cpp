#include <iostream>
#include <bitset>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <cstdint>

using namespace std;

// Reinterpret a float's bytes as a uint32_t)
uint32_t floatToRawBits(float f) {
    uint32_t bits;
    memcpy(&bits, &f, sizeof(float));
    return bits;
}

// Reconstruct a float from raw uint32_t bit pattern
float rawBitsToFloat(uint32_t bits) {
    float f;
    memcpy(&f, &bits, sizeof(float));
    return f;
}

// Print IEEE 754 formatted bit string
void printIEEE(float f) {
    uint32_t bits = floatToRawBits(f);

    bitset<1>  sign((bits >> 31) & 0x1);
    bitset<8>  exponent((bits >> 23) & 0xFF);
    bitset<23> fraction(bits & 0x7FFFFF);

    cout << sign << " " << exponent << " " << fraction;
}

int main(int argc, char* argv[]) {

    // Command-line argument validation 
    if (argc != 3) {
        cout << "usage:" << endl;
        cout << "\t./fp_overflow_checker loop_bound loop_counter" << endl;
        cout << endl;
        cout << "\tloop_bound is a positive floating-point value" << endl;
        cout << "\tloop_counter is a positive floating-point value" << endl;
        return 1;
    }

    // Parse inputs
    float loop_bound   = static_cast<float>(atof(argv[1]));
    float loop_counter = static_cast<float>(atof(argv[2]));

    // Print IEEE representations
    cout << "Loop bound:    ";
    printIEEE(loop_bound);
    cout << "\n";

    cout << "Loop counter:  ";
    printIEEE(loop_counter);
    cout << "\n\n";

    // Extract biased exponents 
    uint32_t boundBits   = floatToRawBits(loop_bound);
    uint32_t counterBits = floatToRawBits(loop_counter);

    int expBound   = static_cast<int>((boundBits   >> 23) & 0xFF);
    int expCounter = static_cast<int>((counterBits >> 23) & 0xFF);

    // Overflow check 
    int expDiff = expBound - expCounter;

    if (expDiff >= 24) {
        uint32_t threshExp  = static_cast<uint32_t>(expCounter + 24);
        uint32_t threshBits = (threshExp << 23);  
        float threshold     = rawBitsToFloat(threshBits);

        cout << "Warning: Possible overflow!" << endl;
        cout << "Overflow threshold:" << endl;
        cout << "\t" << scientific << setprecision(5) << threshold << "\n";
        cout << "\t";
        printIEEE(threshold);
        cout << "\n";
    } else {
        cout << "There is no overflow!" << endl;
    }

    return 0;
}
