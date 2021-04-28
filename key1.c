//
// Created by yura on 27.04.2021.
//

#include "key1.h"
#include "hash.h"
#include <stdlib.h>
#include "stdio.h"





////////////////////////////////////////////////

int add_first_table(Table* table, int key, int keyParent, Info* info, char *key2){
    KeySpace1 item = {key, keyParent, info, key2};
    if (search1(table, key, keyParent) == -1){
        return 1;
    }
    if (table->size1 > table->size){
        return 2;
    }
    table->ks1[table->size1] = item;
    table->size1++;
    return 0;
}

int search1(Table* table, int key, int keyParent){
    int result = check1(table, key);
    if (result >= 0){
        return -1;//дублирование ключей
    }
    if (keyParent == 0){
        return 1;//нет родительского элемента
    } else{
        if (check1(table, keyParent) == -1){
            return -1;//не нашли род элемента
        } else{
            return 1;//наши род элемент
        }
    }
}


int check1(Table* table, int key){
    for (int i = 0; i < table->size1; i++){
        if (key == table->ks1[i].key){
            return i;
        }
    }
    return -1;
}

void print_table_first(Table* table){
    for (int i = 0; i < table->size1; i++){
        print_element_first(table->ks1[i]);
    }
}

void print_element_first(KeySpace1 ks1){
    printf("\tKey-->%d//Parent key-->%d//Info-->%d//%d//%s\n", ks1.key, ks1.par, ks1.inf->firs, ks1.inf->second, ks1.inf->text);
}

int find_element_first(Table* table, int key){
    int result = check1(table, key);
    if (result == -1){
        return -1;
    }
    return result;
}

void print_info_table1(Table* table, int i){
    printf("key (1 table)-->%d//parent key-->%d//key (2 table)-->%s//info-->%d//%d//%s", table->ks1[i].key, table->ks1[i].par,
           table->ks1[i].key2, table->ks1[i].inf->firs, table->ks1[i].inf->second, table->ks1[i].inf->text);
}

void delete_element_1(Table* table, int key, int k){
    int result = check1(table, key);
    int n;
    char *key2 = table->ks1[result].key2;
    mass_int MassInt = {NULL, 0};
    MassInt = check_par1(table, key);
    for (int i = 0; i < MassInt.n; i++){
        n = check1(table, MassInt.mass[i]);
        table->ks1[n].par = 0;
    }
    table->ks1[result] = table->ks1[table->size1-1];
    table->size1--;
    free(MassInt.mass);
    if (k == 1){
        del_hash_table(table, key2, 0);
    }
}


mass_int check_par1(Table* table, int keyPar){
    mass_int mass;
    int* all = NULL;
    int n = 0;
    for (int i = 0; i < table->size1; i++) {
        if (keyPar == table->ks1[i].par){
            n++;
            if (all == NULL){
                all = (int*) malloc(sizeof (int));
            } else{
                all = (int *) realloc(all, n*sizeof (int ));
            }
            all[n-1] = table->ks1[i].key;
        }
    }
    mass.mass = all;
    mass.n = n;
    return mass;
}

void print_parent(Table* table, int keyPar){
    mass_int mass_int = {NULL, 0};
    Table* table_new = NULL;
    mass_int = check_par1(table, keyPar);
    if (mass_int.mass == NULL){
        printf("We can`t find any key with this parent key!\n");
    } else{
        show_par1(table, mass_int, table_new);
    }
    free(mass_int.mass);
}

void show_par1(Table* table, mass_int massInt, Table* table_new){
    KeySpace1 keyS;
    int j;
    table_new = (Table*) malloc(sizeof (Table));
    table_new->ks1 = (KeySpace1*)calloc(massInt.n, sizeof (KeySpace1));
    table_new->size1 = massInt.n;
    table_new->size = table_new->size1;
    for (int i = 0; i < table_new->size1; i++){
        table_new->ks1[i].inf = (struct Inf*) malloc(sizeof (Info));
        j = check1(table, massInt.mass[i]);//номер ключа
        table_new->ks1[i] = table->ks1[j];
        keyS = table_new->ks1[i];
        print_parent_all(keyS);
    }
    free(table_new->ks1);
    free(table_new);
}

void print_parent_all(KeySpace1 keyS){
    printf("Key (table 1)-->%d//Parent key-->%d//Key (table 2)-->%s//Info-->%d//%d//%s\n", keyS.key, keyS.par, keyS.key2, keyS.inf->firs, keyS.inf->second, keyS.inf->text);
}

////////////////////////////////////////////////

