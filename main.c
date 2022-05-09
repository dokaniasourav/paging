#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TABLE_SIZE 4
#define INPUT_SIZE 24

struct table_str {
    int page_number;
    int reference_bit;
    int modified_bit;
    int validity_bit;
    int last_use_index;
};

int main(int argc, char* argv[])
{
    char replacement_policy[50];
    int last_used_global = 0;

    float a = 0.1;
    if(a == 0.1) {
        printf("True");
    }

    char *policy_str[4] = {"First In First Out", "Least Recently Used", "Second Chance", "Invalid Entry"};
    /***************  Initialization sequence  ************************************/
    scanf_s("%[^\n]s", replacement_policy);
    enum {FIFO, LRU, SEC, INVALID} policy = INVALID;

    if(strcasecmp(replacement_policy, "LRU") == 0 || strcasecmp(replacement_policy, "Least recently used") == 0 || strcasecmp(replacement_policy, "") == 0) {
        policy = LRU;
    } else if(strcasecmp(replacement_policy, "FIFO") == 0 || strcasecmp(replacement_policy, "First In First Out") == 0) {
        policy = FIFO;
    } else if(strcasecmp(replacement_policy, "SEC") == 0 || strcasecmp(replacement_policy, "Second Chance") == 0 || strcmp(replacement_policy, "SecondChance") == 0) {
        policy = SEC;
    }
    printf("Policy entered = %s, entered = %s \n", policy_str[policy], replacement_policy);

    struct table_str page_table[TABLE_SIZE];

    for(int i=0; i<TABLE_SIZE; i++) {
        page_table[i].reference_bit = 0;
        page_table[i].validity_bit = 0;
        page_table[i].last_use_index = 0;
    }

    int string_index = 0;
    char* input_string = "0 2 1 3 5 4 6 3 7 4 7 3 3 5 5 3 1 1 1 7 2 3 4 1";

    int page_number, page_index = 0, flag, replace_index;
    for(int k=0; k<INPUT_SIZE; ++k, ++string_index) {
        if(input_string[string_index] == 0) {
            break;
        } else if(input_string[string_index] < '0' || input_string[string_index] > '9') {
            page_number = 0;
            continue;
        }
        page_number = (page_number * 10) + (input_string[string_index] - '0');
        page_index = page_number % TABLE_SIZE;

        if(input_string[string_index+1] < '0' || input_string[string_index+1] > '9') {
            printf("Accessing page number: %d\n", page_number);

            flag = 0;
            for(int i=0; i<TABLE_SIZE; i++) {
                if(page_table[i].validity_bit == 0) {
                    page_table[i].page_number = page_number;
                    page_table[i].validity_bit = 1;
                    page_table[i].reference_bit = 1;
                    page_table[i].last_use_index = last_used_global;
                    last_used_global++;
                    flag = 1;
                    break;
                }
                if(page_table[i].page_number == page_number) {
                    page_table[i].last_use_index = last_used_global;
                    last_used_global++;
                    flag = 2;
                    break;
                }
            }
            if(flag == 0) {             /***************  No elements found in the table ***************/
                if(policy == LRU) {
                    replace_index = 0;
                    for(int x=0; x<TABLE_SIZE; x++) {
                        if(page_table[x].last_use_index < page_table[replace_index].last_use_index) {
                            replace_index = x;
                        }
                    }
                    last_used_global++;
                    page_table[replace_index].page_number = page_number;
                    page_table[replace_index].last_use_index = last_used_global;
                    page_table[replace_index].reference_bit = 1;
                } else if(policy == FIFO) {
                    replace_index = (replace_index+1)%TABLE_SIZE;
                }
            }

        } else {
            continue;
        }
    }





    /***************  Checking initial arguments  *********************************/
//    if(argc != 3) {
//        printf("Usage: %s {number_of_producers} {number_of_consumers} \n", argv[0]);
//        exit(0);
//    }

    printf("\n ******************************************* \n");
    printf(  " -------- Paging system  ------------------- \n");
    printf(  " -------- By: Sourav Dokania --------------- \n");
    printf(  " ******************************************* \n");

    return 0;
}

