/// <summary>
/// 1. Bubble Sort (Livi)
/// 2. Selection Sort
/// 3. Insertion Sort (Abbirami)
/// 4. Merge Sort (Abbirami)
/// 5. Quick Sort (Htet Aung Hlaing)
/// 6. Radix Sort
/// 7. Counting Sort
/// 8. Bucket Sort
/// </summary>

#pragma once

#include "container/news_container.hpp"

void bubble_sort(NewsContainer& news_container) {

}

void selection_sort(NewsContainer& news_container) {

}

void insertion_sort(NewsContainer& news_container) {

}

void merge_sort(NewsContainer& news_container) {

}

void quick_sort(NewsContainer& news_container) {

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
        /// # Step 3
        while (true) {
            News* news_at_memory = news_container.get_news_at_memory(left_pointer);
            if (news_at_memory == nullptr) {
                break;
            }
            if (news_at_memory->publication_date > pivot_date) {
                break;
            }

            left_pointer = news_container.move_to_next(left_pointer);
            if (left_pointer == nullptr) {
                break;
            }
            left_pointer_index++;
        }

        while (true) {
            News* news_at_memory = news_container.get_news_at_memory(right_pointer);
            if (news_at_memory == nullptr) {
                break;
            }
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

void radix_sort(NewsContainer& news_container) {

}

void counting_sort(NewsContainer& news_container) {

}

void bucket_sort(NewsContainer& news_container) {

}
