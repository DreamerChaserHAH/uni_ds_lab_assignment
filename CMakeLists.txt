cmake_minimum_required(VERSION 3.29)
project(Labwork)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

# Main Executables
add_executable(linked_list_implementation src/linked_list_implementation.cpp)
add_executable(array_implementation src/array_implementation.cpp)
add_executable(cross_implementation src/cross_implementation.cpp include/container/array.hpp include/container/linked_list.hpp include/algorithms/search.hpp include/algorithms/sort.hpp)
add_executable(news_data_set_cleaner src/news_data_set_clean.cpp)

add_executable(tests-news-linked-list tests/news_linked_list_test.cpp)

# Livi's Implementations
add_executable(tests-linked-list-bubble-sort tests/algorithms/linked_list/linked_list_bubble_sort.cpp)
add_executable(tests-linked-list-selection-sort tests/algorithms/linked_list/linked_list_selection_sort.cpp)

# Htet Aung Hlaing's Implementation
add_executable(tests-linked-list-quick-sort tests/algorithms/linked_list/linked_list_quick_sort.cpp)
add_executable(tests-linked-list-counting-sort tests/algorithms/linked_list/linked_list_counting_sort.cpp)

# Htet Kaung Myat Oo's Implementation
add_executable(tests-linked-list-bucket-sort tests/algorithms/linked_list/linked_list_bucket_sort.cpp)
add_executable(tests-linked-list-heap-sort tests/algorithms/linked_list/linked_list_heap_sort.cpp)

# Abbirami's Implementation
add_executable(tests-linked-list-merge-sort tests/algorithms/linked_list/linked_list_merge_sort.cpp)
add_executable(tests-linked-list-insertion-sort tests/algorithms/linked_list/linked_list_insertion_sort.cpp)

# Array
# Livi's Implementations
add_executable(tests-array-bubble-sort tests/algorithms/array/array_bubble_sort.cpp)
add_executable(tests-array-selection-sort tests/algorithms/array/array_selection_sort.cpp)

# Htet Aung Hlaing's Implementation
add_executable(tests-array-quick-sort tests/algorithms/array/array_quick_sort.cpp)
add_executable(tests-array-counting-sort tests/algorithms/array/array_counting_sort.cpp)

# Htet Kaung Myat Oo's Implementation
add_executable(tests-array-bucket-sort tests/algorithms/array/array_bucket_sort.cpp)
add_executable(tests-array-heap-sort tests/algorithms/array/array_heap_sort.cpp)

# Abbirami's Implementation
add_executable(tests-array-merge-sort tests/algorithms/array/array_merge_sort.cpp)
add_executable(tests-array-insertion-sort tests/algorithms/array/array_insertion_sort.cpp)

enable_testing()

add_test(news_linked_list_test tests-news-linked-list)
#add_test(news_array_test tests-news-array)
add_test(linked_list_bubble_sort_test tests-linked-list-bubble-sort)
add_test(linked_list_selection_sort_test tests-linked-list-selection-sort)
add_test(linked_list_quick_sort_test tests-linked-list-quick-sort)
add_test(linked_list_bucket_sort_test tests-linked-list-bucket-sort)
add_test(linked_list_counting_sort_test tests-linked-list-counting-sort)
add_test(linked_list_heap_sort_test tests-linked-list-heap-sort)
add_test(linked_list_merge_sort_test tests-linked-list-merge-sort)
add_test(linked_list_insertion_sort_test tests-linked-list-insertion-sort)

add_test(array_bubble_sort_test tests-array-bubble-sort)
add_test(array_selection_sort_test tests-array-selection-sort)
add_test(array_quick_sort_test tests-array-quick-sort)
add_test(array_bucket_sort_test tests-array-bucket-sort)
add_test(array_counting_sort_test tests-array-counting-sort)
add_test(array_heap_sort_test tests-array-heap-sort)
add_test(array_merge_sort_test tests-array-merge-sort)
add_test(array_insertion_sort_test tests-array-insertion-sort)