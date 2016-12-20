#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "tests.h"

// A selection of different unicode characters to pick from.
// As far as I can tell, there are no unicode characters assigned which
// take up more than 4 bytes in utf-8.
static const char *UCHARS[] = {
  "a", "b", "c", "1", "2", "3", " ", "\n", // ASCII
  "©", "¥", "½", // The Latin-1 suppliment (U+80 - U+ff)
  "Ύ", "Δ", "δ", "Ϡ", // Greek (U+0370 - U+03FF)
  "←", "↯", "↻", "⇈", // Arrows (U+2190 – U+21FF)
  "𐆐", "𐆔", "𐆘", "𐆚", // Ancient roman symbols (U+10190 – U+101CF)
};

// s is the size of the buffer, including the \0. This function might use
// fewer bytes than that.
void random_unicode_string(uint8_t *buffer, size_t s) {
  if (s == 0) { return; }
  uint8_t *pos = buffer;
  
  while(1) {
    uint8_t *c = (uint8_t *)UCHARS[rand() % (sizeof(UCHARS) / sizeof(UCHARS[0]))];
    
    size_t bytes = strlen((char *)c);
    
    size_t remaining_space = buffer + s - pos - 1;
    
    if (remaining_space < bytes) {
      break;
    }
    
    memcpy(pos, c, bytes);
    pos += bytes;
  }
  
  *pos = '\0';
}

static const char CHARS[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
"0123456789!@#$%^&*()[]{}<>?,./";
void random_ascii_string(uint8_t *buffer, size_t len) {
  assert(len);
  for (int i = 0; i < len - 1; i++) {
    buffer[i] = CHARS[rand() % (sizeof(CHARS) - 1)];
  }
  buffer[len - 1] = '\0';
}

