#pragma once
#include "../Export.hpp"
#ifdef CPP_MODULES
module;
export module glaze.json;
import glaze.json.escape_unicode;
import glaze.json.invoke;
import glaze.json.jmespath;
import glaze.json.json_concepts;
import glaze.json.json_ptr;
import glaze.json.json_t;
import glaze.json.manage;
import glaze.json.max_write_precision;
import glaze.json.minify;
import glaze.json.ndjson;
import glaze.json.prettify;
import glaze.json.ptr;
import glaze.json.raw_string;
import glaze.json.read;
import glaze.json.schema;
import glaze.json.wrappers;
import glaze.json.write;
import glaze.thread.atomic;
#else
#include "glaze/json/escape_unicode.cppm"
#include "glaze/json/invoke.cppm"
#include "glaze/json/jmespath.cppm"
#include "glaze/json/json_concepts.cppm"
#include "glaze/json/json_ptr.cppm"
#include "glaze/json/json_t.cppm"
#include "glaze/json/manage.cppm"
#include "glaze/json/max_write_precision.cppm"
#include "glaze/json/minify.cppm"
#include "glaze/json/ndjson.cppm"
#include "glaze/json/prettify.cppm"
#include "glaze/json/ptr.cppm"
#include "glaze/json/raw_string.cppm"
#include "glaze/json/read.cppm"
#include "glaze/json/schema.cppm"
#include "glaze/json/wrappers.cppm"
#include "glaze/json/write.cppm"
#include "glaze/thread/atomic.cppm"
#endif

// Glaze Library
// For the license information refer to glaze.hpp


