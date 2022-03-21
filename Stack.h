//
// Created by Admin on 18.02.2021.
//

#ifndef DATA_STRUCTURES_STACK_H
#define DATA_STRUCTURES_STACK_H

#include <iostream>
#include "Queue.h"

template<typename T>
class Stack {
    int size;
    struct Element{
        T info;
        Element * ptr_to_next;
        explicit Element(T elem) : info(elem){
            ptr_to_next = nullptr;
        };
    };
    Element * ptr_to_first;
    Element * ptr_to_last;
public:
    void push(T & to_add) {
        auto * new_element = new Element(to_add);   /// creation of new element
        if(size == 0) {                             //
            ptr_to_first = new_element;             /// creation of first element
            ptr_to_last = ptr_to_first;             /// first is last
        }
        else {                                      /// if tree is not empty
            Element * temp = ptr_to_first;          /// start iterating
            while(temp->ptr_to_next)                /// iteration until last element
                temp = temp->ptr_to_next;
            temp->ptr_to_next = new_element;        /// next element to the last is new_element
            ptr_to_last = new_element;              /// last element is new element
        }
        size++;
    }
    void pop() {                              /// deletion from stack
        Element * to_delete = ptr_to_last;    /// delete last element of stack
        delete to_delete;
        int n = 1;
        size--;                               /// decrement size

        Element * temp = ptr_to_first;        /// start iterating
        while(n != size) {
            temp = temp->ptr_to_next;         /// iterate until last
            n++;
        }
        temp->ptr_to_next = nullptr;          /// set temp to last
        ptr_to_last = temp;                   /// temp was before-last element previously
    }
    void see_the_stack(){
        Element * temp = ptr_to_first;
        int ID = 1;
        while(temp->ptr_to_next){
            std::cout << ID << ". "<< temp->info << std::endl;
            temp = temp->ptr_to_next;
            ID++;
        }
        std::cout << ID << ". " << ptr_to_last->info << std::endl;
    }
    int get_size(){
        return size;
    }
    T get_element(){
        return ptr_to_last->info;
    }
    void deallocate() {
        if(size > 0) {
            Element *element = ptr_to_first;
            Element *next_element;
            while(element) {
                next_element = element->ptr_to_next;
                delete element;
                element = next_element;
            }
        }
    }
    Stack(){
        size = 0;
        ptr_to_first = nullptr;
        ptr_to_last = nullptr;
    }
};


#endif //DATA_STRUCTURES_STACK_H
