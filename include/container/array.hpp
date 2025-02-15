/// <summary>
/// Custom Array Container in C++ with Dedicated Functions
/// </summary>

#pragma once

#include <string>

#include "news.hpp"
#include "news_container.hpp"

class NewsArray: public NewsContainer {
    public:
        void insert(News newNews) override {

        }

        void insert_at_location(News newNews, int location) override {

        }

        News* get_at_location(int locaiton) override {
            return nullptr;
        }
};