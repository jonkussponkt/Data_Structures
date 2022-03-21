#include <iostream>
#include <fstream>
#include "Binary_Tree.h"
#include "Stack.h"
#include "Queue.h"

int main(int argc, char* argv[]) {

    Binary_Tree<int> stack;
    Binary_Tree<char> parse_tree;
    int choice;
    int new_nr;
    std::string name_file(argv[0]);
    std::string file_line;
    std::string expression;
    bool from_file = !name_file.empty();
    std::fstream file;
    if(from_file){
        file.open("file", std::ios::in);
    }
//    do {
//        std::cout << "\nWhat to do: \n1 - add\n2 - delete\n3 - show\n4 - min\n5 - max\n6 - find\n7 - is bst\n8 - parse\n9 - exit\n";
//        std::cin >> choice;
//        switch(choice) {
//            case 1:
//                std::cout << "Input new element\n";
//                std::cin >> new_nr;
//                stack.add(new_nr);
//                break;
//            case 2:
//                std::cout << "Input element to \n";
//                std::cin >> new_nr;
//                stack.remove(new_nr);
//                break;
//            case 3:
//                stack.BFS();
//                break;
//            case 4:
//                std::cout << stack.find_min();
//                break;
//            case 5:
//                std::cout << stack.find_max();
//                break;
//            case 6:
//                std::cout << "Input element to find\n";
//                std::cin >> new_nr;
//                std::cout << stack.find(new_nr);
//            case 7:
//                stack.DFS_preorder();
//                std::cout << std::endl;
//                stack.DFS_inorder();
//                std::cout << std::endl;
//                stack.DFS_postorder();
//                std::cout << std::endl;
//                stack.BFS();
//                std::cout << std::endl;
//                break;
//            case 8:
//                std::cout << "Input ";
//                std::getline(std::cin, expression);
//                parse_tree.parse_exact(expression);
//                break;
//            case 9:
//                if(from_file)
//                    file.close();
//                stack.deallocate();
//                break;
//            default:
//                break;
//        }
//    }
//    while(choice != 9);

    Stack <int> stack1;
    do {
        std::cout << "\nWhat to do: \n1 - add\n2 - delete\n3 - show\n4 - get element from top\n5 - exit\n";
        std::cin >> choice;
        switch(choice) {
            case 1:
                std::cout << "Input new element\n";
                std::cin >> new_nr;
                stack1.push(new_nr);
                break;
            case 2:
                stack1.pop();
                break;
            case 3:
                stack1.see_the_stack();
                break;
            case 4:
                std::cout << stack1.get_element();
                break;
            case 5:
                stack1.deallocate();
                break;
            default:
                break;
        }
    }
    while(choice != 5);

//    Queue <int> queue;
//    do {
//        std::cout << "\nWhat to do: \n1 - add\n2 - delete\n3 - show\n4 - get first element of queue\n5 - exit\n";
//        std::cin >> choice;
//        switch(choice) {
//            case 1:
//                std::cout << "Input new element\n";
//                std::cin >> new_nr;
//                queue.push(new_nr);
//                break;
//            case 2:
//                queue.pop();
//                break;
//            case 3:
//                queue.see_the_queue();
//                break;
//            case 4:
//                std::cout << queue.get_element();
//                break;
//            case 5:
//                queue.deallocate();
//                break;
//            default:
//                break;
//        }
//    }
//    while(choice != 5);

    return 0;
}
