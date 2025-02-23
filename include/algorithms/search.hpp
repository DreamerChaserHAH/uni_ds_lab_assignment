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

inline NewsContainer* binary_search(NewsContainer* original, SEARCH_CRITERIA criteria, std::string search_content) {
    // 1. Verify that the input container is valid and non-empty.
    if (original == nullptr || original->size == 0) {
        return nullptr;
    }

    // 2. Convert the search_content string into a numeric or enumerated value,
    //    and determine the corresponding CRITERIA to compare against.
    long search_value = -1;
    CRITERIA main_criteria;
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
            // If "POLITICS" is given, use the POLITICS enum value; otherwise default to WORLD_NEWS.
            search_value = (search_content == "POLITICS") ? NewsGenre::POLITICS : NewsGenre::WORLD_NEWS;
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

    // 3. Perform a standard binary search to locate one matching element in the container.
    int left = 0, right = original->size - 1, mid = 0;
    int found_index = -1;
    while (left <= right) {
        //calculate the midpoint.
        mid = left + (right - left) / 2;
        News* mid_news = original->get_at_location(mid);
        if (!mid_news)
            break;
        // Compare the midpoint's value (based on main_criteria) to the target (search_value).
        long mid_val = get_criteria_value(mid_news, main_criteria);
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
        News* prev_news = original->get_at_location(start - 1);
        if (prev_news && get_criteria_value(prev_news, main_criteria) == search_value)
            start--;
        else
            break;
    }
    //6. Expand from the found index to include all consecutive matches to the right.
    int end = found_index;
    while (end < original->size - 1) {
        News* next_news = original->get_at_location(end + 1);
        if (next_news && get_criteria_value(next_news, main_criteria) == search_value)
            end++;
        else
            break;
    }

    // // 7. Create a new container to store all the matching items.
    auto* result = static_cast<NewsContainer*>(original->allocate_empty());
    for (int i = start; i <= end; i++) {
        News* news_item = original->get_at_location(i);
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







inline NewsContainer* jump_search(NewsContainer* original, SEARCH_CRITERIA criteria, std::string search_content) {
    // 1. Validate that the container is neither null nor empty.
    if (original == nullptr || original->size == 0)
        return nullptr;

    // 2. Convert the search_content string to a numeric or enumerated value,
    //    depending on which SEARCH_CRITERIA was requested.
    long search_value = -1;
    CRITERIA main_criteria;
    switch (criteria) {
        case SEARCH_PUBLICATION_YEAR:
            // Convert the publication year string to an integer.
            search_value = std::stoi(search_content);
            main_criteria = PUBLICATION_YEAR;
            break;
        case SEARCH_PUBLICATION_MONTH:
            // Convert the publication month string to an integer.
            search_value = std::stoi(search_content);
            main_criteria = PUBLICATION_MONTH;
            break;
        case SEARCH_PUBLICATION_GENRE:
            // If the string is "POLITICS", use the POLITICS enum; otherwise default to WORLD_NEWS.
            search_value = (search_content == "POLITICS") ? NewsGenre::POLITICS : NewsGenre::WORLD_NEWS;
            main_criteria = GENRE;
            break;
        case SEARCH_TRUE_OR_FALSE_NEWS:
            // Convert "true" to 1 and "false" to 0.
            search_value = (search_content == "true") ? 1 : 0;
            main_criteria = IS_TRUE_NEWS;
            break;
        default:
            return nullptr;
    }

    // 3. Determine the jump size (block size) based on the square root of the total number of items.
    int n = original->size;
    int jump = static_cast<int>(std::sqrt(n));
    int prev_index = 0;
    int current_index = jump;

    // 4. Jump ahead by 'jump' steps until we either exceed the array size
    //    or find a block where the value at 'current_index' is >= search_value.
    while (current_index < n &&
           get_criteria_value(original->get_at_location(current_index), main_criteria) < search_value) {
        prev_index = current_index;
        current_index += jump;
        if (current_index > n - 1)
            current_index = n;  // Prevent overshooting the array bounds.
    }

    // 5. Perform a linear search within the identified block (from prev_index up to current_index).
    int found_index = -1;
    for (int i = prev_index; i < current_index; i++) {
        if (i < n) {
            News* news_item = original->get_at_location(i);
            if (news_item && get_criteria_value(news_item, main_criteria) == search_value) {
                found_index = i;
                break;
            }
        }
    }

    // 6. If no match was found in the block, return nullptr.
    if (found_index == -1)
        return nullptr;

    // 7. Expand around the found index to include any consecutive matching elements on both sides.
    int start = found_index;
    while (start > 0) {
        News* prev_news = original->get_at_location(start - 1);
        if (prev_news && get_criteria_value(prev_news, main_criteria) == search_value)
            start--;
        else
            break;
    }
    int end = found_index;
    while (end < n - 1) {
        News* next_news = original->get_at_location(end + 1);
        if (next_news && get_criteria_value(next_news, main_criteria) == search_value)
            end++;
        else
            break;
    }

    // 8. Create a new container and copy all matching elements into it.
    auto* result = static_cast<NewsContainer*>(original->allocate_empty());
    for (int i = start; i <= end; i++) {
        result->insert(*original->get_at_location(i));
    }

    // 9. Return the result if it contains matches; otherwise return nullptr.
    if (result->size == 0)
        return nullptr;
    return result;
}


inline NewsContainer* two_pointer_range_search(NewsContainer* original, CRITERIA criteria) {
    return nullptr;
}
inline NewsContainer* exponential_search(NewsContainer* original, SEARCH_CRITERIA criteria, std::string search_content) {
    // 1. Validate that the container is not null or empty.
    if (original == nullptr || original->size == 0)
        return nullptr;

    // 2. Convert the search_content string into a numeric or enumerated value
    //    depending on the chosen SEARCH_CRITERIA.
    long search_value = -1;
    CRITERIA main_criteria;
    switch (criteria) {
        case SEARCH_PUBLICATION_YEAR:
            // Convert the year string to an integer.
            search_value = std::stoi(search_content);
            main_criteria = PUBLICATION_YEAR;
            break;
        case SEARCH_PUBLICATION_MONTH:
            // Convert the month string to an integer.
            search_value = std::stoi(search_content);
            main_criteria = PUBLICATION_MONTH;
            break;
        case SEARCH_PUBLICATION_GENRE:
            // Map the string "POLITICS" to NewsGenre::POLITICS; otherwise default to WORLD_NEWS.
            search_value = (search_content == "POLITICS") ? NewsGenre::POLITICS : NewsGenre::WORLD_NEWS;
            main_criteria = GENRE;
            break;
        case SEARCH_TRUE_OR_FALSE_NEWS:
            // Convert "true" to 1 and "false" to 0.
            search_value = (search_content == "true") ? 1 : 0;
            main_criteria = IS_TRUE_NEWS;
            break;
        default:
            return nullptr;
    }

    // 3. Check the first element for a quick match.
    int n = original->size;
    News* first_news = original->get_at_location(0);
    if (!first_news) {
        // If the first element is somehow invalid, return nullptr.
        return nullptr;
    }
    if (get_criteria_value(first_news, main_criteria) == search_value) {
        // The target was found at index 0; we will still proceed to find
        // any consecutive matching elements.
        // The next steps (binary search) will handle range detection.
    }

    // 4. Determine the search range exponentially.
    //    Start from index 1, double the index until we either exceed the array
    //    size or find a value >= the target.
    int bound = 1;
    while (bound < n && get_criteria_value(original->get_at_location(bound), main_criteria) < search_value) {
        bound *= 2;
    }

    // 5. Once the range is identified, perform a binary search in that subrange:
    //    from bound/2 up to min(bound, n-1).
    int left = bound / 2;
    int right = (bound < n) ? bound : (n - 1);
    int found_index = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        News* mid_news = original->get_at_location(mid);
        if (!mid_news) {
            break;
        }
        long mid_val = get_criteria_value(mid_news, main_criteria);

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
        News* prev_news = original->get_at_location(start - 1);
        if (prev_news && get_criteria_value(prev_news, main_criteria) == search_value) {
            start--;
        } else {
            break;
        }
    }
    int end = found_index;
    while (end < n - 1) {
        News* next_news = original->get_at_location(end + 1);
        if (next_news && get_criteria_value(next_news, main_criteria) == search_value) {
            end++;
        } else {
            break;
        }
    }

    // 8. Create a new container to store all the matching items.
    auto* result = static_cast<NewsContainer*>(original->allocate_empty());
    for (int i = start; i <= end; i++) {
        News* matching_news = original->get_at_location(i);
        if (matching_news) {
            result->insert(*matching_news);
        }
    }

    // 9. Return the container if it has matches; otherwise, return nullptr.
    if (result->size == 0)
        return nullptr;

    return result;
}


