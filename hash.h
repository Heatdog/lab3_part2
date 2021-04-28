//
// Created by yura on 26.04.2021.
//

#ifndef LAB3_PART2_HASH_H
#define LAB3_PART2_HASH_H

typedef struct Inf{
    int firs;
    int second;
    char *text;
}Info;


typedef struct p{
    Info *inf;
    char *key;
    struct p* next;
    int key1;
}Info_and_key;

typedef struct o{
    Info_and_key *head;
}List;

typedef struct hash {
    int release;
    List *list;
    int key1;
}KeySpace2;

typedef struct key1{
    int key;
    int par;
    Info *inf;
    char *key2;
}KeySpace1;

typedef struct t{
    KeySpace1 *ks1;
    KeySpace2 **ks2;
    int size;
    int size1;
}Table;



Table *new_table(int );
void print_hash_table(Table*);
unsigned int hash(char *, int );
void del_table(Table*);
void free_list(List*);
void print_list(List*);
void print_list_element(Info_and_key*);
void add_hash_table(Table*, char *, Info*, int );
KeySpace2 *add_hash_table_in(KeySpace2*, char*, Info*, int );
Info_and_key *find_hash_element(Table*, char *, int);
Info_and_key *find_hash_element_in_list(KeySpace2 *, char *, int);
void del_hash_table(Table*, char *, int );
void del_hash_table_list(KeySpace2*, Table *,char *, int );
void del_special(Table*, char *, int , int);
void del_special_list(KeySpace2* , Table *, char *, int, int );



#endif //LAB3_PART2_HASH_H
