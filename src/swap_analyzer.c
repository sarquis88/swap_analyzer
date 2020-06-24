#include "../include/swap_analyzer.h"

int
main()
  {
    int info_size = get_info_size();
    int swap_values[ info_size ];
    get_info( swap_values );
    print_parsed_info( swap_values, info_size );
  }

int
get_info_size()
  {
    FILE *file = fopen(LOG_PATH, "r");
    int i = 1;
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
get_info( int * swap_info )
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
            swap_info[i] = (int) strtol(aux, NULL, 10);
            i++;
          }
      }
    fclose(file);
  }

void
print_parsed_info( int * swap_info, int size )
  {
    int acum = 0;
    int max = 0;
    int min = INT_MAX;
    int avg;
    int i;
    int unused;
    int total;
    int recom;
    double max_percent;
    double min_percent;
    double avg_percent;
    double unused_percent;
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

    total = (int) strtol( total_swap, NULL, 10 );
    avg = acum / size;
    unused = total - max;
    recom = (int) ( (total - unused) * 1.5 );
    if (recom == 0)
      {
        recom = (int) (total * 0.1);
      }

    max_percent = ( (double) max / (double) total ) * 100;
    min_percent = ( (double) min / (double) total ) * 100;
    avg_percent = ( (double) avg / (double) total ) * 100;
    unused_percent = ( (double) unused / (double) total ) * 100;

    printf("\n###########################################################\n");
    printf("###################### Swap analyzer ######################\n");
    printf("###########################################################\n\n");
    printf("Data extracted from %d entries\n", size);
    printf("See the entire log in %s\n\n", LOG_PATH);
    printf("Analysis started: \t\t%s\n", analysis_start);
    printf("Analysis finished: \t\t%s\n\n", timestamp);
    printf( "Average swap memory used: \t%d MB (%.0f%c of total)\n",
            avg, avg_percent, 37);
    printf( "Maximum swap memory used: \t%d MB (%.0f%c of total)\n",
            max, max_percent, 37);
    printf( "Minimum swap memory used: \t%d MB (%.0f%c of total)\n\n",
            min, min_percent, 37);
    printf( "Total swap memory size: \t%s MB\n", total_swap);
    printf( "Minimum unused swap memory: \t%d MB (%.0f%c of total)\n\n",
            unused, unused_percent, 37);
    printf( "Posible new swap memory size: \t%d MB (150%c of max. \n"
            "used, or 10%c of total if max. used is zero)\n\n",
            recom, 37, 37);
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
