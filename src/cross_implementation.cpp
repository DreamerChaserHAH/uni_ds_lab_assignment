#include <iostream>
#include <chrono>
#include "../include/algorithms/sort.hpp"
#include "../include/algorithms/search.hpp"
#include "../include/container/array.hpp"
#include "../include/container/linked_list.hpp"

using namespace std;

class MenuSystem {
private:
    NewsContainer* news_container;
    bool useArray;

    NewsContainer* load_news_data(bool useArray) {
        if (news_container) {
            delete news_container;
        }

        if (useArray) {
            news_container = new NewsArray();
        } else {
            news_container = new NewsLinkedList();
        }

        cout << "Reloading data..." << endl;
        news_container->load_from_file("../data/cleaned/fake.csv", false);
        news_container->load_from_file("../data/cleaned/true.csv", true);

        cout << "Data successfully reloaded!\n";
        return news_container;
    }

    CRITERIA select_sort_criteria() {
        int criteriaChoice;
        cout << "\n=== Sorting Criteria ===\n";
        cout << "1. Genre\n2. Publication Date\n3. Is True News\n4. Publication Year\n5. Publication Month\n";
        cout << "Enter your choice: ";
        cin >> criteriaChoice;

        switch (criteriaChoice) {
            case 1: return GENRE;
            case 2: return PUBLICATION_DATE;
            case 3: return IS_TRUE_NEWS;
            case 4: return PUBLICATION_YEAR;
            case 5: return PUBLICATION_MONTH;
            default: cout << "Invalid choice. Defaulting to Publication Date.\n";
                     return PUBLICATION_DATE;
        }
    }

    SEARCH_CRITERIA select_search_criteria() {
        int criteriaChoice;
        cout << "\n=== Searching Criteria ===\n";
        cout << "1. Publication Year\n2. Publication Month\n3. Genre\n4. True/False News\n";
        cout << "Enter your choice: ";
        cin >> criteriaChoice;

        switch (criteriaChoice) {
            case 1: return SEARCH_PUBLICATION_YEAR;
            case 2: return SEARCH_PUBLICATION_MONTH;
            case 3: return SEARCH_PUBLICATION_GENRE;
            case 4: return SEARCH_TRUE_OR_FALSE_NEWS;
            default: cout << "Invalid choice. Defaulting to Publication Year.\n";
                     return SEARCH_PUBLICATION_YEAR;
        }
    }

    void execute_sort(void (*sort_function)(NewsContainer&, CRITERIA), string sort_name) {
        CRITERIA selectedCriteria = select_sort_criteria();
        cout << "Starting " << sort_name << " based on selected criteria.\n";
        auto start_time = chrono::system_clock::now();
        sort_function(*news_container, selectedCriteria);
        auto end_time = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end_time - start_time;
        news_container->display();
        cout << sort_name << " took: " << elapsed_seconds.count() << "s" << endl;
        cout << "Returning to main menu...\n";
    }

    void execute_search(NewsContainer* (*search_function)(NewsContainer*, SEARCH_CRITERIA, string),
                        string search_name) {
        SEARCH_CRITERIA selectedCriteria = select_search_criteria();

        string search_value;
        cout << "Enter search value: ";
        cin.ignore();
        getline(cin, search_value);

        cout << "Starting " << search_name << " for \"" << search_value << "\"...\n";
        auto start_time = chrono::system_clock::now();
        news_container = search_function(news_container, selectedCriteria, search_value);
        auto end_time = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end_time - start_time;

        if (news_container && news_container->size > 0) {
            news_container->display();
        } else {
            cout << "No results found.\n";
        }
        cout << search_name << " took: " << elapsed_seconds.count() << "s" << endl;
        cout << "Returning to main menu...\n";
    }

    void display_data() {
        if (news_container) {
            cout << "Displaying News Data:\n";
            news_container->display();
        } else {
            cout << "No data available. Please load data first.\n";
        }
    }

