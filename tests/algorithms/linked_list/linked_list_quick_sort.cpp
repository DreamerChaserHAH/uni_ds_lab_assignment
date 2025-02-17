#include "algorithms/sort.hpp"
#include "container/linked_list.hpp"
#include <assert.h>

void test_quick_sort_with_linked_list() {
    NewsLinkedList news_linked_list_container;
    news_linked_list_container.load_from_file("test_data/test_source_file.csv");
    quick_sort(news_linked_list_container);
}

int main() {
    test_quick_sort_with_linked_list();
    return 0;
}