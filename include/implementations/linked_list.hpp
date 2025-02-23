//
// Created by Victor Mak on 23/02/2025.
//

#pragma once

#include <iostream>

#include "algorithms/sort.hpp"
#include "algorithms/search.hpp"
#include "container/linked_list.hpp"
#include "ctime"
#include <chrono>


namespace linked_list_implementation {
    void sort_with_bubble_sort(CRITERIA criteria) {
        NewsLinkedList news_container = NewsLinkedList();
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
        NewsLinkedList news_container = NewsLinkedList();
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
        NewsLinkedList news_container = NewsLinkedList();
        std::cout << "Loading from file..." << std::endl;
        news_container.load_from_file("../data/cleaned/fake.csv", false);
        news_container.load_from_file("../data/cleaned/true.csv", true);
        std::cout << "Starting Quick Sort" << endl;
        auto now = std::chrono::system_clock::now();
        quick_sort(news_container,criteria);
        auto end_time = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end_time - now;
        news_container.display();
        std::cout << "Quick Sort took: " << elapsed_seconds.count() << "s" << std::endl;
    }

    void sort_with_counting_sort(CRITERIA criteria) {
        NewsLinkedList news_container = NewsLinkedList();
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
        NewsLinkedList news_container = NewsLinkedList();
        std::cout << "Loading from file..." << std::endl;
        news_container.load_from_file("../data/cleaned/fake.csv", false);
        news_container.load_from_file("../data/cleaned/true.csv", true);
        std::cout << "Starting Merge Sort" << endl;
        auto now = std::chrono::system_clock::now();
        merge_sort(news_container,criteria);
        auto end_time = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end_time - now;
        news_container.display();
        std::cout << "Merge Sort took: " << elapsed_seconds.count() << "s" << std::endl;
    }

    void sort_with_insertion_sort(CRITERIA criteria) {
        NewsLinkedList news_container = NewsLinkedList();
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
        NewsLinkedList news_container = NewsLinkedList();
        std::cout << "Loading from file..." << std::endl;
        news_container.load_from_file("../data/cleaned/fake.csv", false);
        news_container.load_from_file("../data/cleaned/true.csv", true);
        std::cout << "Starting Bucket Sort" << endl;
        auto now = std::chrono::system_clock::now();
        bucket_sort(news_container,criteria);
        auto end_time = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end_time - now;
        news_container.display();
        std::cout << "Bucket Sort took: " << elapsed_seconds.count() << "s" << std::endl;
    }

    void sort_with_heap_sort(CRITERIA criteria) {
        NewsLinkedList news_container;
        std::cout << "Loading from file..." << std::endl;
        news_container.load_from_file("../data/cleaned/fake.csv", false);
        news_container.load_from_file("../data/cleaned/true.csv", true);
        std::cout << "Starting Heap Sort" << std::endl;

        auto now = std::chrono::system_clock::now();
        heap_sort(news_container, criteria);
        auto end_time = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end_time - now;
        news_container.display();
        std::cout << "Heap Sort took: " << elapsed_seconds.count() << "s" << std::endl;
    }

