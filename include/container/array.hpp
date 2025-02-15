/// <summary>
/// Custom Array Container in C++ with Dedicated Functions
/// </summary>

#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include "news.hpp"
#include "news_container.hpp"

class NewsArray : public NewsContainer {
private:
    News* newsArray;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
        try {
            News* newArray = new News[capacity];
            for (int i = 0; i < size; i++) {
                newArray[i] = newsArray[i];
            }
            delete[] newsArray;
            newsArray = newArray;
        } catch (const std::bad_alloc& e) {
            std::cerr << "Memory allocation failed during resize: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    }

public:
    NewsArray(int cap = 10) : size(0), capacity(cap) {
        newsArray = new News[capacity];
    }

    ~NewsArray() {
        delete[] newsArray;
    }

    void insert(News newNews) override {
        if (size == capacity) {
            resize();
        }
        newsArray[size++] = newNews;
    }

    void insert_at_location(News newNews, int location) override {
        if (location < 0 || location > size) {
            throw std::out_of_range("Invalid location");
        }
        if (size == capacity) {
            resize();
        }
        for (int i = size; i > location; i--) {
            newsArray[i] = newsArray[i - 1];
        }
        newsArray[location] = newNews;
        size++;
    }

    News* get_at_location(int location) override {
        if (location < 0 || location >= size) {
            return nullptr;
        }
        return &newsArray[location];
    }

};