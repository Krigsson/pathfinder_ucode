#include "../inc/pathfinder.h"

int **mx_warshall(int **init, const size_t size)
{

    int **warshall_matrix = (int **)malloc(sizeof(int *) * size);
    for (size_t i = 0; i < size; i++)
    {
        warshall_matrix[i] = (int *)malloc(sizeof(int) * size);
        for (size_t j = 0; j < size; j++)
        {
            warshall_matrix[i][j] = init[i][j];
        }
    }

    for (size_t k = 0; k < size; k++)
    {
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = i + 1; j < size; j++)
            {

                if (warshall_matrix[k][j] != INF && warshall_matrix[i][k] != INF && 
                        warshall_matrix[i][k] + warshall_matrix[k][j] < warshall_matrix[i][j]){
                    warshall_matrix[i][j] = warshall_matrix[i][k] + warshall_matrix[k][j];
                    warshall_matrix[j][i] = warshall_matrix[i][k] + warshall_matrix[k][j];
                }
            }
        }
        warshall_matrix[k][k] = 0;
    }

    return warshall_matrix;
}
