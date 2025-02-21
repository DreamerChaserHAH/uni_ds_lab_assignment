/// <summary>
/// Search Algorithms
/// 1. Linear Search (Abbirami)
/// 2. Binary Search
/// 3. Interpolation Search
/// 4. Jump Search (Abbirami)
/// 5. Hash Table
/// 6. Exponential Search (Kaung)
/// 7. Sublist Search
/// 8. Fibonacci Search
/// </summary>

#pragma once

#include <container/news_container.hpp>

enum SEARCH_CRITERIA {
    SEARCH_PUBLICATION_YEAR,
    SEARCH_PUBLICATION_MONTH,
    SEARCH_PUBLICATION_GENRE,
    SEARCH_TRUE_OR_FALSE_NEWS
};

inline NewsContainer* two_pointer_search(NewsContainer* original, SEARCH_CRITERIA criteria, std::string search_content) {
    if (original == nullptr) {
        return nullptr;
    }

    if (original->size == 0) {
        return nullptr;
    }

    long search_value = -1;
    CRITERIA main_criteria = {};
    switch (criteria) {
        case SEARCH_PUBLICATION_YEAR:
            search_value = std::stoi(search_content);
            main_criteria = PUBLICATION_YEAR;
            break;
        case SEARCH_PUBLICATION_MONTH:
            search_value = std::stoi(search_content);
            main_criteria = PUBLICATION_MONTH;
            break;
        case SEARCH_PUBLICATION_GENRE:
            search_value = search_content == "POLITICS"? NewsGenre::POLITICS: NewsGenre::WORLD_NEWS;
            main_criteria = GENRE;
            break;
        case SEARCH_TRUE_OR_FALSE_NEWS:
            search_value = search_content == "true"? 1: 0;
            main_criteria = IS_TRUE_NEWS;
            break;
        default:
            return nullptr;
    }

    int left_index = 0;
    int right_index = original->size - 1;

    while (left_index <= right_index) {
        News* left_news = original->get_at_location(left_index);
        if (left_news == nullptr) {
            break;
        }

        long current_value = get_criteria_value(left_news, main_criteria);
        if (current_value >= search_value) {
            break;
        }
        left_index++;
    }

    while (right_index >= left_index) {
        News* right_news = original->get_at_location(right_index);
        if (right_news == nullptr) {
            break;
        }

        if (get_criteria_value(right_news, main_criteria) <= search_value) {
            break;
        }
        right_index--;
    }

    auto* result = static_cast<NewsContainer*>(original->allocate_empty());
    for (int i = left_index; i <= right_index; i++) {
        result->insert(*original->get_at_location(i));
    }

    if (result->size == 0) {
        return nullptr;
    }
    return result;
}

inline NewsContainer* linear_search(NewsContainer* original, CRITERIA criteria) {
    return nullptr;
}

inline NewsContainer* binary_search(NewsContainer* original, CRITERIA criteria, std::string& target) {
    if (original == nullptr) {
        return nullptr;
    }
    return nullptr;
}

inline NewsContainer* jump_search(NewsContainer* original, CRITERIA criteria) {
    return nullptr;
}

inline NewsContainer* two_pointer_range_search(NewsContainer* original, CRITERIA criteria) {
    return nullptr;
}

inline NewsContainer* exponential_search(NewsContainer* original, CRITERIA criteria) {
    return nullptr;
}

