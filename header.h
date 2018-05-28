#include <kos.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <kos/string.h>
#include <stdio.h>
#include <png/png.h>
#include <zlib/zlib.h>
#include <GL/gl.h>
#include <malloc.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

///////////////////////
//game related
#include "global_var.h"
#include "utils.h"
#include "lib/gl_font.h"
#include "lib/debug_screen.h" //vital
#include "lib/game_object.h" //vital
#include "lib/gl_png.h"
#include "lib/scene.h"
#include "lib/player.h"
