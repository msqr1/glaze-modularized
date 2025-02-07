#pragma once
#include "../Export.hpp"
#ifdef CPP_MODULES
module;
export module glaze.csv;
import glaze.csv.read;
import glaze.csv.write;
import glaze.thread.atomic;
#else
#include "glaze/csv/read.cppm"
#include "glaze/csv/write.cppm"
#include "glaze/thread/atomic.cppm"
#endif

// Glaze Library
// For the license information refer to glaze.hpp


