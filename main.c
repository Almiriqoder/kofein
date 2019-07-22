#include <stdio.h>
#include <stdlib.h>
typedef enum {false, true} bool;
typedef char *str;
struct block {
    struct __key {
        int type;
        union _key {
            bool kboolean;
            float knumber;
            str kstring;
        } key_;
    } key__;
    struct __value {
        int type;
        union _value {
            bool boolean;
            float number;
            str string;
            struct block *array;
        } value_;
    } data;
    struct block *next;
    struct block *self;
    struct block *prev;
    short int queue;
};
int find_block(struct block *start, struct __key k){
    if(start->key__.type == k.type){
        if(start->key__.type == 0){
            if(start->key__.key_.kboolean == k.key_.kboolean){
                return 1;
            } else {
                if(start->next != NULL){
                    return find_block(start->next, k);
                } else {
                    return 0;
                };
            };
        } else {
            if(start->key__.type == 1){
                if(start->key__.key_.knumber == k.key_.knumber){
                    return 1;
                } else {
                    if(start->next != NULL){
                        return find_block(start->next, k);
                    } else {
                        return 0;
                    };
                };
            } else {
                if(start->key__.type == 2){
                    if(start->key__.key_.kstring == k.key_.kstring){
                        return 1;
                    } else {
                        if(start->next != NULL){
                            return find_block(start->next, k);
                        } else {
                            return 0;
                        };
                    };
                };
            };
        };
    } else {
        if(start->next != NULL){
            return find_block(start->next, k);
        } else {
            return 0;
        };
    };
};
int key_eq_binary(struct __key k1, struct __key k2){
    switch(k1.type){
    case 0:
        if(k1.key_.kboolean == k2.key_.kboolean){
            return 1;
        } else {
            return 0;
        };
        break;
    case 1:
        if(k1.key_.knumber == k2.key_.knumber){
            return 1;
        } else {
            return 0;
        };
        break;
    case 2:
        if(k1.key_.kstring == k2.key_.kstring){
            return 1;
        } else {
            return 0;
        };
        break;
    default:
        return  0;
        break;
    };
};
void push_block(struct block *start, struct __key k, struct __value value){
    if(find_block(start, k)){
        if(key_eq_binary(start->key__, k)){
            start->data = value;
        } else {
            push_block(start->next, k, value);
        };
    } else {
        if(start->next == NULL){
            struct block *temp = (struct block *) calloc(1, sizeof start);
            start->next = temp;
            temp->next = NULL;
            temp->self = start->next;
            temp->prev = start->self;
            temp->data = value;
            temp->key__ = k;
        } else {
            push_block(start->next, k, value);
        };
    };
};
int main(){
    struct block start;
    start.self = &start;
    start.next = NULL;
    start.prev = start.self;
    start.queue = 0;
    start.key__.key_.knumber = 1;
    start.key__.type = 1;
    struct __key k;
    k.type = 1;
    k.key_.knumber = 0;
    struct __value sd;
    sd.type = 1;
    sd.value_.number = 10;
    printf("%d, %d, %d, %d\n", sizeof start, sizeof start.key__, sizeof start.data, find_block(start.self, k));
    push_block(start.self, k, sd);
    char q = getchar();
    return 0;
}

/*
print(0)
*/

/*
    0 type is bool
    1 type is number
    2 type is string
    3 type is array-list
    4 type is array-dict
    5 type is class
    6 type is object
    7 type is class
    8 type is NCO
    9 type is functions
    ;
        bools are numbers (true = 1, false = 0)
        strings are arrays-lists
        objects are arrays-dicts with vars and functions named as attributes and methods
        functions are executables strings
        classes are constant objects
        NCOs are objects without classes
    ;
*/