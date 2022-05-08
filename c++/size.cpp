#include <iostream>

int main() {
    char str[10] = "abcdefg";
    char *addr = str + 3;
    std::cout << "size:" << strlen(addr) << std::endl;
    int t = 129;
    std::cout << "result:" << t / 16 << ",result2:" << (t >> 4) << std::endl;
}
