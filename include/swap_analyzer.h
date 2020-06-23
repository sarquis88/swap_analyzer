#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

#define INFO_SIZE             128
#define SWAP_SIZE             16
#define LOAD_SIZE             8
#define TIMESTAMP_SIZE        64
#define SLEEP_S_TIME          60
#define SLEEP_NS_TIME         0
#define LOG_PATH	      "/var/log/swap_analyzer.log"

void init_log                     ( );
void read_swap_info               ( char *buffer );
void read_load_info               ( char *buffer );
void parse_info                   ( char *buffer, char *swap, char *load );
void write_log                    ( char * info);
void sleep                        ( );

long int get_info_size            ( );
void get_info                     ( long int * swap_info );
void print_parsed_info            ( long int * swap_info, long int size );
void get_analysis_start           ( char *analysis_start );

void get_timestamp                ( char *buffer );
