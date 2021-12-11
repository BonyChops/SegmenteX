//
// Created by bonychops on 12/12/21.
//

#include "ResourceManager.h"

int ResourceManager::imgIndex = 0;
Image ResourceManager::images[IMAGE_MAX];

Image ResourceManager::GetImage(string filename) {
    for (int i = 0; i < imgIndex; ++i) {
        if (i >= IMAGE_MAX) {
            cerr << "MAX OF IMAGES REACHED" << endl;
            return (Image) NULL;
        }
        if (images[i].filename == filename) {
            return images[i];
        }
    }
    Image image(filename);
    pushImage(image);
    return image;
}

void ResourceManager::pushImage(Image image) {
    ResourceManager::images[imgIndex] = image;
    imgIndex += 1;
}
