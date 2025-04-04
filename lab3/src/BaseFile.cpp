#include <cstring>
#include <string>
#include "BaseFile.hpp"
#include <iostream>
using namespace std;

BaseFile::BaseFile() : file(nullptr), owns_file(false){
    cout << "BaseFile default constructor called" <<endl;
}

BaseFile::BaseFile(const char* path, const char* mode) : owns_file(true) {
    file = fopen(path,mode);
    cout << "BaseFile path constructor called" <<endl;
}

BaseFile::BaseFile(FILE* f) : file(f) , owns_file(false) {
    cout << "BaseFile FILE* constructor called" <<endl;
}

BaseFile::~BaseFile(){
    if (owns_file && file !=nullptr) {
        fclose(file);
        cout << "BaseFile destructor called" <<endl;
    }
}

//

bool BaseFile::is_open() const{return file!= nullptr && !ferror(file);}

bool BaseFile::can_read() const {
    if ( !is_open()) return false; 
    return true;
}

bool BaseFile::can_write() const {
    if ( !is_open()) return false; 
    return true;
}

//
size_t BaseFile::write_raw(const void* buf,size_t n_bytes ){
    if ( !is_open()) return 0;
    return fwrite(buf,1,n_bytes,file);
}
size_t BaseFile::read_raw(void* buf, size_t max_bytes){
    if ( !is_open()) return 0;
    return fread(buf, 1, max_bytes, file);
}
long BaseFile::tell() const {
    if (!is_open()) return -1;
    return ftell(file);
}

bool BaseFile::seek(long offset) {
    if (!is_open()) return false;
    return fseek(file, offset, SEEK_SET) == 0; // ~~SEEK_SET for absolute offset~~//
}

size_t BaseFile::write(const void* buf, size_t n_bytes) {
    return write_raw(buf, n_bytes);
}

size_t BaseFile::read(void* buf, size_t max_bytes) {
    return read_raw(buf, max_bytes);
}
/*int Base32File::encoded32_size(int rsize) {
    int t = rsize * 8;
    return t + (5 - t % 5) % 5; // bits, padded to multiple of 5
}*/
int Base32File::encoded32_size(int rsize) {
    return (rsize * 8 + 4) / 5; // Characters, not bits
}

int Base32File::decoded32_size(int esize) {
    int t = esize * 5;
    return t / 8; // bytes, dropping padding
}

size_t Base32File::encode32(const char* raw_data, int raw_size, char* dst) {
    if (!raw_data || raw_size <= 0 || !dst) return 0;

    int dataLength = raw_size * 8;
    int paddedLength = dataLength + (5 - (dataLength % 5)) % 5;
    int* binaryData = new int[paddedLength];
    int counter = 0;

    for (int i = 0; i < raw_size; i++) {
        char c = raw_data[i];
        for (int j = 7; j >= 0; j--) {
            binaryData[counter++] = (c >> j) & 1;
        }
    }
    for (int i = dataLength; i < paddedLength; i++) {
        binaryData[i] = 0;
    }

    int resultSize = paddedLength / 5;
    int* encodedValues = new int[resultSize];
    for (int i = 0; i < paddedLength; i += 5) {
        int currentValue = 0;
        for (int j = 0; j < 5; j++) {
            currentValue = (currentValue << 1) | binaryData[i + j];
        }
        encodedValues[i / 5] = currentValue;
    }

    for (int i = 0; i < resultSize; i++) {
        if (encodedValues[i] >= 0 && encodedValues[i] < 32) {
            dst[i] = encoding_map[encodedValues[i]];
        } else {
            dst[i] = '?';
        }
    }

    delete[] binaryData;
    delete[] encodedValues;
    return resultSize;
}

