#include "implementations/linked_list.hpp"

bool check_if_number_or_not(std::string str) {
    for (char i : str) {
        if (!isdigit(i)) {
            return false;
        }
    }
    return true;
}

bool check_input(std::string input_string) {
    return (!cin.fail() && check_if_number_or_not(input_string));
}

void remove_white_space(std::string& text) {
    text.erase(std::remove(text.begin(), text.end(), ' '), text.end());
}

inline std::string prompt_file_path(std::string context) {
    std::cout << context << std::endl;
    std::string file_path;
    std::cin >> file_path;
    remove_white_space(file_path);
    std::cout << file_path << std::endl;
    return file_path;
}

inline std::string prompt_search_content() {
    std::cout << "type the value you are going to search: ";
    std::string file_path;
    std::cin >> file_path;
    remove_white_space(file_path);
    std::cout << file_path << std::endl;
    return file_path;
}

void prompt_benchmark_sub_menu() {
    int choice = -1;
    bool exit_input_loop = false;

    std::string false_news = prompt_file_path("Enter the file path for the false file containing all false news:");
    std::string true_news = prompt_file_path("Enter the file path for the true file containing all true news:");

    while (!exit_input_loop) {
        cout << "**CHOOSE SORTING BENCHMARK**" << std::endl;
        cout << "1. Bubble Sort Benchmark (Livi)" << std::endl;
        cout << "2. Selection Sort Benchmark (Livi)" << std::endl;
        cout << "3. Quick Sort Benchmark (Htet Aung Hlaing)" << std::endl;
        cout << "4. Counting Sort Benchmark (Htet Aung Hlaing)" << std::endl;
        cout << "5. Bucket Sort Benchmark (Htet Kaung Myat Oo" << std::endl;
        cout << "6. Heap Sort Benchmark (Htet Kaung Myat Oo)" << std::endl;
        cout << "7. Merge Sort Benchmark (Abbirami)" << std::endl;
        cout << "8. Insertion Sort Benchmark (Abbirami)" << std::endl;

        cout << "**CHOOSE SEARCHING BENCHMARK**" << std::endl;
        cout << "9. Linear Search (Abbirami)" << std::endl;
        cout << "10. Binary Search (Htet Kaung Myat Oo)" << std::endl;
        cout << "11. Exponential Search (Livi)" << std::endl;
        cout << "12. Two Pointer Search (Htet Aung Hlaing)" << std::endl;

        cout << "13. Go back to main menu" << std::endl;
        cout << ">";
        std::string input_string;
        cin >> input_string;

        if (!check_input(input_string)) {
            std::cout << "Wrong Input. Please try again!" << std::endl;
            break;
        }

        choice = std::stoi(input_string);

        switch (choice) {
            case 1:
                linked_list_implementation::sort_with_bubble_sort_benchmark(false_news, true_news, CRITERIA::PUBLICATION_DATE);
                break;
            case 2:
                linked_list_implementation::sort_with_selection_sort_benchmark(false_news, true_news, CRITERIA::PUBLICATION_DATE);
                break;
            case 3:
                linked_list_implementation::sort_with_quick_sort_benchmark(false_news, true_news, CRITERIA::PUBLICATION_DATE);
                break;
            case 4:
                linked_list_implementation::sort_with_counting_sort_benchmark(false_news, true_news, PUBLICATION_DATE);
                break;
            case 5:
                linked_list_implementation::sort_with_merge_sort_benchmark(false_news, true_news, PUBLICATION_DATE);
                break;
            case 6:
                linked_list_implementation::sort_with_insertion_sort_benchmark(false_news, true_news, PUBLICATION_DATE);
                break;
            case 7:
                linked_list_implementation::sort_with_heap_sort_benchmark(false_news, true_news, PUBLICATION_DATE);
                break;
            case 8:
                linked_list_implementation::sort_with_bucket_sort_benchmark(false_news, true_news, PUBLICATION_DATE);
                break;
            case 9:
                linked_list_implementation::report_fake_political_news_in_each_month_in_2016_linear_benchmark(false_news, true_news);
                break;
            case 10:
                linked_list_implementation::report_fake_political_news_in_each_month_in_2016_binary_benchmark(false_news, true_news);
                break;
            case 11:
                linked_list_implementation::report_fake_political_news_in_each_month_in_2016_exponential_benchmark(false_news, true_news);
                break;
            case 12:
                linked_list_implementation::report_fake_political_news_in_each_month_in_2016_two_pointer_search_benchmark(false_news, true_news);
                break;
            case 13:
                exit_input_loop = true;
                break;
            default:
                break;
        }
    }
}

