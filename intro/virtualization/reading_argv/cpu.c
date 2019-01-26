#include <stdio.h>
#include <stdlib.h>
#include "../../../common.h"

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        fprintf(stderr, "usage: cpu <string>\n");
        exit(1);
    }
    
    char *str = argv[1];
    while (1) {
        Spin(1);
        printf("%s\n", str);
    }

    return 0;
}


// $ gcc -o cpu.out cpu.c -Wall; ./cpu.out strs

// running multiple instances from the same terminal
// $ ./cpu.out A & 
// $ ./cpu.out B & 
// $ ./cpu.out C & 
// $ ./cpu.out D &

// stopging bg processes
// $ kill processid

