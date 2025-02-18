cmake_minimum_required(VERSION 3.30)
project(Labwork)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

#add_executable(array_implementation src/array_implementation.cpp include/container/array.hpp include/algorithms/search.hpp include/algorithms/sort.hpp
#        include/container/news.hpp)
add_executable(linked_list_implementation src/linked_list_implementation.cpp include/container/linked_list.hpp include/algorithms/search.hpp include/algorithms/sort.hpp)
add_executable(cross_implementation src/cross_implementation.cpp include/container/array.hpp include/container/linked_list.hpp include/algorithms/search.hpp include/algorithms/sort.hpp)
add_executable(news_data_set_cleaner src/news_data_set_clean.cpp)

add_executable(tests-news-linked-list tests/news_linked_list_test.cpp)
#add_executable(tests-news-array tests/news_array_test.cpp)

add_executable(tests-linked-list-quick-sort tests/algorithms/linked_list/linked_list_quick_sort.cpp)
add_executable(tests-linked-list-bucket-sort tests/algorithms/linked_list/linked_list_bucket_sort.cpp)
add_executable(tests-linked-list-counting-sort tests/algorithms/linked_list/linked_list_counting_sort.cpp)

enable_testing()

add_test(news_linked_list_test tests-news-linked-list)
#add_test(news_array_test tests-news-array)
add_test(linked_list_quick_sort_test tests-linked-list-quick-sort)
add_test(linked_list_bucket_sort_test tests-linked-list-bucket-sort)
add_test(linked_list_counting_sort_test tests-linked-list-counting-sort)