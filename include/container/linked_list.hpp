/// <summary>
/// Custom Linked List Implementation in C++
/// </summary>
#pragma once
using namespace std;

#include <string>

#include "news.hpp"
#include "news_container.hpp"

struct NewsNode {
    News data;
    NewsNode* nextAddress;
    NewsNode* prevAddress;
};

class NewsLinkedList : public NewsContainer{
private:
    NewsNode* head;
    NewsNode* tail;

public:
    NewsLinkedList() : head(nullptr), tail(nullptr) {

    }

    void insert(News newNews) override{
        auto* newsNode = new NewsNode;
        newsNode->data = std::move(newNews);
        newsNode->nextAddress = nullptr;
        newsNode->prevAddress = tail;

        if (head == nullptr) {
            head = newsNode;
            tail = head;
            return;
        }else {
            tail->nextAddress = newsNode;
            tail = newsNode;
        }
    }

     News* get_at_location(int location) override {
        NewsNode* current = head;
        for (int i = 0; i < location; i++) {
            if (current == nullptr) {
                return nullptr;
            }
            current = current->nextAddress;
        }
        return &(current->data);
    }

    void insert_at_location(News newNews, int location) override {
        auto* newsNode = new NewsNode;
        newsNode->data = std::move(newNews);
        newsNode->nextAddress = nullptr;
        newsNode->prevAddress = nullptr;

        if (location == 0) {
            newsNode->nextAddress = head;
            head->prevAddress = newsNode;
            head = newsNode;
            return;
        }

        NewsNode* current = head;
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

    NewsNode get_head() {
        return *head;
    }

    NewsNode get_tail() {
        return *tail;
    }

    ~NewsLinkedList() {

    }
};


