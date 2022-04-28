#ifndef webpage_h
#define webpage_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

// Retrieves the host up to date HTML page from the file path
void retrieve_webpage(const char* file_path, char* buffer, int buffer_size);

int update_webpage(const char* file_path);

#endif