    void report_fake_political_news_in_each_month_in_2016() {
        auto* news_container = new NewsLinkedList();
        std::cout << "Loading from file..." << std::endl;
        news_container->load_from_file("../data/cleaned/fake.csv", false);
        news_container->load_from_file("../data/cleaned/true.csv", true);

        auto now = std::chrono::system_clock::now();

        std::cout << "Getting all news in 2016..." << std::endl;
        quick_sort(*news_container, CRITERIA::PUBLICATION_DATE);
        NewsLinkedList news_2016_array = *dynamic_cast<NewsLinkedList*>(two_pointer_search(news_container, SEARCH_CRITERIA::SEARCH_PUBLICATION_YEAR, "2016"));

        std::cout << "Getting All Political News in 2016..." << std::endl;
        merge_sort(news_2016_array, CRITERIA::GENRE);
        //news_2016_array.write_to_file("merge_sort_2016.txt");
        NewsLinkedList news_2016_political_array = *dynamic_cast<NewsLinkedList*>(two_pointer_search(&news_2016_array, SEARCH_CRITERIA::SEARCH_PUBLICATION_GENRE, "politics"));
        //news_2016_political_array.write_to_file("2016 politics news.txt");

        std::cout << "Getting All Fake Political News in 2016..." << std::endl;
        counting_sort(news_2016_political_array, CRITERIA::IS_TRUE_NEWS);
        NewsLinkedList fake_2016_political_news_container = *dynamic_cast<NewsLinkedList*>(two_pointer_search(&news_2016_political_array, SEARCH_CRITERIA::SEARCH_TRUE_OR_FALSE_NEWS, "false"));

        std::cout << "Reloading 2016 Political News array" << std::endl;
        merge_sort(news_2016_political_array, PUBLICATION_DATE);
        merge_sort(fake_2016_political_news_container, PUBLICATION_DATE);

        auto* percentage_per_month = new int[12];
        for (int i = 0; i < 12; i++) {
            NewsLinkedList total_news_in_month = *dynamic_cast<NewsLinkedList*>(two_pointer_search(&news_2016_political_array, SEARCH_CRITERIA::SEARCH_PUBLICATION_MONTH, to_string(i + 1)));
            NewsLinkedList fake_news_in_month = *dynamic_cast<NewsLinkedList*>(two_pointer_search(&fake_2016_political_news_container, SEARCH_CRITERIA::SEARCH_PUBLICATION_MONTH, to_string(i + 1)));
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

    void report_fake_political_news_in_each_month_in_2016_linear() {
        auto* news_container = new NewsLinkedList();
        std::cout << "Loading from file..." << std::endl;
        news_container->load_from_file("../data/cleaned/fake.csv", false);
        news_container->load_from_file("../data/cleaned/true.csv", true);

        auto now = std::chrono::system_clock::now();

        std::cout << "Getting all news in 2016..." << std::endl;
        NewsLinkedList news_2016_array = *dynamic_cast<NewsLinkedList*>(linear_search(news_container, SEARCH_CRITERIA::SEARCH_PUBLICATION_YEAR, "2016"));

        std::cout << "Getting All Political News in 2016..." << std::endl;
        //news_2016_array.write_to_file("merge_sort_2016.txt");
        NewsLinkedList news_2016_political_array = *dynamic_cast<NewsLinkedList*>(linear_search(&news_2016_array, SEARCH_CRITERIA::SEARCH_PUBLICATION_GENRE, "politics"));
        //news_2016_political_array.write_to_file("2016 politics news.txt");

        std::cout << "Getting All Fake Political News in 2016..." << std::endl;
        NewsLinkedList fake_2016_political_news_container = *dynamic_cast<NewsLinkedList*>(linear_search(&news_2016_political_array, SEARCH_CRITERIA::SEARCH_TRUE_OR_FALSE_NEWS, "false"));

        std::cout << "Reloading 2016 Political News array" << std::endl;

        auto* percentage_per_month = new int[12];
        for (int i = 0; i < 12; i++) {
            NewsLinkedList total_news_in_month = *dynamic_cast<NewsLinkedList*>(linear_search(&news_2016_political_array, SEARCH_CRITERIA::SEARCH_PUBLICATION_MONTH, to_string(i + 1)));
            NewsLinkedList fake_news_in_month = *dynamic_cast<NewsLinkedList*>(linear_search(&fake_2016_political_news_container, SEARCH_CRITERIA::SEARCH_PUBLICATION_MONTH, to_string(i + 1)));
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
        auto* news_container = new NewsLinkedList();
        std::cout << "Loading from file..." << std::endl;
        news_container->load_from_file("../data/cleaned/fake.csv", false);
        news_container->load_from_file("../data/cleaned/true.csv", true);

        auto now = std::chrono::system_clock::now();

        std::cout << "Getting all news in 2016..." << std::endl;
        quick_sort(*news_container, CRITERIA::PUBLICATION_DATE);
        NewsLinkedList news_2016_array = *dynamic_cast<NewsLinkedList*>(binary_search(news_container, SEARCH_CRITERIA::SEARCH_PUBLICATION_YEAR, "2016"));

        std::cout << "Getting All Political News in 2016..." << std::endl;
        merge_sort(news_2016_array, CRITERIA::GENRE);
        //news_2016_array.write_to_file("merge_sort_2016.txt");
        NewsLinkedList news_2016_political_array = *dynamic_cast<NewsLinkedList*>(binary_search(&news_2016_array, SEARCH_CRITERIA::SEARCH_PUBLICATION_GENRE, "politics"));
        //news_2016_political_array.write_to_file("2016 politics news.txt");

        std::cout << "Getting All Fake Political News in 2016..." << std::endl;
        counting_sort(news_2016_political_array, CRITERIA::IS_TRUE_NEWS);
        NewsLinkedList fake_2016_political_news_container = *dynamic_cast<NewsLinkedList*>(binary_search(&news_2016_political_array, SEARCH_CRITERIA::SEARCH_TRUE_OR_FALSE_NEWS, "false"));

        std::cout << "Reloading 2016 Political News array" << std::endl;
        merge_sort(news_2016_political_array, PUBLICATION_DATE);
        merge_sort(fake_2016_political_news_container, PUBLICATION_DATE);

        auto* percentage_per_month = new int[12];
        for (int i = 0; i < 12; i++) {
            NewsLinkedList total_news_in_month = *dynamic_cast<NewsLinkedList*>(binary_search(&news_2016_political_array, SEARCH_CRITERIA::SEARCH_PUBLICATION_MONTH, to_string(i + 1)));
            NewsLinkedList fake_news_in_month = *dynamic_cast<NewsLinkedList*>(binary_search(&fake_2016_political_news_container, SEARCH_CRITERIA::SEARCH_PUBLICATION_MONTH, to_string(i + 1)));
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

    void report_fake_political_news_in_each_month_in_2016_exponential() {
        auto* news_container = new NewsLinkedList();
        std::cout << "Loading from file..." << std::endl;
        news_container->load_from_file("../data/cleaned/fake.csv", false);
        news_container->load_from_file("../data/cleaned/true.csv", true);

        auto now = std::chrono::system_clock::now();

        std::cout << "Getting all news in 2016..." << std::endl;
        quick_sort(*news_container, CRITERIA::PUBLICATION_DATE);
        NewsLinkedList news_2016_array = *dynamic_cast<NewsLinkedList*>(exponential_search(news_container, SEARCH_CRITERIA::SEARCH_PUBLICATION_YEAR, "2016"));

        std::cout << "Getting All Political News in 2016..." << std::endl;
        merge_sort(news_2016_array, CRITERIA::GENRE);
        //news_2016_array.write_to_file("merge_sort_2016.txt");
        NewsLinkedList news_2016_political_array = *dynamic_cast<NewsLinkedList*>(exponential_search(&news_2016_array, SEARCH_CRITERIA::SEARCH_PUBLICATION_GENRE, "politics"));
        //news_2016_political_array.write_to_file("2016 politics news.txt");

        std::cout << "Getting All Fake Political News in 2016..." << std::endl;
        counting_sort(news_2016_political_array, CRITERIA::IS_TRUE_NEWS);
        NewsLinkedList fake_2016_political_news_container = *dynamic_cast<NewsLinkedList*>(exponential_search(&news_2016_political_array, SEARCH_CRITERIA::SEARCH_TRUE_OR_FALSE_NEWS, "false"));

        std::cout << "Reloading 2016 Political News array" << std::endl;
        merge_sort(news_2016_political_array, PUBLICATION_DATE);
        merge_sort(fake_2016_political_news_container, PUBLICATION_DATE);

        auto* percentage_per_month = new int[12];
        for (int i = 0; i < 12; i++) {
            NewsLinkedList total_news_in_month = *dynamic_cast<NewsLinkedList*>(exponential_search(&news_2016_political_array, SEARCH_CRITERIA::SEARCH_PUBLICATION_MONTH, to_string(i + 1)));
            NewsLinkedList fake_news_in_month = *dynamic_cast<NewsLinkedList*>(exponential_search(&fake_2016_political_news_container, SEARCH_CRITERIA::SEARCH_PUBLICATION_MONTH, to_string(i + 1)));
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
}
