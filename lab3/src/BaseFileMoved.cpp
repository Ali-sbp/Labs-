#include "BaseFileMoved.hpp"
#include <iostream>

using namespace std;

BaseFile::BaseFile() : file(nullptr), owns_file(false) {
    cout << "BaseFile default constructor called" << endl;
}

BaseFile::BaseFile(const char* path, const char* mode) : owns_file(true) {
    file = fopen(path, mode);
    cout << "BaseFile path constructor called" << endl;
}

BaseFile::BaseFile(FILE* f) : file(f), owns_file(false) {
    cout << "BaseFile FILE* constructor called" << endl;
}

BaseFile::~BaseFile() {
    if (owns_file && file != nullptr) {
        fclose(file);
        cout << "BaseFile destructor called, file closed" << endl;
    } else if (file == nullptr) {
        cout << "BaseFile destructor called, no file to close" << endl;
    } else {
        cout << "BaseFile destructor called, not closing file (not owned)" << endl;
    }
}

//move constructor
BaseFile::BaseFile(BaseFile&& other) noexcept : file(other.file), owns_file(other.owns_file) {
    //transfer ownership
    other.file = nullptr;
    other.owns_file = false;
    cout << "BaseFile move constructor called" << endl;
}

//move assignment op
BaseFile& BaseFile::operator=(BaseFile&& other) noexcept {
    cout << "BaseFile move assignment operator called" << endl;
    
    if (this != &other) {
        //clean up (if needed)
        if (owns_file && file != nullptr) {
            fclose(file);
            cout << "  Closing current file in move assignment" << endl;
        }
        
        //transfer ownership
        file= other.file;
        owns_file =other.owns_file;
        
        //reset the source object
        other.file = nullptr;
        other.owns_file = false;
    }
    
    return *this;
}

bool BaseFile::is_open() const {
    return file != nullptr && !ferror(file);
}

bool BaseFile::can_read() const {
    return is_open();
}

bool BaseFile::can_write() const {
    return is_open();
}

size_t BaseFile::write_raw(const void* buf, size_t n_bytes) {
    if (!is_open()) return 0;
    return fwrite(buf, 1, n_bytes, file);
}

size_t BaseFile::read_raw(void* buf, size_t max_bytes) {
    if (!is_open()) return 0;
    return fread(buf, 1, max_bytes, file);
}

long BaseFile::tell() const {
    if (!is_open()) return -1;
    return ftell(file);
}

bool BaseFile::seek(long offset) {
    if (!is_open()) return false;
    return fseek(file, offset, SEEK_SET) == 0;
}

size_t BaseFile::write(const void* buf, size_t n_bytes) {
    return write_raw(buf, n_bytes);
}

size_t BaseFile::read(void* buf, size_t max_bytes) {
    return read_raw(buf, max_bytes);
}