inline CRITERIA prompt_choose_sorting_criteria() {
    int choice = -1;
    while (true) {
        std::cout << "Choose a criteria to initiate sorting" << std::endl;
        std::cout << "1. Publication Date" << std::endl;
        std::cout << "2. Genre" << std::endl;
        std::cout << "3. Is True News" << std::endl;

        std::string input_string;
        cin >> input_string;

        if (!check_input(input_string)) {
            std::cout << "Wrong Input. Please try again!" << std::endl;
            break;
        }

        choice = std::stoi(input_string);

        switch (choice) {
            case 1:
                return CRITERIA::PUBLICATION_DATE;
            case 2:
                return CRITERIA::GENRE;
            case 3:
                return CRITERIA::IS_TRUE_NEWS;
            default:
                std::cout << "Wrong Input" << std::endl;
                break;
        }

    }
}

inline SEARCH_CRITERIA prompt_choose_search_criteria() {
    int choice = -1;
    while (true) {
        std::cout << "Choose a criteria to initiate searching" << std::endl;
        std::cout << "1. Publication Year" << std::endl;
        std::cout << "2. Publication Month" << std::endl;
        std::cout << "3. Genre" << std::endl;
        std::cout << "4. Is True News" << std::endl;

        std::string input_string;
        cin >> input_string;

        if (!check_input(input_string)) {
            std::cout << "Wrong Input. Please try again!" << std::endl;
            break;
        }

        choice = std::stoi(input_string);

        switch (choice) {
            case 1:
                return SEARCH_CRITERIA::SEARCH_PUBLICATION_YEAR;
            case 2:
                return SEARCH_CRITERIA::SEARCH_PUBLICATION_MONTH;
            case 3:
                return SEARCH_CRITERIA::SEARCH_PUBLICATION_GENRE;
            case 4:
                return SEARCH_CRITERIA::SEARCH_PUBLICATION_GENRE;
            default:
                std::cout << "Wrong Input" << std::endl;
            break;
        }
    }
}

void prompt_sorting_algorithm_sub_menu(NewsLinkedList* news_container) {

    if (news_container == nullptr) {
        std::cout << "Please load the news container by choosing option 1 first" << std::endl;
        return;
    }

    CRITERIA criteria = prompt_choose_sorting_criteria();

    int choice = -1;
    bool exit_input_loop = false;

    while (!exit_input_loop) {
        cout << "**CHOOSE SORTING**" << std::endl;
        cout << "1. Bubble Sort (Livi)" << std::endl;
        cout << "2. Selection Sort (Livi)" << std::endl;
        cout << "3. Quick Sort (Htet Aung Hlaing)" << std::endl;
        cout << "4. Counting Sort (Htet Aung Hlaing)" << std::endl;
        cout << "5. Bucket Sort (Htet Kaung Myat Oo" << std::endl;
        cout << "6. Heap Sort (Htet Kaung Myat Oo)" << std::endl;
        cout << "7. Merge Sort (Abbirami)" << std::endl;
        cout << "8. Insertion Sort (Abbirami)" << std::endl;
        cout << "9. Go Back to Previous Screen" << std::endl;

        std::string input_string;
        cin >> input_string;

        if (!check_input(input_string)) {
            std::cout << "Wrong Input. Please try again!" << std::endl;
            break;
        }

        choice = std::stoi(input_string);

        switch (choice) {
            case 1:
                bubble_sort(*news_container, criteria);
                news_container->display();
                break;
            case 2:
                selection_sort(*news_container, criteria);
                news_container->display();
                break;
            case 3:
                quick_sort(*news_container, criteria);
                news_container->display();
                break;
            case 4:
                counting_sort(*news_container, criteria);
                news_container->display();
                break;
            case 5:
                bucket_sort(*news_container, criteria);
                news_container->display();
                break;
            case 6:
                heap_sort(*news_container, criteria);
                news_container->display();
                break;
            case 7:
                merge_sort(*news_container, criteria);
                news_container->display();
                break;
            case 8:
                insertion_sort(*news_container, criteria);
                news_container->display();
                break;
            case 9:
                exit_input_loop = true;
                break;
            default:
                std::cout << "Wrong Input" << std::endl;
                break;
        }
    }
}

