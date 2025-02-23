#include <iostream>

#include "algorithms/sort.hpp"
#include "container/array.hpp"
#include "ctime"
#include <chrono>

#include "algorithms/search.hpp"

using namespace std;

void sort_with_bubble_sort(CRITERIA criteria) {
    NewsArray news_container = NewsArray();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);
    std::cout << "Starting Bubble Sort" << endl;
    auto now = std::chrono::system_clock::now();
    bubble_sort(news_container, criteria);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    news_container.display();
    std::cout << "Bubble Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

void sort_with_selection_sort(CRITERIA criteria) {
    NewsArray news_container = NewsArray();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);
    std::cout << "Starting Selection Sort" << endl;
    auto now = std::chrono::system_clock::now();
    selection_sort(news_container, criteria);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    news_container.display();
    std::cout << "Selection Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

void sort_with_quick_sort(CRITERIA criteria) {
    NewsArray news_container = NewsArray();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);
    std::cout << "Starting Quick Sort" << endl;
    auto now = std::chrono::system_clock::now();
    quick_sort(news_container, criteria);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    news_container.display();
    std::cout << "Quick Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

void sort_with_counting_sort(CRITERIA criteria) {
    NewsArray news_container = NewsArray();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);
    std::cout << "Starting Counting Sort" << endl;
    auto now = std::chrono::system_clock::now();
    counting_sort(news_container, criteria);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    news_container.display();
    std::cout << "Counting Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

void sort_with_merge_sort(CRITERIA criteria) {
    NewsArray news_container = NewsArray();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);
    std::cout << "Starting Merge Sort" << endl;
    auto now = std::chrono::system_clock::now();
    merge_sort(news_container, criteria);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    news_container.display();
    std::cout << "Merge Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

void sort_with_insertion_sort(CRITERIA criteria) {
    NewsArray news_container = NewsArray();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);
    std::cout << "Starting Insertion Sort" << endl;
    auto now = std::chrono::system_clock::now();
    insertion_sort(news_container, criteria);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    news_container.display();
    std::cout << "Insertion Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

void sort_with_bucket_sort(CRITERIA criteria) {
    NewsArray news_container = NewsArray();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);
    std::cout << "Starting Bucket Sort" << std::endl;

    auto now = std::chrono::system_clock::now();
    // Choose the criteria: here we're sorting by publication_date.
    bucket_sort(news_container, criteria);
    auto end_time = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end_time - now;
    news_container.display();
    std::cout << "Bucket Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

void sort_with_heap_sort(CRITERIA criteria) {
    NewsArray news_container;
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);
    std::cout << "Starting Heap Sort" << std::endl;

    auto now = std::chrono::system_clock::now();
    // Choose the criteria: here we're sorting by publication_date.
    heap_sort(news_container, criteria);
    auto end_time = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end_time - now;
    news_container.display();
    std::cout << "Heap Sort took: " << elapsed_seconds.count() << "s" << std::endl;
}

void quick_sort_and_two_pointer_search() {
    NewsArray news_container = NewsArray();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);
    std::cout << "Starting Quick Sort" << std::endl;
    quick_sort(news_container, CRITERIA::PUBLICATION_DATE);
    std::cout << "Starting Two Pointer Search" << std::endl;

    auto now = std::chrono::system_clock::now();
    news_container = *dynamic_cast<NewsArray*>(two_pointer_search(&news_container, SEARCH_CRITERIA::SEARCH_PUBLICATION_YEAR, "2018"));
    auto end_time = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end_time - now;
    news_container.display();
    std::cout << "Two Pointer Search took: " << elapsed_seconds.count() << "s" << std::endl;

}



