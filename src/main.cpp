#include <iostream>
#include <utility>
#include "stb_image.h"
#include "stb_image_resize2.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBIR_INCLUDE_STB_IMAGE_RESIZE2_H_IMPLEMENTATION

using namespace std;

const int desired_channels = 3; // RGB output


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




int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    int x = 0, y = 0, channels = 0;

    const char* input_file = argv[1];
    unsigned char* current_image = loadImage(input_file, x, y, channels);


    return 0;
}
