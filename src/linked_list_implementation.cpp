#include "implementations/linked_list.hpp"

int main() {

    //sort_with_bubble_sort(CRITERIA::PUBLICATION_DATE);
    //sort_with_selection_sort(CRITERIA::PUBLICATION_DATE);

    linked_list_implementation::sort_with_quick_sort(CRITERIA::PUBLICATION_DATE);
    //sort_with_counting_sort(CRITERIA::PUBLICATION_DATE);

    //sort_with_merge_sort(CRITERIA::PUBLICATION_DATE);
    //sort_with_insertion_sort();

    //sort_with_bucket_sort(CRITERIA::PUBLICATION_DATE);
    //sort_with_heap_sort(CRITERIA::PUBLICATION_DATE);

    //report_fake_political_news_in_each_month_in_2016();
    //report_fake_political_news_in_each_month_in_2016_linear();
    //report_fake_political_news_in_each_month_in_2016_binary();
    //linked_list_implementation::report_fake_political_news_in_each_month_in_2016_exponential();

    std::cout << "Hello from Linked List Implementation File" << std::endl;
}