size_t Base32File::decode32(const char* encoded_data, int encoded_size, char* dst) {
    if (!encoded_data || encoded_size <= 0 || !dst) return 0;

    int totalBits = encoded_size * 5;
    int* binaryData = new int[totalBits];
    int bitIndex = 0;

    for (int i = 0; i < encoded_size; i++) {
        char symbol = encoded_data[i];
        int val = -1;
        for (int j = 0; j < 32; j++) {
            if (encoding_map[j] == symbol) {
                val = j;
                break;
            }
        }
        if (val == -1) {
            delete[] binaryData;
            return 0; // Invalid char
        }
        for (int j = 4; j >= 0; j--) {
            binaryData[bitIndex++] = (val >> j) & 1;
        }
    }

    int byteIndex = 0;
    for (int i = 0; i < totalBits; i += 8) {
        int byte = 0;
        for (int j = 0; j < 8 && i + j < totalBits; j++) {
            byte = (byte << 1) | binaryData[i + j];
        }
        dst[byteIndex++] = static_cast<char>(byte);
    }

    delete[] binaryData;
    return byteIndex;
}

Base32File::Base32File(const char* path, const char* mode, const char* table)
    : BaseFile(path, mode) {
    strncpy(encoding_map, table, 32);
    cout << "Base32File path constructor called: " << path << ", mode: " << mode <<endl;
}

Base32File::Base32File(FILE* f, const char* table)
    : BaseFile(f) {
    strncpy(encoding_map, table, 32);
    cout << "Base32File FILE* constructor called" <<endl;
}
Base32File::~Base32File() {
    cout << "Base32File destructor called" <<endl;
}

size_t Base32File::write(const void* buf, size_t n_bytes) {
    if (!is_open()) return 0;
    char* raw_data = static_cast<char*>(const_cast<void*>(buf));
    size_t encoded_size = (n_bytes * 8 + 4) / 5; 
    char* encoded = new char[encoded_size + 1]; // NT
    size_t written = encode32(raw_data, n_bytes, encoded);
    size_t bytes_written = write_raw(encoded, written);
    delete[] encoded;
    return bytes_written;
}

size_t Base32File::read(void* buf, size_t max_bytes) {
    if (!is_open()) return 0;
    size_t encoded_max = (max_bytes * 8 + 4) / 5; // Approx encoded size
    char* encoded = new char[encoded_max + 1];
    size_t bytes_read = read_raw(encoded, encoded_max);
    size_t decoded = decode32(encoded, bytes_read, static_cast<char*>(buf));
    delete[] encoded;
    return decoded;
}
RleFile::RleFile(const char* path, const char* mode) : BaseFile(path, mode) {
    cout << "RleFile path constructor called: " << path << ", mode: " << mode <<endl;
};
RleFile::RleFile(FILE* f) : BaseFile(f) {
    cout << "RleFile FILE* constructor called" <<endl;
}
RleFile::~RleFile() {
    cout << "RleFile destructor called" <<endl;
}

size_t RleFile::compress_rle(const char* raw_data, size_t raw_size, char* dst){
    if (!raw_data || raw_size == 0 || !dst) return 0;
    size_t dst_pos = 0;
    char current = raw_data[0];
    unsigned char count = 1; //unsigned char to be able to make it to 255 instead of 128
    for(int i=1; i<raw_size; i++){
        if(current==raw_data[i] && count < 255) {
            count++;
        }
    else{
        dst[dst_pos]=count;
        dst[dst_pos + 1]= current;
        dst_pos += 2;
        current = raw_data[i];
        count=1;
    }
}
    dst[dst_pos]=count;
    dst[dst_pos +1]=current;
    dst_pos+=2;
return dst_pos;
}