void report_fake_political_news_in_each_month_in_2016() {
    NewsArray news_container = NewsArray();
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);

    auto now = std::chrono::system_clock::now();

    std::cout << "Getting all news in 2016..." << std::endl;
    merge_sort(news_container, CRITERIA::PUBLICATION_DATE);
    NewsArray news_2016_array = *dynamic_cast<NewsArray*>(two_pointer_search(&news_container, SEARCH_CRITERIA::SEARCH_PUBLICATION_YEAR, "2016"));

    std::cout << "Getting All Political News in 2016..." << std::endl;
    merge_sort(news_2016_array, CRITERIA::GENRE);
    news_2016_array.write_to_file("merge_sort_2016.txt");
    NewsArray news_2016_political_array = *dynamic_cast<NewsArray*>(two_pointer_search(&news_2016_array, SEARCH_CRITERIA::SEARCH_PUBLICATION_GENRE, "POLITICS"));

    std::cout << "Getting All Fake Political News in 2016..." << std::endl;
    counting_sort(news_2016_political_array, CRITERIA::IS_TRUE_NEWS);
    NewsArray fake_2016_political_news_container = *dynamic_cast<NewsArray*>(two_pointer_search(&news_2016_political_array, SEARCH_CRITERIA::SEARCH_TRUE_OR_FALSE_NEWS, "false"));

    std::cout << "Reloading 2016 Political News array" << std::endl;
    merge_sort(news_2016_political_array, PUBLICATION_DATE);

    auto* percentage_per_month = new int[12];
    for (int i = 0; i < 12; i++) {
        NewsArray total_news_in_month = *dynamic_cast<NewsArray*>(two_pointer_search(&news_2016_political_array, SEARCH_CRITERIA::SEARCH_PUBLICATION_MONTH, to_string(i + 1)));
        NewsArray fake_news_in_month = *dynamic_cast<NewsArray*>(two_pointer_search(&fake_2016_political_news_container, SEARCH_CRITERIA::SEARCH_PUBLICATION_MONTH, to_string(i + 1)));
        percentage_per_month[i] = (fake_news_in_month.size / (double)total_news_in_month.size) * 100;
    }

    std::cout << "Percentage of Fake Political News in 2016" << std::endl << std::endl;
    std::cout << "January     |" << std::setfill('*') << std::setw(percentage_per_month[0]) << " " << percentage_per_month[0] << "%" << std::endl;
    std::cout << "February    |" << std::setfill('*') << std::setw(percentage_per_month[1]) << " " << percentage_per_month[1] << "%" << std::endl;
    std::cout << "March       |" << std::setfill('*') << std::setw(percentage_per_month[2]) << " " << percentage_per_month[2] << "%" << std::endl;
    std::cout << "April       |" << std::setfill('*') << std::setw(percentage_per_month[3]) << " " << percentage_per_month[3] << "%" << std::endl;
    std::cout << "May         |" << std::setfill('*') << std::setw(percentage_per_month[4]) << " " << percentage_per_month[4] << "%" << std::endl;
    std::cout << "June        |" << std::setfill('*') << std::setw(percentage_per_month[5]) << " " << percentage_per_month[5] << "%" << std::endl;
    std::cout << "July        |" << std::setfill('*') << std::setw(percentage_per_month[6]) << " " << percentage_per_month[6] << "%" << std::endl;
    std::cout << "August      |" << std::setfill('*') << std::setw(percentage_per_month[7]) << " " << percentage_per_month[7] << "%" << std::endl;
    std::cout << "September   |" << std::setfill('*') << std::setw(percentage_per_month[8]) << " " << percentage_per_month[8] << "%" << std::endl;
    std::cout << "October     |" << std::setfill('*') << std::setw(percentage_per_month[9]) << " " << percentage_per_month[9] << "%" << std::endl;
    std::cout << "November    |" << std::setfill('*') << std::setw(percentage_per_month[10]) << " " << percentage_per_month[10] << "%" << std::endl;
    std::cout << "December    |" << std::setfill('*') << std::setw(percentage_per_month[11]) << " " << percentage_per_month[11] << "%" << std::endl;


    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - now;
    //fake_2016_news_container.display();
    std::cout << "The entire process took: " << elapsed_seconds.count() << "s" << std::endl;
}


