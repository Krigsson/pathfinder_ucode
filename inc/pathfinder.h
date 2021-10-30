#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <fcntl.h>

#include "../libmx/inc/libmx.h"
#define INF 9999999
#define INT_MAX 2147483647

//structures
typedef struct s_island{
    char *name;
    int index;
}               island;


typedef struct s_route{
    int *route;
    int paths;
}               route;

//functions
island **mx_get_file_errors(const char *filename);
void mx_fill_array(int ***array, const size_t size, char **islands_txt, const island** islands);
int **mx_warshall(int **init, const size_t size);
void mx_print_spaths(const int **init, int **warshall_array, int islands_count, const island **islands);
void mx_clean_islands(island ***islands);
#endif
