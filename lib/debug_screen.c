#include <kos.h>
#include <kos/string.h>
#include <stdio.h>
#include "gl_font.h"

char *debugData[6];
char *debugName[6];
char mem_buf[32];

int visible = 0;
int release = 0;

void toggleDebug(cont_state_t *state) {
  if (state->buttons & CONT_START)
  {
    if (release == 0)
    {
      if (visible == 0)
        visible = 1;
      else
        visible = 0;
      release = 1;
    }
  }
  else
    release = 0;

}

void setParam(int paramIndex, char *text) {
  debugName[paramIndex] = text;
}

void setString(int paramIndex, char *text) {
  debugData[paramIndex] = text;
}

void setInt(int paramIndex, uint i) {
  char *toString;

  if (debugData[paramIndex] != NULL)
    toString = debugData[paramIndex];
  else
    toString = malloc(8);

  snprintf(toString, 8, "%u", i);
  debugData[paramIndex] = toString;
  //free(toString);
}

void setAdd(int paramIndex, void *pnt) {
  char *toString;

  if (debugData[paramIndex] != NULL)
    toString = debugData[paramIndex];
  else
    toString = malloc(8);

  snprintf(toString, 8, "%p", pnt);
  debugData[paramIndex] = toString;
  //free(toString);
}

void setFloat(int paramIndex, double i) {
  char *toString;

  if (debugData[paramIndex] != NULL)
    toString = debugData[paramIndex];
  else
    toString = malloc(8);

  snprintf(toString, 8, "%f", i);
  debugData[paramIndex] = toString;
  //free(toString);
}

void printString(char *string, int x, int y) {
  bfont_draw_str(vram_s + 640 * y + x, 640, 0, string);
}

void memoryInfo(){
  long maxMem = 4077736;
  long avail = pvr_mem_available();
  double rem;


  rem = (avail / maxMem) * 100;
  snprintf(mem_buf, 32, "PVR:%0.2f/100", rem);
  setParam(0, mem_buf);
}

void debugScreen() {
  int left = 16;
  int right = 16 * 32;
  int lineHeight = 20;
  char cursorPos[16];

  bfont_set_encoding(BFONT_CODE_ISO8859_1);
  memoryInfo();
  if (visible == 1)
  {
    for (int i = 0; i < 6; i++)
    {
      /*
      if (debugName[i] != '\0')
        writeFont(debugName[i], 16, 460 - lineHeight * i);
      if (debugData[i] != '\0')
        writeFont(debugData[i], 512, 460 - lineHeight * i);
        */
      if (debugName[i] != '\0')
        bfont_draw_str(vram_s + 640 * lineHeight * i + left, 640, 1, debugName[i]);
      if (debugData[i] != '\0')
        bfont_draw_str(vram_s + 640 * lineHeight * i + right, 640, 1, debugData[i]);
    }
  }
}


