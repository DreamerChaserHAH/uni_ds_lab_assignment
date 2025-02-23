/// <summary>
/// 1. Bubble Sort (Livi)
/// 2. Selection Sort (Livi)
/// 3. Insertion Sort (Abbirami)
/// 4. Merge Sort (Abbirami)
/// 5. Quick Sort (Htet Aung Hlaing)
/// 6. Heap Sort (Kaung)
/// 7. Counting Sort (Htet Aung Hlaing)
/// 8. Bucket Sort (Kaung)
/// </summary>

#pragma once

#include "../../include/container/news_container.hpp"

inline void bubble_sort(NewsContainer& news_container, CRITERIA criteria) {
    int n = news_container.size;
    bool swapped;

    // Step 1: Loop through the entire list multiple times
    for (int i = 0; i < n - 1; i++) {
        swapped = false;

        // Step 2: Compare adjacent elements and swap if needed
        for (int j = 0; j < n - i - 1; j++) {
            News* news1 = news_container.get_at_location(j);
            News* news2 = news_container.get_at_location(j + 1);

            if (news1 && news2 && news1->is_greater_than(*news2, criteria, &news_container)) {
                news_container.swap_news(j, j + 1);
                swapped = true;
            }
        }

        // Step 3: If no swaps were made in this pass, the list is sorted
        if (!swapped) {
            break;
        }
    }

}

inline void selection_sort(NewsContainer& news_container, CRITERIA criteria) {
    int n = news_container.size;  

    // Step 1: Iterate over each element in the container
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;  // Assume the first unsorted element is the smallest

        // Step 2: Find the minimum element in the remaining unsorted array
        for (int j = i + 1; j < n; j++) {
            News* current_news = news_container.get_at_location(j);
            News* min_news = news_container.get_at_location(min_index);
            
            if (current_news && min_news) {
                // Compare publication dates to find the earliest one
                if (current_news->is_lower_than(*min_news, criteria, &news_container)) {
                    min_index = j;  // Update index of new minimum element
                }
            }
        }

        // Step 3: Swap the found minimum element with the first element of the unsorted part
        if (min_index != i) {
            news_container.swap_news(i, min_index);
        }
    }
}

inline void insertion_sort(NewsContainer& news_container, CRITERIA criteria) {
    /// Here's the insertion sort algorithm implementation working with the NewsContainer (both linkedlist and array)
    /// 1. Start from the second element and compare it with the previous element
    /// 2. If the previous element is greater than the current element, swap the two elements
    /// 3. Continue this process until the current element is greater than the previous element
    /// 4. Repeat the process for all element

    for (int i = 1; i < news_container.size; i++) {
        News* current_news_address = news_container.get_at_location(i);
        if (current_news_address == nullptr) {
            break;
        }
        News current_news = *current_news_address;
        int j = i - 1;
        void* compare_news_node = news_container.get_node_at_location(j);
        if (compare_news_node == nullptr) {
            break;
        }
        while (j >= 0 && news_container.get_news_at_memory(compare_news_node)->is_greater_than(current_news, criteria, &news_container)) {
            news_container.swap_news(j, j + 1);
            compare_news_node = news_container.move_to_prev(compare_news_node);
            if (compare_news_node == nullptr) {
                break;
            }
            j--;
        }
        std::cout << "Insertion Sort Element: " << i << " Inserted At: " << j << std::endl;
    }
}

inline void merge_sort(NewsContainer& news_container, CRITERIA criteria) {
    if (news_container.size <= 1) {
        return;
    }
    // splitting the list at the midpoint
    int size = news_container.size;
    int half_point = size / 2;
    if (news_container.size % 2 == 1) {
        half_point += 1;
    }
    NewsContainer* left_container = nullptr;
    NewsContainer* right_container = nullptr;

    if (size == 2) {
        left_container = static_cast<NewsContainer *>(news_container.split_left(1));
        right_container = static_cast<NewsContainer *>(news_container.split_right(0));
    }else {
        left_container = static_cast<NewsContainer*>(news_container.split_left(news_container.size % 2 == 1 ? half_point : half_point + 1));
        right_container = static_cast<NewsContainer*>(news_container.split_right(news_container.size % 2 == 1? half_point - 1: half_point));
    }

    if (left_container == nullptr || right_container == nullptr) {
        return;
    }

    int left_size = left_container->size;
    int right_size = right_container->size;

    //recursive sort the halves
    merge_sort(*left_container, criteria);
    merge_sort(*right_container, criteria);

    // Merge the two sides
    int number_of_elements = left_container->size + right_container->size;
    auto* final_container = static_cast<NewsContainer *>(news_container.allocate_empty_copy());
    int left_index = 0;
    int right_index = 0;
    for (int i = 0; i < number_of_elements; i++) {
        if (left_index > left_container->size - 1) {
            final_container->put_at_location(*right_container->get_at_location(right_index), i);
            right_index++;
            continue;
        }
        if (right_index > right_container->size - 1) {
            final_container->put_at_location(*left_container->get_at_location(left_index), i);
            left_index++;
            continue;
        }

        News* left_news = left_container->get_at_location(left_index);
        News* right_news = right_container->get_at_location(right_index);

        if (left_news->is_greater_than(*right_news, criteria, &news_container)) {
            final_container->put_at_location(*right_news, i);
            right_index++;
            continue;
        }
        final_container->put_at_location(*left_news, i);
        left_index++;
    }
    //overwrite original list with this sorted list
    news_container.overwrite_at_position(final_container, 0);
}

