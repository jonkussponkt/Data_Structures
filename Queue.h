//
// Created by Admin on 18.02.2021.
//

#ifndef DATA_STRUCTURES_QUEUE_H
#define DATA_STRUCTURES_QUEUE_H

#include <iostream>

template<typename T>
class Queue {
    int size;
    struct Element{
        T info;
        Element * ptr_to_next;
        explicit Element(T number) : info(number){
            ptr_to_next = nullptr;
        }
    };
    Element * ptr_to_first;
public:
    void push(T & to_add){
        Element * new_element;
        new_element = new Element(to_add);  /// adding new element to queue

        if(size == 0)                       /// if queue is empty
            ptr_to_first = new_element;     /// then new element is first element
        else {
            Element * temp = ptr_to_first;  /// otherwise
            while(temp->ptr_to_next)        /// iterating through whole queue
                temp = temp->ptr_to_next;
            temp->ptr_to_next = new_element;  /// new element is
        }
        size++;
    }
    void pop(){
        Element * to_delete = ptr_to_first;     /// only first element is deleted
        ptr_to_first = to_delete->ptr_to_next;  /// now first element is next to the previous one
        delete to_delete;                       /// delete
    }
    void see_the_queue(){
        Element * temp = ptr_to_first;
        int ID = 1;
        while(temp->ptr_to_next) {
            std::cout << ID << ". "<< temp->info << std::endl;
            temp = temp->ptr_to_next;
            ID++;
        }
        std::cout << ID << ". " << temp->info << std::endl;
    }
    T get_element(){
        return ptr_to_first->info;
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
    explicit Queue() {
        size = 0;
        ptr_to_first = nullptr;
    }
};

#endif //DATA_STRUCTURES_QUEUE_H
