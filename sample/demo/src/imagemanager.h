/*
 *
 * Created by shacking on 24/01/17.
 */
#ifndef __SGE_IMAGEMANAGER_H
#define __SGE_IMAGEMANAGER_H

#include "engine.h"

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
    bool load (const std::string &path);

    /**
     * Get a reference to an image in the cache.
     * @param path Location of image in resource directory.
     * @return Reference to image.
     */
    sge::Image* get (const std::string &path);

    void reload ();

private:
    std::map<std::string, std::unique_ptr<sge::Image>> mImages;
};

#endif /* __SGE_IMAGEMANAGER_H */
