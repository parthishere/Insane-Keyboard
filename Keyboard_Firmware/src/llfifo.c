/*******************************************************************************
 * Copyright (C) 2023 by Parth Thakkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Parth Thakkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    llfifo.c
 * @brief
 *
 *
 * @author  Parth Thakkar
 * @date    14 September 2023
 *
 */
#include "llfifo.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct llfifo_node llfifo_node_t;

#define ERROR -1
#define ZERO 0 

// Define the structure for a node in the FIFO
typedef struct llfifo_s { 
    int capacity;
    int max_capacity;  
    unsigned int current_node; 
    llfifo_node_t *head;
    llfifo_node_t *tail;
} lliffo_t;

// Define the structure for the FIFO
typedef struct llfifo_node {
    void* data;
    llfifo_node_t *next_node;
}llfifo_node_t;

// Initialize variables to track memory allocation and deallocation

#ifdef DEBUG 

static int mallocfree = 0;
static int mallocuse = 0;

void * mymalloc(size_t size, const char* file, int line);
void  myfree(void* ptr, const char* file, int line);

#define mymalloc mymalloc
#define myfree myfree

#endif

#ifndef __LLFIFO_C__
#define __LLFIFO_C__


// Function to create an llfifo instance
llfifo_t *llfifo_create(int capacity, int max_capacity){
    if (capacity < ZERO || max_capacity <= ZERO || capacity > max_capacity) {
        return NULL; // Invalid parameters
    }

    //create pointer to structure
    lliffo_t *lliffo_object_pointer = (lliffo_t *)malloc(sizeof(lliffo_t));

    if (!lliffo_object_pointer) {
        return NULL; // Memory allocation failed
    }

    lliffo_object_pointer->capacity = capacity;
    lliffo_object_pointer->max_capacity = max_capacity;
    lliffo_object_pointer->current_node = ZERO;
    lliffo_object_pointer->head = NULL;
    lliffo_object_pointer->tail = NULL;
    
    for (int i=ZERO; i<capacity; i++){
        llfifo_node_t *node = (llfifo_node_t*) malloc(sizeof(llfifo_node_t));

        if (!node) {
            llfifo_node_t *node = lliffo_object_pointer->head;
            while (node) {
                // memory allocation failed
                llfifo_node_t *next = node->next_node;

                free(node);
                node = NULL;

                node = next;
            }
            free(lliffo_object_pointer); // Clean up and return NULL if memory allocation fails
            lliffo_object_pointer = NULL;

            return NULL;
        }
        node->data = NULL;
        node->next_node = NULL;

        if (lliffo_object_pointer->tail != NULL && lliffo_object_pointer->head != NULL){
            // this means already first node is assigned and we have to link the next node 
            lliffo_object_pointer->tail->next_node = node;
            lliffo_object_pointer->tail = node;
        }
        else{
            // this means tail object NULL that means we have to assign it the value
            // this will only execute once when i will be 0;
            lliffo_object_pointer->head = node;
            lliffo_object_pointer->tail = node;
           
        }
    }

    return lliffo_object_pointer;
}
 

int llfifo_enqueue(llfifo_t *FIFO, void *element){

    if (!FIFO) return ERROR;

    llfifo_node_t * fifo_node;
    if (FIFO->head) fifo_node = FIFO->head;

    // Check for invalid element or if the FIFO is already full
    if (!element || (FIFO->current_node) > (FIFO->max_capacity)) return ERROR;

    if ((FIFO->current_node == FIFO->capacity)){

        if (FIFO->current_node == ZERO){
            // If it's the first node, allocate memory for it
            llfifo_node_t *new_node = (llfifo_node_t *) malloc(sizeof(llfifo_node_t));

            if(!new_node){
                // if allocation is failed free the fifo as it is the first element
                free(FIFO);
                FIFO = NULL;

                return ERROR;
            } 

            // assigning the values to new node
            new_node->data = element;
            new_node->next_node = NULL;

            // we have to set head and tail to new node as there was no node available and we created first node
            FIFO->head = new_node;
            FIFO->tail = new_node;

            //increase the capacity
            FIFO->capacity++;
            FIFO->current_node++ ;

            return FIFO->current_node;
        }

        if ((FIFO->current_node) == (FIFO->max_capacity)) {
            // If the FIFO is not empty and at capacity, dequeue the oldest element should be dropped and this is done by this dequeue function (it will pop the first element and push the llfifo to left)
            llfifo_dequeue(FIFO);
            fifo_node = FIFO->head;
            
        }

        else if (FIFO->current_node < FIFO->max_capacity){
            // this means that we have to create a new node and assign values to it
            llfifo_node_t *new_node = (llfifo_node_t *) malloc(sizeof(llfifo_node_t));
            ;

            if(!new_node){
                // cleanup if node allocation fails
                llfifo_node_t *temp_head_node = FIFO->head;
                while (temp_head_node) {
                    llfifo_node_t *next = temp_head_node->next_node;

                    free(temp_head_node);
                    temp_head_node = NULL;

                    temp_head_node = next;
                }
                // freeing up structure
                free(FIFO);
                FIFO = NULL;

                return ERROR;
            } 
            new_node->data = NULL;
            new_node->next_node = NULL;

            // shifting tail node to new node
            FIFO->tail->next_node = new_node;
            FIFO->tail = new_node;

            // we have created a new node so we have to increase the capacity
            FIFO->capacity++;

            // pushing data to last node and returning the length
            llfifo_node_t* fifo_temp_head = FIFO->head;   

            // this is for getting last node of structure (tail)
            while(fifo_temp_head && fifo_temp_head->next_node){
                fifo_temp_head = (fifo_temp_head->next_node);
            }

            if (fifo_temp_head) fifo_temp_head->data = element;
            FIFO->current_node++ ;
            return FIFO->current_node;
           
        }
    }

    // if current node is not equal to capacity of max_node, we have to get the last node and push data to it for that we are looping through each element 
    while(fifo_node && fifo_node->data && fifo_node->next_node){
        fifo_node = (fifo_node->next_node);
    }

    // setting the data
    if (fifo_node) fifo_node->data = element;

    // increasing the current node length
    FIFO->current_node++ ;

    return FIFO->current_node;

}

