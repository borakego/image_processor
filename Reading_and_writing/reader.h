#ifndef READER_H
#define READER_H

#include <cerrno>
#include <fstream>
#include <string>

#include "../Image/Image.h"
#include "Utils.h"

namespace reading_and_writing {
class Reader {
public:
    explicit Reader(const std::string& path);
    Image Read();

private:
    std::string file_name_;
    size_t BytesToNumber(const unsigned char* bytes) const;
};

const size_t GetPaddingSize(size_t width);
}  // namespace reading_and_writing
#endif  // READER_H