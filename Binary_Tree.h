//
// Created by Admin on 23.02.2021.
//

#ifndef DATA_STRUCTURES_BINARY_TREE_H
#define DATA_STRUCTURES_BINARY_TREE_H

#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>

template<typename T>
class Binary_Tree {
    int size;
    struct Node {
        Node * ptr_to_left;
        T element;                      /// one node with two children: left and right
        Node * ptr_to_right;
        explicit Node(T new_element) : element(new_element) {
            ptr_to_left = nullptr;
            ptr_to_right = nullptr;
        }
    };
    Node * ptr_to_first;
public:
    void add(T new_elem) {
        auto * new_node = new Node(new_elem);
        Node * temp = ptr_to_first;
        Node * ptr_to_next;
        if(ptr_to_first == nullptr)     /// if tree is empty, first node is created
            ptr_to_first = new_node;
        else {                                      /// according to definition of binary tree
            if (new_elem < temp->element)           /// if new element is smaller than current element
                ptr_to_next = temp->ptr_to_left;    /// then we go to left subtree
            else                                    /// otherwise
                ptr_to_next = temp->ptr_to_right;   /// we go to right subtree
            while(ptr_to_next) {                    /// and we iterate through whole tree following the rule above
                if (new_elem < temp->element) {
                    ptr_to_next = temp->ptr_to_left;
                    if(ptr_to_next)
                        temp = ptr_to_next;
                }
                else {
                    ptr_to_next = temp->ptr_to_right;
                    if(ptr_to_next)
                        temp = ptr_to_next;
                }
            }
            if (new_elem <= temp->element)
                temp->ptr_to_left = new_node;
            else
                temp->ptr_to_right = new_node;
        }
        size++;
    }
    void parse_exact(const std::string & expression){
        Node * parent, * current;
        this->add(' ');
        current = ptr_to_first;
        for(char i : expression){
            if (i == '('){
                current->ptr_to_left = new Node(' ');
                parent = current;
                current = current->ptr_to_left;
            }
            else if(i == '+' || i == '-' || i == '*' || i == '/'){
                parent->element = i;
                parent->ptr_to_right = new Node(' ');
                current = parent->ptr_to_right;
            }
            else if(isdigit(i)){
                current->element = i;
            }
            else if(i == ')'){
                current = parent;
            }
        }
        this->BFS();

    }
    void remove(T elem) {
        Node * temp = ptr_to_first;
        Node * ptr_to_next;
        if (size == 1) {
            delete ptr_to_first;
            ptr_to_first = nullptr;
        }
        else {
            if (elem == temp->element)
                ptr_to_next = temp;
            else if (elem < temp->element)
                ptr_to_next = temp->ptr_to_left;
            else
                ptr_to_next = temp->ptr_to_right;
            while (ptr_to_next) {
                if (elem == temp->element)
                    break;
                else if (elem < temp->element) {
                    ptr_to_next = temp->ptr_to_left;
                    if (ptr_to_next) {
                        if (ptr_to_next->element == elem)
                            break;
                        else
                            temp = ptr_to_next;
                    }
                }
                else {
                    ptr_to_next = temp->ptr_to_right;
                    if (ptr_to_next) {
                        if (ptr_to_next->element == elem)
                            break;
                        else
                            temp = ptr_to_next;
                    }
                }
            }
            if (ptr_to_next->ptr_to_left == nullptr && ptr_to_next->ptr_to_right == nullptr) { //no children
                if (temp->ptr_to_right) {
                    if (ptr_to_next->element == temp->ptr_to_right->element)
                        temp->ptr_to_right = nullptr;
                }
                if (temp->ptr_to_left) {
                    if (ptr_to_next->element == temp->ptr_to_left->element)
                        temp->ptr_to_left = nullptr;
                }
                delete ptr_to_next;
            }
            else if (ptr_to_next->ptr_to_left && ptr_to_next->ptr_to_right == nullptr) {
                if (temp->ptr_to_left) {
                    if (temp->ptr_to_left->element == ptr_to_next->element)
                        temp->ptr_to_left = ptr_to_next->ptr_to_left;
                }
                if (temp->ptr_to_right) {
                    if (temp->ptr_to_right->element == ptr_to_next->element)
                        temp->ptr_to_right = ptr_to_next->ptr_to_left;
                }
                delete ptr_to_next;
            }
            else if (ptr_to_next->ptr_to_left == nullptr && ptr_to_next->ptr_to_right) {
                if (temp->ptr_to_left) {
                    if (temp->ptr_to_left->element == ptr_to_next->element)
                        temp->ptr_to_left = ptr_to_next->ptr_to_right;
                }
                if (temp->ptr_to_right) {
                    if (temp->ptr_to_right->element == ptr_to_next->element)
                        temp->ptr_to_right = ptr_to_next->ptr_to_right;
                }
                delete ptr_to_next;
            }
            else if (ptr_to_next->ptr_to_left && ptr_to_next->ptr_to_right) {
                Node * min = ptr_to_next->ptr_to_right; ///przechodzimy do prawego poddrzewa węzłą ktory usuwamy
                Node * temporary;
                while (min->ptr_to_left) ///szukanie minimum w prawym poddrzewie
                    min = min->ptr_to_left;
                ptr_to_next->element = min->element;  ///przypisujemy wartość minimum jako wartośc w węźle
                ///z którego wartość usuwamy
                //ptr_to_next = ptr_to_next->ptr_to_right;
                if (min->ptr_to_right) {
                    temporary = min->ptr_to_right;
                    ptr_to_next = ptr_to_next->ptr_to_right;
                    while (ptr_to_next->ptr_to_left && ptr_to_next->ptr_to_left->ptr_to_left)
                        ptr_to_next = ptr_to_next->ptr_to_left;
                    ptr_to_next->ptr_to_left = temporary;
                    ptr_to_next->ptr_to_left->ptr_to_left = nullptr;
                    delete ptr_to_next->ptr_to_left->ptr_to_left;
                }
                else {
                    //if(ptr_to_next->ptr_to_right->element == min->element) {
                    ptr_to_next->ptr_to_right = nullptr;
                    delete ptr_to_next->ptr_to_right;
                    //}
                }
                /*ptr_to_next->ptr_to_right->ptr_to_left = min->ptr_to_right;

                while (ptr_to_next->ptr_to_left && ptr_to_next->ptr_to_left->ptr_to_left)
                    ptr_to_next = ptr_to_next->ptr_to_left;
                ptr_to_next->ptr_to_left = nullptr;
                delete ptr_to_next->ptr_to_left; ///usuwamy minimum*/
            }
        }
        size--;
    }
    bool find(int x){
        Node * temp = ptr_to_first;
        while(temp) {
            if(x == temp->element)
                return true;
            else if (x < temp->element) {
                temp = temp->ptr_to_left;
            }
            else if(x > temp->element){
                temp = temp->ptr_to_right;
            }
        }
        return false;
    }
    T find_max(){
        if(size == 1)
            return ptr_to_first->element;
        Node * temp = ptr_to_first;
        Node * ptr_to_next = temp->ptr_to_right;
        while(ptr_to_next){
            temp = temp->ptr_to_right;
            ptr_to_next = temp->ptr_to_right;
        }
        return temp->element;
    }
    T find_min() {
        if(size == 1)
            return ptr_to_first->element;
        Node * temp = ptr_to_first;
        Node * ptr_to_next = temp->ptr_to_left;
        while(ptr_to_next){
            temp = temp->ptr_to_left;
            ptr_to_next = temp->ptr_to_left;
        }
        return temp->element;
    }
    void DFS_preorder() {
        Node * temp = ptr_to_first;
        std::vector<Node *> stack;
        while(temp) {
            std::cout << temp->element << " ";
            if(temp->ptr_to_right)
                stack.emplace_back(temp->ptr_to_right);
            if(temp->ptr_to_left)
                stack.emplace_back(temp->ptr_to_left);
            if(stack.empty())
                temp = nullptr;
            else {
                temp = stack.back();
                stack.pop_back();
            }
        }
    }
    void DFS_inorder() {
        Node * temp = ptr_to_first;
        std::vector<Node *> stack;
        while(!stack.empty() || temp) {
            if(temp) {
                stack.template emplace_back(temp);
                temp = temp->ptr_to_left;
            }
            else {
                temp = stack.back();
                stack.pop_back();
                std::cout << temp->element << " ";
                temp = temp->ptr_to_right;
            }
        }
    }
    void DFS_postorder() {
        Node * previous, * current;
        std::vector<Node *> stack;
        previous = nullptr;
        stack.template emplace_back(ptr_to_first);
        while(!stack.empty()) {
            current = stack.back();
            // jeśli obecny jest którymś dzieckiem poprzedniego
            if(previous == nullptr || previous->ptr_to_left == current || previous->ptr_to_right == current) {
                if(current->ptr_to_left)
                    stack.template emplace_back(current->ptr_to_left);
                else if(current->ptr_to_right)
                    stack.template emplace_back(current->ptr_to_right);
            }
                // jeśli poprzednim jest lewe dziecko obecnego
            else if(current->ptr_to_left == previous) {
                if(current->ptr_to_right)
                    stack.template emplace_back(current->ptr_to_right);
            }
            else {
                std::cout << current->element << " ";
                stack.pop_back();
            }
            previous = current;
        }
    }
    int get_height() {
        Node * node = ptr_to_first;
        std::vector<Node *> queue;
        queue.template emplace_back(node);
        int node_count;
        int height = -1;

        while(true) {
            node_count = queue.size();
            if (node_count == 0) {
                // std::cout << height << std::endl;
                break;
            }
            else
                height++;
            while (node_count > 0) {
                node = queue[0];
                if (node->ptr_to_left)
                    queue.emplace_back(node->ptr_to_left);
                if (node->ptr_to_right)
                    queue.emplace_back(node->ptr_to_right);
                queue.erase(queue.begin());
                node_count--;
            }
        }
        return height;
    }
    void BFS() {
        Node * node;
        int height = get_height() + 1;
        int length = static_cast<int>(pow(2, height));

        std::vector<std::vector<Node *> > to_write;
        std::vector<Node *> temp;
        std::vector<Node *> temp2;
        temp.emplace_back(ptr_to_first);
        to_write.emplace_back(temp);

        int j = 0;
        while(j < to_write.size()) {
            while(!temp.empty()) {
                node = temp[0];
                if (node) {
                    if (node->ptr_to_left) {
                        temp2.emplace_back(node->ptr_to_left);
                    }
                    else {
                        temp2.emplace_back(nullptr);
                    }
                    if (node->ptr_to_right) {
                        temp2.emplace_back(node->ptr_to_right);
                    }
                    else {
                        temp2.emplace_back(nullptr);
                    }
                }
                temp.erase(temp.begin());
            }
            if(!temp2.empty()) {
                to_write.emplace_back(temp2);
                temp = temp2;
                temp2.clear();
            }
            j++;
        }
        for(auto & i : to_write) {
            for(int k = 0; k < i.size(); k++) {
                for (int l = 0; l < 2*length-1; l++)
                    std::cout << " ";
                if(k > 0 || i.at(k) == nullptr) {
                    for (int l = 0; l < 2*length; l++)
                        std::cout << " ";
                }
                if(i.at(k))
                    std::cout << i.at(k)->element;
            }
            std::cout << std::endl;
            length /= 2;
        }
    }
    bool is_bst() {
        Node * node = ptr_to_first;
        std::vector<Node *> parents;
        //node->ptr_to_left->ptr_to_right->ptr_to_left->element = 5;
        while(node) {
            std::cout << node->element << " ";
            if(node->ptr_to_left) {
                if (node->ptr_to_left->element >= node->element)
                    return false;
                parents.emplace_back(node->ptr_to_left);
            }
            if(node->ptr_to_right) {
                if(node->ptr_to_right->element < node->element)
                    return false;
                parents.emplace_back(node->ptr_to_right);
            }
            if(parents.empty())
                break;
            //node = parents[0]; //KOLEJKA
            // parents.erase(parents.begin()); //KOLEJKA
            //node = parents.back(); //STOS
            //parents.pop_back();   //STOS
        }
        return true;
    }
    void deallocate() {
        if(size > 0) {
            Node * previous, * current;
            std::vector<Node *> stack;
            previous = nullptr;
            stack.emplace_back(ptr_to_first);
            while(!stack.empty()) {
                current = stack.back();
                // jeśli obecny jest którymś dzieckiem poprzedniego
                if(previous == nullptr || previous->ptr_to_left == current || previous->ptr_to_right == current) {
                    if(current->ptr_to_left)
                        stack.template emplace_back(current->ptr_to_left);
                    else if(current->ptr_to_right)
                        stack.template emplace_back(current->ptr_to_right);
                }
                    // jeśli poprzednim jest lewe dziecko obecnego
                else if(current->ptr_to_left == previous) {
                    if(current->ptr_to_right)
                        stack.template emplace_back(current->ptr_to_right);
                }
                else {
                    std::cout << current->element << " ";
                    delete stack.back();
                    stack.pop_back();
                }
                previous = current;
            }
        }
    }
    Binary_Tree(){
        size = 0;
        ptr_to_first = nullptr;
    }
};


