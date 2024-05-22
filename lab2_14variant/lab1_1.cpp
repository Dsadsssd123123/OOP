#include <iostream>

int main()
{
    int a, b, c, d;
    std::cout << "Введіть значення a, b, c, d: ";
    std::cin >> a >> b >> c >> d;

    int result = (((d << 4) + (d << 3) + (d << 1)) + ((a << 3) + (a << 2))) >> 11; // (d*15 + 12*a) / 2048
    result *= b;                                                                   // result = result * b
    result = (result << 11) - (c << 7) + (d << 4);                                 // 2049 * b * ((d*15 + 12*a)/2048) - c*100 + d*14

    std::cout << "Результат: " << result << std::endl;

    return 0;
}
