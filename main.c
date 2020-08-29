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

struct Libro {
  char * titulo;
  int paginas;
};

typedef void * (*iterator_t)(vector * array);
typedef void * (*print_t)(void *);


typedef struct{
    iterator_t begin;
    iterator_t end;
    iterator_t next;
    iterator_t prev;
}iterator;

typedef iterator  (*begin_t)(vector * array);

void * printInt(void *);

void * printFloat(void *);

void * printLibro(void *);

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

int setDirection(iterator it, int forward)
{
    if(it.next == next && it.prev == prev)
    {
        return forward;
    }
    if(it.next == next)
    {
        if(forward == 0){
            printf("This iterator should always go forward");
        }
    }
    if(it.next == prev)
    {
        if(forward == 1){
            printf("This iterator should always go backward");
        }
    }
    
    return 1;
}

void recorre(iterator it, vector array, int forward, print_t printThis){
    if(setDirection(it, forward)){
        for(void * aux = it.begin(&array); it.next(&array) != NULL; aux = it.next(&array))
        {
            array.current = aux;
            (*printThis)(aux);
        }
    }else{
        for(void * aux = it.end(&array); it.prev(&array) != NULL; aux = it.prev(&array))
        {
            array.current = aux;
            (*printThis)(aux);
        }
    }
        
}


/* printing functions */

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

int main(int argc, const char * argv[])
{
    vector enteros;
    enteros.first = (float *) malloc(N*sizeof(float));
    enteros.current = enteros.first;
    enteros.count = N;
    enteros.size = sizeof(float);

    float * aux = enteros.first;
    float * last = enteros.first + (N*sizeof(float));

    printf("\n\n--- Ejercicio #1 ENTEROS ---\n\n");

    printf("\n---> Asignación \n");
    for (; aux < last; ++aux) {
        *aux = rand() % 100 *1.5;
        printf(" assigned %f,    \t ", *aux);
    }

    printf("\n---> Recorrido \n");

    iterator it = init(&reverse, &enteros);
    recorre(it, enteros, 0, &printFloat);
    
    vector libros;
    libros.first = (struct Libro *) malloc(N*sizeof(struct Libro));
    libros.current = libros.first;
    libros.count = N;
    libros.size = sizeof(struct Libro);

    struct Libro * aux_libros = libros.first;
    struct Libro * last_libros = libros.first + (N*sizeof(struct Libro));

    
    printf("\n\n--- Ejercicio #2 LIBROS ---\n\n");
    
    printf("\n---> Asignación \n");
    int count = 0;
     for (; aux_libros < last_libros; ++aux_libros) {
        aux_libros->paginas = rand() % 100;
        aux_libros->titulo = "titulo "+count;
        count++;

        printf(" páginas: %d \n", aux_libros->paginas);
        printf(" titulo: nombre de prueba %s \n", aux_libros->titulo);


    }

    printf("\n---> Recorrido \n");
    iterator it_libros = init(&reverse, &libros);
    recorre(it_libros, libros, 0, &printLibro);


}