inline void quick_sort(NewsContainer& news_container, CRITERIA criteria) {

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

    if (news_container.size == 0) {
        return;
    }
    /// # Step 1
    News* pivot_news_pointer = news_container.get_news_at_memory(tail_pointer);
    if (pivot_news_pointer == nullptr) {
        return;
    }
    long pivot_value = news_container.get_criteria_value(pivot_news_pointer, criteria);
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

            if (news_container.get_criteria_value(news_at_memory, criteria) > pivot_value) {
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
            if (news_container.get_criteria_value(news_at_memory, criteria) < pivot_value) {
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
        quick_sort(*left_container, criteria);
        quick_sort(*right_container, criteria);
    }

}

inline void counting_sort(NewsContainer& news_container, CRITERIA criteria) {
    /// 1. Understand which element has the highest value
    /// 2. Create an temporary array with max + 1 elements
    /// 3. Store the occurence of each unique input
    /// 4. Cumlative sum each element and put into each index
    /// 5. Generate the final sorted container

    void *tail_pointer = news_container.get_tail();
    /// # Step 1
    long max_value = 0;
    if (criteria == CRITERIA::PUBLICATION_DATE) {
        max_value = news_container.get_max_date();
    }else if (criteria == CRITERIA::IS_TRUE_NEWS) {
        max_value = 1;
    }else {
        max_value = 10000;
    }

    /// # Step 2
    long* count_array = new long[max_value + 1];
    for (time_t i = 0; i <= max_value; i++) {
        count_array[i] = 0;
    }

    /// # Step 3
    void* current_pointer = news_container.head;
    while (current_pointer != nullptr) {
        News* current_news = news_container.get_news_at_memory(current_pointer);
        if (current_news == nullptr) {
            break;
        }
        count_array[news_container.get_criteria_value(current_news, criteria)]++;
        current_pointer = news_container.move_to_next(current_pointer);
    }

    /// # Step 4
    for (time_t i = 1; i <= max_value; i++) {
        count_array[i] += count_array[i - 1];
    }

    /// 5. Step 5
    auto* sorted_container = static_cast<NewsContainer*>(news_container.allocate_empty_copy());
    for (int j = news_container.size - 1; j >= 0; j--) {
        News* current_news = news_container.get_at_location(j);
        if (current_news == nullptr) {
            break;
        }
        int index = count_array[news_container.get_criteria_value(current_news, criteria)];
        sorted_container->put_at_location(*current_news, index - 1);
        count_array[news_container.get_criteria_value(current_news, criteria)]--;
    }
    delete[] count_array;
    news_container = *sorted_container;
}

void heapify(NewsContainer& news_container, int i, int n, CRITERIA criteria);

// Builds a max heap and then performs heap sort.
inline void heap_sort(NewsContainer& news_container, CRITERIA criteria) {
    int n = news_container.size;

    // 1. Build a max heap by calling 'heapify' on all non-leaf nodes.
    //    We start from the last non-leaf node: (n/2 - 1).
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(news_container, i, n, criteria);
    }

    // 2. Extract elements from the heap one by one by:
    //    - Swapping the first (largest) element with the last element in the current heap.
    //    - "Removing" the last element from the heap by decreasing the considered size.
    //    - Re-heapifying the reduced heap to restore the max-heap property.
    for (int i = n - 1; i > 0; i--) {
        // Move the root (largest) to the end of the array.
        news_container.swap_news(0, i);

        // Re-heapify the remaining (now smaller) heap to maintain the max-heap structure.
        heapify(news_container, 0, i, criteria);
    }
}

