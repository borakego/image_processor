#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>

namespace utils {
const int BMP_HEADER_SIZE = 14;
const int DIB_HEADER_SIZE = 40;
const int PADDING_SIZE = 4;
const int BYTES_PER_PIXEL = 3;
const int HEADER_WIDTH_OFFSET = 4;
const int HEADER_HEIGHT_OFFSET = 8;
const int FORMAT_FILE_FIRST_POSITION = 0;
const int FORMAT_FILE_SECOND_POSITION = 1;
const int SIZE_POSITION = 2;
const int PIXS_POSITION = 10;
const int DIB_HEADER_SIZE_POSITION = 0;
const int CNT_OF_PLANES = 1;
const int CNT_OF_PLANES_POSITION = 12;
const int BITS_PER_PIXEL = 24;
const int BITS_PER_PIXEL_POSITION = 14;
const int COLOR_MAX_VALUE = 255;
const double GS_VALUE_RED = 0.299;
const double GS_VALUE_GREEN = 0.587;
const double GS_VALUE_BLUE = 0.114;
const int RESOLUTION_WIDTH_POSITION = 24;
const int RESOLUTION_HEIGHT_POSITION = 28;
const int RESOLUTION = 2835;
const std::vector<char> FORMAT_BYTES = {'B', 'M'};
const std::vector<int> OFFSETS_OF_BYTES = {8, 16, 24};
}  // namespace utils

#endif  // UTILS_H