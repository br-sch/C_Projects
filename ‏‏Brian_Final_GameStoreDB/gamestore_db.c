/*
Assigned by:
Name: Brian Sch
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>


// Defyining paths
#define USERS_PATH "users.txt"
#define ITEMS_PATH "items.txt"
#define LOG_PATH "log.txt"
//

void flush_input() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// Defyining structs
typedef struct user
{
    struct user* prev;

    char username[16];
    char password[16];
    char fullname[21];
    int level;

    struct user* next;
} user;

typedef struct item
{
    struct item* prev;

    int id;
    char item_name[43];
    char plataform[16];
    float price;
    bool instock;
    char release_date[11];

    struct item* next;
} item;


//


// user section start ----------------------------------------------

// 1.View user list 
void print_user_list(user* head) {
    user* current = head;
    printf("%-15s %-15s %-1s %-20s\n", "Username", "Password", "L", "Full Name");
    while (current != NULL) {
        printf("%-15s %-15s %-1d %-20s\n", current->username, current->password, current->level, current->fullname);
        current = current->next;
    }
    printf("\n");
}

// 2. Insert a user into the linked list 
void insert_at_end(user** head, user* node_to_insert) {

    user* temp = *head;

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

// 3. Read user file
user* read_user_file(char file_name[200]) {

    // file variables
    FILE* fp;

    fp = fopen(file_name, "r");
    char buffer[200];

    // linked list variables
    user* head = NULL;
    user *tmp = NULL;

    // temp variables
    char username[16];
    char password[16];
    char fullname[21];
    int level, check;
    char temp[1];
    //


    // checking if file exists if not it creates a new file
    if (fp == NULL)
    {
        printf("File doesnt exist\n");
        printf("Creating new file\n");

        fp = fopen(file_name, "w+");
        fprintf(fp, "%-15s %-15s %-1s %-20s\n", "Username", "Password", "L", "Full Name");
        fprintf(fp, "%-15s %-15s %-1d %-20s", "admin", "admin", 3, "System_Manager");
        fclose(fp);
        fp = fopen(file_name, "r");
        
    }
    

    // avoids the first row of datad
    fseek(fp, 56, SEEK_SET);
    

    while (!feof(fp)) {

        user* tmp = malloc(sizeof(user));

        tmp->prev = NULL;
        
        fgets(tmp->username, 16, fp);
        fgets(buffer, 2, fp);
        fgets(tmp->password, 16, fp);
        fgets(buffer, 4, fp);
        check = sscanf(buffer, "%d", &tmp->level);
        fgets(tmp->fullname, 21, fp);
        fgets(buffer, 4, fp);
        
        

        tmp->next = NULL;

        tmp->username[15] = '\0';
        tmp->password[15] = '\0';
        tmp->fullname[20] = '\0';
        
        insert_at_end(&head, tmp);
    }


    fclose(fp);


    return head;

}

// 4. Write user file
void write_user_file(char file_name[200], user** head){
    // file variables
    FILE* fp;
    user* current = *head;

    fp = fopen(file_name, "w+");

    fprintf(fp, "%-15s %-15s %-1s %-20s\n", "Username", "Password", "L", "Full Name");

    while (current != NULL) {
        if (current->next != NULL) {

            fprintf(fp, "%-15s %-15s %-1d %-20s\n", current->username, current->password, current->level, current->fullname);
            
            current = current->next;
        }
        else {
            fprintf(fp, "%-15s %-15s %-1d %-20s", current->username, current->password, current->level, current->fullname);
            
            current = current->next;

        }
    }
    fclose(fp);
}

// 5. Search for a user
user* search_user(user* user_head, char user_name[16]) {

    user* tmp = user_head;
    char tmp_name[16];
    int compare;

    char artist_name[30];
    sscanf(tmp->username, "%s", &tmp_name);
    compare = strcmp(user_name, tmp_name);

    while (compare != 0) {
      if(tmp->next == NULL){
        return NULL;
      }
      else {
        tmp = tmp->next;
        sscanf(tmp->username, "%s", &tmp_name);
        compare = strcmp(user_name, tmp_name);
      }
            
     }

    return tmp;
} 

// 6. Delete user
void delete_user(user** head) {
    user* temp, * temp2, * del, *curr;
    char user_name[16];
    int sel, check;

    printf("\nEnter the username to delete: ");
    gets(user_name, 16);

    del = search_user(*head, user_name);
    curr = del;

    if(del == NULL)
    {
        printf("\nUsername not found\n");
        return;
    }
    printf("%-15s %-15s %-1s %-20s\n", "Username", "Password", "L", "Full Name");
    printf("%-15s %-15s %-1d %-20s\n", curr->username, curr->password, curr->level, curr->fullname);

    printf("\nIs this the user to delete? [Yes ('1') / No ('0')]: ");
    check = scanf("%d", &sel);


    if (sel == 1)
    {
        if (del->next == NULL) {
            temp = curr->prev;
            temp->next = NULL;
            curr = temp;
            free(del);
        }

        else if (del->prev == NULL) {
            temp = curr->next;
            temp->prev = NULL;
            curr = temp;
            *head = curr;
            free(del);
        }
        else {

            temp = curr->prev;
            temp2 = curr->next;
            temp->next = temp2;
            temp2->prev = temp;
            curr = temp;
            free(del);
        }
    }

    printf("\nUser deleted\n");
    flush_input();
    return;
}

// 7. Add user
void add_user(user** head) {
    user* temp = *head;
    char user_name[16];
    int check;

    // creating new node
    user* new = malloc(sizeof(user));

    new->prev = NULL;

    printf("\nEnter the username to add: ");
    gets(user_name, 16);
    temp = search_user(*head, user_name);

    while (temp != NULL) {

        printf("\nUsername already exists!");
        printf("\nEnter the username: ");
        gets(user_name, 16);
        temp = search_user(*head, user_name);

    }

    strcpy(new->username, user_name);
    printf("\nEnter the password: ");
    gets(new->password, 16);
    printf("\nEnter the full name: ");
    gets(new->fullname, 21);
    printf("\nEnter the security level[1-3]: ");
    check = scanf("%d", &new->level);

    new->next = NULL;

    // insert at end

    insert_at_end(&*head, new);

    printf("\nUser name added!\n");
    flush_input();

    return;
}

// 8. Update user
void update_user(user* head)
{
    user* temp = head;
    char user_name[16];
    int sel, check;

    printf("\nEnter the username to update: ");
    gets(user_name, 16);

    temp = search_user(head, user_name);
    

    if (temp == NULL)
    {
        printf("\nUsername not found");
        return;
    }
    printf("%-15s %-15s %-1s %-20s\n", "Username", "Password", "L", "Full Name");
    printf("%-15s %-15s %-1d %-20s\n", temp->username, temp->password, temp->level, temp->fullname);

    printf("Is this the user to update? [Yes ('1') / No ('0')]: ");
    check = scanf("%d", &sel);


    if (sel == 1)
    {
        flush_input();
        printf("\nEnter the new username: ");
        gets(temp->username, 16);
        printf("\nEnter the new password: ");
        gets(temp->password, 16);
        printf("\nEnter the new full name: ");
        gets(temp->fullname, 21);
        printf("\nEnter the new security level[1-3]: ");
        scanf("%d", &temp->level);

        printf("\nUser updated!\n");
    }

    flush_input();
    return;
}

// User section end ----------------------------------------------


void remove_spaces(char *str, char *tmp_name) {
    int i = 0;
    int j = 0;
    //int len = strlen(str);

    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != 32)
        {
            tmp_name[j] = str[i];
            j++;
        }

    }
    tmp_name[j] = '\0';

}


// Item section start ----------------------------------------------

// 1.View item list 
void print_item_list(item *head) {
    item *current = head;
    printf("%-4s %-42s%-15s%-8s %-10s %-12s\n", "ID", "Name", "Plataform", "Price", "instock", "Release Date");
    while (current != NULL) {
        printf("%-4d %-42s%-15s%-8.2f %-10i %-10s\n", current->id, current->item_name, current->plataform, current->price, current->instock, current->release_date);
        current = current->next;
    }
    printf("\n");
}

// 2. Insert an item into the linked list 
void insert_item_end(item** head, item* node_to_insert) {

    item* temp = *head;

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

// 3. Read item file
item* read_item_file(char file_name[200]) {

    

    // file variables
    FILE* fp;

    fp = fopen(file_name, "r");
    int i = 0;
    char buffer[200];

    // linked list variables
    item* head = NULL;
    item* tmp = NULL;

    // temp variables
    int id;
    char item_name[43];
    char plataform[16];
    float price;
    bool instock;
    char release_date[11];
    //


    // checking if file exists
    if (fp == NULL)
    {
        printf("File doesnt exist!\n");
        printf("Creating new file...\n");

        fp = fopen(file_name, "w+");
        fprintf(fp, "%-4s %-42s%-15s%-8s %-10s %-10s\n", "ID", "Name", "Plataform", "Price", "instock", "Release Date");
        fprintf(fp, "%-4d %-42s%-15s%-8.2f %-10i %-10s", 0, "Sample", "sample", 00.00, 1, "01/01/2000");
        fclose(fp);
        fp = fopen(file_name, "r");
    }


    fseek(fp, sizeof(item) + 8, SEEK_SET);


    while (!feof(fp)) {

        item* tmp = malloc(sizeof(item));

        tmp->prev = NULL;

        fgets(buffer, 6, fp);
        sscanf(buffer, "%d", &tmp->id);
        fgets(tmp->item_name, 43, fp);
        fgets(tmp->plataform, 16, fp);
        fgets(buffer, 8, fp);
        sscanf(buffer, "%f", &tmp->price);
        fgets(buffer, 14, fp);
        sscanf(buffer, "%d", &tmp->instock);
        fgets(tmp->release_date, 12, fp);


        tmp->next = NULL;
        tmp->release_date[10] = '\0';
        insert_item_end(&head, tmp);

        i++;
    }


    fclose(fp);

    

    return head;

}

// 4. Write item file
void write_item_file(char file_name[200], item** head)
{
    // file variables
    FILE* fp;
    item* current = *head;

    fp = fopen(file_name, "w+");

    // checking if file exists
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    fprintf(fp, "%-4s %-42s%-15s%-8s %-10s %-10s\n", "ID", "Name", "Plataform", "Price", "instock", "Release Date");

    while (current != NULL)
    {
        if (current->next != NULL)
        {

            fprintf(fp, "%-4d %-42s%-15s%-8.2f %-10i %-10s\n", current->id, current->item_name, current->plataform, current->price, current->instock, current->release_date);

            current = current->next;
        }
        else
        {
            fprintf(fp, "%-4d %-42s%-15s%-8.2f %-10i %-10s", current->id, current->item_name, current->plataform, current->price, current->instock, current->release_date);

            current = current->next;

        }
    }
    fclose(fp);
}

// 5. Search for an item
void search_item(item* head)
{

    item* tmp = head;
    int i;
    char buff[200];
    int compare;
    int sel;

    printf("1. Search by 'Item Name'\n");
    printf("2. Search by 'Plataform'\n");
    printf("3. Search by 'Price Tag'\n");
    printf("4. Search by 'Instock'(yes/no)\n");
    printf("5. Search by 'Release Date'\n");
    printf("\nPlease enter the search settings:");

    gets(buff);
    sscanf(buff, "%d", &sel);


    while (sel > 5)
    {

        printf("\nNo such action exists yet!\n");
        printf("Please select an action: ");
        gets(buff);
        sscanf(buff, "%d", &sel);

    }
    switch (sel)
    {
        case 1:
            // search by item's name

            i = 0;
            char item_name[43];
            char tmp_name[43];
            char tmp_name2[43];

            printf("Please enter the item's name:");
            gets(item_name);
            remove_spaces(item_name, tmp_name2);

            printf("%-4s %-42s%-15s%-8s %-10s %-12s\n", "ID", "Name", "Plataform", "Price", "instock", "Release Date");

            while (tmp != NULL)
            {
                
                remove_spaces(tmp->item_name, tmp_name);
                compare = strcmp(tmp_name2, tmp_name);

                if (compare == 0)
                {
                    printf("%-4d %-42s%-15s%-8.2f %-10i %-10s\n", tmp->id, tmp->item_name, tmp->plataform, tmp->price, tmp->instock, tmp->release_date);
                    i++;
                }
                tmp = tmp->next;

            }
            if (i == 0)
            {
                printf("\nThe item '%s' was not found\n", item_name);
            }

            break;

        case 2:
            // search by plataform
        
            i = 0;
            char plataform[16];
            char tmp_plat[16];
            char tmp_plat2[16];

            printf("Please enter the plataform:");
            gets(plataform);
            remove_spaces(plataform, tmp_plat2);

            printf("%-4s %-42s%-15s%-8s %-10s %-12s\n", "ID", "Name", "Plataform", "Price", "instock", "Release Date");

            while (tmp != NULL)
            {
                remove_spaces(tmp->plataform, tmp_plat);
                compare = strcmp(tmp_plat2, tmp_plat);

                if (compare == 0)
                {
                    printf("%-4d %-42s%-15s%-8.2f %-10i %-10s\n", tmp->id, tmp->item_name, tmp->plataform, tmp->price, tmp->instock, tmp->release_date);
                    i++;
                }
                tmp = tmp->next;

            }
            if (i == 0)
            {
                printf("\nThe plataform '%s' was not found\n", plataform);
            }

            break;

        case 3:
            // search by price tag
            i = 0;
            float tmp_price;

            printf("Please enter if you want to search above the price ('1') or below ('0'):");
            scanf("%d", &sel);
            printf("Please enter the price tag:");
            scanf("%f", &tmp_price);

            printf("%-4s %-42s%-15s%-8s %-10s %-12s\n", "ID", "Name", "Plataform", "Price", "instock", "Release Date");

            switch (sel)
            {
                case 0:

                    while (tmp != NULL) {

                        if (tmp->price < tmp_price) {
                            printf("%-4d %-42s%-15s%-8.2f %-10i %-10s\n", tmp->id, tmp->item_name, tmp->plataform, tmp->price, tmp->instock, tmp->release_date);
                            i++;
                        }
                        tmp = tmp->next;

                    }
                    if (i == 0) {
                        printf("\nItems below the price '%.2f' were not found\n", tmp_price);
                    }

                    break;

                case 1:

                    while (tmp != NULL) {

                        if (tmp->price > tmp_price) {
                            printf("%-4d %-42s%-15s%-8.2f %-10i %-10s\n", tmp->id, tmp->item_name, tmp->plataform, tmp->price, tmp->instock, tmp->release_date);
                            i++;
                        }
                        tmp = tmp->next;

                    }
                    if (i == 0) {
                        printf("\nItems above the price '%.2f' were not found\n", tmp_price);
                    }
                    break;
            }

            flush_input();
            break;

        case 4:
            // Search by instock

            i = 0;
            bool tmp_stock;

            printf("Please enter if you want to search an item in stock ('1') or out of stock ('0'):");
            scanf("%d", &sel);

            printf("%-4s %-42s%-15s%-8s %-10s %-12s\n", "ID", "Name", "Plataform", "Price", "instock", "Release Date");

            switch (sel)
            {
                case 0:

                    while (tmp != NULL)
                    {

                        if (!tmp->instock)
                        {
                            printf("%-4d %-42s%-15s%-8.2f %-10i %-10s\n", tmp->id, tmp->item_name, tmp->plataform, tmp->price, tmp->instock, tmp->release_date);
                            i++;
                        }
                        tmp = tmp->next;

                    }
                    if (i == 0)
                    {
                        printf("\nItems below the price '%.2f' were not found\n", tmp_price);
                    }

                    break;

                case 1:

                    while (tmp != NULL)
                    {

                        if (tmp->instock)
                        {
                            printf("%-4d %-42s%-15s%-8.2f %-10i %-10s\n", tmp->id, tmp->item_name, tmp->plataform, tmp->price, tmp->instock, tmp->release_date);
                            i++;
                        }
                        tmp = tmp->next;

                    }
                    if (i == 0)
                    {
                        printf("\nItems above the price '%.2f' were not found\n", tmp_price);
                    }
                    break;
            }

            flush_input();
            break;

        case 5:
            // search by dates

            i = 0;
            char date[11];
            char tmp_date[11];

            char *day;
            char *month;
            char *year;

            char *tmp_day;
            char *tmp_month;
            char *tmp_year;

            printf("Please enter the release date to search as 'dd/mm/yyyy':");
            gets(date);
            
            day = strtok(date, "/");
            month = strtok(NULL, "/");
            year = strtok(NULL, "/");

            printf("Please enter if you want to search an item before ('0') or after ('1') the date:");
            scanf("%d", &sel);

            printf("%-4s %-42s%-15s%-8s %-10s %-12s\n", "ID", "Name", "Plataform", "Price", "instock", "Release Date");

            switch(sel)
            {
                case 0:
                    // before the date
                    while (tmp->next != NULL)
                    {
                        strcpy(tmp_date, tmp->release_date);
                        tmp_day = strtok(tmp_date, "/");
                        tmp_month = strtok(NULL, "/");
                        tmp_year = strtok(NULL, "/");

                        compare = strcmp(tmp_year, year);

                        if (compare < 0)
                        {
                            printf("%-4d %-42s%-15s%-8.2f %-10i %-10s\n", tmp->id, tmp->item_name, tmp->plataform, tmp->price, tmp->instock, tmp->release_date);
                            i++;
                        }
                        else if (compare == 0) 
                        {
                            compare = strcmp(tmp_month, month);

                            if (compare < 0)
                            {
                                printf("%-4d %-42s%-15s%-8.2f %-10i %-10s\n", tmp->id, tmp->item_name, tmp->plataform, tmp->price, tmp->instock, tmp->release_date);
                                i++;
                            }
                            else if (compare == 0)
                            {
                                compare = strcmp(tmp_day, day);
                                
                                if (compare < 0)
                                {
                                    printf("%-4d %-42s%-15s%-8.2f %-10i %-10s\n", tmp->id, tmp->item_name, tmp->plataform, tmp->price, tmp->instock, tmp->release_date);
                                    i++;
                                }

                            }

                        }
                        tmp = tmp->next;

                    }
                    if (i == 0)
                    {
                        printf("\nItem's earlier than '%s' were not found\n", date);
                    }
                    break;

                case 1:
                    // after the date
                    while (tmp->next != NULL)
                    {
                        strcpy(tmp_date, tmp->release_date);
                        tmp_day = strtok(tmp_date, "/");
                        tmp_month = strtok(NULL, "/");
                        tmp_year = strtok(NULL, "/");

                        compare = strcmp(tmp_year, year);

                        if (compare > 0)
                        {
                            printf("%-4d %-42s%-15s%-8.2f %-10i %-10s\n", tmp->id, tmp->item_name, tmp->plataform, tmp->price, tmp->instock, tmp->release_date);
                            i++;
                        }
                        else if (compare == 0)
                        {
                            compare = strcmp(tmp_month, month);

                            if (compare > 0)
                            {
                                printf("%-4d %-42s%-15s%-8.2f %-10i %-10s\n", tmp->id, tmp->item_name, tmp->plataform, tmp->price, tmp->instock, tmp->release_date);
                                i++;
                            }
                            else if (compare == 0)
                            {
                                compare = strcmp(tmp_day, day);

                                if (compare >= 0)
                                {
                                    printf("%-4d %-42s%-15s%-8.2f %-10i %-10s\n", tmp->id, tmp->item_name, tmp->plataform, tmp->price, tmp->instock, tmp->release_date);
                                    i++;
                                }

                            }

                        }
                        tmp = tmp->next;

                    }
                    if (i == 0)
                    {
                        printf("\nItem's later than '%s' were not found\n", date);
                    }
                    break;     
            }

            flush_input();
            break;
    }
}

// 6. Delete an item
void delete_item(item** head) {
    

    item* curr = *head;
    int i = 0;
    int id, check;
    int sel;
 

    printf("Please enter the id of the item to delete:");
    scanf("%d", &id);

    printf("\n%-4s %-42s%-15s%-8s %-10s %-12s\n", "ID", "Name", "Plataform", "Price", "instock", "Release Date");

    flush_input();
    while (curr != NULL && curr->id != id)
    {
        curr = curr->next;

    }
    if (curr->id == id)
    {
        printf("%-4d %-42s%-15s%-8.2f %-10i %-10s\n", curr->id, curr->item_name, curr->plataform, curr->price, curr->instock, curr->release_date);
        i++;

    }
    else
    {
        printf("Item was not found\n");
        return;
    }

    printf("Is this the item to delete [Yes ('1') / No ('0')]?: ");
    scanf("%d", &sel);

    if (sel == 1) {

        item* temp, * temp2, * del = curr;

        if (del->next == NULL) {
            temp = curr->prev;
            temp->next = NULL;
            curr = temp;
            free(del);
        }

        else if (del->prev == NULL) {
            temp = curr->next;
            temp->prev = NULL;
            curr = temp;
            *head = curr;
            free(del);
        }
        else {

            temp = curr->prev;
            temp2 = curr->next;
            temp->next = temp2;
            temp2->prev = temp;
            curr = temp;
            free(del);
        }
    }

    flush_input();
    return;
}

//7. Add an item
void add_item(item** head) {
    item* temp = *head;
    int flag = 0;


    // creating new node
    item* new = malloc(sizeof(item));

    new->prev = NULL;

    printf("\nEnter the item's ID: ");
    scanf("%d", &new->id);

    while (temp != NULL) {

        if (new->id == temp->id) {
            printf("\nID already exists!");
            printf("\nEnter the item's ID: ");
            scanf("%d", &new->id);
            temp = *head;
        }
        else {
            temp = temp->next;
        }
    }
    flush_input();
    printf("\nEnter the games name: ");
    gets(new->item_name, 43);
    printf("\nEnter the plataform: ");
    gets(new->plataform, 16);
    printf("\nEnter the price: ");
    scanf("%f", &new->price);
    printf("\nEnter if the item is in stock( 0 for no, 1 for yes): ");
    scanf("%d", &new->instock);
    flush_input();
    printf("\nEnter the release date (dd/mm/yyyy): ");
    gets(new->release_date, 11);

    new->next = NULL;

    // insert at end

    insert_item_end(&*head, new);

}

//8. Update item price
void update_item(item* head)
{
    item* tmp = head;
    item* update_item;
    int i = 0;
    int id;
    float new_price;

    printf("Please enter the ID of the item to update:");
    scanf("%d", &id);

    printf("\n%-4s %-42s%-15s%-8s %-10s %-12s\n", "ID", "Name", "Plataform", "Price", "instock", "Release Date");

    flush_input();
    while (tmp != NULL && tmp->id != id)
    {
        tmp = tmp->next;

    }
    if (tmp->id == id)
    {
        printf("%-4d %-42s%-15s%-8.2f %-10i %-10s\n", tmp->id, tmp->item_name, tmp->plataform, tmp->price, tmp->instock, tmp->release_date);
        i++;

        printf("\nEtner the new price tag: ");
        scanf("%f", &new_price);
        tmp->price = new_price;

    }
    else
    {
        printf("Item was not found\n");
    }

    flush_input();
    return;
}

// Item section end   ----------------------------------------------



// Logger and free memory ----------------------------------------------
void free_user_memory(user* head) {
    user* temp = head;

    while (temp != NULL) {
        user* free_node = temp;
        temp = temp->next;
        free(free_node);
    }
}

void free_item_memory(item* head) {
    item* temp = head;

    while (temp != NULL) {
        item* free_node = temp;
        temp = temp->next;
        free(free_node);
    }
}

void getDateTime(int* day, int* month, int* year, int* hours, int* mins)
{
    time_t rawtime;
    struct tm timeinfo;

    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);

    *day = timeinfo.tm_mday;
    *month = timeinfo.tm_mon + 1;
    *year = timeinfo.tm_year + 1900;
    *hours = timeinfo.tm_hour;
    *mins = timeinfo.tm_min;
}

void logger(FILE* log, char message[200]){

    int day, month, year, hours, mins;
    getDateTime(&day, &month, &year, &hours, &mins);

    fprintf(log, "[%02d/%02d/%d][%02d:%02d][%s]\n", day, month, year, hours, mins, message);
    
}

//----------------------------------------------





int main(int argc, char* argv[])
{
    // time for logger
    int day, month, year, hours, mins;
    getDateTime(&day, &month, &year, &hours, &mins);
    printf("Current computer time: %02d/%02d/%d, %02d:%02d\n", day, month, year, hours, mins);
    time_t rawtime = time(NULL);
    char* time_str = ctime(&rawtime);
    time_str[strlen(time_str) - 1] = '\0';
    printf("[%s]\n", time_str);

    struct tm* info;

    time(&rawtime);
    info = localtime(&rawtime);
    // 
    

    // creating log
    if (argc < 4)
    {
        argv[3] = LOG_PATH;
    }

    FILE* log;
    log = fopen(argv[3], "w+");
    //


    // reading user file
    user* user_head;

    if (argc < 2)
    {
        argv[1] = USERS_PATH;
    }

    user_head = read_user_file(argv[1]);
    //


    // program start message
    printf("\n\n~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!\n\n");
    printf("Welcome to Brainspot program!");
    printf("\n\n~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!\n\n");
    //


    // log in section ~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!

    user* user_current = user_head;
    user* user_logged;
    char user_name[16];
    char password[16];
    char tmp_name[16];
    int count = 0;
    int compare, check;

    printf("\n\n~!~!~!~!~!~ Log in Menu ~!~!~!~!~!~!~!\n\n");

    while (count < 3)
    {

        printf("Username: ");
        gets(user_name);
        printf("Password: ");
        gets(password);

        user_logged = search_user(user_head, user_name);

        if (user_logged != NULL) {

            sscanf(user_logged->password, "%s", &tmp_name);
            compare = strcmp(password, tmp_name);

            if (compare != 0) {
            printf("\nUsername or password are incorrect!\n\n");
            count++;
            }
            else count = 5;
        }
        else {
            printf("\nUsername or password are incorrect!\n\n");
            count++;
        }
    }

    if (count != 5)
    {
        printf("\nFailed to log in 3 times! The program will exit now!\n");
        return 0;
    }
    else
    {
        printf("Logged in successfully!\n\n");
    }
    // log in end ~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!


    // enter user menu option for security level 3
    int user_menu = 0;
    char buff[2];
    unsigned int sel;

    // user menu ~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!
    if (user_logged->level == 3)
    {
        while (user_menu == 0)
        {
            printf("\n\n~!~!~!~!~!~ User Menu ~!~!~!~!~!~!~!\n\n");

            printf("1. View user list\n");
            printf("2. Search for a user\n");
            printf("3. Add user to the list\n");
            printf("4. Update user\n");
            printf("5. Delete user\n");
            printf("6. Exit user menu\n\n");

            printf("Please select an action: ");

            gets(buff);
            check = sscanf(buff, "%d", &sel);

            while (sel > 6) {

                printf("\nNo such action exists yet!\n");
                printf("Please select an action: ");
                gets(buff);
                check = sscanf(buff, "%d", &sel);
            }

            switch (sel)
            {
            case 1:
                // 1. View user list
                print_user_list(user_head);


                logger(log, " '1. View user list' was selected ");
                break;

            case 2:
                // 2. Search for a user
                printf("\nSearch for username: ");
                gets(user_name);

                user_current = search_user(user_head, user_name);
                printf("\nSelected User:\n");
                printf("%-15s %-15s %-1s %-20s\n", "Username", "Password", "L", "Full Name\n");

                if (user_current == NULL) {
                    printf("\nUsername not found!\n");
                }
                else {
                    
                    printf("%-15s %-15s %-1d %-20s\n", user_current->username, user_current->password, user_current->level, user_current->fullname);
                }

                logger(log, " '2. Search for a user' was selected ");
                break;

            case 3:
                // 3. Add user to the list
                add_user(&user_head);

                logger(log, " '3. Add user to the list' was selected ");
                break;

            case 4:
                // 4. Update user
                update_user(user_head);

                logger(log, " '4. Update user' was selected ");
                break;

            case 5:
                // 5. Delete user
                delete_user(&user_head);

                logger(log, " '5. Delete user' was selected ");
                break;

            case 6:
                // 6. Exit user menu
                user_menu = 1;

                logger(log, " '5. Exit user menu' was selected ");
                break;
            }
        }
    }
    // user menu end ~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!
    

    // reading item file
    item* item_head;

    if (argc < 3)
    {
        argv[2] = ITEMS_PATH;
    }

    // printing item list
    printf("\n\n~!~!~!~!~!~ Item List ~!~!~!~!~!~!~!\n\n");
    item_head = read_item_file(argv[2]);
    print_item_list(item_head);
    printf("\n\n~!~!~!~!~!~ Item List ~!~!~!~!~!~!~!\n\n");
    //


    // item menu ~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!
    item* item_current = item_head;

    int item_menu = 0;
    int id;
    char item_name[43];
    char plataform[16];
    float price;
    bool instock;
    char release_date[11];

    while (item_menu == 0)
    {
        printf("\n\n~!~!~!~!~!~ Item Menu ~!~!~!~!~!~!~!\n\n");

        printf("1. View item list\n");
        printf("2. Search for an item\n");
        printf("3. Add item to the list\n");
        printf("4. Exit program\n");

        if (user_logged->level > 1)
        {
            printf("5. Update price item\n");
            printf("6. Delete item\n");
        }

        printf("\nPlease select an action: ");
        gets(buff);
        check = sscanf(buff, "%d", &sel);
        

        while ((sel > 6 && user_logged->level > 1) || (sel > 4 && user_logged->level == 1))
        {

            printf("\nNo such action exists yet!\n");
            printf("Please select an action: ");
            gets(buff);
            check = sscanf(buff, "%d", &sel);
        }

        switch (sel)
        {
            case 1:
                print_item_list(item_head);

                logger(log, " '1. View item list' was selected ");
                break;

            case 2:
                search_item(item_head);

                logger(log, " '2. Search for an item' was selected ");
                break;

            case 3:
                add_item(&item_head);
                printf("\nItem added to the list!\n");

                logger(log, " '3. Add item to the list' was selected ");
                break;

            case 4:
                item_menu = 1;

                logger(log, " '4. Exit item menu' was selected ");
                break;

            case 5:
                update_item(item_head);
                printf("\nItem price updated!\n");
                
                logger(log, " '5. Update item' was selected ");
                break;

            case 6:
                delete_item(&item_head);
                printf("\nItem deleted from the list!\n");
                
                logger(log, " '6. Delete item' was selected ");
                break;
        } 
    }
    // item menu end ~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!
    
    // closing program ~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!
    write_user_file(argv[1], &user_head);
    write_item_file(argv[2], &item_head);
    printf("\nwriting to files...\n");
    logger(log, "Program closed succesfuly");
    fclose(log);
    free_user_memory(user_head);
    free_item_memory(item_head);

    printf("Program closed succesfuly!\n");
    return 0;
}
