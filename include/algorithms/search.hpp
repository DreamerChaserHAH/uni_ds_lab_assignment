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
#include <cmath>

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

    if (search_value == -1) {
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
        if (current_value == search_value) {
            break;
        }
        left_index++;
    }

    while (right_index >= left_index) {
        News* right_news = news_container->get_at_location(right_index);
        if (right_news == nullptr) {
            break;
        }

        if (news_container->get_criteria_value(right_news, main_criteria) == search_value) {
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

    if (search_value == -1) {
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

    // 2. Convert the search_content string into a numeric or enumerated value,
    //    and determine the corresponding CRITERIA to compare against.
    long search_value = -1;
    CRITERIA main_criteria;
    News example;
    switch (criteria) {
        case SEARCH_PUBLICATION_YEAR:
            // Convert year from string to integer.
            search_value = std::stoi(search_content);
            main_criteria = PUBLICATION_YEAR;
            break;
        case SEARCH_PUBLICATION_MONTH:
            // Convert month from string to integer.
            search_value = std::stoi(search_content);
            main_criteria = PUBLICATION_MONTH;
            break;
        case SEARCH_PUBLICATION_GENRE:
            example.genre = "\""+search_content+"\"";
            search_value = news_container->get_criteria_value(&example, GENRE);
            main_criteria = GENRE;
            break;
        case SEARCH_TRUE_OR_FALSE_NEWS:
            // Convert "true" to 1, "false" to 0.
            search_value = (search_content == "true") ? 1 : 0;
            main_criteria = IS_TRUE_NEWS;
            break;
        default:
            return nullptr;
    }

    if (search_value == -1) {
        return nullptr;
    }

    int left = 0, right = news_container->size - 1, mid = 0;
    int found_index = -1;
    while (left <= right) {
        //calculate the midpoint.
        mid = left + (right - left) / 2;
        News* mid_news = news_container->get_at_location(mid);
        if (!mid_news)
            break;
        long mid_val = news_container->get_criteria_value(mid_news, main_criteria);
        // Compare the midpoint's value (based on main_criteria) to the target (search_value).
        if (mid_val == search_value) {
            found_index = mid;
            break;
        } else if (mid_val < search_value) {
            left = mid + 1; //search in the right half
        } else {
            right = mid - 1;// search in the left half
        }
    }

    // // 4. If we never found a matching element, return nullptr.
    if (found_index == -1) {
        return nullptr;
    }

    // 5. Expand from the found index to include all consecutive matches to the left.
    int start = found_index;
    while (start > 0) {
        News* prev_news = news_container->get_at_location(start - 1);
        if (prev_news && news_container->get_criteria_value(prev_news, main_criteria) == search_value)
            start--;
        else
            break;
    }
    //6. Expand from the found index to include all consecutive matches to the right.
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
    //8. If the resulting container is empty for some reason, return nullptr.
    if (result->size == 0) {
        return nullptr;
    }
    // 9. Otherwise, return the container with the matching elements.
    return result;
}

inline NewsContainer* exponential_search(NewsContainer* news_container, SEARCH_CRITERIA criteria, std::string search_content) {
    // 1. Validate that the container is not null or empty.
    if (news_container == nullptr || news_container->size == 0)
        return nullptr;

    // 2. Convert the search_content string into a numeric or enumerated value
    //    depending on the chosen SEARCH_CRITERIA.
    long search_value = -1;
    CRITERIA main_criteria;
    News example;
    switch (criteria) {
        case SEARCH_PUBLICATION_YEAR:
            // Convert year from string to integer.
                search_value = std::stoi(search_content);
        main_criteria = PUBLICATION_YEAR;
        break;
        case SEARCH_PUBLICATION_MONTH:
            // Convert month from string to integer.
                search_value = std::stoi(search_content);
        main_criteria = PUBLICATION_MONTH;
        break;
        case SEARCH_PUBLICATION_GENRE:
            example.genre = "\""+search_content+"\"";
        search_value = news_container->get_criteria_value(&example, GENRE);
        main_criteria = GENRE;
        break;
        case SEARCH_TRUE_OR_FALSE_NEWS:
            // Convert "true" to 1, "false" to 0.
                search_value = (search_content == "true") ? 1 : 0;
        main_criteria = IS_TRUE_NEWS;
        break;
        default:
            return nullptr;
    }

    if (search_value == -1) {
        return nullptr;
    }

    // 3. Check the first element for a quick match.
    int n = news_container->size;
    News* first_news = news_container->get_at_location(0);
    if (!first_news) {
        // If the first element is somehow invalid, return nullptr.
        return nullptr;
    }
    if (news_container->get_criteria_value(first_news, main_criteria) == search_value) {
        // The target was found at index 0; we will still proceed to find
        // any consecutive matching elements.
        // The next steps (binary search) will handle range detection.
    }

    // 4. Determine the search range exponentially.
    //    Start from index 1, double the index until we either exceed the array
    //    size or find a value >= the target.
    int bound = 1;
    while (bound < n && news_container->get_criteria_value(news_container->get_at_location(bound), main_criteria) < search_value) {
        bound *= 2;
    }

    // 5. Once the range is identified, perform a binary search in that subrange:
    //    from bound/2 up to min(bound, n-1).
    int left = bound / 2;
    int right = (bound < n) ? bound : (n - 1);
    int found_index = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        News* mid_news = news_container->get_at_location(mid);
        if (!mid_news) {
            break;
        }
        long mid_val = news_container->get_criteria_value(mid_news, main_criteria);

        if (mid_val == search_value) {
            // We found an instance of the target.
            found_index = mid;
            break;
        } else if (mid_val < search_value) {
            // Move to the right half of the current subrange.
            left = mid + 1;
        } else {
            // Move to the left half of the current subrange.
            right = mid - 1;
        }
    }

    // 6. If no match was found at all, return nullptr.
    if (found_index == -1)
        return nullptr;

    // 7. Expand around the found index to include all consecutive matching elements.
    //    This handles the case where multiple items share the same search value.
    int start = found_index;
    while (start > 0) {
        News* prev_news = news_container->get_at_location(start - 1);
        if (prev_news && news_container->get_criteria_value(prev_news, main_criteria) == search_value) {
            start--;
        } else {
            break;
        }
    }
    int end = found_index;
    while (end < n - 1) {
        News* next_news = news_container->get_at_location(end + 1);
        if (next_news && news_container->get_criteria_value(next_news, main_criteria) == search_value) {
            end++;
        } else {
            break;
        }
    }

    // 8. Create a new container to store all the matching items.
    auto* result = static_cast<NewsContainer*>(news_container->allocate_empty());
    for (int i = start; i <= end; i++) {
        News* matching_news = news_container->get_at_location(i);
        if (matching_news) {
            result->insert(*matching_news);
        }
    }

    // 9. Return the container if it has matches; otherwise, return nullptr.
    if (result->size == 0)
        return nullptr;

    return result;
}


