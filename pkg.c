#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __BASH_RUNAS "sudo"

void usage() {
    printf("pkg - A wrapper to merge basic xbps commands into one\n");
}

void as_root(char *arg) {
    char cmd[100];
    sprintf(cmd, "%s %s", __BASH_RUNAS, arg);
    system(cmd);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        usage();
        exit(1);
    }

    if (strcmp(argv[1], "in") == 0) {
        as_root("xbps-install");
        exit(0);
    } else if (strcmp(argv[1], "rm") == 0) {
        as_root("xbps-remove -R");
        exit(0);
    } else if (strcmp(argv[1], "srch") == 0) {
        system("xbps-query -Rs");
        exit(0);
    } else if (strcmp(argv[1], "clean") == 0) {
        printf("pkg: Cleaning cache...\n");
        as_root("xbps-remove -O");
        printf("pkg: Removing orphans...\n");
        as_root("xbps-remove -o");
        exit(0);
    } else if (strcmp(argv[1], "updt") == 0) {
        as_root("xbps-install -Su");
        exit(0);
    } else if (strcmp(argv[1], "show") == 0) {
        system("xbps-query -R");
        exit(0);
    } else if (strcmp(argv[1], "h") == 0) {
        usage();
        exit(0);
    } else {
        usage();
        exit(1);
    }

    return 0;
}
