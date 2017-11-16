/*
 *
 * Created by shacking on 24/01/17.
 */
#include "ImageManager.h"

bool ImageManager::Load (const std::string &path) {
    if (images.find(path) == images.end()) {
        images[path] = std::make_unique<sge::Image>(path.c_str());
        return true;
    }

    return false;
}

sge::Image* ImageManager::Get (const std::string &path) {
    return images[path].get();
}

void ImageManager::Reload () {
    for (auto &pair : images) {
        std::string name = pair.first;
        images[name] = std::make_unique<sge::Image>(name.c_str());
    }
}