    void exitProgram() {
        cout << "Exiting program..." << endl;
        exit(0);
    }

public:
    MenuSystem() : news_container(nullptr), useArray(true) {}

    void showMenu() {
        int choice;

        while (true) {
            cout << "===== PERFORMANCE OF SEARCH AND SORT ALGORITHMS =====\n";
            cout << "1. Array Implementation\n";
            cout << "2. Linked List Implementation\n";
            cout << "3. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 3) {
                exitProgram();
            }

            if (choice != 1 && choice != 2) {
                cout << "Invalid choice. Please enter 1 or 2.\n";
                continue;
            }

            useArray = (choice == 1);
            load_news_data(useArray);

            while (true) {
                int subChoice;
                cout << "\n=== MAIN MENU ===\n";
                cout << "1. Sorting Algorithms\n";
                cout << "2. Searching Algorithms\n";
                cout << "3. Display Data\n";
                cout << "4. Reload Data\n";
                cout << "5. Back to Implementation Selection\n";
                cout << "6. Exit\n";
                cout << "Enter your choice: ";
                cin >> subChoice;

                if (subChoice == 1) {
                    int sortChoice;
                    do {
                        cout << "\n=== Sorting Algorithms ===\n";
                        cout << "1. Bubble Sort\n2. Selection Sort\n3. Quick Sort\n4. Merge Sort\n";
                        cout << "5. Heap Sort\n6. Counting Sort\n7. Bucket Sort\n8. Insertion Sort\n9. Back to Main Menu\n";
                        cout << "Enter your choice: ";
                        cin >> sortChoice;

                        switch (sortChoice) {
                            case 1: execute_sort(bubble_sort, "Bubble Sort"); break;
                            case 2: execute_sort(selection_sort, "Selection Sort"); break;
                            case 3: execute_sort(quick_sort, "Quick Sort"); break;
                            case 4: execute_sort(merge_sort, "Merge Sort"); break;
                            case 5: execute_sort(heap_sort, "Heap Sort"); break;
                            case 6: execute_sort(counting_sort, "Counting Sort"); break;
                            case 7: execute_sort(bucket_sort, "Bucket Sort"); break;
                            case 8: execute_sort(insertion_sort, "Insertion Sort"); break;
                            case 9: cout << "Returning to Main Menu...\n"; break;
                            default: cout << "Invalid choice. Try again.\n";
                        }
                    } while (sortChoice != 9);
                }
                else if (subChoice == 2) {
                    int searchChoice;
                    do {
                        cout << "\n=== Searching Algorithms ===\n";
                        cout << "1. Linear Search\n2. Binary Search\n3. Interpolation Search\n4. Jump Search\n";
                        cout << "5. Hash Table\n6. Exponential Search\n7. Sublist Search\n8. Fibonacci Search\n9. Back to Main Menu\n";
                        cout << "Enter your choice: ";
                        cin >> searchChoice;

                        switch (searchChoice) {
                            case 1: execute_search(linear_search, "Linear Search"); break;
                            case 2: execute_search(binary_search, "Binary Search"); break;
                            case 3: /* Implement Interpolation Search */ break;
                            case 4: execute_search(two_pointer_search, "Jump Search"); break;
                            case 5: /* Implement Hash Table Search */ break;
                            case 6: execute_search(exponential_search, "Exponential Search"); break;
                            case 7: break;
                            case 8:  break;
                            case 9: cout << "Returning to Main Menu...\n"; break;
                            default: cout << "Invalid choice. Try again.\n";
                        }
                    } while (searchChoice != 9);
                }
                else if (subChoice == 3) {
                    display_data();
                }
                else if (subChoice == 4) {
                    load_news_data(useArray);
                }
                else if (subChoice == 5) {
                    break;
                }
                else if (subChoice == 6) {
                    exitProgram();
                }
            }
        }
    }
};

int main() {
    MenuSystem menu;
    menu.showMenu();
    return 0;
}