// Maintains the max-heap property by moving a potentially out-of-place element down the tree.
inline void heapify(NewsContainer& news_container, int i, int n, CRITERIA criteria) {
    // 'i' is the index of the node that may violate the max-heap property.
    int largest = i;           // Assume the current node 'i' is largest.
    int left = 2 * i + 1;      // Left child index in the array-based tree.
    int right = 2 * i + 2;     // Right child index in the array-based tree.

    //  to safely get the comparison value, or INT_MIN if the pointer is null.

    // Pointers to the current node, left child, and right child (if they exist).
    News* largestNews = news_container.get_at_location(largest);
    News* leftNews   = (left < n) ? news_container.get_at_location(left) : nullptr;
    News* rightNews  = (right < n) ? news_container.get_at_location(right) : nullptr;

    // 1. Compare the left child with the current 'largest' node.
    if (leftNews) {
        // If the left child's value is greater than or equal to the largest so far, update 'largest'.
        if (leftNews->is_equal_or_greater_than(*largestNews, criteria, &news_container)) {
            largest = left;
            largestNews = leftNews;
        }
    }

    // 2. Compare the right child with the current 'largest' node.
    if (rightNews) {
        // If the right child's value is greater than or equal to the largest so far, update 'largest'.
        if (rightNews->is_equal_or_greater_than(*largestNews, criteria, &news_container)) {
            largest = right;
            largestNews = rightNews;
        }
    }
    // 3. If the 'largest' index has changed, swap the current node with the new largest
    //    and then recursively heapify the affected subtree.
    if (largest != i) {
        news_container.swap_news(i, largest);
        heapify(news_container, largest, n, criteria);
    }
}



    /*
    This function performs a bucket sort based on the year of each news article,
    then sorts each year's bucket by month/day. The steps are:

    1. Find the minimum and maximum year values in the container.
    2. Create dynamic buckets, one for each year between min and max.
    3. Distribute articles into their corresponding year bucket.
    4. Sort each bucket internally by month/day (publication_date).
    5. Merge the sorted buckets back into the original container.
    6. Free the allocated memory for buckets.
*/
inline void bucket_sort(NewsContainer& news_container, CRITERIA criteria) {
    // If the container is empty, there's nothing to sort.
    if (news_container.size == 0) return;

    // 1. Find the min and max year in the dataset.
    long min_value = INT_MAX, max_value = INT_MIN;
    for (int i = 0; i < news_container.size; i++) {
        News* news = news_container.get_at_location(i);
        if (news) {
            // We'll assume 'criteria' is PUBLICATION_YEAR.
            long value = news_container.get_criteria_value(news, criteria);  // Get just the year
            if (value < min_value) min_value = value;
            if (value > max_value) max_value = value;
        }
    }

    // The number of buckets is (max_year - min_year + 1).
    long bucket_count = max_value - min_value + 1;

    // 2. Create dynamic buckets. Each bucket is a dynamic array of News objects.
    //    We also keep track of each bucket's size and capacity for potential resizing.
    News** buckets = new News*[bucket_count];
    int* bucket_sizes = new int[bucket_count]();      // Initialize to zero
    int* bucket_capacities = new int[bucket_count](); // Initialize to zero

    // Initialize each bucket with a small default capacity (e.g., 10).
    for (int i = 0; i < bucket_count; i++) {
        bucket_capacities[i] = 10;
        buckets[i] = new News[bucket_capacities[i]];
    }

    // 3. Distribute each article into the appropriate bucket based on its year.
    //    The index of the bucket is (article_year - min_value).
    for (int i = 0; i < news_container.size; i++) {
        News* news = news_container.get_at_location(i);
        if (news) {
            int year_index = news->get_year() - min_value;

            // If the bucket is full, resize it by doubling its capacity.
            if (bucket_sizes[year_index] >= bucket_capacities[year_index]) {
                int new_capacity = bucket_capacities[year_index] * 2;
                News* new_bucket = new News[new_capacity];

                // Copy existing items into the newly allocated bucket.
                for (int j = 0; j < bucket_sizes[year_index]; j++) {
                    new_bucket[j] = buckets[year_index][j];
                }

                delete[] buckets[year_index];
                buckets[year_index] = new_bucket;
                bucket_capacities[year_index] = new_capacity;
            }

            // Insert the news article into its corresponding bucket.
            buckets[year_index][bucket_sizes[year_index]++] = *news;
        }
    }

    // 4. Sort each bucket internally by publication_date (month/day),
    //    using a simple insertion sort here.
    for (int i = 0; i < bucket_count; i++) {
        int size = bucket_sizes[i];

        for (int j = 1; j < size; j++) {
            News key = buckets[i][j];
            int k = j - 1;
            // Compare publication_date to order by month/day within the year.
            while (k >= 0 && buckets[i][k].publication_date > key.publication_date) {
                buckets[i][k + 1] = buckets[i][k];
                k--;
            }
            buckets[i][k + 1] = key;
        }
    }

    // 5. Merge the sorted buckets back into the original container,
    //    overwriting items in ascending order.
    int index = 0;
    for (int i = 0; i < bucket_count; i++) {
        for (int j = 0; j < bucket_sizes[i]; j++) {
            news_container.put_at_location(buckets[i][j], index++);
        }
    }

    // 6. Free all the dynamically allocated memory for the buckets.
    for (int i = 0; i < bucket_count; i++) {
        delete[] buckets[i];
    }
    delete[] buckets;
    delete[] bucket_sizes;
    delete[] bucket_capacities;
}



