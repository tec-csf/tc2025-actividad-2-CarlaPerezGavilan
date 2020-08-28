//
//  main.c
//  ejercicio actividad 2 - iterador 
//
//  Created by Carla Pérez Gavilán on 27/08/20.
//  Copyright (c) 2020 Carla Pérez Gavilán. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct{
    size_t size;
    size_t count;
    void * first;
    void * current;
} vector;

typedef void * (*iterator_t)(vector * array);


typedef struct{
    iterator_t begin;
    iterator_t end;
    iterator_t next;
    iterator_t prev;
}iterator;

typedef iterator * (*begin_t)(vector * array);


void * begin(vector * array){
    return array->first;
}

void * end(vector * array){
    return array->first+(array->count*array->size)-array->size;
}

void * next(vector * array){
    if(array->current == end(array)){
        return NULL;
    }else{
        return array->current + array->size;
    }
}

void * prev(vector * array){
    if(array->current == begin(array)){
        return NULL;
    }else{
        return array->current - array->size;
    }
    
}



iterator * forward(vector * array){
    iterator it;
    it.begin = begin;
    it.end = end;
    it.next = next;
    array->current = it.begin(array);
    return &it;
}

iterator * reverse(vector * array){
    iterator it; 
    it.begin = end;
    it.end = begin;
    it.next = prev;
    array->current = it.begin(array);
    return &it;
}

iterator * bidirect(vector * array){
    iterator it;
    it.begin = begin;
    it.end = end;
    it.next = next;
    it.prev = prev;
    array->current = it.begin(array);
    return &it;
}

iterator * init(begin_t initialize, vector * array){
    return (*initialize)(array);
}

void recorre(iterator it, vector array){
    int count = 0;
   for(int * aux = it.begin(&array); it.next(&array) != NULL; aux = it.next(&array)){
        array.current = aux;
        printf(" %4d es el ìndice %4d \n", *aux, count);
        count++;
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
    int * last = enteros.first + (N*sizeof(int));

    for (; aux < last; ++aux) {
        *aux = rand() % 100;
        printf(" assigned %4d \n", *aux);
    }

    iterator it = *(init(&forward, &enteros));


    recorre(it, enteros);
    
}

