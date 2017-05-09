#include "stringUtilities.h"

bool isOnlyDigits(const char *text)
{
  int length = strlen(text);
  for (int i = 0; i < length; i++) {
    if (!isdigit(text[i])) {
      return false;
    }
  }
  return true;
}
