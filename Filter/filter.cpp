#include "filter.h"

template <typename T>
std::vector<T> filter::Filter::GetPixel(const std::vector<std::vector<T>>& matrix, const Image& img,
                                        const std::size_t& x, const std::size_t y) const {
    T red = 0;
    T green = 0;
    T blue = 0;
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix.front().size(); ++j) {
            red += img.GetColor(std::clamp(static_cast<int>(i + x) - 1, 0, static_cast<int>(img.GetHeight() - 1)),
                                std::clamp(static_cast<int>(j + y) - 1, 0, static_cast<int>(img.GetWidth() - 1)))
                       .red *
                   matrix[i][j];
            green += img.GetColor(std::clamp(static_cast<int>(i + x) - 1, 0, static_cast<int>(img.GetHeight() - 1)),
                                  std::clamp(static_cast<int>(j + y) - 1, 0, static_cast<int>(img.GetWidth() - 1)))
                         .green *
                     matrix[i][j];
            blue += img.GetColor(std::clamp(static_cast<int>(i + x) - 1, 0, static_cast<int>(img.GetHeight() - 1)),
                                 std::clamp(static_cast<int>(j + y) - 1, 0, static_cast<int>(img.GetWidth() - 1)))
                        .blue *
                    matrix[i][j];
        }
    }
    return {blue, green, red};
}

uint8_t filter::Clamp(int color, const uint8_t max_color = 255) {
    if (color < 0) {
        return 0;
    } else if (color > max_color) {
        return max_color;
    }
    return static_cast<uint8_t>(color);
}

Image filter::Sharpering::Apply(const Image& img) const {
    std::vector<std::vector<Color>> new_data;
    const std::vector<std::vector<int>> matrix = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
    for (size_t i = 0; i < img.GetHeight(); ++i) {
        std::vector<Color> row(img.GetWidth());
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            std::vector<int> colors = GetPixel(matrix, img, i, j);
            row[j].blue = Clamp(colors[0]);
            row[j].green = Clamp(colors[1]);
            row[j].red = Clamp(colors[2]);
        }
        new_data.push_back(row);
    }
    return {new_data};
}

Image filter::Grayscale::Apply(const Image& img) const {
    std::vector<std::vector<Color>> new_data;
    for (size_t i = 0; i < img.GetHeight(); ++i) {
        std::vector<Color> row(img.GetWidth());
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            double avg = utils::GS_VALUE_RED * static_cast<double>(img.GetColor(i, j).red);
            avg += utils::GS_VALUE_GREEN * static_cast<double>(img.GetColor(i, j).green);
            avg += utils::GS_VALUE_BLUE * static_cast<double>(img.GetColor(i, j).blue);
            uint8_t avg_value = static_cast<uint8_t>(std::round(avg));
            row[j] = {avg_value, avg_value, avg_value};
        }
        new_data.push_back(row);
    }
    return {new_data};
}

Image filter::Negative::Apply(const Image& img) const {
    std::vector<std::vector<Color>> new_data;
    for (size_t i = 0; i < img.GetHeight(); ++i) {
        std::vector<Color> row(img.GetWidth());
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            row[j] = {static_cast<uint8_t>(utils::COLOR_MAX_VALUE - img.GetColor(i, j).blue),
                      static_cast<uint8_t>(utils::COLOR_MAX_VALUE - img.GetColor(i, j).green),
                      static_cast<uint8_t>(utils::COLOR_MAX_VALUE - img.GetColor(i, j).red)};
        }
        new_data.push_back(row);
    }
    return {new_data};
}

Image filter::EdgeDetection::Apply(const Image& img) const {
    int threshold = img.threshold;
    std::vector<std::vector<Color>> new_data;
    for (size_t i = 0; i < img.GetHeight(); ++i) {
        std::vector<Color> row(img.GetWidth());
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            double avg = utils::GS_VALUE_RED * static_cast<double>(img.GetColor(i, j).red);
            avg += utils::GS_VALUE_GREEN * static_cast<double>(img.GetColor(i, j).green);
            avg += utils::GS_VALUE_BLUE * static_cast<double>(img.GetColor(i, j).blue);
            uint8_t avg_value = static_cast<uint8_t>(std::round(avg));
            row[j] = {avg_value, avg_value, avg_value};
        }
        new_data.push_back(row);
    }
    const std::vector<std::vector<int>> matrix = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    Image img1 = {new_data};
    std::vector<std::vector<Color>> new_data1;
    for (size_t i = 0; i < img1.GetHeight(); ++i) {
        std::vector<Color> row(img1.GetWidth());
        for (size_t j = 0; j < img1.GetWidth(); ++j) {
            std::vector<int> colors = GetPixel(matrix, img1, i, j);
            if (colors[0] > threshold) {
                row[j].blue = static_cast<uint8_t>(utils::COLOR_MAX_VALUE);
                row[j].green = static_cast<uint8_t>(utils::COLOR_MAX_VALUE);
                row[j].red = static_cast<uint8_t>(utils::COLOR_MAX_VALUE);
            } else {
                row[j].blue = static_cast<uint8_t>(0);
                row[j].green = static_cast<uint8_t>(0);
                row[j].red = static_cast<uint8_t>(0);
            }
        }
        new_data1.push_back(row);
    }
    return {new_data1};
}

Image filter::Crop::Apply(const Image& img) const {
    std::vector<std::vector<Color>> new_data;
    size_t width = std::min(img.crop_width, img.GetWidth());
    size_t height = std::min(img.crop_height, img.GetHeight());
    for (size_t i = img.GetHeight() - height; i < img.GetHeight(); ++i) {
        std::vector<Color> row(width);
        for (size_t j = 0; j < width; ++j) {
            row[j] = img.GetColor(i, j);
        }
        new_data.push_back(row);
    }
    return {new_data};
}

std::unique_ptr<filter::Filter> filter::CreateFilter(const parser::Token& token) {
    const std::string& filter = token.name;
    if (filter == "-sharp") {
        if (!token.args.empty()) {
            throw std::invalid_argument("Invalid argument for sharpering filter");
        }
        std::unique_ptr<filter::Sharpering> ptr = std::make_unique<filter::Sharpering>();
        return ptr;
    } else if (filter == "-neg") {
        if (!token.args.empty()) {
            throw std::invalid_argument("Invalid argument for negative filter");
        }
        std::unique_ptr<filter::Negative> ptr = std::make_unique<filter::Negative>();
        return ptr;
    } else if (filter == "-gs") {
        if (!token.args.empty()) {
            throw std::invalid_argument("Invalid argument for grayscale filter");
        }
        std::unique_ptr<filter::Grayscale> ptr = std::make_unique<filter::Grayscale>();
        return ptr;
    } else if (filter == "-edge") {
        std::unique_ptr<filter::EdgeDetection> ptr = std::make_unique<filter::EdgeDetection>();
        return ptr;
    } else if (filter == "-crop") {
        std::unique_ptr<filter::Crop> ptr = std::make_unique<filter::Crop>();
        return ptr;
    } else {
        throw std::invalid_argument("Invalid filter" + filter);
    }
}