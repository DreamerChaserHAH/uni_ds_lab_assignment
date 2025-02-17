#include "algorithms/sort.hpp"
#include "container/linked_list.hpp"
#include <assert.h>

void test_quick_sort_with_linked_list() {
    NewsLinkedList news_linked_list_container;
    news_linked_list_container.load_from_file("test_data/test_source_file.csv");
    bucket_sort(news_linked_list_container);

    News test1example;
    test1example.title = "\"Title 2\"";
    test1example.content = "\"Text 2\"";
    test1example.genre = NewsGenre::POLITICS;
    struct tm tm = {};
    parse_date("\"November 21, 2015\"", tm);
    test1example.publication_date = mktime(&tm);

    assert(test1example == *news_linked_list_container.get_at_location(0));
}

int main() {
    test_quick_sort_with_linked_list();
    return 0;
}