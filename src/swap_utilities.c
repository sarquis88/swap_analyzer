#include "../include/swap_analyzer.h"

void get_timestamp( char * buffer )
  {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer,  "%d-%02d-%02d %02d:%02d:%02d",
            tm.tm_year + 1900, tm.tm_mon + 1,
            tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  }
