#include <iostream>
#include <cstring>
#include "BaseFile.hpp"

int main() {
    // Write phase
    {
        Base32File2 base32_outer(new Base32File2(new RleFile2(new BaseFile("../tests/output33.txt", "wb"))));
        write_int(base32_outer, 123456);
    }

    // Read phase
    {
        Base32File2 base32_outer(new Base32File2(new RleFile2(new BaseFile("../tests/output33.txt", "rb"))));
        char buffer[7] = {0};
        size_t bytes_read = base32_outer.read(buffer, 6);
        buffer[bytes_read] = '\0';
        std::cout << "Decoded: " << buffer << ", Bytes read: " << bytes_read << std::endl;

        if (strncmp(buffer, "123456", 6) == 0 && bytes_read == 6) {
            std::cout << "Test passed!" << std::endl;
        } else {
            std::cout << "Test failed!" << std::endl;
        }
    }
    return 0;
}