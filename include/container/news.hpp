// Author : Htet Aung Hlaing
// Created Date : 11th Feb, 2025
// <summary>
// Contains the base classes and enum (News and NewsGenre) to be used in other implementations
// </summary>

#pragma once

#include <string>
#include <ctime>

class NewsContainer; // Forward declaration

enum CRITERIA {
    GENRE,
    PUBLICATION_DATE,
    IS_TRUE_NEWS,
    PUBLICATION_YEAR,
    PUBLICATION_MONTH
};

enum NewsGenre {
    MIDDLE_EAST = 0,
    US_NEWS = 1,
    WORLD_NEWS = 2,
    GOVERNMENT = 3,
    LEFT_NEWS = 4,
    GENERAL = 5,
    UNCATEGORIZED = 6
};

struct News {
    std::string title;
    std::string content;
    std::string genre;
    time_t publication_date;
    tm publication_time_info;
    bool is_true = false;

    bool is_greater_than(News& news, CRITERIA criteria, NewsContainer* news_container);
    bool is_lower_than(News& news, CRITERIA criteria, NewsContainer* news_container);
    bool is_equal_or_greater_than(News& news, CRITERIA criteria, NewsContainer* news_container);
    bool is_equal_or_lower_than(News& news, CRITERIA criteria, NewsContainer* news_container);

    int get_year() {
        return publication_time_info.tm_year + 1900; // convert to full years
    }

    int get_month() {
        return publication_time_info.tm_mon + 1; // convert to full months
    }

    int get_date_in_year() {
        return publication_time_info.tm_yday + 1;
    }
    bool operator==(const News & news) const = delete;
};

