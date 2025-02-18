/// <summary>
/// 1. Bubble Sort (Livi)
/// 2. Selection Sort
/// 3. Insertion Sort (Abbirami)
/// 4. Merge Sort (Abbirami)
/// 5. Quick Sort (Htet Aung Hlaing)
/// 6. Radix Sort (Kaung)
/// 7. Counting Sort (Htet Aung Hlaing)
/// 8. Bucket Sort (Kaung)
/// </summary>

#pragma once

#include "container/news_container.hpp"

inline void bubble_sort(NewsContainer& news_container) {

}

inline void selection_sort(NewsContainer& news_container) {

}

inline void insertion_sort(NewsContainer& news_container) {

}

inline void merge_sort(NewsContainer& news_container) {

}

inline void quick_sort(NewsContainer& news_container) {

    /// Here's the quick sort algorithm implementation working with the NewsContainer (both linkedlist and array)
    /// 1. Set the last element as pivot
    /// 2. Have two pointers: item from left and item from right
    /// 3. any item from the left with the publication date greater than the pivot date
    ///  and any item from the right with the publication date less than the pivot date
    ///  get swapped using the swap method in the news container
    /// 4. if the index of the left pointer is greater than or equal to the right pointer, swap the pivot with the left pointer
    /// 5. recursively call the function for the two sides of the pivot
    /// References: https://www.youtube.com/watch?v=Hoixgm4-P4M

    void* head_pointer = news_container.head;
    void* tail_pointer = news_container.get_tail();

    /// # Step 1
    News* pivot_news_pointer = news_container.get_news_at_memory(tail_pointer);
    if (pivot_news_pointer == nullptr) {
        return;
    }
    time_t pivot_date = pivot_news_pointer->publication_date;

    /// # Step 2
    int left_pointer_index = 0;
    void* left_pointer = head_pointer;

    int right_pointer_index = news_container.size - 2;
    void* right_pointer = news_container.move_to_prev(tail_pointer);

    do {
        News left, right;
        /// # Step 3
        while (left_pointer_index <= news_container.size - 2) {
            News* news_at_memory = news_container.get_news_at_memory(left_pointer);
            if (news_at_memory == nullptr) {
                break;
            }
            left = *news_at_memory;

            if (news_at_memory->publication_date > pivot_date) {
                break;
            }

            left_pointer = news_container.move_to_next(left_pointer);
            if (left_pointer == nullptr) {
                break;
            }
            left_pointer_index++;
        }

        while (right_pointer_index >= 0) {
            News* news_at_memory = news_container.get_news_at_memory(right_pointer);
            if (news_at_memory == nullptr) {
                break;
            }
            right = *news_at_memory;
            if (news_at_memory->publication_date < pivot_date) {
                break;
            }

            right_pointer = news_container.move_to_prev(right_pointer);
            if (right_pointer == nullptr) {
                break;
            }
            right_pointer_index--;
        }

        if (left_pointer_index >= right_pointer_index) {
            /// # Step 4
            news_container.swap_news(left_pointer_index, news_container.size - 1);
            break;
        }

        news_container.swap_news(left_pointer_index, right_pointer_index);
    }while (true);

    /// # Step 5

    if (left_pointer_index > 0) {
        auto* left_container = static_cast<NewsContainer*>(news_container.split_left(left_pointer_index));
        auto* right_container = static_cast<NewsContainer*>(news_container.split_right(left_pointer_index));

        quick_sort(*left_container);
        quick_sort(*right_container);
    }

}

