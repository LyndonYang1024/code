#include <iostream>
#include <nmmintrin.h>

int main() {
    const char *str = "aaa\nbbb\nccc";
    int length = strlen(str);
    std::cout << "str:" << str << std::endl;
    __m128i newline_char = _mm_set1_epi8('\n');
    __m128i data = _mm_loadu_si128((__m128i *)str);
    int mask = _mm_movemask_epi8(_mm_cmpeq_epi8(data, newline_char));
    if (mask != 0)
        return ffs(mask);
    int index = 16 - ((size_t)str & 15);
    for (; index < length; index += 16) {
        data = _mm_load_si128((__m128i *)(str + index));
        mask = _mm_movemask_epi8(_mm_cmpeq_epi8(data, newline_char));
        if (mask != 0) {
          std::cout << "index:" << index << ",ffs:"<< ffs(mask) << std::endl;  
          return index + ffs(mask);
        }
    }
}
