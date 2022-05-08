#include <iostream>
#include <nmmintrin.h>

static const int CHARS_PER_128_BIT_REGISTER = 16;
static const int SSE_BITMASK[CHARS_PER_128_BIT_REGISTER] = {
  1 << 0,
  1 << 1,
  1 << 2,
  1 << 3,
  1 << 4,
  1 << 5,
  1 << 6,
  1 << 7,
  1 << 8,
  1 << 9,
  1 << 10,
  1 << 11,
  1 << 12,
  1 << 13,
  1 << 14,
  1 << 15,
};

static int sse42_strchr(const char* s, int c) {

    assert(c >= 0);
    assert(c < 256);

    const __m128i set = _mm_setr_epi8(c, 0, 0, 0, 0, 0, 0, 0, 
                                      0, 0, 0, 0, 0, 0, 0, 0);

    const uint8_t mode =
        _SIDD_UBYTE_OPS |
        _SIDD_CMP_EQUAL_ANY |
        _SIDD_LEAST_SIGNIFICANT;
        
    __m128i* mem = reinterpret_cast<__m128i*>(const_cast<char*>(s));
    const __m128i chunk = _mm_loadu_si128(mem);
    int idx = _mm_cmpistri(set, chunk, mode);
    std::cout << "idx:" << idx << std::endl;
    return idx;
}

int main() {
    std::string str = "bb\nccc\nddd";
    char c = '\n';
    int idx = sse42_strchr(str.c_str(), c);
    sse42_strchr(const_cast<char*>(str.c_str()) + idx + 1, c);
}

