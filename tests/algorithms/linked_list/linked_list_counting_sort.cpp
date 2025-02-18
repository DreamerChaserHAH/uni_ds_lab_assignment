#include "algorithms/sort.hpp"
#include "container/linked_list.hpp"
#include <assert.h>

void test_counting_sort_with_linked_list_1() {

    NewsLinkedList news_linked_list_container;
    news_linked_list_container.load_from_file("test_data/test_source_file.csv");
    counting_sort(news_linked_list_container);

    News test1example;
    test1example.title = "\"Title 2\"";
    test1example.content = "\"Text 2\"";
    test1example.genre = NewsGenre::POLITICS;
    struct tm tm = {};
    parse_date("\"November 21, 2015\"", tm);
    test1example.publication_date = mktime(&tm);

    assert(test1example == *news_linked_list_container.get_at_location(0));
}

void test_counting_sort_with_linked_list_2() {

    NewsLinkedList news_linked_list_container;
    news_linked_list_container.load_from_file("test_data/test_source_file.csv");
    counting_sort(news_linked_list_container);


    /// Title 3,Holy Shit,worldnews,"March 14, 2016"
    News test2example;
    test2example.title = "\"Title 3\"";
    test2example.content = "\"Holy Shit\"";
    test2example.genre = NewsGenre::WORLD_NEWS;
    struct tm tm = {};
    parse_date("\"March 14, 2016\"", tm);
    test2example.publication_date = mktime(&tm);
    assert(test2example == *news_linked_list_container.get_at_location(1));
}

int main() {
    test_counting_sort_with_linked_list_1();
    test_counting_sort_with_linked_list_2();
    return 0;
}