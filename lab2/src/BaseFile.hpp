#ifndef BASEFILE_HPP
#define BASEFILE_HPP
#include <cstdio>
class IFile {
    public:
        virtual bool can_read() const = 0;
        virtual bool can_write() const = 0;
        virtual size_t read(void* buf, size_t max_bytes) = 0;
        virtual size_t write(const void* buf, size_t n_bytes) = 0;
        virtual ~IFile() = default; 
    };
    //3.2
    class Base32File2 : public IFile {
    private:
        IFile* target; 
        char encoding_map[32];
        int encoded32_size(int rsize);
        int decoded32_size(int esize);
        size_t encode32(const char* raw_data, int raw_size, char* dst);
        size_t decode32(const char* encoded_data, int encoded_size, char* dst);
    
    public:
        Base32File2(IFile* target, const char* table = "abcdefghijklmnopqrstuvwxyz012345");
        virtual ~Base32File2();
    
        bool can_read() const override;
        bool can_write() const override;
        size_t read(void* buf, size_t max_bytes) override;
        size_t write(const void* buf, size_t n_bytes) override;
    };

    class RleFile2 : public IFile {
        private:
            IFile* target; //
            size_t compress_rle(const char* raw_data, size_t raw_size, char* dst);
            size_t decompress_rle(const char* compressed_data, size_t compressed_size, char* dst);
            
        public:
            RleFile2(IFile* target);
            virtual ~RleFile2();
            
            bool can_read() const override;
            bool can_write() const override;
            size_t read(void* buf, size_t max_bytes) override;
            size_t write(const void* buf, size_t n_bytes) override;
            };    
        

    class BaseFile : public IFile{
    protected:
    FILE* file;
    bool owns_file; 
    public:
    //constructors
    BaseFile();
    BaseFile(const char* path, const char* mode);
    BaseFile(FILE* f);
    //destructor
    virtual ~BaseFile();
    //status methods
    bool is_open() const;
    bool can_read() const override;
    bool can_write() const override;
    //raw IO methods
    size_t write_raw(const void* buf,size_t n_bytes);
    size_t read_raw(void* buf, size_t max_bytes);
    //position methods
    long tell() const;
    bool seek(long offset);
    //inheritance 
    virtual size_t write(const void* buf, size_t n_bytes) override;
    virtual size_t read(void* buf, size_t max_bytes) override;
};
        class Base32File : public BaseFile {
    private:
        char encoding_map[32];
        int encoded32_size(int rsize);
        int decoded32_size(int esize);
        size_t encode32(const char* raw_data, int raw_size, char* dst);
        size_t decode32(const char* encoded_data, int encoded_size, char* dst);
    
    public:
        Base32File(const char* path, const char* mode, const char* table = "abcdefghijklmnopqrstuvwxyz012345");
        Base32File(FILE* f, const char* table = "abcdefghijklmnopqrstuvwxyz012345");
        ~Base32File();
    
        size_t write(const void* buf, size_t n_bytes) override;
        size_t read(void* buf, size_t max_bytes) override;
    };
        class RleFile : public BaseFile {
        private:
        size_t compress_rle(const char* raw_data, size_t raw_size, char* dst);
        size_t decompress_rle(const char* compressed_data, size_t compressed_size, char* dst);
        
        public:
        RleFile(const char* path, const char* mode);
        RleFile(FILE* f);
        ~RleFile();
        size_t write(const void* buf, size_t n_bytes) override;
        size_t read(void* buf, size_t max_bytes) override;    
    };


    void write_int(IFile& file, int n);


    
#endif //BASEFFILE_HPP