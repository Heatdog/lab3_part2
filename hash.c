//has
// Created by yura on 26.04.2021.
//

#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "key1.h"
#include "for_all.h"


unsigned int hash(char *key, int size){
    unsigned int result;
    for (result = 0; *key != '\0'; key++){//как в книге кергана
        result = *key + (31 * result);
    }
    return (result % size);
}

Table *new_table(int size){
    Table *table = (Table*)malloc(sizeof (Table));
    table->ks2 = (KeySpace2**)calloc(size, sizeof (KeySpace2*));
    table->ks1 = (KeySpace1*)calloc(size, sizeof (KeySpace1));
    for (int i = 0; i < size; i++){
        table->ks2[i] = (KeySpace2*)malloc(sizeof (KeySpace2));
        table->ks2[i]->list = (List *)malloc(sizeof (List));
        table->ks2[i]->list->head = NULL;
        table->ks2[i]->release = 0;
        table->ks1[i].inf = NULL;
    }
    table->size = size;
    table->size1 = 0;
    return table;
}

void del_table(Table* table){
    for (int i = 0; i < table->size; i++){
        free_list(table->ks2[i]->list);
    }
    free(table->ks1);
    free(table->ks2);
    free(table);
}

void free_list(List* list){
    Info_and_key *ptr = NULL, *ptr_prev = NULL;
    ptr = list->head;
    while (ptr){
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev);
    }
    free(list);
}

////////////////////////////////////////////////////////////////////////////////

void print_hash_table(Table* table){
    unsigned int result;
    for (int i = 0; i < table->size; i++){
        Info_and_key *ptr = table->ks2[i]->list->head;
        if (ptr == NULL){
            continue;
        }
        result = hash(ptr->key, table->size);
        printf("\t%d -->", result);
        print_list(table->ks2[i]->list);
    }
}

void print_list(List* list){
    Info_and_key *ptr = list->head;
    while (ptr){
        print_list_element(ptr);
        ptr = ptr->next;
    }
}

void print_list_element(Info_and_key* ptr){
    printf("key (1 table)-->%d//Key (2 table)-->%s//Info-->%d//%d//%s\n", ptr->key1, ptr->key,ptr->inf->firs, ptr->inf->second, ptr->inf->text);
}


////////////////////////////////////////////////////////////

void add_hash_table(Table* table, char *key, Info* info, int key1){
    unsigned int result = hash(key, table->size);
    table->ks2[result] = add_hash_table_in(table->ks2[result], key, info, key1);
}

KeySpace2 *add_hash_table_in(KeySpace2* ks2, char *key, Info* info, int key1){
    Info_and_key *ptr_prev = NULL, *ptr = NULL;
    ptr_prev = ks2->list->head;
    ptr = (Info_and_key*)malloc(sizeof (Info_and_key));
    ptr->key = key;
    ptr->inf = info;
    ptr->key1 = key1;
    ptr->next = ptr_prev;
    ks2->list->head = ptr;
    ks2->release++;
    return ks2;
}

//////////////////////////////////////////////////////////////

Info_and_key *find_hash_element(Table* table, char *key, int n) {
    Info_and_key *info = NULL;
    unsigned int result = hash(key, table->size);
    info = find_hash_element_in_list(table->ks2[result], key, n);
    return info;
}

Info_and_key *find_hash_element_in_list(KeySpace2 *ks2, char *key, int n){
    Info_and_key *ptr = ks2->list->head;
    int summ, k = 1;
    if (n == 2){
        scan_int(&summ);
    }
    for (int i = 0; i < ks2->release; i++){
        if (strcmp(ptr->key, key) == 0){
            if (n == 2){
                if (k == summ){
                    return ptr;
                } else{
                    k++;
                }
            } else{
                print_list_element(ptr);
            }
        }
        ptr = ptr->next;
    }
    return NULL;
}

///////////////////////////////////////////////////////////////

void del_hash_table(Table* table, char *key, int n){
    unsigned int result = hash(key, table->size);
    del_hash_table_list(table->ks2[result], table, key, n);
}

void del_hash_table_list(KeySpace2* ks2, Table *table, char *key, int n){
    Info_and_key *ptr_prev = NULL, *ptr = NULL;
    ptr = ks2->list->head;
    int sum = 0;
    for (int i = 0; i < ks2->release; i++){
        if (strcmp(ptr->key, key) == 0){
            if (ks2->release == 1){
                if (n == 1){
                    delete_element_1(table, ptr->key1, 0);
                }
                free(ptr);
                ks2->list->head = NULL;
                ks2->release--;
                return;
            }else{
                if (ptr == ks2->list->head){
                    ks2->list->head = ptr->next;
                    if (n == 1){
                        delete_element_1(table, ptr->key1, 0);
                    }
                    free(ptr);
                    sum++;
                    ptr = ks2->list->head;
                } else{
                    ptr_prev->next = ptr->next;
                    if (n == 1){
                        delete_element_1(table, ptr->key1, 0);
                    }
                    free(ptr);
                    sum++;
                    ptr = ptr_prev->next;
                }
            }
        } else{
            ptr_prev = ptr;
            ptr = ptr->next;
        }
    }
    ks2->release -= sum;
}


/////////////////////////////////////////////////////////////

void del_special(Table* table, char *key, int release, int n){
    unsigned int result = hash(key, table->size);
    del_special_list(table->ks2[result], table, key, release, n);
}


void del_special_list(KeySpace2 *ks2, Table *table, char *key, int sum, int n){
    int k = 1;
    Info_and_key *ptr = NULL, *ptr_prev = NULL;
    ptr = ks2->list->head;
    for (int i = 0; i < ks2->release; i++){
        if (strcmp(key, ptr->key) == 0){
            if (sum == k){
                if (ks2->release == 1){
                    if (n == 1){
                        delete_element_1(table, ptr->key1, 0);
                    }
                    free(ptr);
                    ks2->list->head = NULL;
                    ks2->release--;
                    return;
                }else{
                    if (ptr == ks2->list->head){
                        ks2->list->head = ptr->next;
                        if (n == 1){
                            delete_element_1(table, ptr->key1, 0);
                        }
                        free(ptr);
                        ks2->release--;
                        return;
                    } else{
                        ptr_prev->next = ptr->next;
                        if (n == 1){
                            delete_element_1(table, ptr->key1, 0);
                        }
                        free(ptr);
                        ks2->release--;
                        return;
                    }
                }
            } else{
                k++;
                ptr_prev = ptr;
                ptr = ptr->next;
            }
        }else{
            ptr_prev = ptr;
            ptr = ptr->next;
        }
    }
}


