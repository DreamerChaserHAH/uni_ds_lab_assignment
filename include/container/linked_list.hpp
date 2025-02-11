/// <summary>
/// Custom Linked List Implementation in C++
/// </summary>
#pragma once
#include "news.hpp"
using namespace std;

struct NewsNodePtr {
    News data;
    NewsNodePtr* nextAddress;
    NewsNodePtr* prevAddress;
};
class NewsLinkedList {
private:
    NewsNodePtr* head;
    NewsNodePtr* tail;
public:
    NewsLinkedList(string filePath) : head(nullptr), tail(nullptr) {}
    void InsertNode(News structNews);
    void insertAtLocation(News structNews, int location);
    NewsNodePtr* getAtLocation(int location);
    NewsNodePtr* getHead();
    NewsNodePtr* getTail();
    void displayArticle();
    ~NewsLinkedList();
};


