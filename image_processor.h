#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <iostream>
#include <sstream>

#include "Filter/filter.h"
#include "Image/Image.h"
#include "Parser/parser.h"
#include "Reading_and_writing/reader.h"
#include "Reading_and_writing/writer.h"

std::vector<parser::Token> Parse(int argc, char** argv);

Image GetImage(const std::string& path);

void WriteImage(const Image& image, const std::string& path);

Image ApplyFilter(Image& image, const std::vector<parser::Token>& tokens);

#endif  // IMAGE_PROCESSOR_H