size_t RleFile::decompress_rle(const char* compressed_data, size_t compressed_size, char* dst){
    if (!compressed_data || compressed_size == 0 || !dst) return 0;
    if (compressed_size % 2 != 0){
        cout<<"malformed compressed data"<<endl;
        return 0;
    }
    size_t dst_pos=0;
    unsigned char count=0;
    for(int i=0; i<compressed_size; i+=2){
        count= static_cast<unsigned char>(compressed_data[i]); //0-255
        for(unsigned char  j=0; j<count;j++){
            dst[dst_pos + j]=compressed_data[i+1];
        }
        dst_pos += count;
    }
return dst_pos;
}
size_t RleFile::write(const void* buf, size_t n_bytes){
    if (!is_open()) return 0;

    const char* raw_data = static_cast<const char*>(buf);
    char* compressed = new char[2 * n_bytes];
    
    size_t compressed_size = compress_rle(raw_data, n_bytes, compressed);
    size_t bytes_written = write_raw(compressed, compressed_size);
    
    delete[] compressed;
    
    return bytes_written;
}
size_t RleFile::read(void* buf, size_t max_bytes) {
    if (!is_open()) return 0;
    char* output = static_cast<char*>(buf);
    size_t max_compressed_size = 2 * max_bytes;
    char* compressed = new char[max_compressed_size];
    size_t bytes_read = read_raw(compressed, max_compressed_size);
    if (bytes_read == 0) {
        delete[] compressed;
        return 0;
    }
    if (bytes_read % 2 != 0) {
        delete[] compressed;
        return 0;
    }
    size_t decompressed_size = decompress_rle(compressed, bytes_read, output);
    delete[] compressed;
    return (decompressed_size > max_bytes) ? max_bytes : decompressed_size;
}

//2.5
/*void write_int(BaseFile& file, int n) {
    if (n < 0) {
        const char minus = '-';
        file.write(&minus, 1);
        n = -n;
    }
    char digits[10];
    int len = 0;
    while (n > 0) {
        digits[len++] = '0' + (n % 10);
        n /= 10;
    }
    for (int i = len - 1; i >= 0; i--) {
        file.write(&digits[i], 1);
    }
}
*/

//3.1 
void write_int(IFile& file, int n) {
    if (n < 0) {
        const char minus = '-';
        file.write(&minus, 1);
        n = -n;
    }
    char digits[10];
    int len = 0;
    while (n > 0) {
        digits[len++] = '0' + (n % 10);
        n /= 10;
    }
    char buffer[10];
    for (int i = 0; i < len; i++) {
        buffer[i] = digits[len - 1 - i];
    }
    file.write(buffer, len);
}

//3.2
Base32File2::Base32File2(IFile* target, const char* table) : target(target) {
    strncpy(encoding_map, table, 32);
}

Base32File2::~Base32File2() {
    cout<<"Base32File2 Des Called"<<endl;
    delete target; //clean up owned IFile*
}

bool Base32File2::can_read() const {
    return target->can_read();
}

bool Base32File2::can_write() const {
    return target->can_write();
}

size_t Base32File2::write(const void* buf, size_t n_bytes) {
    char* raw_data = static_cast<char*>(const_cast<void*>(buf));
    size_t encoded_size = (n_bytes * 8 + 4) / 5; // Correct chars
    char* encoded = new char[encoded_size];
    size_t written = encode32(raw_data, n_bytes, encoded);
    std::cout << "Base32 encoded: " << std::string(encoded, written) << ", Size: " << written << endl;
    size_t bytes_written = target->write(encoded, written);
    delete[] encoded;
    return bytes_written;
}

size_t Base32File2::read(void* buf, size_t max_bytes) {
    size_t encoded_max = (max_bytes * 8 + 4) / 5;
    char* encoded = new char[encoded_max + 1];
    size_t bytes_read = target->read(encoded, encoded_max);
    encoded[bytes_read] = '\0'; // ~~~~~~~~~~~>> reads 1 extra byte, causes overflow
    std::cout << "Base32 read: " << std::string(encoded, bytes_read) << ", Bytes: " << bytes_read << std::endl;
    size_t decoded = decode32(encoded, bytes_read, static_cast<char*>(buf));
    std::cout << "Base32 decoded: " << std::string((char*)buf, decoded) << ", Size: " << decoded << std::endl;
    delete[] encoded;
    return decoded;
}
int Base32File2::encoded32_size(int rsize) {
    return (rsize * 8 + 4) / 5; // ~~~second heap overflow
}

int Base32File2::decoded32_size(int esize) {
    int t = esize * 5;
    return t / 8; // bytes, dropping padding (same logic)
}

