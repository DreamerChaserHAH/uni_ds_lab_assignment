// Author : Htet Aung Hlaing
// Created Date : 11th Feb, 2025
// <summary>
// Contains the base classes and enum (News and NewsGenre) to be used in other implementations
// </summary>

#pragma once

#include <string>
#include <ctime>

#include "linked_list.hpp"

enum NewsGenre {
    WORLD_NEWS,
    POLITICS
};

struct News {
    std::string title;
    std::string content;
    NewsGenre genre;
    time_t publication_date;

    bool operator==(const News & news) const = default;
};
