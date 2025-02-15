//
// Created by Victor Mak on 11/02/2025.
//

#include "container/linked_list.hpp"
#include <assert.h>
#include <iomanip>
#include <sstream>
#include <ctime>


void test_linked_list_insertion() {
    NewsLinkedList news_linked_list_container;
    News news1;
    news1.title = "Test Title 1";
    news1.content = "Test Content 1";
    news1.genre = NewsGenre::POLITICS;
    news1.publication_date = time(nullptr);

    news_linked_list_container.insert(news1);

    assert(news1 == news_linked_list_container.get_head().data);
    assert(news1 == news_linked_list_container.get_tail().data);

    News news2;
    news2.title = "Test Title 2";
    news2.content = "Test Content 2";
    news2.genre = NewsGenre::POLITICS;
    news2.publication_date = time(nullptr);

    news_linked_list_container.insert(news2);

    assert(news1 == news_linked_list_container.get_head().data);
    assert(news2 == news_linked_list_container.get_tail().data);

}

void test_linked_list_get_at_location() {
    NewsLinkedList news_linked_list_container;
    News news1;
    news1.title = "Test Title 1";
    news1.content = "Test Content 1";
    news1.genre = NewsGenre::WORLD_NEWS;
    news1.publication_date = time(nullptr);

    news_linked_list_container.insert(news1);

    News news2;
    news2.title = "Test Title 2";
    news2.content = "Test Content 2";
    news2.genre = NewsGenre::POLITICS;
    news2.publication_date = time(nullptr);

    news_linked_list_container.insert(news2);

    News news3;
    news3.title = "Test Title 3";
    news3.content = "Test Content 3";
    news3.genre = NewsGenre::WORLD_NEWS;
    news3.publication_date = time(nullptr);

    news_linked_list_container.insert(news3);

    assert(news1 == *news_linked_list_container.get_at_location(0));
    assert(news2 == *news_linked_list_container.get_at_location(1));
    assert(news3 == *news_linked_list_container.get_at_location(2));
    assert(nullptr == news_linked_list_container.get_at_location(3));
}

void test_linked_list_insert_at_location() {
    NewsLinkedList news_linked_list_container;
    News news1;
    news1.title = "Test Title 1";
    news1.content = "Test Content 1";
    news1.genre = NewsGenre::POLITICS;
    news1.publication_date = time(nullptr);

    news_linked_list_container.insert(news1);

    News news2;
    news2.title = "Test Title 2";
    news2.content = "Test Content 2";
    news2.genre = NewsGenre::POLITICS;
    news2.publication_date = time(nullptr);

    news_linked_list_container.insert(news2);

    News news3;
    news3.title = "Test Title 3";
    news3.content = "Test Content 3";
    news3.genre = NewsGenre::POLITICS;
    news3.publication_date = time(nullptr);

    news_linked_list_container.insert(news3);

    assert(news1 == *news_linked_list_container.get_at_location(0));
    assert(news2 == *news_linked_list_container.get_at_location(1));
    assert(news3 == *news_linked_list_container.get_at_location(2));
    assert(nullptr == news_linked_list_container.get_at_location(3));

    News randomInsertionNews;
    randomInsertionNews.title = "Random";
    randomInsertionNews.content = "Random Content";
    randomInsertionNews.genre = NewsGenre::POLITICS;
    randomInsertionNews.publication_date = time(nullptr);

    news_linked_list_container.insert_at_location(randomInsertionNews, 1);
    assert(randomInsertionNews == *news_linked_list_container.get_at_location(1));
    assert(news2 == *news_linked_list_container.get_at_location(2));
}

void test_linked_list_load_from_file() {
    NewsLinkedList news_linked_list_container;
    news_linked_list_container.load_from_file("test_data/test_source_file.csv");

    News test1example;
    test1example.title = "\"Title 1\"";
    test1example.content = "\"Text 1\"";
    test1example.genre = NewsGenre::WORLD_NEWS;
    struct tm tm = {};
    parse_date("\"December 28, 2017\"", tm);
    test1example.publication_date = mktime(&tm);

    assert(news_linked_list_container.get_at_location(0) != nullptr);
    News at_location = *news_linked_list_container.get_at_location(0);
    assert(test1example == at_location);
}

int main() {
    test_linked_list_insertion();
    test_linked_list_get_at_location();
    test_linked_list_insert_at_location();
    test_linked_list_load_from_file();
}