inline void counting_sort(NewsContainer& news_container) {
    /// 1. Understand which element has the highest publication date
    /// 2. Create an temporary array with max + 1 elements
    /// 3. Store the occurence of each unique input
    /// 4. Cumlative sum each element and put into each index
    /// 5. Generate the final sorted container

    void *tail_pointer = news_container.get_tail();
    /// # Step 1
    time_t max_date = news_container.get_max_date();

    /// # Step 2
    long* count_array = new long[max_date + 1];
    for (time_t i = 0; i <= max_date; i++) {
        count_array[i] = 0;
    }

    /// # Step 3
    void* current_pointer = news_container.head;
    while (current_pointer != nullptr) {
        News* current_news = news_container.get_news_at_memory(current_pointer);
        if (current_news == nullptr) {
            break;
        }
        count_array[current_news->publication_date]++;
        current_pointer = news_container.move_to_next(current_pointer);
    }

    /// # Step 4
    for (time_t i = 1; i <= max_date; i++) {
        count_array[i] += count_array[i - 1];
    }

    /// 5. Step 5
    auto* sorted_container = static_cast<NewsContainer*>(news_container.allocate_empty_copy());
    for (int j = news_container.size - 1; j >= 0; j--) {
        News* current_news = news_container.get_at_location(j);
        if (current_news == nullptr) {
            break;
        }
        int index = count_array[current_news->publication_date];
        sorted_container->put_at_location(*current_news, index - 1);
        count_array[current_news->publication_date]--;
    }
    delete[] count_array;
    news_container = *sorted_container;
}

inline void heap_sort(NewsContainer& news_container) {

}

inline void bucket_sort(NewsContainer& news_container) {

    /*
     step 1 - find min and max publication year
     step 2 - create new bucket
     step 3 - distribute articles into the correct year bucket
     step 4 - sort each bucket using insertion sort (by full publication_date)
     step 5 - merged sorted bucket into 'news_container'
     step 6 - delete the bucket
     */
    if (news_container.size == 0) return;  // Edge case: empty container

    // Step 1: Find min and max publication year
    int min_year = INT_MAX, max_year = INT_MIN;
    for (int i = 0; i < news_container.size; i++) {
        News* news = news_container.get_at_location(i);
        if (news) {
            int year = news->getYear();
            min_year = std::min(min_year, year);
            max_year = std::max(max_year, year);
        }
    }

    int bucket_count = max_year - min_year + 1;

    // step 2 - Create buckets manually using raw arrays
    int* bucket_sizes = new int[bucket_count]();  // Track number of elements in each bucket
    const int MAX_BUCKET_SIZE = 20000;  // Adjust based on dataset
    News** buckets = new News*[bucket_count];

    for (int i = 0; i < bucket_count; i++) {
        buckets[i] = new News[MAX_BUCKET_SIZE];  // Allocate array for each bucket
    }

    // Step 3: Distribute articles into the correct bucket
    for (int i = 0; i < news_container.size; i++) {
        News* news = news_container.get_at_location(i);
        if (news) {
            int year = news->getYear();
            int index = year - min_year;

            if (bucket_sizes[index] >= MAX_BUCKET_SIZE) {
                std::cerr << "Bucket overflow for year " << year << "!" << std::endl;
                continue;
            }

            buckets[index][bucket_sizes[index]] = *news;  // Store news in bucket
            bucket_sizes[index]++;
        }
    }

    // Step 4: Sort each bucket using Insertion Sort (by full `publication_date`)
    for (int i = 0; i < bucket_count; i++) {
        int size = bucket_sizes[i];
        for (int j = 1; j < size; j++) {
            News key = buckets[i][j];
            int k = j - 1;

            // Sort by full `publication_date`
            while (k >= 0 && buckets[i][k].publication_date > key.publication_date) {
                buckets[i][k + 1] = buckets[i][k];
                k--;
            }
            buckets[i][k + 1] = key;
        }
    }

    // Step 5: Merge sorted buckets back into `news_container`
    int index = 0;
    for (int i = 0; i < bucket_count; i++) {
        for (int j = 0; j < bucket_sizes[i]; j++) {
            news_container.insert_at_location(buckets[i][j], index++);
        }
    }

    // Step 6: Free allocated memory
    for (int i = 0; i < bucket_count; i++) {
        delete[] buckets[i];
    }
    delete[] buckets;
}

