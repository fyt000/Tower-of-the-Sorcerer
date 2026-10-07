#pragma once
#if defined(_WIN32)
#define NOMINMAX
#define NOGDI
#define NOUSER
#endif
#define MA_NO_ENGINE
#define MA_NO_NODE_GRAPH
#define MA_NO_RESOURCE_MANAGER
#define MA_NO_GENERATION
#define MA_NO_ENCODING
#define MA_NO_FLAC
#define MA_NO_MP3
#include "miniaudio.h"
