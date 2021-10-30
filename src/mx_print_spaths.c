#include "../inc/pathfinder.h"

void mx_route(const int **init, int **warshall_array, route *way, int islands_count, const island **islands);
void mx_print_path(const int **init, route *way, const island **islands);

void mx_print_spaths(const int **init, int **warshall_array, int islands_count, const island **islands){

    route *way = (route*)malloc(sizeof(route));
    way->route = (int*)malloc(sizeof(int) * (islands_count + 1));
    for(int i = 0; i < islands_count; i++){
        for(int j = i + 1; j < islands_count; j++){
            way->paths = 1;
            way->route[0] = j;
            way->route[1] = i;
            mx_route(init, warshall_array, way, islands_count, islands);
        }
    }
    free(way->route);
    free(way);
}

void mx_route(const int **init, int **warshall_array, route *way, int islands_count, const island **islands){
    int end = way->route[way->paths];
    int start = way->route[0];
    for(int k = 0; k < islands_count; k++){
        if(k != way->route[way->paths] && (init[end][k] == warshall_array[end][start] - warshall_array[k][start])){
            way->paths++;
            way->route[way->paths] = k;
            mx_route(init, warshall_array, way, islands_count, islands);
            way->paths--;
        }
    }

    if(way->route[way->paths] != start) return;
    mx_print_path(init, way, islands);
}

void mx_print_path(const int **init, route *way, const island **islands){
    int distance = 0;

    for(int i = 0; i < 40; i++){
        mx_printchar('=');
    }
    mx_printstr("\nPath: ");
    mx_printstr(islands[way->route[1]]->name);
    mx_printstr(" -> ");
    mx_printstr(islands[way->route[0]]->name);
    mx_printchar('\n');
    mx_printstr("Route: ");
    for(int i = 1; i < way->paths + 1; i++){
        mx_printstr(islands[way->route[i]]->name);
        if(i < way->paths){
            mx_printstr(" -> ");
        }
    }

    mx_printstr("\nDistance: ");
        for (int i = 1; i < way->paths; i++) {
            int temp = init[way->route[i]][way->route[i + 1]];
            mx_printint(temp);
            distance += temp;
            if (i < way->paths - 1) {
                mx_printstr(" + ");
            }
        }

        if(way->paths != 2) {
            mx_printstr(" = ");
            mx_printint(distance);
        }
    mx_printchar('\n');
    for(int i = 0; i < 40; i++){
        mx_printchar('=');
    }
    mx_printchar('\n');
}
