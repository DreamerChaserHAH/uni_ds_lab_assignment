/// <summary>
/// Search Algorithms
/// 1. Linear Search (Abbirami)
/// 2. Binary Search
/// 3. Interpolation Search
/// 4. Jump Search (Abbirami)
/// 5. Hash Table
/// 6. Exponential Search
/// 7. Sublist Search
/// 8. Fibonacci Search
/// </summary>

#pragma once

#include <container/news_container.hpp>

enum SEARCH_CRITERIA {
    GENRE,
    PUBLICATION_DATE,
    TRUE_NEWS
};

inline NewsContainer* linear_search(NewsContainer* original, SEARCH_CRITERIA criteria) {
    return nullptr;
}

inline NewsContainer* binary_search(NewsContainer* original, SEARCH_CRITERIA criteria, std::string& target) {
    if (original == nullptr) {
        return nullptr;
    }
    return nullptr;
}

inline NewsContainer* jump_search(NewsContainer* original, SEARCH_CRITERIA criteria) {
    return nullptr;
}

inline NewsContainer* two_pointer_range_search(NewsContainer* original, SEARCH_CRITERIA criteria) {
    return nullptr;
}

