//
// Created by bonychops on 11/12/21.
//

#ifndef PROG_GAME_RESOURCEMANAGER_H
#define PROG_GAME_RESOURCEMANAGER_H

#include "Define.h"
#include "Image.h"


class ResourceManager {
public:
    static Image GetImage(string filename);

    static void pushImage(Image image);

private:
    static int imgIndex;
    static Image images[IMAGE_MAX];
};


#endif //PROG_GAME_RESOURCEMANAGER_H
