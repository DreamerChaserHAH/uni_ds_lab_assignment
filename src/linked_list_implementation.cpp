#include <iostream>

#include "container/linked_list.hpp"

int main() {
    NewsLinkedList news_container = NewsLinkedList();
    news_container.load_from_file("../data/cleaned/fake.csv");
    news_container.load_from_file("../data/cleaned/true.csv");
    std::cout << "News Container Size: " << news_container.size << std::endl;
    std::cout << "Hello from Linked List Implementation File" << std::endl;
}