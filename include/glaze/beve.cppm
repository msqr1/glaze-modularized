#pragma once
#ifdef CPP_MODULES
module;
#endif
#include "../Export.hpp"
#ifdef CPP_MODULES
export module glaze.beve;
import glaze.beve.header;
import glaze.beve.ptr;
import glaze.beve.read;
import glaze.beve.wrappers;
import glaze.beve.write;
import glaze.thread.atomic;
#else
#include "glaze/beve/header.cppm"
#include "glaze/beve/ptr.cppm"
#include "glaze/beve/read.cppm"
#include "glaze/beve/wrappers.cppm"
#include "glaze/beve/write.cppm"
#include "glaze/thread/atomic.cppm"
#endif

// Glaze Library
// For the license information refer to glaze.hpp


