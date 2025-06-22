/*
Assigned by:
Name: Brian Sch
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void flush_input() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

typedef struct playlist
{
    struct Linked_list* prev;

    int id;
    char artist_name[30];
    char album_name[30];
    char track_name[30];
    int track_number;

    struct Linked_list* next;
} node;


int countLines(FILE* fp) {

    int count = 1;  // Line counter (result)
    char c;  // To store a character read from file

    // Extract characters from file and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp)) // EOF defines the end of a file
        if (c == '\n') // Increment count if this character is newline
            count++;

    return count;
}

void printlist(node* head) {
    node* current = head;
    printf("ID   ArtistName                    AlbumName                     TrackName                     TrackNo\n");
    while (current != NULL) {
        printf("%-5d%-30s%-30s%-30s%d\n", current->id, current->artist_name, current->album_name, current->track_name, current->track_number);
        current = current->next;
    }
    printf("\n");
}

void insert_at_end(node** head, node* node_to_insert) {

    node* temp = *head;

    if (*head == NULL) {
        *head = node_to_insert;
    }
    else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node_to_insert;
        node_to_insert->prev = temp;
    }
}


node* read_file(char file_name[200]) {

    printf("Reading file...\n");

    // file variables
    FILE* fp;

    fp = fopen(file_name, "r");
    int i = 0;
    char buffer[200];

    // linked list variables
    node* head = NULL;
    node *tmp = NULL;

    // temp variables
    int id;
    char artist_name[30];
    char album_name[30];
    char track_name[30];
    int track_number;
    //


    // checking if file exists
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }


    fseek(fp, sizeof(node) -4 , SEEK_SET);
    

    while (!feof(fp)) {

        node* tmp = malloc(sizeof(node));

        tmp->prev = NULL;
        
        fgets(buffer, 6, fp);
        sscanf(buffer, "%d", &tmp->id);
        fgets(tmp->artist_name, 31, fp);
        fgets(tmp->album_name, 31, fp);
        fgets(tmp->track_name, 31, fp);
        fgets(buffer, 6, fp);
        sscanf(buffer, "%d", &tmp->track_number);
        

        tmp->next = NULL;

        tmp->artist_name[29] = '\0';
        tmp->album_name[29] = '\0';
        tmp->track_name[29] = '\0';
        
        insert_at_end(&head, tmp);

        i++;
    }


    fclose(fp);

    printf("File reading was succesful!\n");

    return head;

}

void write_file(char file_name[200], node** head){
    // file variables
    FILE* fp;
    node* current = *head;

    fp = fopen(file_name, "w");

    // checking if file exists
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    fprintf(fp, "ID   ArtistName                    AlbumName                     TrackName                     TrackNo\n");

    while (current != NULL) {
        if (current->next != NULL) {

            fprintf(fp, "%-5d%-30s%-30s%-30s%d\n", current->id, current->artist_name, current->album_name, current->track_name, current->track_number);
            
            current = current->next;
        }
        else {
            fprintf(fp, "%-5d%-30s%-30s%-30s%d", current->id, current->artist_name, current->album_name, current->track_name, current->track_number);
            
            current = current->next;

        }
    }
    fclose(fp);
}

//----------------------------------------------

// 1. Play the current song
void play_curr_song(node *current){
    
    
    printf("\nnow playing:\n");
    printf("ID   ArtistName                    AlbumName                     TrackName                     TrackNo\n");
    printf("%-5d%-30s%-30s%-30s%d", current->id, current->artist_name, current->album_name, current->track_name, current->track_number);
    return 0;
}

//2. Next song
node* next_song(node* current) {
    if (current->next != NULL) {
        current = current->next;
        return current;
    }
    else {
        printf("\n\nThere isn't anymore songs in the list!\n");
        return current;
    }
}

//3. Previous song
node* prev_song(node* current) {
    if (current->prev != NULL) {
        current = current->prev;
        return current;
    }
    else {
        printf("\n\nThis is the first song in the list!\n");
        return current;
    }
}

//4. Search for a song

node* search_song(node* head) {

    node* tmp = head;
    int i;
    char buff[200];
    char tmp_name[30];
    int compare;
    int sel;

    printf("1. Search by 'Artist Name'\n");
    printf("2. Search by 'Album Name'\n");
    printf("3. Search by 'Track_name'\n");
    printf("\nPlease enter the search settings:");

    gets(buff);
    sscanf(buff, "%d", &sel);


    while (sel > 3) {

        printf("\nNo such action exists yet!\n");
        printf("Please select an action: ");
        gets(buff);
        sscanf(buff, "%d", &sel);

    }
    switch (sel) {
    case 1:
        i = 0;
        char artist_name[30];

        printf("Please enter the artist name:");
        scanf("%s",&artist_name);
        sscanf(tmp->artist_name, "%s", &tmp_name);
        compare = strcmp(artist_name, tmp_name);

        while (compare != 0) {
            if(tmp->next == NULL){
                printf("\nThe artist '%s' wasn't found\n", artist_name);
                return NULL;
            }
            else {
                tmp = tmp->next;
                sscanf(tmp->artist_name, "%s", &tmp_name);
                compare = strcmp(artist_name, tmp_name);
                i++;
            }
            
        }
        printf("\nThe artist '%s' was found!\n", artist_name);
        return tmp;
        break;

    case 2:
        i = 0;
        char album_name[30];

        printf("Please enter the album's name:");
        scanf("%s", &album_name);
        sscanf(tmp->album_name, "%s", &tmp_name);
        compare = strcmp(album_name, tmp_name);

        while (compare != 0) {
            if (tmp->next == NULL) {
                printf("\nThe artist '%s' wasn't found\n", album_name);
                return NULL;
            }
            else {
                tmp = tmp->next;
                sscanf(tmp->album_name, "%s", &tmp_name);
                compare = strcmp(album_name, tmp_name);
                i++;
            }
            
        }
        printf("\nThe artist '%s' was found!\n", album_name);
        return tmp;
        break;

    case 3:
        i = 0;
        char track_name[30];

        printf("Please enter the album's name:");
        scanf("%s", &track_name);
        sscanf(tmp->track_name, "%s", &tmp_name);
        compare = strcmp(track_name, tmp_name);

        while (compare != 0) {
            if (tmp->next == NULL) {
                printf("\nThe artist '%s' wasn't found\n", track_name);
                return NULL;
            }
            else {
                tmp = tmp->next;
                sscanf(tmp->track_name, "%s", &tmp_name);
                compare = strcmp(track_name, tmp_name);
                i++;
            }
            
        }
        printf("\nThe artist '%s' was found!\n", track_name);
        return tmp;
        break;
    }
} 

//5. Delete the current song

node* delete_song(node* curr, node** head){
    node* temp, * temp2, * del = curr;

    if (del->next == NULL) {
        temp = curr->prev;
        temp->next = NULL;
        curr = temp;
        free(del);
        return temp;
    }

    else if (del->prev == NULL) {
        temp = curr->next;
        temp->prev = NULL;
        curr = temp;
        *head = curr;
        free(del);
        return temp;
    }
    else {

        temp = curr->prev;
        temp2 = curr->next;
        temp->next = temp2;
        temp2->prev = temp;
        curr = temp;
        free(del);
        return temp;
    }

}

//6. Add a song to the end of the list

void add_song(node** head){
    node* temp = *head;
    int flag = 0;

    
    // creating new node
    node* new = malloc(sizeof(node));

    new->prev = NULL;

    printf("\nEnter the song's ID:");
    scanf("%d", &new->id);

    while (temp != NULL) {

        if (new->id == temp->id) {
            printf("\nID already exists!");
            printf("\nEnter the song's ID:");
            scanf("%d", &new->id);
            temp = *head;
        }
        else {
            temp = temp->next;
        }
 
    }
    flush_input();
    printf("\nEnter the artist name:");
    gets(new->artist_name, 31);
    printf("\nEnter the album's name:");
    gets(new->album_name, 31);
    printf("\nEnter the track name:");
    gets(new->track_name, 31);
    printf("\nEnter the track number:");
    scanf("%d", &new->track_number);

    new->next = NULL;

    // insert at end
  
    insert_at_end(&*head, new);

}

//7. Sort the playlist

void sort_playlist(node** head){
    node* tmp1 = *head;
    node* tmp2 = tmp1->next;
    int sel;

    printf("\n\n");
    printf("1. Sort by 'Artist Name'\n");
    printf("2. Sort by 'Album Name'\n");
    printf("3. Sort by 'Track_name'\n");
    printf("\nPlease enter the search settings:");

    scanf("%d", &sel);


    while (sel > 3) {

        printf("\nNo such action exists yet!\n");
        printf("Please select an action: ");
        scanf("%d", &sel);

    }
    switch (sel) {
    case 1:
        while (tmp1->next != NULL) {
            if ((strcmp(tmp1->artist_name, tmp2->artist_name)) > 0) {

                node swap1;

                swap1 = *tmp1;

                tmp1->id = tmp2->id;
                strcpy(tmp1->artist_name, tmp2->artist_name);
                strcpy(tmp1->album_name, tmp2->album_name);
                strcpy(tmp1->track_name, tmp2->track_name);
                tmp1->track_number = tmp2->track_number;

                tmp2->id = swap1.id;
                strcpy(tmp2->artist_name, swap1.artist_name);
                strcpy(tmp2->album_name, swap1.album_name);
                strcpy(tmp2->track_name, swap1.track_name);
                tmp2->track_number = swap1.track_number;

                tmp1 = *head;
                tmp2 = tmp1->next;

            }
            else {
                tmp1 = tmp1->next;
                tmp2 = tmp2->next;
            }

        }
        break;

    case 2:
        while (tmp1->next != NULL) {
            if ((strcmp(tmp1->album_name, tmp2->album_name)) > 0) {

                node swap1;

                swap1 = *tmp1;

                tmp1->id = tmp2->id;
                strcpy(tmp1->artist_name, tmp2->artist_name);
                strcpy(tmp1->album_name, tmp2->album_name);
                strcpy(tmp1->track_name, tmp2->track_name);
                tmp1->track_number = tmp2->track_number;

                tmp2->id = swap1.id;
                strcpy(tmp2->artist_name, swap1.artist_name);
                strcpy(tmp2->album_name, swap1.album_name);
                strcpy(tmp2->track_name, swap1.track_name);
                tmp2->track_number = swap1.track_number;

                tmp1 = *head;
                tmp2 = tmp1->next;

            }
            else {
                tmp1 = tmp1->next;
                tmp2 = tmp2->next;
            }

        }
        break;

    case 3:
        while (tmp1->next != NULL) {
            if ((strcmp(tmp1->track_name, tmp2->track_name)) > 0) {

                node swap1;

                swap1 = *tmp1;

                tmp1->id = tmp2->id;
                strcpy(tmp1->artist_name, tmp2->artist_name);
                strcpy(tmp1->album_name, tmp2->album_name);
                strcpy(tmp1->track_name, tmp2->track_name);
                tmp1->track_number = tmp2->track_number;

                tmp2->id = swap1.id;
                strcpy(tmp2->artist_name, swap1.artist_name);
                strcpy(tmp2->album_name, swap1.album_name);
                strcpy(tmp2->track_name, swap1.track_name);
                tmp2->track_number = swap1.track_number;

                tmp1 = *head;
                tmp2 = tmp1->next;

            }
            else {
                tmp1 = tmp1->next;
                tmp2 = tmp2->next;
            }

        }
        break;
    }

}

//8. Shuffle the playlist

void shuffle(node** head, struct tm* info){

    

    time_t rawtime;
    time(&rawtime);
    info = localtime(&rawtime);
    int dominator = info->tm_sec;
    node* tmp1 = *head;
    node* tmp2 = tmp1->next;

    while (tmp1->next != NULL) {
        if (tmp1->id % (dominator + 1 ) > tmp2->id % (dominator + 1)) {

            node swap1;

            swap1 = *tmp1;

            tmp1->id = tmp2->id;
            strcpy(tmp1->artist_name, tmp2->artist_name);
            strcpy(tmp1->album_name, tmp2->album_name);
            strcpy(tmp1->track_name, tmp2->track_name);
            tmp1->track_number = tmp2->track_number;

            tmp2->id = swap1.id;
            strcpy(tmp2->artist_name, swap1.artist_name);
            strcpy(tmp2->album_name, swap1.album_name);
            strcpy(tmp2->track_name, swap1.track_name);
            tmp2->track_number = swap1.track_number;

            tmp1 = *head;
            tmp2 = tmp1->next;
            //tmp1 = tmp1->next;
            //tmp2 = tmp2->next;

        }
        else {
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }

    }
}

//----------------------------------------------

void free_memory(node* head) {
    node* temp = head;

    while (temp != NULL) {
        node* free_node = temp;
        temp = temp->next;
        free(free_node);
    }
}

void logger(FILE* log, char message[200]){

    time_t rawtime = time(NULL);
    char* time_str = ctime(&rawtime);
    time_str[strlen(time_str) - 1] = '\0';

    fprintf(log, "[%s][%s]\n", time_str, message);
    
}

//----------------------------------------------






int main(int argc, char* argv[])
{
    // time for logger
    time_t rawtime = time(NULL);
    char* time_str = ctime(&rawtime);
    time_str[strlen(time_str) - 1] = '\0';
    printf("[%s]\n", time_str);

    struct tm* info;

    time(&rawtime);
    info = localtime(&rawtime);
    //
    

    if (argc < 3) {
        argv[2] = "logger.txt";
    }
   
    
    
    FILE* log;
    log = fopen(argv[2], "w+");
    
    

    int exit = 0;

    node* head;
    node* current;
    node* srch_temp;

    

    if (argc < 2) {
        argv[1] = "filename.txt";
    }

    
    char buff[200];
    char start[10];

    

    

    unsigned int sel;

    head = read_file(argv[1]);

    current = head;

    logger(log, "Playlist started");

    while (exit == 0) {

        printf("\n\n~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!\n\n");
        printf("Welcome to Brian's playlist!");
        printf("\n\n~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!\n\n");
        printlist(head);
        printf("\n\n~!~!~!~!~!~ Main Menu ~!~!~!~!~!~!~!\n\n");

        printf("1. Play the current song\n");
        printf("2. Next song\n");
        printf("3. Previous song\n");
        printf("4. Search a song\n");
        printf("5. Delete the current song\n");
        printf("6. Add a song to the playlist\n");
        printf("7. Sort the playlist\n");
        printf("8. Shuffle\n");
        printf("9. Exit\n\n");

        printf("Please select an action: ");
        gets(buff);
        sscanf(buff, "%d", &sel);

        
        while (sel > 9) {

            printf("\nNo such action exists yet!\n");
            printf("Please select an action: ");
            gets(buff);
            sscanf(buff, "%d", &sel);

        }
        
     
        switch (sel)
        {
        case 1:

            play_curr_song(current);
            logger(log, "Playlist playing the current song");
       
            break;

        case 2:

            current = next_song(current);
            play_curr_song(current);
            logger(log, "Playlist playing the next song");
            break;

        case 3:

            current = prev_song(current);
            play_curr_song(current);
            logger(log, "Playlist playing the previous song");
   
            break;

        case 4:
            
            srch_temp = search_song(head);

            if (srch_temp != NULL) {  
                current = srch_temp;
                printf("\nSearch completed!\n");
                play_curr_song(current);
            }

            flush_input();
            logger(log, "Playlist searches for a song");

            
            break;

        case 5:

            current = delete_song(current, &head);
            printf("Song deleted from the playlist!");
            logger(log, "Song deleted from the playlist");
            
            break;

        case 6:

            add_song(&head);
            printf("\nSong added to the playlist!\n");
            logger(log, "Song added to the playlist");
            break;

        case 7:

            sort_playlist(&head);
            printf("\nSorting completed!\n");
            logger(log, "The playlist was sorted");

            break;

        case 8:

            shuffle(&head, info);
            printf("\n\n Shuffle completed!\n\n");
            logger(log, "The playlist was shuffled");
            

            break;

        case 9:
            
            exit = 1;
            logger(log, "An exit from the playlist was requested");
            break;

        }
        printf("\n\n~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!\n\n");
        
        if (exit != 1) {
            printf("To go back to the menu enter any character:");
            gets(start);
            
        }
        



    }

    write_file(argv[1], &head);
    logger(log, "Playlist closed succesfuly");
    fclose(log);
    free_memory(head);
    return 0;

}