void * llfifo_dequeue(llfifo_t *fifo){ 
    // if structure is null return error
    if (!fifo) return NULL;
    
    // checking some conditions for ideal dequeue
    if (!(fifo->head) || fifo->current_node <= ZERO || (fifo->capacity == ZERO)) return NULL;

    // getting head
    llfifo_node_t *node = fifo->head;
    
    void* temp_data = node->data;
    // we will shift data to left for each element so that when we dequeue it all the elements are shifted to left and head is free 
    while(node->data && node->next_node){
        // shifting 
        node->data = node->next_node->data;
        node = node->next_node;
    }
    // setting last node data to null for next enqueue
    node->data = NULL;

    // decrementing the current node by one 
    (fifo->current_node)--;

    return temp_data;
}




int llfifo_length(llfifo_t *fifo){
    if (!fifo) {
        return ERROR; // Invalid FIFO
    }

    return fifo->current_node;
}

int llfifo_capacity(llfifo_t *fifo){
    if (fifo == NULL) {
        return ERROR; // Invalid FIFO
    }
    return fifo->capacity;
}

int llfifo_max_capacity(llfifo_t *fifo){
    if (!fifo) {
        return ERROR; // Invalid FIFO
    }
    return fifo->max_capacity;
}

void llfifo_destroy(llfifo_t *fifo) {
    
    if (!fifo) {
        return; // Nothing to destroy
    }
    
    // Check if the head is there other wise there are no nodes to destroy
    if(!fifo->head){
        free(fifo);
        fifo=NULL;
        return;
    } 

    // Free all nodes
    llfifo_node_t *node = fifo->head;
    while (node) {
        if (!node->next_node) {
            // this means we are at last node

            free(*&node); // setting address to variable to null so that data is also set to NULL
            if(!node){
                 // if still node is not free we are freeing it again
                free(node);
                node = NULL;
            }
            
            break;
        } 
        llfifo_node_t *next = node->next_node;

        free(*&node); // free pointer to address of node
        if(!node){
            // if still node is not free we are freeing it again
            free(node);
            node = NULL;
        }
        
        // shifting to next node for freeing
        node = next;

    }

    free(*&fifo);// Free the FIFO structure
    if(!fifo){
        // if still structure is not free we are freeing it again
        free(fifo);
        fifo = NULL;
    }
    
   
}
    
#ifdef DEBUG


int return_malloc_free(){
    
    return mallocfree;
}

int return_malloc_use(){
    return mallocuse;
}

void * mymalloc(size_t size, const char* file, int line){
    void* ptr = malloc(size);
    mallocuse++;
    return ptr;
}

void  myfree(void* ptr, const char* file, int line){
    free(ptr);
    mallocfree++;
}

void print_len_cap_max_cap(llfifo_t *fifo)
{
    if (!fifo) return;

    // print some debug information 
    printf("length of the fifo-> %u, capacity of the llfifo-> %d, max_cap-> %d\n, free-> %d, use-> %d\n", fifo->current_node, fifo->capacity, fifo->max_capacity, mallocfree, mallocuse);

    if(!fifo->head) {
        return;
    }

    llfifo_node_t *node = fifo->head;

    while(node->data){
        printf("data: %p\n", node->data); // printing pointer(address) to the data
        if (node->next_node){
            node = node->next_node; // shifitng to next node
        }
        else break;
    }
    printf("----------\n\n");
}

#endif


#endif






