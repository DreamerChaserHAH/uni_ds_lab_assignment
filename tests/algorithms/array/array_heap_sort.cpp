#include "algorithms/sort.hpp"
#include "container/array.hpp"
#include <assert.h>

void test_heap_sort_with_array_1() {

    NewsArray news_array_container;
    news_array_container.load_from_file("test_data/test_source_file.csv");
    heap_sort(news_array_container);

    News test1example;
    test1example.title = "\"Title 2\"";
    test1example.content = "\"Text 2\"";
    test1example.genre = NewsGenre::POLITICS;
    struct tm tm = {};
    parse_date("\"November 21, 2015\"", tm);
    test1example.publication_date = mktime(&tm);

    assert(test1example == *news_array_container.get_at_location(0));
}

void test_heap_sort_with_array_2() {

    NewsArray news_array_container;
    news_array_container.load_from_file("test_data/test_source_file.csv");
    heap_sort(news_array_container);


    /// Title 3,Holy Shit,worldnews,"March 14, 2016"
    News test2example;
    test2example.title = "\"Title 3\"";
    test2example.content = "\"Holy Shit\"";
    test2example.genre = NewsGenre::WORLD_NEWS;
    struct tm tm = {};
    parse_date("\"March 14, 2016\"", tm);
    test2example.publication_date = mktime(&tm);
    assert(test2example == *news_array_container.get_at_location(1));
}

int main() {
    test_heap_sort_with_array_1();
    test_heap_sort_with_array_2();
    return 0;
}