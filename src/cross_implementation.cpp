#include <iostream>
#include <chrono>
#include <limits> // For input validation
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
        while (true) {
            cout << "\n=== Sorting Criteria ===\n";
            cout << "1. Genre\n2. Publication Date\n3. Is True News\n4. Publication Year\n5. Publication Month\n";
            cout << "Enter your choice: ";
            cin >> criteriaChoice;

            if (cin.fail() || criteriaChoice < 1 || criteriaChoice > 5) {
                cout << "Invalid input! Please enter a number between 1 and 5.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        }

        switch (criteriaChoice) {
            case 1: return GENRE;
            case 2: return PUBLICATION_DATE;
            case 3: return IS_TRUE_NEWS;
            case 4: return PUBLICATION_YEAR;
            case 5: return PUBLICATION_MONTH;
        }
        return PUBLICATION_DATE; // Default case (should never reach)
    }

    SEARCH_CRITERIA select_search_criteria() {
        int criteriaChoice;
        while (true) {
            cout << "\n=== Searching Criteria ===\n";
            cout << "1. Publication Year\n2. Publication Month\n3. Genre\n4. True/False News\n";
            cout << "Enter your choice: ";
            cin >> criteriaChoice;

            if (cin.fail() || criteriaChoice < 1 || criteriaChoice > 4) {
                cout << "Invalid input! Please enter a number between 1 and 4.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        }

        switch (criteriaChoice) {
            case 1: return SEARCH_PUBLICATION_YEAR;
            case 2: return SEARCH_PUBLICATION_MONTH;
            case 3: return SEARCH_PUBLICATION_GENRE;
            case 4: return SEARCH_TRUE_OR_FALSE_NEWS;
        }
        return SEARCH_PUBLICATION_YEAR; // Default case
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
        NewsContainer* result = search_function(news_container, selectedCriteria, search_value);
        auto end_time = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end_time - start_time;

        if (result && result->size > 0) {
            result->display();
        } else {
            cout << "Invalid search value or no results found.\nReturning to main menu...\n";
        }
        cout << search_name << " took: " << elapsed_seconds.count() << "s" << endl;
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

            if (cin.fail() || (choice != 1 && choice != 2 && choice != 3)) {
                cout << "Invalid input! Please enter 1, 2, or 3.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (choice == 3) {
                exitProgram();
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

                if (cin.fail() || subChoice < 1 || subChoice > 6) {
                    cout << "Invalid input! Please enter a valid option.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (subChoice == 1) {
                    int sortChoice;
                    do {
                        cout << "\n=== Sorting Algorithms ===\n";
                        cout << "1. Bubble Sort\n2. Selection Sort\n3. Quick Sort\n4. Merge Sort\n";
                        cout << "5. Heap Sort\n6. Counting Sort\n7. Bucket Sort\n8. Insertion Sort\n9. Back to Main Menu\n";
                        cout << "Enter your choice: ";
                        cin >> sortChoice;

                        if (cin.fail() || sortChoice < 1 || sortChoice > 9) {
                            cout << "Invalid input! Please enter a valid option.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }

                        switch (sortChoice) {
                            case 1: execute_sort(bubble_sort, "Bubble Sort"); break;
                            case 2: execute_sort(selection_sort, "Selection Sort"); break;
                            case 3: execute_sort(quick_sort, "Quick Sort"); break;
                            case 4: execute_sort(merge_sort, "Merge Sort"); break;
                            case 5: execute_sort(heap_sort, "Heap Sort"); break;
                            case 6: execute_sort(counting_sort, "Counting Sort"); break;
                            case 7: execute_sort(bucket_sort, "Bucket Sort"); break;
                            case 8: execute_sort(insertion_sort, "Insertion Sort"); break;
                        }
                    } while (sortChoice != 9);
                }
                else if (subChoice == 2) {
                    execute_search(linear_search, "Linear Search");
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
