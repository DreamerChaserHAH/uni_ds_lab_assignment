/// <summary>
/// Custom Linked List Implementation in C++
/// </summary>
#pragma once
using namespace std;

#include <string>

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

    NewsLinkedList(NewsNode* head_pointer, NewsNode* tail_pointer, int size) {
        this->head = head_pointer;
        this->size = size;
        this->tail = tail_pointer;
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
        return (current->data);
    }

    NewsNode* get_node_at_location(int location) {
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
    }

    void delete_at_location(int location) override {
        NewsNode* node = get_node_at_location(location);
        if (node == nullptr) {
            return;
        }

        node->prevAddress->nextAddress = node->nextAddress;
        node->nextAddress->prevAddress = node->prevAddress;
        if (node == tail) {
            tail = node->prevAddress;
        }

        if (node == head) {
            head = node->nextAddress;
        }

        delete node;
    }

    void overwrite_at_position(NewsContainer *value_container, int starting_location) override {
        int new_container_size = value_container->size;
        NewsNode* current_node = get_node_at_location(starting_location);
        if (current_node == nullptr) {
            return;
        }
        int index = 0;
        while (true) {
            if (index >= new_container_size) {
                break;
            }
            current_node->data = value_container->get_at_location(index);
            current_node = current_node->nextAddress;
            index++;
        }
    }

    void put_at_location(News newNews, int location) override {
        NewsNode* node_ptr = get_node_at_location(location);
        if (node_ptr == nullptr) {
            return;
        }
        node_ptr->data = new News(newNews);
    }

    void swap_news(int i, int j) override {
        NewsNode* node1 = get_node_at_location(i);
        NewsNode* node2 = get_node_at_location(j);

        if (node1 == nullptr || node2 == nullptr) {
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
        return static_cast<NewsNode*>(current)->nextAddress;
    }

    void* move_to_prev(void *current) override{
        return static_cast<NewsNode*>(current)->prevAddress;
    }

    void* split_left(int mid_point) override {
        auto* current = static_cast<NewsNode*>(head);
        NewsNode* new_head = current;
        NewsNode* new_tail = get_node_at_location(mid_point - 1);

        if (current == nullptr) {
            return nullptr;
        }

        return new NewsLinkedList(new_head, new_tail, mid_point);
    }

    void* split_right(int mid_point) override {
        auto* current = static_cast<NewsNode*>(head);
        NewsNode* new_head = get_node_at_location(mid_point + 1);
        NewsNode* new_tail = tail;

        if (current == nullptr) {
            return nullptr;
        }
        return new NewsLinkedList(new_head, new_tail, size - mid_point - 1);
    }

    void* allocate_empty_copy() override {
        auto* to_return = new NewsLinkedList();
        for (int i = 0; i < size; i++) {
            to_return->insert_empty();
        }
        to_return->size = this->size;
        return to_return;
    }

};


