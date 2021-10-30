#include "../inc/pathfinder.h"

void mx_fill_array(int ***array, const size_t size, char **islands_txt, const island** islands){
    for (int i = 0; islands_txt[i]; i++)
    {
        char *first = mx_strndup(islands_txt[i], mx_get_char_index(islands_txt[i], '-'));
        islands_txt[i] += mx_get_char_index(islands_txt[i], '-') + 1;
        char *second = mx_strndup(islands_txt[i], mx_get_char_index(islands_txt[i], ','));
        islands_txt[i] += mx_get_char_index(islands_txt[i], ',') + 1;
        int weight = mx_atoi(islands_txt[i]);
        int row = 0;
        int col = 0;
        int row_checked = 0;
        int col_checked = 0;
        for (size_t j = 0; j < size; j++)
        {
            if (mx_strcmp(first, islands[j]->name) == 0 && !row_checked)
            {
                row_checked = 1;
                row = islands[j]->index;
            }
            else if (mx_strcmp(second, islands[j]->name) == 0 && !col_checked)
            {
                col = islands[j]->index;
                col_checked = 1;
            }

            if (row_checked && col_checked)
                break;
        }
        (*array)[row][col] = weight;
        (*array)[col][row] = weight;
    }
}

