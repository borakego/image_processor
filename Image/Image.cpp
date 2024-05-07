#include "Image.h"

Image::Image(size_t height, size_t width) {
    this->height_ = height;
    this->width_ = width;
}

Image::Image(const std::vector<std::vector<Color>>& data) {
    this->data_ = data;
    this->height_ = data.size();
    this->width_ = data[0].size();
}

Image::Image(const Image& other) {
    this->height_ = other.GetHeight();
    this->width_ = other.GetWidth();
    this->data_ = other.GetData();
}

size_t Image::GetHeight() const {
    return this->height_;
}

size_t Image::GetWidth() const {
    return this->width_;
}

const std::vector<std::vector<Color>>& Image::GetData() const {
    return this->data_;
}

Color& Image::GetColor(size_t x, size_t y) {
    return this->data_[x][y];
}

const Color& Image::GetColor(size_t x, size_t y) const {
    return this->GetData()[x][y];
}

void Image::SetColor(size_t x, size_t y, Color color) {
    this->data_[x][y] = color;
}

bool Image::CheckHeightAndWidth(size_t x, size_t y) const {
    if (x == this->GetHeight() && y == this->GetWidth()) {
        return true;
    }
    return false;
}