void prompt_searching_algorithm_sub_menu(NewsLinkedList* news_container) {

    if (news_container == nullptr) {
        std::cout << "Please load the news container by choosing option 1 first" << std::endl;
        return;
    }


    int choice = -1;
    bool exit_input_loop = false;

    while (!exit_input_loop) {
        cout << "**CHOOSE SEARCHING**" << std::endl;
        cout << "1. Linear Search (Abbirami)" << std::endl;
        cout << "2. Binary Search (Htet Kaung Myat Oo)" << std::endl;
        cout << "3. Exponential Search (Livi)" << std::endl;
        cout << "4. Two Pointer Search (Htet Aung Hlaing)" << std::endl;
        cout << "5. Go back to Previous Screen" << std::endl;

        std::string input_string;
        cin >> input_string;

        if (!check_input(input_string)) {
            std::cout << "Wrong Input. Please try again!" << std::endl;
            break;
        }

        choice = std::stoi(input_string);
        SEARCH_CRITERIA search_criteria = prompt_choose_search_criteria();
        std::string search_content = prompt_search_content();

        switch (choice) {
            case 1:
                linear_search(news_container, search_criteria, search_content);
                news_container->display();
                break;
            case 2:
                binary_search(news_container, search_criteria, search_content);
                news_container->display();
                break;
            case 3:
                exponential_search(news_container, search_criteria, search_content);
                news_container->display();
                break;
            case 4:
                two_pointer_search(news_container, search_criteria, search_content);
                news_container->display();
                break;
            default:
                std::cout << "Wrong Input" << std::endl;
                break;
        }
    }

}

int main() {

    std::cout << "Hello from Linked List Implementation File" << std::endl;
    int choice = -1;
    NewsLinkedList* news_linked_list = nullptr;

    bool end_application = false;
    while (!end_application) {
        cout << "1. Load News Linked List" << std::endl;
        cout << "2. Apply Sorting Algorithm" << std::endl;
        cout << "3. Apply Searching Algorithm" << std::endl;
        cout << "4. Benchmarking" << std::endl;
        cout << "5. Exit Application" << std::endl;
        cout << ">";
        std::string input_string;
        cin >> input_string;

        if (!check_input(input_string)) {
            std::cout << "Wrong Input! Please try again" << std::endl;
            break;
        }

        choice = std::stoi(input_string);
        switch (choice) {
            case 1:
                news_linked_list = new NewsLinkedList();
                std::cout << "Enter the file path for the false file containing all false news:";
                news_linked_list->load_from_file(false);
                std::cout << "Enter the file path for the true file containing all true news:";
                news_linked_list->load_from_file(true);
                std::cout << "Loading From File Completed\n";
                break;
            case 2:
                prompt_sorting_algorithm_sub_menu(news_linked_list);
                break;
            case 3:
                prompt_searching_algorithm_sub_menu(news_linked_list);
                break;
            case 4:
                //benchmarking
                prompt_benchmark_sub_menu();
                break;
            case 5:
                std::cout << "Application received quit signal" << std::endl;
                end_application = true;
                break;
            default:
                std::cout << "Invalid Input" << std::endl;
                break;
        }

    }
}