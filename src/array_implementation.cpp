#include <iostream>

#include "algorithms/sort.hpp"
#include "container/array.hpp"
#include "ctime"
#include <chrono>

using namespace std;

void sort_with_bubble_sort() {
    NewsArray news_container = NewsArray();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);
    std::cout << "Starting Bubble Sort" << endl;
    auto now = std::chrono::system_clock::now();
    bubble_sort(news_container);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    news_container.display();
    std::cout << "Bubble Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

void sort_with_selection_sort() {
    NewsArray news_container = NewsArray();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);
    std::cout << "Starting Selection Sort" << endl;
    auto now = std::chrono::system_clock::now();
    selection_sort(news_container);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    news_container.display();
    std::cout << "Selection Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

void sort_with_quick_sort(SORT_CRITERIA sort_criteria) {
    NewsArray news_container = NewsArray();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);
    std::cout << "Starting Quick Sort" << endl;
    auto now = std::chrono::system_clock::now();
    quick_sort(news_container, sort_criteria);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    news_container.display();
    std::cout << "Quick Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

void sort_with_counting_sort(SORT_CRITERIA criteria) {
    NewsArray news_container = NewsArray();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);
    std::cout << "Starting Counting Sort" << endl;
    auto now = std::chrono::system_clock::now();
    counting_sort(news_container, criteria);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    news_container.display();
    std::cout << "Counting Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

void sort_with_merge_sort(SORT_CRITERIA criteria) {
    NewsArray news_container = NewsArray();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);
    std::cout << "Starting Merge Sort" << endl;
    auto now = std::chrono::system_clock::now();
    merge_sort(news_container, criteria);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    news_container.display();
    std::cout << "Merge Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

void sort_with_insertion_sort() {
    NewsArray news_container = NewsArray();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);
    std::cout << "Starting Insertion Sort" << endl;
    auto now = std::chrono::system_clock::now();
    insertion_sort(news_container);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    news_container.display();
    std::cout << "Insertion Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

void sort_with_bucket_sort() {
    NewsArray news_container = NewsArray();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);
    std::cout << "Starting Bucket Sort" << std::endl;

    auto now = std::chrono::system_clock::now();
    // Choose the criteria: here we're sorting by publication_date.
    SORT_CRITERIA criteria = PUBLICATION_DATE;
    bucket_sort(news_container, criteria);
    auto end_time = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end_time - now;
    news_container.display();
    std::cout << "Bucket Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

void sort_with_heap_sort() {
    NewsArray news_container;
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);
    std::cout << "Starting Heap Sort" << std::endl;

    auto now = std::chrono::system_clock::now();
    // Choose the criteria: here we're sorting by publication_date.
    SORT_CRITERIA criteria = PUBLICATION_DATE;
    heap_sort(news_container, criteria);
    auto end_time = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end_time - now;
    news_container.display();
    std::cout << "Heap Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}



int main() {

    //sort_with_bubble_sort();
    //sort_with_selection_sort();

    //sort_with_quick_sort(SORT_CRITERIA::TRUE_NEWS);
    //sort_with_counting_sort(SORT_CRITERIA::TRUE_NEWS);

    //sort_with_merge_sort(SORT_CRITERIA::TRUE_NEWS);
    //sort_with_insertion_sort();

    //sort_with_bucket_sort();
    //sort_with_heap_sort();

    std::cout << "Hello from Array List Implementation File" << std::endl;
}