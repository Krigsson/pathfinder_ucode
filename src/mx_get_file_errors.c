#include "../inc/pathfinder.h"
int mx_first_line(const char *str_file){
    while(*str_file != '\n'){
        if(!mx_isdigit(*str_file)){
            return 1;
        }
        str_file++;
    }

    return 0;
}
int mx_check_num(const char *str_file){
    while(*str_file){
        if(!mx_isdigit(*str_file)){
            return 1;
        }
        str_file++;
    }

    return 0;
}

int mx_check_island_existance(island ***islands, int *insert_index, const char *island){
    int exist = 0;
    for (int i = 0; i < *insert_index; i++)
    {
        if (mx_strcmp((*islands)[i]->name, island) == 0)
        {
            exist = 1;
            break;
        }
    }
    if(!exist){
        (*islands)[*insert_index]->name = (char*) island;
        (*islands)[*insert_index]->index = *insert_index;
        *insert_index += 1;
    }

    return exist;
}

int mx_invalid_line(const char *line, island ***islands, int *insert_index){
    int invalid = 0;
    int delim_index_dash = mx_get_char_index(line, '-');
    int delim_index_comma = 0;
    if(delim_index_dash < 0){
        return 1;
    }

    char *first_dis = mx_strndup(line, delim_index_dash);
    if(first_dis == NULL){
        invalid = 1;
    }

    line += (delim_index_dash + 1);
    delim_index_comma = mx_get_char_index(line, ',');
    if(delim_index_comma < 0){
        invalid = 1;
    }
    char *second_dist = mx_strndup(line, delim_index_comma);

    if(second_dist == NULL){
        invalid = 1;
    }
    if(mx_strlen(first_dis) == 0 || mx_strlen(second_dist) == 0){
        invalid = 1;
    }
    if(mx_strcmp(first_dis, second_dist) == 0){
        invalid = 1;
    }
    line += (delim_index_comma + 1);
    if(mx_check_num((const char*) line)){
        invalid = 1;
    }
    for(int i = 0; i < mx_strlen(first_dis); i++){
        if(!mx_isalpha(first_dis[i])){
            invalid = 1;
            break;
        }
    }
    for(int i = 0; i < mx_strlen(second_dist); i++){
        if(!mx_isalpha(second_dist[i])){
            invalid = 1;
            break;
        }
    }
    if(first_dis != NULL || mx_strlen(first_dis) != 0){
       
        if(mx_check_island_existance(islands, insert_index, first_dis)){
            free(first_dis);
        }
    }
    if(second_dist != NULL || mx_strlen(second_dist) != 0){
        if(mx_check_island_existance(islands, insert_index, second_dist)){
            free(second_dist);
        }
    }

    return invalid; 
}

int mx_invalid_lines(const char *str_file, island ***islands){
    char **lines = mx_strsplit(str_file, '\n');
    int islands_count = mx_atoi(lines[0]);
    int insert_index = 0;
    int invalid_line = 0;
    (*islands) = (island**)malloc(sizeof(island*) * (islands_count + 1));
    for(int i = 0; i < islands_count + 1; i++){
        (*islands)[i] = (island*)malloc(sizeof(island));
    }
    
    for(int i = 1; lines[i]; i++){
        if(mx_invalid_line(lines[i], islands, &insert_index)){
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 1));
            mx_printerr(" is not valid\n");
            mx_del_strarr(&lines);
            invalid_line = 1;
            break;
        }
    }
    if(lines)
        mx_del_strarr(&lines);
    if(!invalid_line)
        (*islands)[insert_index] = NULL;
    if(islands_count != insert_index || invalid_line){
        (*islands)[islands_count] = NULL;
        if(!invalid_line)
            mx_printerr("error: invalid number of islands\n");
        return 1;
    }
    return 0;
}

int mx_duplicate_lines(const char *str_file){

    char **lines = mx_strsplit(str_file, '\n');
    int size = 0;
    int invalid = 0;
    for(; lines[size]; size++);

    for(int i = 1; i < size - 1 && !invalid; i++){
        for(int j = i + 1; j < size && !invalid; j++){
            char *first = mx_strndup(lines[i], mx_get_char_index(lines[i], ','));
            char *second = mx_strndup(lines[j], mx_get_char_index(lines[j], ','));
            if(mx_strcmp(first, second) == 0){
                invalid = 1;
            }

            free(first);
            free(second);
        }
    }

    mx_del_strarr(&lines);
    return invalid;
}

int mx_big_bridges_length(const char *str_file){
    int invalid = 0;
    int sum = 0;
    char **lines = mx_strsplit(str_file, '\n');
    for(int i = 1 ; lines[i]; i++){
        char *temp = mx_strstr(lines[i], ",");
        temp++;
        int num_temp = mx_atoi(temp);

        int overflow = num_temp + sum;
        if(sum > 0 && num_temp > 0 && overflow < 0){
            invalid = 1;
            break;
        }
        else if(sum < 0 && num_temp < 0 && overflow > 0){
            invalid = 1;
            break;
        }
        sum += overflow;
    }
    mx_del_strarr(&lines);
    return invalid;
}

island **mx_get_file_errors(const char *filename){
    int open_file = open(filename, O_RDONLY);
    int has_errors = 0;
    island **islands = NULL;
    char *str_file = 0;
    if(open_file < 0){
        mx_printerr("error: file ");
        mx_printerr(filename);
        mx_printerr(" does not exist\n");
        has_errors = 1;    
    }
    else if(mx_strlen((str_file = mx_file_to_str(filename))) == 0){
        mx_printerr("error: file ");
        mx_printerr(filename);
        mx_printerr(" is empty\n");
        has_errors = 1;
    }
    else if(mx_first_line(str_file)){
        mx_printerr("error: line 1 is not valid\n");
        has_errors = 1;
    }
    else if(mx_invalid_lines(str_file, &islands) > 0){
        has_errors = 1;
    }
    else if(mx_duplicate_lines(str_file)){
        mx_printerr("error: duplicate bridges\n");
        has_errors = 1;
    }
    else if(mx_big_bridges_length(str_file)){
        mx_printerr("sum of bridges lengths is too big\n");
        has_errors = 1;
    }

    close(open_file);
    if(str_file != NULL)
        free(str_file);
    if(has_errors){
        if(islands != NULL)
            mx_clean_islands(&islands);
        exit(-1);
    }
    return islands;
}

