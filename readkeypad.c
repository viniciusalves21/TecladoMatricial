#include <stdio.h>
#include "pico/stdlib.h"

int readkeypad (int mat[4][4]){
    int ret, i, j;
        for(i = 0; i < 4; i++){
            if(!gpio_get(mat[i][0])){
                for(j = 0; j < 4; j++){
                    if(!gpio_get(mat[i][j])){
                        ret = mat[i][j];
                        return ret;
                    }
                }
            } 
        }
}























