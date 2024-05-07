#ifndef FILTER_H
#define FILTER_H

#include <algorithm>
#include <cmath>
#include <memory>
#include <stdexcept>

#include "../Image/Image.h"
#include "../Parser/parser.h"
#include "../Reading_and_writing/Utils.h"

namespace filter {
class Filter {
public:
    Filter() = default;
    virtual ~Filter() = default;
    virtual Image Apply(const Image& image) const = 0;

protected:
    template <typename T>
    std::vector<T> GetPixel(const std::vector<std::vector<T>>& matrix, const Image& img, const std::size_t& x,
                            const std::size_t y) const;
};

class Sharpering : public Filter {
public:
    Image Apply(const Image& image) const override;
};

class Negative : public Filter {
public:
    Image Apply(const Image& image) const override;
};

class Grayscale : public Filter {
public:
    Image Apply(const Image& image) const override;
};

class EdgeDetection : public Filter {
public:
    Image Apply(const Image& image) const override;
};

class Crop : public Filter {
public:
    Image Apply(const Image& image) const override;
};

std::unique_ptr<Filter> CreateFilter(const parser::Token& tokens);

uint8_t Clamp(int color, const uint8_t max_color);

}  // namespace filter

#endif  // FILTER_H