#endif //DATA_STRUCTURES_BINARY_TREE_H


/* //
// Created by Admin on 20.03.2021.
//

#ifndef DATA_STRUCTURES_HEAP_H
#define DATA_STRUCTURES_HEAP_H

#include <vector>
#include <iostream>
#include <cmath>

template<typename T>
class Heap {
    std::vector<T> Tree;
public:
    void add() {
        T node, temp;
        std::cout << "Input new value\n";
        std::cin >> node;
        Tree.emplace_back(node);
        int i = Tree.size() - 1;
        while(i > 0) {
            if(Tree[(i - 1) / 2] < Tree[i]) {
                swap(i, (i - 1) / 2);
            }
            i = (i - 1) / 2;
        }
    }
    void add(T arg) {
        //T node, temp;
        //std::cout << "Input new value\n";
        //std::cin >> node;
        Tree.emplace_back(arg);
        int i = Tree.size() - 1;
        while(i > 0) {
            if(Tree[(i - 1) / 2] < Tree[i]) {
                swap(i, (i - 1) / 2);
            }
            i = (i - 1) / 2;
        }
    }
    void print_a_heap() {
        int level = 1;
        int height = log2(Tree.size()) + 1;
        int i = 0;
        while(i < Tree.size()) {
            while(i < pow(2, level) - 1) {
                for(int j = 0; j < height; j++)
                    std::cout << " ";
                std::cout << Tree.at(i);
                i++;
            }
            std::cout << std::endl;
            height--;
            level++;
        }
    }
    void heap_sort() {
        std::vector<T> sorted;
        int max_index;
        int index;
        size_t i;
        T temp;
        while (!Tree.empty()) {
            index = Tree.size() - 1;
            if (Tree.size() > 1) {
                max_index = find_max();
                swap(index, max_index);
            }
            sorted.emplace_back(Tree.back());
            Tree.pop_back();
            std::cout << Tree.size() << std::endl;
            i = 0;
            if(!Tree.empty()) {
                while (2 * i + 1 < Tree.size() - 1) {
                    if (Tree.at(2 * i + 1) > Tree.at(i))
                        swap(2 * i + 1, i);
                    if (Tree.at(2 * i + 2) > Tree.at(i))
                        swap(2 * i + 2, i);
                    i++;
                }
            }
        }
        for(int j = sorted.size() - 1; j >= 0; j--)
            std::cout << sorted.at(j) << " ";
    }
    void heap_sort(T * array, int size) {
        for(int i = 0; i < size; i++){
            add(array[i]);
        }
        heap_sort();
    }
    int find_max(){
        int max = 0, i;
        for(i = 1; i < Tree.size(); i++){
            if(Tree.at(i) > Tree.at(max))
                max = i;
        }
        return max;
    }
    void swap(int i, int j) {
        T temp = Tree.at(i);
        Tree.at(i) = Tree.at(j);
        Tree.at(j) = temp;
    }
    Heap() {
        Tree = {};
    }
};

#endif //DATA_STRUCTURES_HEAP_H
*/