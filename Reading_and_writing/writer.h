#ifndef WRITER_H
#define WRITER_H

#include <algorithm>
#include <cerrno>
#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>

#include "../Image/Image.h"
#include "reader.h"
#include "Utils.h"

namespace reading_and_writing {
class Writer {
public:
    explicit Writer(std::string path);
    void Write(const Image& image);

private:
    void WriteBMPHeader(unsigned char* bmp_header, size_t size_of_file);
    void WriteDIBHeader(unsigned char* dib_header, size_t width, size_t height);

    template <typename T>
    void NumberToBytes(T number, unsigned char* bytes);

    std::string filename_;
};
}  // namespace reading_and_writing

#endif  // WRITER_H