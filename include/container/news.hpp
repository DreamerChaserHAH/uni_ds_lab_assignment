// Author : Htet Aung Hlaing
// Created Date : 11th Feb, 2025
// <summary>
// Contains the base classes and enum (News and NewsGenre) to be used in other implementations
// </summary>

#pragma once

#include <string>
#include <ctime>

enum NewsGenre {
    WORLD_NEWS,
    POLITICS,
    OTHERS
};

enum CRITERIA {
    GENRE,
    PUBLICATION_DATE,
    IS_TRUE_NEWS
};

struct News {
    std::string title;
    std::string content;
    NewsGenre genre;
    time_t publication_date;
    tm publication_time_info;
    bool is_true = false;

    bool is_greater_than(News& news, CRITERIA criteria) {
        switch (criteria) {
            case GENRE:
                return genre > news.genre;
            case PUBLICATION_DATE:
                return (get_year() > news.get_year()) ? true: (get_year() == news.get_year()? get_date_in_year() > news.get_date_in_year(): false);
            case IS_TRUE_NEWS:
                return is_true > news.is_true;
            default:
                return false;
        }
    }

    bool is_lower_than(News& news, CRITERIA criteria) {
        switch (criteria) {
            case GENRE:
                return genre < news.genre;
            case PUBLICATION_DATE:
                return (get_year() < news.get_year()) ? true: (get_year() == news.get_year()? get_date_in_year() < news.get_date_in_year(): false);
            case IS_TRUE_NEWS:
                return is_true < news.is_true;
            default:
                return false;
        }
    }

    bool is_equal_or_greater_than(News& news, CRITERIA criteria) {
        switch (criteria) {
            case GENRE:
                return genre >= news.genre;
            case PUBLICATION_DATE:
                return (get_year() > news.get_year()) ? true: (get_year() == news.get_year() ? get_date_in_year() >= news.get_date_in_year(): false);
            case IS_TRUE_NEWS:
                return is_true >= news.is_true;
            default:
                return false;
        }
    }

    bool is_equal_or_lower_than(News& news, CRITERIA criteria) {
        switch (criteria) {
            case GENRE:
                return genre <= news.genre;
            case PUBLICATION_DATE:
                return (get_year() < news.get_year()) ? true: (get_year() == news.get_year() ? get_date_in_year() <= news.get_date_in_year(): false);
            case IS_TRUE_NEWS:
                return is_true <= news.is_true;
            default:
                return false;
        }
    }

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