size_t Base32File2::encode32(const char* raw_data, int raw_size, char* dst) {
    if (!raw_data || raw_size <= 0 || !dst) return 0;

    int dataLength = raw_size * 8;
    int paddedLength = dataLength + (5 - (dataLength % 5)) % 5;
    int* binaryData = new int[paddedLength];
    int counter = 0;

    for (int i = 0; i < raw_size; i++) {
        char c = raw_data[i];
        for (int j = 7; j >= 0; j--) {
            binaryData[counter++] = (c >> j) & 1;
        }
    }
    for (int i = dataLength; i < paddedLength; i++) {
        binaryData[i] = 0;
    }

    int resultSize = paddedLength / 5;
    int* encodedValues = new int[resultSize];
    for (int i = 0; i < paddedLength; i += 5) {
        int currentValue = 0;
        for (int j = 0; j < 5; j++) {
            currentValue = (currentValue << 1) | binaryData[i + j];
        }
        encodedValues[i / 5] = currentValue;
    }

    for (int i = 0; i < resultSize; i++) {
        if (encodedValues[i] >= 0 && encodedValues[i] < 32) {
            dst[i] = encoding_map[encodedValues[i]];
        } else {
            dst[i] = '?';
        }
    }

    delete[] binaryData;
    delete[] encodedValues;
    return resultSize;
}
/*size_t Base32File2::encode32(const char* raw_data, int raw_size, char* dst) {
    if (!raw_data || raw_size <= 0 || !dst) return 0;
    int bits = raw_size * 8;
    int chars = (bits + 4) / 5 > 8 ? 8 : (bits + 4) / 5; // Cap at 8
    int usable_bits = chars * 5;
    char* binaryData = new char[usable_bits];
    int bit_pos = 0;

    for (int i = 0; i < raw_size; i++) {
        char c = raw_data[i];
        for (int j = 7; j >= 0 && bit_pos < usable_bits; j--) {
            binaryData[bit_pos++] = (c >> j) & 1;
        }
    }
    while (bit_pos < usable_bits) binaryData[bit_pos++] = 0;

    for (int i = 0; i < chars; i++) {
        int value = 0;
        for (int j = 0; j < 5; j++) {
            value = (value << 1) | binaryData[i * 5 + j];
        }
        dst[i] = encoding_map[value];
    }
    delete[] binaryData;
    return chars;
}
*/
size_t Base32File2::decode32(const char* encoded_data, int encoded_size, char* dst) {
    if (!encoded_data || encoded_size <= 0 || !dst) return 0;

    int totalBits = encoded_size * 5;
    int* binaryData = new int[totalBits];
    int bitIndex = 0;

    for (int i = 0; i < encoded_size; i++) {
        char symbol = encoded_data[i];
        int val = -1;
        for (int j = 0; j < 32; j++) {
            if (encoding_map[j] == symbol) {
                val = j;
                break;
            }
        }
        if (val == -1) {
            std::cout << "Invalid Base32 char at " << i << ": " << symbol << std::endl; // ~~~~debug print
            delete[] binaryData;
            return 0; // Invalid char
        }
        for (int j = 4; j >= 0; j--) {
            binaryData[bitIndex++] = (val >> j) & 1;
        }
    }
    std::cout << "Base32 bits decoded: " << bitIndex << std::endl;// ~~~~~> debug print 
    int byteIndex = 0;
    for (int i = 0; i < totalBits; i += 8) {
        int byte = 0;
        for (int j = 0; j < 8 && i + j < totalBits; j++) {
            byte = (byte << 1) | binaryData[i + j];
        }
        dst[byteIndex++] = static_cast<char>(byte);
    }

    delete[] binaryData;
    return byteIndex;
}
/*size_t Base32File2::decode32(const char* encoded_data, int encoded_size, char* dst) {
    if (!encoded_data || encoded_size <= 0 || !dst) return 0;
    int totalBits = encoded_size * 5;
    int bytes_out = (totalBits + 7) / 8;
    int* binaryData = new int[totalBits];
    int bitIndex = 0;

    for (int i = 0; i < encoded_size; i++) {
        char symbol = encoded_data[i];
        int val = -1;
        for (int j = 0; j < 32; j++) {
            if (encoding_map[j] == symbol) {
                val = j;
                break;
            }
        }
        if (val == -1) {
            std::cout << "Invalid Base32 char at " << i << ": " << (int)symbol << std::endl;
            delete[] binaryData;
            return 0;
        }
        for (int j = 4; j >= 0; j--) {
            binaryData[bitIndex++] = (val >> j) & 1;
        }
    }
    std::cout << "Base32 bits decoded: " << bitIndex << std::endl;

    for (int i = 0; i < bytes_out; i++) {
        int byte = 0;
        for (int j = 0; j < 8 && (i * 8 + j) < totalBits; j++) {
            byte = (byte << 1) | binaryData[i * 8 + j];
        }
        dst[i] = static_cast<char>(byte);
    }

    delete[] binaryData;
    return bytes_out;
}*/
RleFile2::RleFile2(IFile* target) : target(target) {}

