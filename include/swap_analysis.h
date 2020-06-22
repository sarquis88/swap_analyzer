#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define INFO_SIZE             128
#define SWAP_SIZE             16
#define LOAD_SIZE             8
#define SLEEP_S_TIME          3
#define SLEEP_NS_TIME         0

void init_log           ( );
void read_swap_info     ( char *buffer );
void read_load_info     ( char *buffer );
void parse_info         ( char *buffer, char *swap, char *load );
void write_log          ( char * info);
void sleep              ( );
