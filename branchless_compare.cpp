#include <limits>

template<size_t bit>
constexpr int compare_bitwise(int a, int b) {
    int a_bit = (a >> bit) & 1;
    int b_bit = (b >> bit) & 1;

    a &= ~(1 << bit);
    b &= ~(1 << bit);

    int current_bit_difference = a_bit - b_bit;
    int absolute_current_bit_difference = current_bit_difference & 1;
    return current_bit_difference + (1 - absolute_current_bit_difference) * compare_bitwise<bit - 1>(a, b);
}

template<>
constexpr int compare_bitwise<0>(int a, int b) {
    return a - b;
}

constexpr int compare(int a, int b) {
    constexpr size_t int_sz = sizeof(int) * 8 - 1;
    int a_sign_bit = (a >> int_sz) & 1;
    int b_sign_bit = (b >> int_sz) & 1;

    a &= 0x7FFFFFFF;
    b &= 0x7FFFFFFF;
    int current_bit_difference = b_sign_bit - a_sign_bit;
    int absolute_current_bit_difference = current_bit_difference & 1;

    return current_bit_difference + (1 - absolute_current_bit_difference) * compare_bitwise<int_sz>(a, b);
}

int main() {
    static_assert(compare(1, 2) == -1);
    static_assert(compare(2, 1) == 1);
    static_assert(compare(-1, 1) == -1); 
    static_assert(compare(-100, -101) == 1);
    static_assert(compare(-100, -100) == 0);
    static_assert(compare(std::numeric_limits<int>::min(), std::numeric_limits<int>::min() + 1) == -1);
    static_assert(compare(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()) == -1);
    static_assert(compare(std::numeric_limits<int>::min(), -1) == -1);
    static_assert(compare(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()) == 0);
    static_assert(compare(std::numeric_limits<int>::max(), std::numeric_limits<int>::min()) == 1);
    static_assert(compare(std::numeric_limits<int>::max(), -1) == 1);
    return 0;
}