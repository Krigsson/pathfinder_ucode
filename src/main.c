#include "../inc/pathfinder.h"

#define V 7
int main(int argc, char *argv[])
{
    if(argc != 2){
        mx_printerr("usage: ./pathfinder [filename]\n");
        return -1;
    }

    island **islands = mx_get_file_errors(argv[1]);
    size_t size = 0;
    for(; islands[size]; size++);

    char *input = mx_file_to_str(argv[1]);
    while(*input != '\n') input++;
    input++;
    char **islands_txt = mx_strsplit(input, '\n');

    int **G = (int **)malloc(sizeof(int *) * size);
    for (size_t i = 0; i < size; i++)
    {
        G[i] = (int *)malloc(sizeof(int) * size);
        for (size_t j = 0; j < size; j++)
            G[i][j] = INF;
    }

    mx_fill_array(&G, size, islands_txt, (const island**) islands);

    int **warshall_arr = mx_warshall(G, size);
    mx_print_spaths((const int**)G, warshall_arr, size, (const island**) islands);


    mx_clean_islands(&islands);
    for(size_t i = 0; i < size; i++){
        free(warshall_arr[i]);
        free(G[i]);
    }
    free(warshall_arr);
    free(G);
    return 0;
}