void report_fake_political_news_in_each_month_in_2016_binary() {
    NewsArray news_container;
    std::cout << "Loading from file..." << std::endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);
    auto start_time = std::chrono::system_clock::now();
    std::cout << "Getting all news in 2016..." << std::endl;

    // Step 1: Sort by publication date.
    merge_sort(news_container, CRITERIA::PUBLICATION_DATE);
    // Filter news from 2016 using binary search.
    NewsArray news_2016_array = *dynamic_cast<NewsArray*>(binary_search(&news_container, SEARCH_PUBLICATION_YEAR, "2016"));

    std::cout << "Getting All Political News in 2016..." << std::endl;
    // Step 2: Sort by genre and filter political news.
    merge_sort(news_2016_array, CRITERIA::GENRE);
    NewsArray news_2016_political_array = *dynamic_cast<NewsArray*>(binary_search(&news_2016_array, SEARCH_PUBLICATION_GENRE, "POLITICS"));

    std::cout << "Getting All Fake Political News in 2016..." << std::endl;
    // Step 3: Sort by truth value and filter fake news.
    counting_sort(news_2016_political_array, CRITERIA::IS_TRUE_NEWS);
    NewsArray fake_2016_political_news_container = *dynamic_cast<NewsArray*>(binary_search(&news_2016_political_array, SEARCH_TRUE_OR_FALSE_NEWS, "false"));

    std::cout << "Reloading 2016 Political News array" << std::endl;
    // Step 4: Ensure the container is sorted by month
    merge_sort(news_2016_political_array, CRITERIA::PUBLICATION_DATE);
    
    int percentage_per_month[12] = {0};
    for (int i = 0; i < 12; i++) {
        std::string month = std::to_string(i + 1);
        NewsArray total_news_in_month = *dynamic_cast<NewsArray*>(binary_search(&news_2016_political_array, SEARCH_PUBLICATION_MONTH, month));
        NewsArray fake_news_in_month = *dynamic_cast<NewsArray*>(binary_search(&fake_2016_political_news_container, SEARCH_PUBLICATION_MONTH, month));
        if (total_news_in_month.size > 0) {
            percentage_per_month[i] = (fake_news_in_month.size / (double)total_news_in_month.size) * 100;
        } else {
            percentage_per_month[i] = 0;
        }
    }

    // Display the monthly percentages.
    std::cout << "Percentage of Fake Political News in 2016:" << std::endl;
    const char* months[12] = {"January", "February", "March", "April", "May", "June",
                              "July", "August", "September", "October", "November", "December"};
    for (int i = 0; i < 12; i++) {
        std::cout << months[i] << " | " << std::setfill('*') << std::setw(percentage_per_month[i])
                  << " " << percentage_per_month[i] << "%" << std::endl;
    }
    auto end_time = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end_time - start_time;
    std::cout << "The entire process took: " << elapsed_seconds.count() << "s" << std::endl;

}

void report_fake_political_news_in_each_month_in_2016_jump() {
    NewsArray news_container = NewsArray();
    cout << "Loading from file..." << endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);

    auto now = chrono::system_clock::now();

    cout << "Filtering all news in 2016 using Jump Search..." << endl;
    merge_sort(news_container, CRITERIA::PUBLICATION_DATE);
    NewsArray news_2016_array = *dynamic_cast<NewsArray*>(jump_search(&news_container, SEARCH_PUBLICATION_YEAR, "2016"));

    cout << "Filtering Political News in 2016 using Jump Search..." << endl;
    merge_sort(news_2016_array, CRITERIA::GENRE);
    NewsArray news_2016_political_array = *dynamic_cast<NewsArray*>(jump_search(&news_2016_array, SEARCH_PUBLICATION_GENRE, "POLITICS"));

    cout << "Filtering Fake News in 2016 Political News using Jump Search..." << endl;
    counting_sort(news_2016_political_array, CRITERIA::IS_TRUE_NEWS);
    NewsArray fake_2016_political_news_container = *dynamic_cast<NewsArray*>(jump_search(&news_2016_political_array, SEARCH_TRUE_OR_FALSE_NEWS, "false"));

    cout << "Reloading 2016 Political News array sorted by date..." << endl;
    merge_sort(news_2016_political_array, CRITERIA::PUBLICATION_DATE);

    int percentage_per_month[12] = {0};
    for (int i = 0; i < 12; i++) {
        string month = to_string(i + 1);
        NewsArray total_news_in_month = *dynamic_cast<NewsArray*>(jump_search(&news_2016_political_array, SEARCH_PUBLICATION_MONTH, month));
        NewsArray fake_news_in_month = *dynamic_cast<NewsArray*>(jump_search(&fake_2016_political_news_container, SEARCH_PUBLICATION_MONTH, month));
        if (total_news_in_month.size > 0)
            percentage_per_month[i] = (fake_news_in_month.size / (double)total_news_in_month.size) * 100;
        else
            percentage_per_month[i] = 0;
    }

    // Use a loop to display the month percentages.
    const char* months[12] = {"January", "February", "March", "April", "May", "June",
                              "July", "August", "September", "October", "November", "December"};
    cout << "Percentage of Fake Political News in 2016 (Jump Search):" << endl << endl;
    for (int i = 0; i < 12; i++) {
        cout << months[i] << " | "
             << setfill('*') << setw(percentage_per_month[i]) << " "
             << percentage_per_month[i] << "%" << endl;
    }

    auto end_time = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end_time - now;
    cout << "Jump Search process took: " << elapsed_seconds.count() << "s" << endl;
}

