/*
 *
 * Created by shacking on 24/01/17.
 */
#include "imagemanager.h"

bool ImageManager::load (const std::string &path) {
    if (mImages.find(path) == mImages.end()) {
        mImages[path] = std::make_unique<sge::Image>(path.c_str());
        return true;
    }

    return false;
}

sge::Image* ImageManager::get (const std::string &path) {
    return mImages[path].get();
}

void ImageManager::reload () {
    for (auto &pair : mImages) {
        std::string name = pair.first;
        mImages[name] = std::make_unique<sge::Image>(name.c_str());
    }
}
