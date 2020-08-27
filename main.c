#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct{
    size_t size;
    size_t count;
    void * first;
    void * current;
} vector;

typedef void * (*begin_t)(vector array);

typedef void * (*end_t)(vector array);

typedef void * (*next_t)(vector array); 

typedef void * (*prev_t)(vector array); 

void * begin(vector array){
    return array.first;
}

void * end(vector array){
    return array.first+(array.count*array.size);
}

void * next(vector array){
    if(array.current == end(array)){
        return NULL;
    }else{
        array.current= array.current+array.size;
        return array.current;
    }
}

void * prev(vector array){
    if(array.current == begin(array)){
        return NULL;
    }else{
        array.current= array.current-array.size;
        return array.current;
    }
    
}

typedef struct{
    begin_t begin;
    end_t end;
    next_t next;
}iterator;

void recorre(iterator it, vector array){
    it.begin = begin;
    it.end = end;
    it.next = next;
    
    printf("this is first element %s", it.begin(array));
    printf("this is last element %s", it.end(array));

    for(void * aux = it.begin(array); aux<it.end(array); it.next(array)){
        printf(" element %s", aux);
    }
}

int main(int argc, const char * argv[])
{
    vector enteros;
    enteros.first = (int *) malloc(N*sizeof(int));
    enteros.current = enteros.first;
    enteros.count = N;
    enteros.size = sizeof(int);

    int * aux = enteros.first;
    int * last = enteros.first + N;

    for (; aux < last; ++aux) {
        *aux = rand() % 100;
    }

    iterator forward;
    forward.begin = begin;
    forward.end = end;
    forward.next = next;
    recorre(forward, enteros);
    
}