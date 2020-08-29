[![Work in Repl.it](https://classroom.github.com/assets/work-in-replit-14baed9a392b3a25080506f3b7b6d57f295ec2978f6f33ec97e36a161684cbe9.svg)](https://classroom.github.com/online_ide?assignment_repo_id=3002582&assignment_repo_type=AssignmentRepo)

## Author

Carla Pérez Gavilán Del Castillo, A01023033
[Carla's Github](https://github.com/CarlaPerezGavilan)

## Date

27-agosto-2020

## Description

This exercise attempts to implement three types of iterators (similar to those already implemented in the std library for C++): forward, reverse and bidirectional. 

The aim is to use generic functions and pointers, in order to create the implementation. 

## Implementation

* Function Recorre uses the following paramters:
    * [input] it: type of iterator that you want to use,
    * [input] array: structure vector with array you want to iterate, 
    * [input] forward: 0 in case you want to iterate forward or 1 if backward,
    * [input] printThis: printing function for this type of data,

## Instructions

Demuestre el funcionamiento del programa de la siguiente manera:

Recorriendo un arreglo de números enteros utilizando un Forward Iterator.
Recorriendo un arreglo de estructuras del tipo Libro, utilizando un Bidirectional Iterator.
struct  Libro {
  char * titulo;
  int paginas;
}

El iterador debe contener, al menos, las siguientes funcionalidades: 

* begin :  Regresa un apuntador al primer elemento 
* end : Regresa un apuntador al último elemento
* next : Regresa un apuntador al siguiente elemento. Si se llegó al final debe regresar NULL.
* prev : Regresa un apuntador al elemento anterior. Si llegó al inicio debe regresar NULL.

Tenga en cuenta que debe existir una función genérica denominada Recorre que debe recibir como parámetros un arreglo de cualquier tipo y un iterador de cualquier tipo y debe recorrer el arreglo utilizando el iterador especificado y mostrar el contenido del arreglo.

## References

* [a link](https://github.com/vcubells/tc2025/blob/master/Tema_1_Apuntadores/ordenamiento_generico/ordenamiento_generico/main.c)
* [a link](http://cs.boisestate.edu/~amit/teaching/253/handouts/07-c-generic-coding-handout.pdf)
* [a link](https://moodlearn.ariel.ac.il/pluginfile.php/1079766/mod_resource/content/0/12_generic_programming_in_C.pdf)

