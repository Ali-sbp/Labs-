#include <iostream>
#include "BaseFile.hpp"
#include <cstring>
using namespace std;

int main() {
   
    //2. test 
    Base32File f("../tests/test32.txt", "w+");
    if (!f.is_open()) {
        cout << "Failed to open file" << endl;
        return 1;
    }

    const char* data = "Hello";
    size_t written = f.write(data, strlen(data));
    cout << "Wrote " << written << " bytes (encoded)" << endl;

    f.seek(0);

    char buffer[20] = {0};
    size_t read = f.read(buffer, 20);
    cout << "Read " << read << " bytes: " << buffer << endl;

    cout << "Position: " << f.tell() << endl;

    Base32File f2("../tests/test32_custom.txt", "w+", "0123456789abcdefghijABCDEFGHIJ+-");
    const char* data2 = "Test";
    f2.write(data2, strlen(data2));
    f2.seek(0);
    char buffer2[20] = {0};
    f2.read(buffer2, 20);
    cout << "Custom table read: " << buffer2 <<endl;

//2.3
    {
        cout << "Creating RleFile object" <<endl;
    {
        RleFile rle("../tests/test_rle.txt", "w");
    }
        cout << "RleFile scope ended" <<endl;

        cout << "Creating Base32File object" <<endl;
    {
        Base32File base32("../tests/test_base32.txt", "w");
    }
        cout << "Base32File scope ended" << endl;
    }
    
//2.4
{
    BaseFile bf("../tests/base.txt", "w");
    Base32File b32f("../tests/base32.txt", "w");
    RleFile rf("../tests/rle.txt", "w");

    // same code for bf
    int n = 123456;
    if (n < 0) { 
        const char minus = '-';
        bf.write(&minus, 1); 
        n = -n;
    }
    char digits[10]; // buffer for digits
    int len = 0;
    while (n > 0) {
        digits[len++] = '0' + (n % 10); // extract digits right to left
        n /= 10;
    }
    for (int i = len - 1; i >= 0; i--) {
        bf.write(&digits[i], 1); // write digits left to right
    }

    // same code for b32f
    n = 123456;
    if (n < 0) { 
        const char minus = '-';
        b32f.write(&minus, 1); 
        n = -n;
    }
    len = 0;
    while (n > 0) {
        digits[len++] = '0' + (n % 10);
        n /= 10;
    }
    for (int i = len - 1; i >= 0; i--) {
        b32f.write(&digits[i], 1);
    }

    // same code for rf
    n = 11123456;
    if (n < 0) { 
        const char minus = '-';
        rf.write(&minus, 1); 
        n = -n;
    }
    len = 0;
    while (n > 0) {
        digits[len++] = '0' + (n % 10);
        n /= 10;
    }
    for (int i = len - 1; i >= 0; i--) {
        rf.write(&digits[i], 1);
    }
}
//2.5
{
    BaseFile bf("../tests/base25.txt", "w");
    Base32File b32f("../tests/base3225.txt", "w");
    RleFile rf("../tests/rle25.txt", "w");

    write_int(bf, 123456);
    write_int(b32f, 123456);
    write_int(rf, 11123456);
}
//3.2
{
    Base32File2 b32f(new BaseFile("../tests/xxbase32.txt", "w"));
    RleFile2 rf(new Base32File("../tests/xxrle_base32.txt", "w"));
    
    write_int(b32f, 123456);
    write_int(rf, 123456);
}
//3.3
{
    IFile* writer = new Base32File2(new Base32File2(new RleFile2(new BaseFile("../tests/output33.txt", "wb"))));
    write_int(*writer, 123456); //~~> base32 ~~> base32 ~~> Rle ~~>write
    delete writer;

    // File ~~> Rle decompress ~~> base32 decode ~~> base32 decode
    IFile* reader = new Base32File2(new Base32File2(new RleFile2(new BaseFile("../tests/output33.txt", "rb"))));
    char buffer[7] = {0}; // + null terminator
    size_t bytes_read = reader->read(buffer, 6);
    cout << "\n ** \n Bytes read: " << bytes_read << ", Buffer: " << buffer <<"\n ** \n"<<endl;
    delete reader;
}
//test


return 0;
}