//
// Image loader.
//
// FIXME: Support for Indexed files or files that aren't 3-4 Bytes per pixel.
//
#include "../Engine.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>

namespace sge {

u32 Image::MaxTextureDimension () {
    i32 result;

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &result);

    return static_cast<u32>(result);
}

// Flags
static constexpr u8 FLIP_VERTICAL   = 0x01;
static constexpr u8 FLIP_HORIZONTAL = 0x02;

// Read into the SDL_Surface->format struct and determine the attributes
// for pixel width and ordering as a printable string.
static
std::string SDL_PixelFormat_String (const SDL_PixelFormat * const pf) {
    std::stringstream ss;
    switch(pf->BitsPerPixel) {
    case 8: { // Indexed Palette
        ss << "Indexed";
        if (pf->palette) {
            ss << " (" << pf->palette->ncolors << " color)";
        }
        return ss.str();
    }
    case 24: { // RGB

        if (0xFF000000 == pf->Rmask) ss << "R";
        if (0xFF000000 == pf->Gmask) ss << "G";
        if (0xFF000000 == pf->Bmask) ss << "B";
        if (0x00FF0000 == pf->Rmask) ss << "R";
        if (0x00FF0000 == pf->Gmask) ss << "G";
        if (0x00FF0000 == pf->Bmask) ss << "B";
        if (0x0000FF00 == pf->Rmask) ss << "R";
        if (0x0000FF00 == pf->Gmask) ss << "G";
        if (0x0000FF00 == pf->Bmask) ss << "B";
        if (0x000000FF == pf->Rmask) ss << "R";
        if (0x000000FF == pf->Gmask) ss << "G";
        if (0x000000FF == pf->Bmask) ss << "B";

        return ss.str();
    }
    case 32: { // RGBA

        if (0xFF000000 == pf->Rmask) ss << "R";
        if (0xFF000000 == pf->Gmask) ss << "G";
        if (0xFF000000 == pf->Bmask) ss << "B";
        if (0xFF000000 == pf->Amask) ss << "A";
        if (0x00FF0000 == pf->Rmask) ss << "R";
        if (0x00FF0000 == pf->Gmask) ss << "G";
        if (0x00FF0000 == pf->Bmask) ss << "B";
        if (0x00FF0000 == pf->Amask) ss << "A";
        if (0x0000FF00 == pf->Rmask) ss << "R";
        if (0x0000FF00 == pf->Gmask) ss << "G";
        if (0x0000FF00 == pf->Bmask) ss << "B";
        if (0x0000FF00 == pf->Amask) ss << "A";
        if (0x000000FF == pf->Rmask) ss << "R";
        if (0x000000FF == pf->Gmask) ss << "G";
        if (0x000000FF == pf->Bmask) ss << "B";
        if (0x000000FF == pf->Amask) ss << "A";

        return ss.str();
    }
    default:
        return "Unknown";
    }
}

// Debug Surface info for a loaded image. Useful for debugging the
// image resizing/flipping functions.
static
void print_SDL_surface_info (const char * const filename, const SDL_Surface * const surface) {
    console.Debugf("SDL_Surface (%s), Size: %dx%d, Pitch: %d bytes, PixelFormat: %u Bytes (%ubpp) %s\n",
                   filename,
                   surface->w, surface->h, surface->pitch,
                   (unsigned) surface->format->BytesPerPixel,
                   (unsigned) surface->format->BitsPerPixel,
                   SDL_PixelFormat_String(surface->format).c_str());
}

// Copy the contents of an SDL_Surface to a new allocated
// copy, also allows flipping the image across vertical and
// horizontal axes.
static
bool copy_surface (SDL_Surface * const src, SDL_Surface * dest, const u8 flags = 0) {

    if (SDL_MUSTLOCK(src)) {
        console.Debug("SDL_MUSTLOCK: Locking input surface\n");
        SDL_LockSurface(src);
    }

    // Add palette reference for indexed surfaces.
    if (src->format->BytesPerPixel == 1) {
        SDL_SetSurfacePalette(dest, src->format->palette);
    }

    // FIXME [smh] Re-implement horizontal flipping with correct pixelformat.
    if (flags & (FLIP_VERTICAL | FLIP_HORIZONTAL)) {
        // Do Line level reordering of the pixel buffer
        u32 w = dest->pitch;
        u8 *src_buf = reinterpret_cast<u8*>(src->pixels);
        u8 *dst_buf = reinterpret_cast<u8*>(dest->pixels);

        for (u32 y = 0, yMax = dest->h, ry = dest->h - 1; y < yMax; y++, ry--) {
            std::memcpy(dst_buf + (y * w), src_buf + (ry * w), w);
        }
    } else {
        // Just do a fast copy
        std::memcpy(dest->pixels, src->pixels, dest->pitch * dest->h);
    }

    if (SDL_MUSTLOCK(src)) {
        console.Debug("SDL_MUSTLOCK: Unlocking input src\n");
        SDL_UnlockSurface(src);
    }

    return true;
}

