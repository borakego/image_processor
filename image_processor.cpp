#include "image_processor.h"

int main(int argc, char** argv) {
    try {
        std::vector<parser::Token> tokens = Parse(argc, argv);
        Image img = GetImage(tokens[1].name);
        img = ApplyFilter(img, tokens);
        WriteImage(img, tokens[2].name);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

std::vector<parser::Token> Parse(int argc, char** argv) {
    std::vector<parser::Token> tokens = parser::Parse(argc, argv);
    if (tokens.size() < 2) {
        throw std::invalid_argument("Not enough arguments");
    }
    return tokens;
}

Image GetImage(const std::string& path) {
    reading_and_writing::Reader reader(path);
    Image image = reader.Read();
    return image;
}

void WriteImage(const Image& image, const std::string& path) {
    reading_and_writing::Writer writer(path);
    writer.Write(image);
}

Image ApplyFilter(Image& image, const std::vector<parser::Token>& tokens) {
    for (size_t i = 3; i < tokens.size(); ++i) {
        if (tokens[i].name == "-edge") {
            if (tokens[i].args.size() != 1) {
                throw std::invalid_argument("Invalid argument for Edge Detection filter");
            }
            image.threshold =
                static_cast<uint8_t>(std::stod(tokens[i].args[0]) * static_cast<double>(utils::COLOR_MAX_VALUE));
        } else if (tokens[i].name == "-crop") {
            if (tokens[i].args.size() != 2) {
                throw std::invalid_argument("Invalid argument for crop filter");
            }
            image.crop_width = static_cast<size_t>(std::stoi(tokens[i].args[0]));
            image.crop_height = static_cast<size_t>(std::stoi(tokens[i].args[1]));
        }
        image = filter::CreateFilter(tokens[i])->Apply(image);
    }
    return image;
}
