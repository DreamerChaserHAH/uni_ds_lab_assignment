/// <summary>
/// Custom Linked List Implementation in C++
/// </summary>
#pragma once
using namespace std;

#include "news.hpp"
#include "news_container.hpp"

struct NewsNode {
    News* data;
    NewsNode* nextAddress;
    NewsNode* prevAddress;
};

class NewsLinkedList : public NewsContainer{
private:
    NewsNode* tail;

    NewsLinkedList(NewsNode* head_pointer, NewsNode* tail_pointer, int size, time_t max_date, int distinct_number_of_genres, GenreIndex* genre_index) {
        this->head = head_pointer;
        this->size = size;
        this->tail = tail_pointer;
        this->max_date = max_date;
        this->distinct_number_of_genres = distinct_number_of_genres;
        this->genre_index = genre_index;
    }

public:
    NewsLinkedList() : tail(nullptr) {

    }

    void insert(News newNews) override{
        auto* newsNode = new NewsNode;
        newsNode->data = new News(newNews);
        newsNode->nextAddress = nullptr;
        newsNode->prevAddress = tail;
        size++;

        if (newNews.publication_date > max_date) {
            max_date = newNews.publication_date;
        }

        if (head == nullptr) {
            head = newsNode;
            tail = static_cast<NewsNode*>(head);
            return;
        }else {
            tail->nextAddress = newsNode;
            tail = newsNode;
        }

        update_distincts(&newNews);
    }

    void insert_empty() override {
        auto* newsNode = new NewsNode;
        newsNode->data = nullptr;;
        newsNode->nextAddress = nullptr;
        newsNode->prevAddress = tail;
        size++;

        if (head == nullptr) {
            head = newsNode;
            tail = static_cast<NewsNode*>(head);
            return;
        }else {
            if (tail != nullptr) {
                tail->nextAddress = newsNode;
                tail = newsNode;
            }
        }

    }

     News* get_at_location(int location) override {
        auto* current = static_cast<NewsNode*>(head);
        for (int i = 0; i < location; i++) {
            current = current->nextAddress;
        }
        if (current == nullptr) {
            return nullptr;
        }

        if (current->data == nullptr) {
            return nullptr;
        }

        return (current->data);
    }

    void* get_node_at_location(int location) override {
        auto* current = static_cast<NewsNode*>(head);
        for (int i = 0; i < location; i++) {
            if (current == nullptr) {
                return nullptr;
            }
            current = current->nextAddress;
        }
        return current;
    }

    void insert_at_location(News newNews, int location) override {
        auto* newsNode = new NewsNode;
        newsNode->data = new News(newNews);
        newsNode->nextAddress = nullptr;
        newsNode->prevAddress = nullptr;
        size++;

        if (newNews.publication_date > max_date) {
            max_date = newNews.publication_date;
        }

        if (location == 0) {
            newsNode->nextAddress = static_cast<NewsNode*>(head);
            newsNode->nextAddress->prevAddress = newsNode;
            head = newsNode;
            return;
        }

        auto* current = static_cast<NewsNode*>(head);
        for (int i = 0; i < location - 1; i++) {
            if (current == nullptr) {
                return;
            }
            current = current->nextAddress;
        }

        newsNode->nextAddress = current->nextAddress;
        newsNode->prevAddress = current;
        current->nextAddress = newsNode;

        update_distincts(&newNews);
    }

    void delete_at_location(int location) override {
        auto* node = static_cast<NewsNode *>(get_node_at_location(location));
        if (node == nullptr) {
            return;
        }

        if (node->prevAddress != nullptr) {
            node->prevAddress->nextAddress = node->nextAddress;
        }

        if (node->nextAddress != nullptr) {
            node->nextAddress->prevAddress = node->prevAddress;
        }

        if (node == tail) {
            tail = node->prevAddress;
        }

        if (node == head) {
            head = node->nextAddress;
        }
        update_distincts(node->data, nullptr);
        delete node->data;
        delete node;
    }

    void overwrite_at_position(NewsContainer *value_container, int starting_location) override {
        int new_container_size = value_container->size;
        auto* current_node = static_cast<NewsNode*>(get_node_at_location(starting_location));
        if (current_node == nullptr) {
            return;
        }
        int index = 0;
        while (true) {
            if (index >= new_container_size) {
                break;
            }
            News* new_value = value_container->get_at_location(index);
            update_distincts(current_node->data,  new_value);
            current_node->data = new_value;
            current_node = current_node->nextAddress;
            index++;
        }
    }

    void put_at_location(News newNews, int location) override {
        auto* node_ptr = static_cast<NewsNode*>(get_node_at_location(location));
        if (node_ptr == nullptr) {
            return;
        }
        update_distincts(node_ptr->data, &newNews);
        node_ptr->data = new News(newNews);
    }

    void swap_news(int i, int j) override {
        auto* node1 = static_cast<NewsNode *>(get_node_at_location(i));
        NewsNode* node2 = nullptr;

        if (node1 == nullptr) {
            return;
        }

        if (j == i + 1) {
            node2 = node1->nextAddress;
        }
        else if (j == i - 1) {
            node2 = node1->prevAddress;
        }
        else {
            node2 = static_cast<NewsNode*>(get_node_at_location(j));
        }

        if (node2 == nullptr) {
            return;
        }

        News* temp = node1->data;
        node1->data = node2->data;
        node2->data = temp;
    }

    NewsNode get_head() {
        return *static_cast<NewsNode*>(head);
    }

    NewsNode get_tail_node() {
        return *tail;
    }

    void* get_tail() override{
        return tail;
    }

    News* get_news_at_memory(void *memory) override {
        if (memory == nullptr) {
            return nullptr;
        }

        return static_cast<NewsNode*>(memory)->data;
    }

    void* move_to_next(void *current) override {
        if (current == tail) {
            return nullptr;
        }
        return static_cast<NewsNode*>(current)->nextAddress;
    }

    void* move_to_prev(void *current) override{
        if (current == head) {
            return nullptr;
        }
        return static_cast<NewsNode*>(current)->prevAddress;
    }

    void* split_left(int mid_point) override {
        auto* current = static_cast<NewsNode*>(head);
        NewsNode* new_head = current;
        auto* new_tail = static_cast<NewsNode*>(get_node_at_location(mid_point - 1));

        if (current == nullptr) {
            return nullptr;
        }

        return new NewsLinkedList(new_head, new_tail, mid_point, max_date, distinct_number_of_genres, distinct_number_of_keyword, genre_index, keyword_index);
    }

    void* split_right(int mid_point) override {
        auto* current = static_cast<NewsNode*>(head);
        auto* new_head = static_cast<NewsNode *>(get_node_at_location(mid_point + 1));
        NewsNode* new_tail = tail;

        if (current == nullptr) {
            return nullptr;
        }
        return new NewsLinkedList(new_head, new_tail, size - mid_point - 1, max_date, distinct_number_of_genres, genre_index);
    }

    void* allocate_empty_copy() override {
        auto* to_return = new NewsLinkedList();
        for (int i = 0; i < size; i++) {
            to_return->insert_empty();
        }
        to_return->size = this->size;
        return to_return;
    }

    void* allocate_empty() override {
        return new NewsLinkedList();
    }

};


