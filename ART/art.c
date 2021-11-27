/* File         : art.c */
/* Deskripsi    : menampilkan ascii art */

#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 128

void print_image(char *filename) {
    FILE *fptr = NULL;

    if ((fptr = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "error opening %s\n", filename);
    }
    char read_string[MAX_LEN];
    while (fgets(read_string, sizeof(read_string), fptr) != NULL)
        printf("%s", read_string);
    fclose(fptr);
}

void MainMenu() {
    print_image("ART/mainmenu.txt");
}
void Command() {
    print_image("ART/command.txt");
}