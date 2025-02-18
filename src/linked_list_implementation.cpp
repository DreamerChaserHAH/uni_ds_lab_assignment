#include <iostream>

#include "algorithms/sort.hpp"
#include "container/linked_list.hpp"
#include "ctime"
#include <chrono>

int sort_with_quick_sort() {
    NewsLinkedList news_container = NewsLinkedList();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv");
    news_container.load_from_file("../data/cleaned/true.csv");
    std::cout << "Starting Quick Sort" << endl;
    auto now = std::chrono::system_clock::now();
    quick_sort(news_container);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    std::cout << "Quick Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

int sort_with_counting_sort() {
    NewsLinkedList news_container = NewsLinkedList();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv");
    news_container.load_from_file("../data/cleaned/true.csv");
    std::cout << "Starting Counting Sort" << endl;
    auto now = std::chrono::system_clock::now();
    counting_sort(news_container);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    std::cout << "Counting Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

int sort_with_merge_sort() {
    NewsLinkedList news_container = NewsLinkedList();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv");
    news_container.load_from_file("../data/cleaned/true.csv");
    std::cout << "Starting Merge Sort" << endl;
    auto now = std::chrono::system_clock::now();
    merge_sort(news_container);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    std::cout << "Merge Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

int sort_with_insertion_sort() {
    NewsLinkedList news_container = NewsLinkedList();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv");
    news_container.load_from_file("../data/cleaned/true.csv");
    std::cout << "Starting Insertion Sort" << endl;
    auto now = std::chrono::system_clock::now();
    insertion_sort(news_container);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    std::cout << "Insertion Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

int sort_with_bucket_sort() {
    NewsLinkedList news_container = NewsLinkedList();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv");
    news_container.load_from_file("../data/cleaned/true.csv");
    std::cout << "Starting Bucket Sort" << endl;
    auto now = std::chrono::system_clock::now();
    bucket_sort(news_container);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    std::cout << "Bucket Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

int sort_with_heap_sort() {
    NewsLinkedList news_container = NewsLinkedList();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv");
    news_container.load_from_file("../data/cleaned/true.csv");
    std::cout << "Starting Heap Sort" << endl;
    auto now = std::chrono::system_clock::now();
    heap_sort(news_container);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    std::cout << "Heap Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

int main() {
    sort_with_quick_sort();
    sort_with_counting_sort();

    sort_with_merge_sort();
    sort_with_insertion_sort();

    sort_with_bucket_sort();
    sort_with_heap_sort();

    std::cout << "Hello from Linked List Implementation File" << std::endl;
}