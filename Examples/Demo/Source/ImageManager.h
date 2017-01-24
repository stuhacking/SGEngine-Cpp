/*
 *
 * Created by shacking on 24/01/17.
 */
#ifndef __SGENGINE_IMAGEMANAGER_H
#define __SGENGINE_IMAGEMANAGER_H

#include "Engine.h"

#include <memory>
#include <string>
#include <map>

class ImageManager {
public:

    /**
     * Load an image from a path.
     * @param path Location of image in resource directory.
     * @return true if image was loaded, false otherwise.
     */
    bool Load (const std::string &path);

    /**
     * Get a reference to an image in the cache.
     * @param path Location of image in resource directory.
     * @return Reference to image.
     */
    sge::Image* Get (const std::string &path);

    void Reload ();

private:
    std::map<std::string, std::unique_ptr<sge::Image>> images;
};

#endif /* __SGENGINE_IMAGEMANAGER_H_H */
