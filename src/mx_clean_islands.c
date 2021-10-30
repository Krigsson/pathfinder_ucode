#include "../inc/pathfinder.h"
#include <stdio.h>
void mx_clean_islands(island ***islands){

    for(int i = 0; (*islands)[i]; i++){
        if((*islands)[i]->name)
            free((*islands)[i]->name);
        free((*islands)[i]);
    }

}

