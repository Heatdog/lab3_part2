//
// Created by yura on 26.04.2021.
//

#include "for_all.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "key1.h"


const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show"};
const int N =sizeof(msgs) / sizeof(msgs[0]);


char *scan_string(char *s){
    s = (char *)calloc(100, sizeof (char ));
    scanf("%s", s);
    s = (char *)realloc(s, strlen(s)+1);
    return s;
}

void scan_int(int *i){
    int n;
    do {
        n = scanf("%d", i);
        if (n != 1){
            printf("You`re wrong! please, try again\n");
            scanf("%*c");
        }
    } while (n != 1);
}

Info *scan_info(Info* info){
    info = malloc(sizeof (Info));
    printf("Please, enter first int\nFirst int-->");
    scan_int(&info->firs);
    printf("Please, enter second int\nSecond int-->");
    scan_int(&info->second);
    printf("Please, enter text\nText-->");
    info->text = scan_string(info->text);
    return info;
}

void dialog(Table* table)
{
    int rc = 0;
    while (1) {
        printf("\n-------------------\n");
        for (int i = 0; i < N; i++){
            puts(msgs[i]);
        }
        puts("Make your choice: --> ");
        scan_int(&rc);
        switch (rc) {
            case 0:{
                return;
            }
            case 1:{
                D_Add(table);
                break;
            }
            case 2:{
                D_Find(table);
                break;
            }
            case 3:{
                D_Delete(table);
                break;
            }
            default:{
                D_Show(table);
                break;
            }
        }
    }
}

void D_Add(Table* table){
    char *key2 = NULL;
    Info *info = NULL;
    int key1, keyParent, result;
    printf("Please, enter key for first table\nKey--->");
    scan_int(&key1);
    printf("Please, enter prent key (if you don`t want to have a parent key, enter 0)\nParent key--->");
    scan_int(&keyParent);
    printf("Please, enter key for second table (Type string)\nKey--->");
    key2 = scan_string(key2);
    printf("Please, enter value\n");
    info = scan_info(info);
    result = add_first_table(table, key1, keyParent, info, key2);
    switch (result) {
        case 1: {
            printf("Duplicated key or parent key\n");
            return;
        }
        case 2:{
            printf("Table is full!\n");
            return;
        }
        default:{
            add_hash_table(table, key2, info, key1);
            return;
        }
    }
}

void D_Show(Table* table){
    int choose, key;
    printf("Print all table (print 1) or table with using parent key (print 2)\n");
    scan_int(&choose);
    if (choose == 1){
        printf("\t1 table\n");
        print_table_first(table);
        printf("\t2 table (hash)\n");
        print_hash_table(table);
    } else{
        printf("Enter parent key\nKey-->");
        scan_int(&key);
        print_parent(table, key);
    }
}

void D_Find(Table* table){
    char *key = NULL;
    Info_and_key *info = NULL;
    int key1, result, choose, wait;
    printf("Please, enter space (1 or 2) in which you want ot find an element\nYou`re chose-->");
    scan_int(&choose);
    if (choose == 1){
        printf("Please, enter key for first table\nKey--->");
        scan_int(&key1);
        result = find_element_first(table, key1);
        if (result == -1){
            printf("We can`t find this element!\n");
        } else{
            print_info_table1(table, result);
        }
    } else{
        printf("Please, enter key for second table\nKey-->");
        key = scan_string(key);
        printf("Do you want to find all elements with this key (enter 1) or with special release? (enter 2)\nChoose-->");
        scan_int(&wait);
        if (wait == 2){
            printf("Enter release\nRelease-->");
        }
        info = find_hash_element(table, key, wait);
        if (info == NULL && wait == 2){
            printf("We can`t find this element!\n");
        } else{
            if (wait == 2){
                print_list_element(info);
            }
        }
    }
}

void D_Delete(Table* table){
    char *key = NULL;
    int key1;
    int choose, release, k;
    printf("With which key (in 1 or 2 table) do you want to delete?\nChoose-->");
    scan_int(&k);
    if (k == 1){
        printf("(1 table) Please, enter key\nKey-->");
        scan_int(&key1);
        delete_element_1(table, key1, 1);
    } else{
        printf("If you want to delete all items, enter 1. If you want to delete special release, enter 2 (or another "
               "number expect 1)\nYou`re chose-->");
        scan_int(&choose);
        printf("Please, enter key\nKey-->");
        key = scan_string(key);
        if (choose == 1){
            del_hash_table(table, key, 1);
        } else{
            printf("Please, enter release\nRelease-->");
            scan_int(&release);
            del_special(table, key, release, 1);
        }
    }
}
