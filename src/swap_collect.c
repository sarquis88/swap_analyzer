#include "../include/swap_analysis.h"

unsigned long entry;

int
main()
  {
    entry = 0;
    char swap[SWAP_SIZE];
    char load[LOAD_SIZE];
    char info[INFO_SIZE];
    init_log();

    while ( 1 )
      {
        entry++;

        read_swap_info( swap );

        read_load_info( load );

        parse_info( info, swap, load );

        write_log( info );

        sleep();
      }
  }

void
init_log()
  {
    FILE *file = fopen("/var/log/swap_analysis.log", "w+");

    if( file != NULL)
      {
        char msg[INFO_SIZE];
        sprintf(msg,  "-Swap analysis-\n\nNew entry each %d second/s\n\n"
                      , SLEEP_S_TIME);
        fprintf(file, "%s<entry>\t\t<swap size>[MB]\t\t<CPU load average>\n",
                      msg);
      }
    fclose( file );
  }

void
read_swap_info( char *buffer )
  {
    FILE *file = fopen("/proc/swaps", "r");

    if( file != NULL)
      {
        char line[INFO_SIZE];
        fgets(line, INFO_SIZE, file);
        fgets(line, INFO_SIZE, file);

        char *aux = strtok(line, "\t");
        aux = strtok(NULL, "\t");

        sprintf(buffer, "%s", aux);
      }
    fclose( file );
  }

void
read_load_info( char *buffer )
  {
    double load_avg[1];
    getloadavg(load_avg, 1);
    sprintf(buffer, "%.2f", load_avg[0]);
  }

void
parse_info( char *buffer, char *swap, char *load)
  {
    sprintf( buffer, "%ld\t\t%s\t\t\t%s", entry, swap, load);
  }

void
write_log( char *info )
  {
    FILE *file = fopen("/var/log/swap_analysis.log", "a");

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