void report_fake_political_news_in_each_month_in_2016_exponential() {
    NewsArray news_container = NewsArray();
    cout << "Loading from file..." << endl;
    news_container.load_from_file("../data/cleaned/fake.csv", false);
    news_container.load_from_file("../data/cleaned/true.csv", true);

    auto now = chrono::system_clock::now();

    cout << "Filtering all news in 2016 using Exponential Search..." << endl;
    // Ensure the container is sorted by publication date.
    merge_sort(news_container, CRITERIA::PUBLICATION_DATE);
    NewsArray news_2016_array = *dynamic_cast<NewsArray*>(exponential_search(&news_container, SEARCH_PUBLICATION_YEAR, "2016"));

    cout << "Filtering Political News in 2016 using Exponential Search..." << endl;
    merge_sort(news_2016_array, CRITERIA::GENRE);
    NewsArray news_2016_political_array = *dynamic_cast<NewsArray*>(exponential_search(&news_2016_array, SEARCH_PUBLICATION_GENRE, "POLITICS"));

    cout << "Filtering Fake News in 2016 Political News using Exponential Search..." << endl;
    counting_sort(news_2016_political_array, CRITERIA::IS_TRUE_NEWS);
    NewsArray fake_2016_political_news_container = *dynamic_cast<NewsArray*>(exponential_search(&news_2016_political_array, SEARCH_TRUE_OR_FALSE_NEWS, "false"));

    cout << "Reloading 2016 Political News array sorted by date..." << endl;
    merge_sort(news_2016_political_array, CRITERIA::PUBLICATION_DATE);

    int percentage_per_month[12] = {0};
    for (int i = 0; i < 12; i++) {
        string month = to_string(i + 1);
        NewsArray total_news_in_month = *dynamic_cast<NewsArray*>(exponential_search(&news_2016_political_array, SEARCH_PUBLICATION_MONTH, month));
        NewsArray fake_news_in_month = *dynamic_cast<NewsArray*>(exponential_search(&fake_2016_political_news_container, SEARCH_PUBLICATION_MONTH, month));
        if (total_news_in_month.size > 0)
            percentage_per_month[i] = (fake_news_in_month.size / (double)total_news_in_month.size) * 100;
        else
            percentage_per_month[i] = 0;
    }

    const char* months[12] = {"January", "February", "March", "April", "May", "June",
                              "July", "August", "September", "October", "November", "December"};
    cout << "Percentage of Fake Political News in 2016 (Exponential Search):" << endl << endl;
    for (int i = 0; i < 12; i++) {
        cout << months[i] << " | "
             << setfill('*') << setw(percentage_per_month[i]) << " "
             << percentage_per_month[i] << "%" << endl;
    }

    auto end_time = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end_time - now;
    cout << "Exponential Search process took: " << elapsed_seconds.count() << "s" << endl;
}

int main() {

    //sort_with_bubble_sort(CRITERIA::PUBLICATION_MONTH);
    //sort_with_selection_sort();

    //sort_with_quick_sort(CRITERIA::IS_TRUE_NEWS);
    //sort_with_counting_sort(CRITERIA::GENRE);

    //sort_with_merge_sort(CRITERIA::IS_TRUE_NEWS);
    //sort_with_insertion_sort(CRITERIA::IS_TRUE_NEWS);

    //sort_with_bucket_sort(CRITERIA::PUBLICATION_DATE);
    //sort_with_heap_sort(CRITERIA::PUBLICATION_DATE);

    //report_fake_political_news_in_each_month_in_2016();
    //report_fake_political_news_in_each_month_in_2016_binary();
    //report_fake_political_news_in_each_month_in_2016_jump();
    //report_fake_political_news_in_each_month_in_2016_exponential();

    std::cout << "Hello from Array List Implementation File" << std::endl;
}