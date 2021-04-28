//
// Created by yura on 27.04.2021.
//

#ifndef LAB3_PART2_KEY1_H
#define LAB3_PART2_KEY1_H

#include "hash.h"


typedef struct n{
    int* mass;
    int n;
}mass_int;


int add_first_table(Table*, int, int, Info*, char *);
int search1(Table*, int, int );
void print_table_first(Table*);
void print_element_first(KeySpace1);
int find_element_first(Table*, int);
void print_info_table1(Table*, int);
void delete_element_1(Table*, int , int );
int check1(Table*, int );
mass_int check_par1(Table*, int );
void print_parent(Table*, int );
void show_par1(Table*, mass_int , Table*);
void print_parent_all(KeySpace1);


#endif //LAB3_PART2_KEY1_H
