#include <iostream>
#include <utility>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_resize2.h"

using namespace std;

const int desired_channels = 3; // RGBA output


unsigned char* loadImage(const char* filename, int& width, int& height, int& channels) {
    unsigned char* image = stbi_load(filename, &width, &height, &channels, desired_channels);

    if (!image) {
        cerr << "Error loading image: " << stbi_failure_reason() << endl;
        return nullptr;
    }

    return image;
}


pair<int, int> getNewSize() {
    cout << "New size" << endl;
    int width, height;
    cin >> width >> height;

    return make_pair(width, height);
}

void createAsciiArt(unsigned char* image, int width, int height, int channels) {
    const char* ascii_chars = " .:-=+*#%&$@";

    int num_chars = strlen(ascii_chars);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * channels;
            unsigned char r = image[index];
            unsigned char g = image[index + 1];
            unsigned char b = image[index + 2];

            // Convert to grayscale
            unsigned char gray = static_cast<unsigned char>(0.299 * r + 0.587 * g + 0.114 * b);
            int char_index = (gray * (num_chars - 1)) / 255;
            cout << ascii_chars[char_index];
        }
        cout << endl;
    }

}

unsigned char* resizeImage(unsigned char* input_image, int input_width, int input_height, int input_channels, int new_width, int new_height) {
    unsigned char* resized_image = new unsigned char[new_width * new_height * input_channels];

    if (!stbir_resize_uint8_srgb(input_image, input_width, input_height, 0, resized_image, new_width, new_height, 0, STBIR_RGB)) {
        delete[] resized_image;
        return nullptr;
    }

    return resized_image;
}

void processImage(const char* input_file) {
    int x = 0, y = 0, channels = 0;

    unsigned char* current_image = loadImage(input_file, x, y, channels);
    if (!current_image) {
        return;
    }

    auto [new_width, new_height] = getNewSize();

    unsigned char* resized_image = resizeImage(
        current_image,
        x,
        y,
        channels,
        new_width,
        new_height);

    if (!resized_image) {
        return;
    }

    createAsciiArt(resized_image, new_width, new_height, channels);

    stbi_image_free(current_image);
    delete[] resized_image;
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    const char* input_file = argv[1];

    processImage(input_file);

    return 0;
}
