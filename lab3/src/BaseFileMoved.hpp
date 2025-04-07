#ifndef BASEFILEMOVED_HPP
#define BASEFILEMOVED_HPP

#include <cstdio>

class IFile {
public:
    virtual bool can_read() const = 0;
    virtual bool can_write() const = 0;
    virtual size_t read(void* buf, size_t max_bytes) = 0;
    virtual size_t write(const void* buf, size_t n_bytes) = 0;
    virtual ~IFile() = default;
};

class BaseFile : public IFile {
protected:
    FILE* file;
    bool owns_file;

public:
    //cons
    BaseFile();
    BaseFile(const char* path, const char* mode);
    BaseFile(FILE* f);
    
    virtual ~BaseFile();
    
    //delete copy operations
    BaseFile(const BaseFile& other) = delete;
    BaseFile& operator=(const BaseFile& other) = delete;
    
    //move operations
    BaseFile(BaseFile&& other) noexcept;
    BaseFile& operator=(BaseFile&& other) noexcept;
    
    //status methods
    bool is_open() const;
    bool can_read() const override;
    bool can_write() const override;
    
    //IO methods
    size_t write_raw(const void* buf, size_t n_bytes);
    size_t read_raw(void* buf, size_t max_bytes);
    
    long tell() const;
    bool seek(long offset);
    
    //inheritance 
    virtual size_t write(const void* buf, size_t n_bytes) override;
    virtual size_t read(void* buf, size_t max_bytes) override;
};

#endif // BASEFILEMOVED_HPP