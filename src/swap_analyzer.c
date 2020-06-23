#include "../include/swap_analyzer.h"

int
main()
  {
    long int info_size = get_info_size();
    long int swap_info[ info_size ];
    get_info( swap_info );
    print_parsed_info( swap_info, info_size );
  }

long int
get_info_size()
  {
    FILE *file = fopen(LOG_PATH, "r");
    long int i = 1;
    if( file != NULL )
      {
        char line[INFO_SIZE];
        while( fgets(line, INFO_SIZE, file) != NULL )
          {
            i++;
          }
        i -= 8;
      }
      fclose(file);
      return i;
  }

void
get_info( long int * swap_info )
  {
    FILE *file = fopen(LOG_PATH, "r");
    if( file != NULL )
      {
        char line[INFO_SIZE];
        int i;
        for(i = 0; i < 7; i++)
          fgets(line, INFO_SIZE, file);

        i = 0;
        while( fgets(line, INFO_SIZE, file) != NULL )
          {
            char *aux = strtok(line, "\t");
            aux = strtok(NULL, "\t\t");
            swap_info[i] = strtol(aux, NULL, 10);
            i++;
          }
      }
    fclose(file);
  }

void
print_parsed_info( long int * swap_info, long int size )
  {
    long int acum = 0;
    long int max = 0;
    long int min = LONG_MAX;
    long int i;
    long int avg;
    long int unused;
    int recom;
    char analysis_start[TIMESTAMP_SIZE];
    char timestamp[TIMESTAMP_SIZE];
    char total_swap[SWAP_SIZE];

    for(i = 0; i < size; i++)
      {
        acum += swap_info[i];

        if( swap_info[i] > max )
          max = swap_info[i];
        if( swap_info[i] < min )
          min = swap_info[i];
      }

    get_analysis_start( analysis_start );
    get_timestamp( timestamp );
    get_total_swap( total_swap );

    avg = acum / size;
    unused = strtol( total_swap, NULL, 10 ) - max;
    recom = (int)(strtol( total_swap, NULL, 10 ) - unused);
    recom = (int) (recom * 1.5);

    printf("\n#############################################################\n");
    printf(  "####################### Swap analyzer #######################\n");
    printf(  "#############################################################\n\n");
    printf("Data extracted from %ld entries\n", size);
    printf("See the entire log in %s\n\n", LOG_PATH);
    printf("Analysis started: \t\t%s\n", analysis_start);
    printf("Analysis finished: \t\t%s\n\n", timestamp);
    printf("Average swap memory used: \t%ld MB\n", avg);
    printf("Maximum swap memory used: \t%ld MB\n", max);
    printf("Minimum swap memory used: \t%ld MB\n\n", min);
    printf("Total swap memory size: \t%s MB\n", total_swap);
    printf("Minimum unused swap memory: \t%ld MB\n\n", unused);
    printf("Posible new swap memory size: \t%d MB\n", recom);
    printf("Last recommendation is the result of (Max. swap used) * (1.5)\n\n");
  }

void
get_analysis_start( char *analysis_start )
  {
    FILE *file = fopen(LOG_PATH, "r");
    if( file != NULL )
      {
        char line[INFO_SIZE];
        int i;
        for(i = 0; i < 5; i++)
          fgets(line, INFO_SIZE, file);
        sprintf( analysis_start, "%s", line);
        analysis_start[ strlen(analysis_start) - 1] = '\0';
      }
    fclose(file);
  }

void
get_total_swap( char *total_swap)
  {
    FILE *file = fopen(SWAP_PATH, "r");

    if( file != NULL)
      {
        char line[INFO_SIZE];
        fgets(line, INFO_SIZE, file);
        fgets(line, INFO_SIZE, file);

        char *aux = strtok(line, "\t");
        aux = strtok(NULL, "\t");

        sprintf(total_swap, "%s", aux);
      }
    fclose( file );
  }