RleFile2::~RleFile2() {
    cout<<"RleFile2 Des Called"<<endl;
    delete target; //clean up owned IFile*
}

bool RleFile2::can_read() const {
    return target->can_read();
}

bool RleFile2::can_write() const {
    return target->can_write();
}

size_t RleFile2::write(const void* buf, size_t n_bytes) {
    const char* raw_data = static_cast<const char*>(buf);
    char* compressed = new char[2 * n_bytes];
    size_t compressed_size = compress_rle(raw_data, n_bytes, compressed);
    std::cout << "RLE compressed size: " << compressed_size << std::endl;//~~~>debug print
    size_t bytes_written = target->write(compressed, compressed_size); //~~>delegate
    delete[] compressed;
    return bytes_written;
}

size_t RleFile2::read(void* buf, size_t max_bytes) {
    char* compressed = new char[2 * max_bytes];
    size_t bytes_read = target->read(compressed, 2 * max_bytes);
    if (bytes_read == 0 || bytes_read % 2 != 0) {
        delete[] compressed;
        return 0;
    }
    char* temp = new char[2 * max_bytes];
    size_t decompressed_size = decompress_rle(compressed, bytes_read, temp);
    size_t bytes_to_copy = (decompressed_size > max_bytes) ? max_bytes : decompressed_size;
    memcpy(buf, temp, bytes_to_copy);
    delete[] temp;
    delete[] compressed;
    return bytes_to_copy;
}

size_t RleFile2::compress_rle(const char* raw_data, size_t raw_size, char* dst){
    if (!raw_data || raw_size == 0 || !dst) return 0;
    size_t dst_pos = 0;
    char current = raw_data[0];
    unsigned char count = 1; //unsigned char to be able to make it to 255 instead of 128
    for(int i=1; i<raw_size; i++){
        if(current==raw_data[i] && count < 255) {
            count++;
        }
    else{
        dst[dst_pos]=count;
        dst[dst_pos + 1]= current;
        dst_pos += 2;
        current = raw_data[i];
        count=1;
    }
}
    dst[dst_pos]=count;
    dst[dst_pos +1]=current;
    dst_pos+=2;
return dst_pos;
}

size_t RleFile2::decompress_rle(const char* compressed_data, size_t compressed_size, char* dst){
    if (!compressed_data || compressed_size == 0 || !dst) return 0;
    if (compressed_size % 2 != 0){
        std::cout<<"malformed compressed data"<<std::endl;
        return 0;
    }
    size_t dst_pos=0;
    unsigned char count=0;
    for(int i=0; i<compressed_size; i+=2){
        count= static_cast<unsigned char>(compressed_data[i]); //0-255
        for(unsigned char  j=0; j<count;j++){
            dst[dst_pos + j]=compressed_data[i+1];
        }
        dst_pos += count;
    }
return dst_pos;
}