// Load image directly into a GL Texture using SDL_image as
// the provider.
// This method always vertically flips the input file.
static
bool LoadImageSDL(const char * const filename) {
    SDL_Surface *surface, *flipped;
    u32 internalFormat, format;

    console.Debugf("Loading Image: %s\n", filename);

    surface = IMG_Load(filename);
    if (nullptr == surface) {
        console.Errorf("SDL Error when loading image file. -- %s: %s\n", filename, IMG_GetError());
        return false;
    }

    IF_DEBUG( print_SDL_surface_info(filename, surface); );

    if (surface->format->BytesPerPixel == 4) {
        internalFormat = GL_RGBA8;
        format = GL_RGBA;
    } else {
        internalFormat = GL_RGB8;
        format = GL_RGB;
    }

    // TODO: Use internal pixel buffer structure, standardize pixel format after read.
    flipped = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                   surface->w, surface->h,
                                   surface->format->BitsPerPixel,
                                   surface->format->Rmask, surface->format->Gmask,
                                   surface->format->Bmask, surface->format->Amask);

    if (!flipped) {
        console.Errorf("Unable to create copy surface. -- %s\n", IMG_GetError());
        return false;
    }

    bool success = copy_surface(surface, flipped, FLIP_VERTICAL);
    if (!success) {
        console.Error("Unable to write to surface copy. -- %s\n");
        return false;
    }

    u32 w = FMath::Nearest2Pow(flipped->w);
    u32 h = FMath::Nearest2Pow(flipped->h);
    if (w != static_cast<u32>(flipped->w) || h != static_cast<u32>(flipped->h)) {
        console.Debug("WARNING: Image dimensions are not powers of two which may cause issues.\n");
    }

    // FIXME [smh] This doesn't seem to work on OS X now - Do better detection of pixelformat.
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 internalFormat,
                 w, h, 0,
                 format,
                 GL_UNSIGNED_BYTE,
                 flipped->pixels);

    SDL_FreeSurface(surface);
    SDL_FreeSurface(flipped);

    return true;
}

//======================
// Image Methods
//======================

Image::Image(const char * const filename) {
    m_repeat[0] = m_repeat[1] = GL_CLAMP_TO_BORDER;
    m_filter = GL_LINEAR;

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    if (!LoadImageSDL(filename)) {
        console.Errorf("Failed to load image file. -- %s\n", filename);
        glDeleteTextures(1, &m_id);
        m_id = 0;
    }
}

void Image::Bind() const {
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_repeat[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_repeat[1]);
}

void Image::SetRepeat (const bool repeat, const bool mirror) {
    if (repeat) {
        if (mirror) {
            m_repeat[0] = m_repeat[1] = GL_MIRRORED_REPEAT;
        } else {
            m_repeat[0] = m_repeat[1] = GL_REPEAT;
        }
    } else {
        m_repeat[0] = m_repeat[1] = GL_CLAMP_TO_BORDER;
    }
}

void Image::SetRepeatX (const bool repeat, const bool mirror) {
    if (repeat) {
        if (mirror) {
            m_repeat[0] = GL_MIRRORED_REPEAT;
        } else {
            m_repeat[0] = GL_REPEAT;
        }
    } else {
        m_repeat[0] = GL_CLAMP_TO_BORDER;
    }
}

void Image::SetRepeatY (const bool repeat, const bool mirror) {
    if (repeat) {
        if (mirror) {
            m_repeat[1] = GL_MIRRORED_REPEAT;
        } else {
            m_repeat[1] = GL_REPEAT;
        }
    } else {
        m_repeat[1] = GL_CLAMP_TO_BORDER;
    }
}

} /* namespace sge */
