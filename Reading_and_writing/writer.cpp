#include "writer.h"

reading_and_writing::Writer::Writer(std::string filename) : filename_(std::move(filename)) {
}

void reading_and_writing::Writer::WriteBMPHeader(unsigned char* bmp_header, size_t size_of_file) {
    bmp_header[utils::FORMAT_FILE_FIRST_POSITION] = utils::FORMAT_BYTES[0];
    bmp_header[utils::FORMAT_FILE_SECOND_POSITION] = utils::FORMAT_BYTES[1];
    NumberToBytes(size_of_file, bmp_header + utils::SIZE_POSITION);
    bmp_header[utils::PIXS_POSITION] = utils::BMP_HEADER_SIZE + utils::DIB_HEADER_SIZE;
}

void reading_and_writing::Writer::WriteDIBHeader(unsigned char* dib_header, size_t width, size_t height) {
    dib_header[utils::DIB_HEADER_SIZE_POSITION] = utils::DIB_HEADER_SIZE;
    NumberToBytes(width, dib_header + utils::HEADER_WIDTH_OFFSET);
    NumberToBytes(height, dib_header + utils::HEADER_HEIGHT_OFFSET);
    dib_header[utils::CNT_OF_PLANES_POSITION] = utils::CNT_OF_PLANES;
    dib_header[utils::BITS_PER_PIXEL_POSITION] = utils::BITS_PER_PIXEL;
    NumberToBytes(utils::RESOLUTION, dib_header + utils::RESOLUTION_WIDTH_POSITION);
    NumberToBytes(utils::RESOLUTION, dib_header + utils::RESOLUTION_HEIGHT_POSITION);
}

void reading_and_writing::Writer::Write(const Image& image) {
    std::ofstream out_file;
    out_file.open(filename_, std::ios::binary | std::ios::out);
    if (!out_file.is_open()) {
        throw std::invalid_argument("Can\'t open file" + filename_);
    }
    if (errno == EACCES) {
        throw std::invalid_argument("You don\'t have permission to write in file" + filename_);
    }
    const size_t file_size = utils::BMP_HEADER_SIZE + utils::DIB_HEADER_SIZE +
                             image.GetHeight() * image.GetWidth() * utils::BYTES_PER_PIXEL +
                             GetPaddingSize(image.GetWidth()) * image.GetHeight();

    unsigned char bmp_header[utils::BMP_HEADER_SIZE] = {};
    std::fill(bmp_header, bmp_header + utils::BMP_HEADER_SIZE, 0);
    WriteBMPHeader(bmp_header, file_size);
    unsigned char dib_header[utils::DIB_HEADER_SIZE] = {};
    std::fill(dib_header, dib_header + utils::DIB_HEADER_SIZE, 0);
    WriteDIBHeader(dib_header, image.GetWidth(), image.GetHeight());

    out_file.write(reinterpret_cast<char*>(bmp_header), utils::BMP_HEADER_SIZE);
    out_file.write(reinterpret_cast<char*>(dib_header), utils::DIB_HEADER_SIZE);
    unsigned char empty_pixel[utils::BYTES_PER_PIXEL] = {0, 0, 0};
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            uint8_t red = static_cast<uint8_t>(image.GetColor(i, j).red);
            uint8_t green = static_cast<uint8_t>(image.GetColor(i, j).green);
            uint8_t blue = static_cast<uint8_t>(image.GetColor(i, j).blue);
            unsigned char pixel[utils::BYTES_PER_PIXEL] = {blue, green, red};
            out_file.write(reinterpret_cast<char*>(pixel), utils::BYTES_PER_PIXEL);
        }
        out_file.write(reinterpret_cast<char*>(empty_pixel),
                       static_cast<std::streamsize>(GetPaddingSize(image.GetWidth())));
    }
    out_file.close();
}

template <typename T>
void reading_and_writing::Writer::NumberToBytes(T number, unsigned char* bytes) {
    *bytes = number;
    for (size_t i = 0; i < utils::OFFSETS_OF_BYTES.size(); ++i) {
        *(bytes + i + 1) = number >> utils::OFFSETS_OF_BYTES[i];
    }
}