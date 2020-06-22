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
    FILE *file = fopen("/var/log/swap_analysis.log", "r");
    long int i = 1;
    if( file != NULL )
      {
        char line[INFO_SIZE];
        while( fgets(line, INFO_SIZE, file) != NULL )
          {
            i++;
          }
        i -= 6;
      }
      return i;
  }

void
get_info( long int * swap_info )
  {
    FILE *file = fopen("/var/log/swap_analysis.log", "r");
    if( file != NULL )
      {
        char line[INFO_SIZE];
        int i;
        for(i = 0; i < 5; i++)
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
  }

void
print_parsed_info( long int * swap_info, long int size )
  {
    long int acum = 0;
    long int max = 0;
    long int min = LONG_MAX;
    long int i;
    for(i = 0; i < size; i++)
      {
        acum += swap_info[i];

        if( swap_info[i] > max )
          max = swap_info[i];
        if( swap_info[i] < min )
          min = swap_info[i];
      }
    float avg = (float) ( (acum / size) );

    printf("\n-Swap analyzer-\n\n");
    printf("Data extracted from %ld entries\n\n", size);
    printf("Average swap memory: %.2f MB\n", avg);
    printf("Maximum swap memory: %ld MB\n", max);
    printf("Minimum swap memory: %ld MB\n\n", min);
  }
