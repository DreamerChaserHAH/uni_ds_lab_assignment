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
    int capacity;
    News* head_pointer;

    void resize() {
        capacity *= 2;
        try {
            News* newArray = new News[capacity];
            for (int i = 0; i < size; i++) {
                newArray[i] = static_cast<News*>(head)[i];
            }
            delete[] static_cast<News*>(head);
            head = newArray;
            head_pointer = newArray;
        } catch (const std::bad_alloc& e) {
            std::cerr << "Memory allocation failed during resize: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    }

public:
    NewsArray(int cap = 10) : capacity(cap) {
        head = new News[capacity];
        head_pointer = static_cast<News*>(head);
    }

    NewsArray(News* head, int capacity, int size) {
        this->head = head;
        this->capacity = capacity;
        this->size = size;
        head_pointer = static_cast<News*>(head);
    }

    ~NewsArray() override{
        //delete[] newsArray;
    }

    void insert(News newNews) override {
        if (size == capacity) {
            resize();
        }

        if (newNews.publication_date > max_date) {
            max_date = newNews.publication_date;
        }

        static_cast<News*>(head)[size++] = newNews;
    }

    void insert_empty() override {
        if (size == capacity) {
            resize();
        }
        static_cast<News*>(head)[size++] = News();
    }

    void insert_at_location(News newNews, int location) override {
        if (location < 0 || location > size) {
            throw std::out_of_range("Invalid location");
        }
        if (size == capacity) {
            resize();
        }
        for (int i = size; i > location; i--) {
            static_cast<News*>(head)[i] = static_cast<News*>(head)[i - 1];
        }

        if (newNews.publication_date > max_date) {
            max_date = newNews.publication_date;
        }

        static_cast<News*>(head)[location] = newNews;
        size++;
    }

    News* get_at_location(int location) override {
        if (location < 0 || location >= size) {
            return nullptr;
        }
        return &static_cast<News*>(head)[location];
    }

    void delete_at_location(int location) override {
        if (location < 0 || location >= size) {
            throw std::out_of_range("Invalid location");
        }
        for (int i = location; i < size - 1; i++) {
            static_cast<News*>(head)[i] = static_cast<News*>(head)[i + 1];
        }
        size--;
    }

    void* get_node_at_location(int location) override {
        return get_at_location(location);
    }

    void overwrite_at_position(NewsContainer *value_container, int starting_location) override {
        /// value_container is a NewsArray with an arbitrary size
        /// we will insert the value inside the value_container to the current container's starting_location
        /// If there is more than one element, we will replace one by one using the put_at_location function
        int inserting_container_size = value_container->size;
        for (int i = 0; i < inserting_container_size; i++) {
            News* current_news = value_container->get_at_location(i);
            if (current_news == nullptr) {
                break;
            }
            put_at_location(*current_news, starting_location + i);
        }
    }

    void put_at_location(News newNews, int location) override {
        if (location < 0 || location >= size) {
            throw std::out_of_range("Invalid location");
        }
        static_cast<News*>(head)[location] = newNews;
    }

    void swap_news(int i, int j) override {
        if (i < 0 || i >= size || j < 0 || j >= size) {
            throw std::out_of_range("Invalid location");
        }
        News temp = static_cast<News*>(head)[i];
        static_cast<News*>(head)[i] = static_cast<News*>(head)[j];
        static_cast<News*>(head)[j] = temp;
    }

    void* get_tail() override {
        //return the address of the last element
        return &static_cast<News*>(head)[size - 1];
    }

    News* get_news_at_memory(void* memory) override{
        return static_cast<News*>(memory);
    }

    void* move_to_next(void* current) override {
        //current pointer is the address of the current element
        //return the address of the next element
        if (current == nullptr || current == get_tail()) {
            return nullptr;
        }

        return static_cast<News*>(current) + 1;
    }

    void* move_to_prev(void* current) override{
        //previous pointer is the address of the previous element
        //return the address of the next element
        if (current == nullptr || current == head) {
            return nullptr;
        }
        return static_cast<News*>(current) - 1;
    }

    void* split_left(int mid_point) override{
        ///split the array to the left excluding the midpoint
        ///the return pointer must be related to the current array

        return new NewsArray(static_cast<News*>(head), mid_point, mid_point);
    }

    void* split_right(int mid_point) override{
        //split the array to the right excluding the midpoint
        //the return pointer must be related to the current array

        return new NewsArray(static_cast<News*>(head) + mid_point + 1, size - (mid_point + 1), size - (mid_point + 1));
    }

    void* allocate_empty_copy() override {
        auto* to_return = new NewsArray(capacity);
        for (int i = 0; i < size; i++) {
            to_return->insert(static_cast<News*>(head)[i]);
        }
        return to_return;
    }
};