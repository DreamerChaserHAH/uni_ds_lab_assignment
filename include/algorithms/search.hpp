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

inline NewsContainer* two_pointer_search(NewsContainer* news_container, SEARCH_CRITERIA criteria, std::string search_content) {
    if (news_container == nullptr) {
        return nullptr;
    }

    if (news_container->size == 0) {
        return nullptr;
    }

    long search_value = -1;
    CRITERIA main_criteria = {};
    News example;
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
            example.genre = "\""+search_content+"\"";
            search_value = news_container->get_criteria_value(&example, GENRE);
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
    int right_index = news_container->size - 1;

    while (left_index <= right_index) {
        News* left_news = news_container->get_at_location(left_index);
        if (left_news == nullptr) {
            break;
        }

        long current_value = news_container->get_criteria_value(left_news, main_criteria);
        if (current_value >= search_value) {
            break;
        }
        left_index++;
    }

    while (right_index >= left_index) {
        News* right_news = news_container->get_at_location(right_index);
        if (right_news == nullptr) {
            break;
        }

        if (news_container->get_criteria_value(right_news, main_criteria) <= search_value) {
            break;
        }
        right_index--;
    }

    auto* result = static_cast<NewsContainer*>(news_container->allocate_empty());
    for (int i = left_index; i <= right_index; i++) {
        News* news_at_location = news_container->get_at_location(i);
        result->insert(*news_container->get_at_location(i));
    }

    if (result->size == 0) {
        return nullptr;
    }
    return result;
}

inline NewsContainer* linear_search(NewsContainer* news_container, SEARCH_CRITERIA criteria, std::string search_content) {
    if (news_container == nullptr || news_container->size == 0) {
        return nullptr;
    }

    long search_value = -1;
    CRITERIA main_criteria;
    News example;
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
            example.genre = "\""+search_content+"\"";
            search_value = news_container->get_criteria_value(&example, GENRE);
            main_criteria = GENRE;
        break;
        case SEARCH_TRUE_OR_FALSE_NEWS:
            search_value = (search_content == "true") ? 1 : 0;
            main_criteria = IS_TRUE_NEWS;
        break;
        default:
            return nullptr;
    }

    auto* result = static_cast<NewsContainer *>(news_container->allocate_empty());
    for (int i = 0; i < news_container->size; i++) {
        News* news_item = news_container->get_at_location(i);
        if (news_container->get_criteria_value(news_item, main_criteria) == search_value) {
            result->insert(*news_item);
        }
    }
    return result;
}

inline NewsContainer* binary_search(NewsContainer* news_container, SEARCH_CRITERIA criteria, std::string search_content) {
    if (news_container == nullptr || news_container->size == 0) {
        return nullptr;
    }

    long search_value = -1;
    CRITERIA main_criteria;
    News example;
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
            example.genre = "\""+search_content+"\"";
            search_value = news_container->get_criteria_value(&example, GENRE);
            main_criteria = GENRE;
            break;
        case SEARCH_TRUE_OR_FALSE_NEWS:
            search_value = (search_content == "true") ? 1 : 0;
            main_criteria = IS_TRUE_NEWS;
            break;
        default:
            return nullptr;
    }

    int left = 0, right = news_container->size - 1, mid = 0;
    int found_index = -1;
    while (left <= right) {
        mid = left + (right - left) / 2;
        News* mid_news = news_container->get_at_location(mid);
        if (!mid_news)
            break;
        long mid_val = news_container->get_criteria_value(mid_news, main_criteria);
        if (mid_val == search_value) {
            found_index = mid;
            break;
        } else if (mid_val < search_value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // If no matching element was found, return nullptr.
    if (found_index == -1) {
        return nullptr;
    }

    // Expand to find the entire range of matching items.
    int start = found_index;
    while (start > 0) {
        News* prev_news = news_container->get_at_location(start - 1);
        if (prev_news && news_container->get_criteria_value(prev_news, main_criteria) == search_value)
            start--;
        else
            break;
    }

    int end = found_index;
    while (end < news_container->size - 1) {
        News* next_news = news_container->get_at_location(end + 1);
        if (next_news && news_container->get_criteria_value(next_news, main_criteria) == search_value)
            end++;
        else
            break;
    }

    // Create a new container and copy the matching news.
    auto* result = static_cast<NewsContainer*>(news_container->allocate_empty());
    for (int i = start; i <= end; i++) {
        News* news_item = news_container->get_at_location(i);
        if (news_item) {
            result->insert(*news_item);
        }
    }
    if (result->size == 0) {
        return nullptr;
    }
    return result;
}

inline NewsContainer* jump_search(NewsContainer* news_container, CRITERIA criteria) {
    return nullptr;
}

inline NewsContainer* exponential_search(NewsContainer* news_container, CRITERIA criteria) {
    return nullptr;
}

