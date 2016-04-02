#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define STR_LEN 256

int main(int argc, char* argv[]){

    int i, num_places, ret;

    /* list takes a command parameter */
	if ( argc <= 1  ) {
        printf("enter 'list help' for correct usage instructions\n");
        return 0;       
	}

	getenv("HOME");

	char* home = getenv("HOME");
	char list_save_path[ PATH_MAX ];
	strcpy( list_save_path, home );
	strcat( list_save_path, "/Documents/projects/list/list_save" );

    /* open save file for reading and writing (bytes) */
    FILE* store = fopen(list_save_path, "ab+");

    if ( !store ) {
        return 0;
        printf("error: could not access save file.");
    } 

    num_places = ftell( store ) / STR_LEN;
    /* printf("%d\n", num_places); */
    rewind( store );

    
    if ( strncmp(argv[1], "help", strlen(argv[1])) == 0 ){

        printf("USAGE:\n");
        printf("    list print -- print entire list\n");
        printf("    list add -- add new entry to the list\n");
        printf("    list del [n] -- remove the nth entry from the list\n");
        printf("    * max entry size is %d characters\n", STR_LEN);

    } else if ( strncmp(argv[1], "print", strlen(argv[1])) == 0 ) {

        char* temp = malloc(STR_LEN);
        for ( i = 0; i < num_places; i++ ) {

            fseek( store, STR_LEN * i, SEEK_SET );

            /* printf("pos: %d\n", (int) (ftell( store ) / sizeof(place))); */

            ret = fread( temp, STR_LEN, 1, store );

            if ( errno != 0 ) { 
                perror("error");
            } else {
                printf("%d. %s\n", i + 1, temp);
            }
        }

        free( temp );

    } else if ( strncmp(argv[1], "add", strlen(argv[1])) == 0 ) {

        char* new = malloc(STR_LEN);
        scanf("%[^\n]s", new);
        fseek( store, 0, SEEK_END );
        fwrite( new, STR_LEN, 1, store );

        free( new );

    } else if ( strncmp(argv[1], "del", strlen(argv[1])) == 0 ) {

        fclose( store );

        FILE* store = fopen(list_save_path,"rb+");

        int copy_start = (int) strtol(argv[2], (char **)NULL, 10);

        if ( copy_start > num_places || copy_start <= 0 ) {
            printf("item #%d does not exist\n", copy_start);
            return 0;
        }
        
        int copy_size = num_places - copy_start;
        int paste_start = copy_start - 1;

        char* temp = malloc( STR_LEN * copy_size );
        fseek( store, STR_LEN * copy_start, SEEK_SET );
        fread( temp, STR_LEN, copy_size, store );

        fseek( store, STR_LEN * paste_start, SEEK_SET );
        fwrite( temp, STR_LEN * copy_size, 1, store );
        ftruncate( fileno(store), (num_places - 1) * STR_LEN );

    } else if ( strncmp(argv[1], "clear", strlen(argv[1])) == 0 ) {
    	
    	ftruncate( fileno(store), 0 );

    } else {

        printf("enter 'list help' for correct usage instructions\n");
        return 0;
    }

    fclose( store );

	return 0;
}
