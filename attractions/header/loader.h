#ifndef LOADER_H
#define LOADER_H

#include <allegro.h>

BITMAP* image_loader(const char* filepath);
SAMPLE* sound_loader(const char* filepath);
FILE *file_loader(const char* filepath, const char* mode)

#endif // LOADER_H
