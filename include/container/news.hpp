// Author : Htet Aung Hlaing
// Created Date : 11th Feb, 2025
// <summary>
// Contains the base classes and enum (News and NewsGenre) to be used in other implementations
// </summary>

#pragma once

#include <string>
#include <ctime>

#include "news_container.hpp"

enum NewsGenre {
    WORLD_NEWS,
    POLITICS,
    OTHERS
};

struct News {
    std::string title;
    std::string content;
    NewsGenre genre;
    time_t publication_date;

    int getYear() const {
        struct tm* timeinfo = localtime(&publication_date);
        return timeinfo->tm_year + 1900; // convert to full years
    }

    bool operator==(const News & news) const = default;
};




