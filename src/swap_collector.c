#include "../include/swap_analyzer.h"

unsigned long entry;

int
main()
  {
    entry = 0;
    char swap[SWAP_SIZE];
    char info[INFO_SIZE];
    init_log();

    while ( 1 )
      {
        entry++;
        read_swap_info( swap );
        parse_info( info, swap );
        write_log( info );
        sleep();
      }
  }

void
init_log()
  {
    FILE *file = fopen(LOG_PATH, "w+");

    if( file != NULL)
      {
        char msg[INFO_SIZE];
        char timestamp[TIMESTAMP_SIZE];
        get_timestamp( timestamp );
        sprintf(msg,  "-Swap analysis-\n\nNew entry each %d second/s\n\n%s\n\n"
                      , SLEEP_S_TIME, timestamp);
        fprintf(file, "%s<entry>\t\t<swap size>[MB]\n", msg);
      }
    fclose( file );
  }

void
read_swap_info( char *buffer )
  {
    FILE *file = fopen(SWAP_PATH, "r");

    if( file != NULL)
      {
        char line[INFO_SIZE];
        fgets(line, INFO_SIZE, file);
        fgets(line, INFO_SIZE, file);

        char *aux = strtok(line, "\t");
        aux = strtok(NULL, "\t");
        aux = strtok(NULL, "\t");

        sprintf(buffer, "%s", aux);
      }
    fclose( file );
  }

void
parse_info( char *buffer, char *swap)
  {
    sprintf( buffer, "%ld\t\t%s", entry, swap);
  }

void
write_log( char *info )
  {
    FILE *file = fopen(LOG_PATH, "a");

    if( file != NULL)
      {
        fprintf(file, "%s\n", info);
      }
    fclose( file );
  }

void
sleep()
  {
    struct timespec time;
    time.tv_sec = SLEEP_S_TIME;
    time.tv_nsec = SLEEP_NS_TIME;
    nanosleep(&time ,NULL);
  }
