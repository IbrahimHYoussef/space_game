#if WIN_32
#include <string.h>

#include <windows.h>
void DisplaySystemMessage(char *message) {
  if (strlen(message) > 50) {
    return;
  }
  char messagef[50];
  sprintf(messagef, "xmessage -center '%s'", message);
  system(messagef);
}

#endif

#if LINUX
#include <stdlib.h>
#include <string.h>

void DisplaySystemMessage(char *message) {
  if (strlen(message) > 50) {
    return;
  }
  char messagef[50];
  sprintf(messagef, "xmessage -center '%s'", message);
  system(messagef);
}

#endif
