//
//  main.c
//  ejercicio actividad 2 - iterador 
//
//  Created by Carla Pérez Gavilán on 27/08/20.
//  Copyright (c) 2020 Carla Pérez Gavilán. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define N 10

/* Defining Structures */

typedef struct{
    size_t size;
    size_t count;
    void * first;
    void * current;
} vector;

struct Libro {
  char * titulo;
  int paginas;
};

/* Defining Structure and Generic Function Iterator */

typedef void * (*iterator_t)(vector * array);

typedef struct{
    iterator_t begin;
    iterator_t end;
    iterator_t next;
    iterator_t prev;
}iterator;

/* Defining Generic Functions */

typedef void * (*print_t)(void *);

typedef iterator  (*begin_t)(vector * array);

/* Printing Function */

void * printInt(void *);

void * printFloat(void *);

void * printLibro(void *);

/* Auxiliary Functions  */

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

/* Implementation Iterator Types  */

iterator forward(vector * array){
    iterator it;
    it.begin = begin;
    it.end = end;
    it.next = next;
    array->current = it.begin(array);
    return it;
}

iterator reverse(vector * array){
    iterator it; 
    it.begin = end;
    it.end = begin;
    it.next = prev;
    array->current = it.begin(array);
    return it;
}

iterator  bidirect(vector * array){
    iterator it;
    it.begin = begin;
    it.end = end;
    it.next = next;
    it.prev = prev;
    array->current = it.begin(array);
    return it;
}

iterator init(begin_t initialize, vector * array){
    return (*initialize)(array);
}

/* Auxiliary Function Set Direction  */

int setDirection(iterator it, int forward)
{
    if(it.next == next && it.prev == prev)
    {
        return forward;
    }
    if(it.next == next)
    {
        if(forward == 0){
            printf("This iterator should always go forward \n");
        }
    }
    if(it.next == prev)
    {
        if(forward == 1){
            printf("This iterator should always go backward \n");
        }
    }
    
    return 1;
}

/* Function "Recorre" 
    @[input] it: type of iterator that you want to use,
    @[input] array: structure vector with array you want to iterate, 
    @[input] forward: 0 in case you want to iterate forward or 1 if backward,
    @[input] printThis: printing function for this type of data,
  */

void recorre(iterator it, vector array, int forward, print_t printThis){
    if(setDirection(it, forward) == 1)
    {
        array.current = it.begin(&array);
        for(void * aux = it.begin(&array); it.next(&array) != NULL; aux = it.next(&array))
        {
            array.current = aux;
            (*printThis)(aux);
        }
    }
    if(setDirection(it, forward) == 0)
    {
        array.current = it.end(&array);
        for(void * aux = it.end(&array); it.prev(&array) != NULL; aux = it.prev(&array))
        {
            array.current = aux;
            (*printThis)(aux);
        }
    }
        
}


/* Implementation Printing Functions */

void * printInt(void * printed)
{
    int print = *(int *)printed;
    printf(" element: %d \n", print);
}

void * printFloat(void * printed)
{
    float print = *(float *)printed;
    printf(" element: %f \n", print);
}

void * printLibro(void * printed)
{
    struct Libro print = *(struct Libro *)printed;
    printf(" titulo del libro: %s \n", print.titulo);
    printf(" num de páginas: %d \n ", print.paginas);
}

/* Testing */


int main(int argc, const char * argv[])
{
    vector enteros;
    enteros.first = (int *) malloc(N*sizeof(int));
    enteros.current = enteros.first;
    enteros.count = N;
    enteros.size = sizeof(int);

    int * aux = enteros.first;
    int * last = enteros.first + (N*sizeof(int));

    printf("\n\n--- Ejercicio #1 ENTEROS ---\n\n");

    printf("\n---> Asignación \n");
    for (; aux < last; ++aux) {
        *aux = rand() % 100 *1.5;
        printf(" assigned %d \n ", *aux);
    }

    printf("\n\n---> Recorrido \n");

    iterator it = init(&forward, &enteros);
    recorre(it, enteros, 1, &printInt);
    
    vector libros;
    libros.first = (struct Libro *) malloc(N*sizeof(struct Libro));
    libros.current = libros.first;
    libros.count = N;
    libros.size = sizeof(struct Libro);

    struct Libro * aux_libros = libros.first;
    struct Libro * last_libros = libros.first + (N*sizeof(struct Libro));


    printf("\n\n--- Ejercicio #2 LIBROS ---\n\n");
    
    char * names[] = {
        " 1 Caperucitar roja",
        " 2 Hanzel y Gretel",
        "3 La vuelta al mundo en 80 días",
        "4 Narnia",
        "5 Los tres cerditos",
        "6 Harry Potter",
        "7 Percy Jackson",
        "8 Superman comic",
        "9 Marvel universe",
        "10 La iliada"
    };

    printf("\n---> Asignación \n");
    int count = 0;
     for (; aux_libros < last_libros; ++aux_libros) {
        aux_libros->paginas = rand() % 100;
        aux_libros->titulo = names[count];
        count++;

        printf(" páginas: %d \n", aux_libros->paginas);
        printf(" titulo: nombre de prueba %s \n", aux_libros->titulo);


    }

    printf("\n---> Recorrido Forward\n");
    iterator it_libros = init(&bidirect, &libros);
    recorre(it_libros, libros, 1, &printLibro);

    printf("\n---> Recorrido Backward\n");
    recorre(it_libros, libros, 0, &printLibro);


}

