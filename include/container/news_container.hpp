//
// Created by Victor Mak on 15/02/2025.
//

#pragma once

#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "container/news.hpp"

inline std::string remove_whitespace(const std::string& input) {
    std::string result = input;
    result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
    return result;
}

inline std::string remove_special_characters(const std::string& input) {
    std::string result = input;
    result.erase(std::remove_if(result.begin(), result.end(), [](char c) { return !std::isalnum(c); }), result.end());
    return result;
}

inline void parse_date(const std::string& date_str, struct tm& tm) {
    std::istringstream ss(date_str);
    ss >> std::get_time(&tm, "\"%b %d, %Y\"");
    if (ss.fail()) {
        std::istringstream ss2(date_str);
        ss2 >> std::get_time(&tm, "\"%d-%b-%y\"");
        if (ss2.fail()) {
            std::cerr << "Failed to parse date: " << date_str << std::endl;
        }
    }
}

const std::string unimportant_keywords[51] = {"the", "to", "of", "and", "a", "in", "that", "s", "is", "for", "on", "it", "was", "with", "he", "as", "by", "are", "this", "have",
"from", "t", "will", "about", "but", "be", "at", "an", "i", "me", "my", "mine", "he", "his", "him", "she", "her", "hers", "they", "them", "theirs", "it", "its", "we", "ours", "us", "our", "you", "yours", "their", "your"};

struct GenreIndex {
    std::string genre_name;
    int count = 0;
};

struct KeywordIndex {
    std::string keyword;
    int count = 0;
};

class NewsContainer {
    protected:
        ///the max date obtained from the news
        time_t max_date;
    public:
        ///The starting pointer from which this container will be able to access
        void* head;
        /// the size of the container
        int size;
        /// A record of all the detected genres in the container;
        GenreIndex* genre_index{};
        /// The number of distinct genres in the container
        int distinct_number_of_genres;

        NewsContainer(): size(0), head(nullptr), max_date(0), genre_index(new GenreIndex[30]), distinct_number_of_genres(0) {}

        NewsContainer(int size, void* head, time_t max_date): size(size), head(head), max_date(max_date), distinct_number_of_genres(0){}

        virtual ~NewsContainer() = default;

        /// update the distinct value counter
        void update_distincts(News* newNews);

        /// update the distinct value counter
        void update_distincts(News* oldNews, News* newNews);

        /// get genre value converted into criteria for sorting and searching
        long get_genre_criteria_value(News* news);

        /// get criteria value depending on the inputted criteria
        long get_criteria_value(News* news, CRITERIA critiera);

        /// get maximum date
        time_t get_max_date();

        /// load from the file
        void load_from_file(const std::string& filepath, bool are_true_news);

        /// load from the file by continuously checking whether if the file path is correct or not
        void load_from_file(bool are_true_news);

        /// display the keywords inside
        void display_keyword_demographics();

        /// print all the values out onto the console
        void display();

        /// print the size of the container;
        void display_total_number_of_articles();

        /// write the contents inside the container into a file for viewing purposes
        void write_to_file(const std::string& file_path);

        /// insert the value at the end of the container
        virtual void insert(News newNews) = 0;

        /// insert an empty value at the end of the container
        virtual void insert_empty() = 0;

        /// insert the value at a specific location, pushing back the existing value
        virtual void insert_at_location(News newNews, int location) = 0;

        /// delete the value at a specific location, pull back the existing value
        virtual void delete_at_location(int location) = 0;

        /// get the value at a particular location
        virtual News* get_at_location(int location) = 0;

        /// get the value at a particular location (could be NewsNode* for LinkedList, could be News for Array)
        virtual void* get_node_at_location(int location) = 0;

        /// taking another container as a parameter, overwrite the values in the current container from a predefined location
        virtual void overwrite_at_position(NewsContainer* value_container, int starting_location) = 0;

        /// Put the value at the designated location, overwriting the existing values
        virtual void put_at_location(News newNews, int location) = 0;

        /// Swap between two elements in the container with predefined indexes
        virtual void swap_news(int i, int j) = 0;

        /// Swap between two elements in the container with predefined memory locations
        static void swap_news(News* news1, News* news2) {
            News temp = *news1;
            *news1 = *news2;
            *news2 = temp;
        }

        /// get the last element in the container
        virtual void* get_tail() = 0;

        /// get the news at the memory location
        virtual News* get_news_at_memory(void* memory) = 0;

        /// move to next element (can be used for both Array and LinkedList)
        virtual void* move_to_next(void* current) = 0;

        /// move to previous element (can be used for both Array and LinkedList)
        virtual void* move_to_prev(void* previous) = 0;

        /// Split the container from the left exclusive of the midpoint
        virtual void* split_left(int mid_point) = 0;

        /// Split the container from the right exclusive of the midpoint
        virtual void* split_right(int mid_point) = 0;

        /// Create a container of the same type with the same amount of elements
        virtual void* allocate_empty_copy() = 0;

        /// Allocate Empty Container of the same type
        virtual void* allocate_empty() = 0;
};

inline void NewsContainer::update_distincts(News* newNews) {
    if (newNews == nullptr) {
        return;
    }
    /// check if genre is in the genre index already or not
    bool genre_exists = false;
    for (int i = 0; i < distinct_number_of_genres; i++) {
        if (genre_index[i].genre_name == newNews->genre) {
            genre_index[i].count++;
            genre_exists = true;
            break;
        }
    }

    //if it does not exist create a new genre and add 1 into there
    if (!genre_exists) {
        genre_index[distinct_number_of_genres].genre_name = newNews->genre;
        genre_index[distinct_number_of_genres].count = 1;
        distinct_number_of_genres++;
    }
}

inline void NewsContainer::update_distincts(News* oldNews, News* newNews) {
    /// delete the news and update details
    /// check if genre is in the genre index already or not

    if (oldNews == nullptr) {
        return;
    }

    for (int i = 0; i < distinct_number_of_genres; i++) {
        if (genre_index[i].genre_name == oldNews->genre) {
            genre_index[i].count--;
            break;
        }
    }

    if (newNews == nullptr) {
        return;
    }

    /// check if genre is in the genre index already or not
    bool genre_exists = false;
    for (int i = 0; i < distinct_number_of_genres; i++) {
        if (genre_index[i].genre_name == newNews->genre) {
            genre_index[i].count++;
            genre_exists = true;
            break;
        }
    }

    //if it does not exist create a new genre and add 1 into there
    if (!genre_exists) {
        genre_index[distinct_number_of_genres].genre_name = newNews->genre;
        genre_index[distinct_number_of_genres].count = 1;
        distinct_number_of_genres++;
    }
}

inline long ::NewsContainer::get_genre_criteria_value(News *news) {
    for (int gi = 0; gi < distinct_number_of_genres; gi++) {
        std::string current_genre_name = genre_index[gi].genre_name;
        if (genre_index[gi].genre_name == news->genre) {
            return gi;
        }
    }
    return -1;
}

inline long ::NewsContainer::get_criteria_value(News *news, CRITERIA critiera) {
    switch (critiera) {
        case GENRE:
            return get_genre_criteria_value(news);
        case PUBLICATION_DATE:
            return news->publication_date;
        case IS_TRUE_NEWS:
            return news->is_true;
        case PUBLICATION_YEAR:
            return news->get_year();
        case PUBLICATION_MONTH:
            return news->get_month();
        default:
            return 0;
    }
}

inline void NewsContainer::display_keyword_demographics() {
        int distinct_number_of_keywords = 0;
        KeywordIndex* keyword_index = new KeywordIndex[100000];

        bool reached_quarter = false;
        bool reached_halved = false;
        bool reached_three_quarters = false;
        for (int i = 0; i < size; i++) {
            News* news = get_at_location(i);
            std::string content = news->content;
            std::istringstream ss(content);
            std::string word;

            if (!reached_quarter && i >= size / 4) {
                std::cout << "25% of the data has been processed" << std::endl;
                reached_quarter = true;
            }

            if (!reached_halved && i >= size / 2) {
                std::cout << "50% of the data has been processed" << std::endl;
                reached_halved = true;
            }

            if (!reached_three_quarters && i >= size * 3 / 4) {
                std::cout << "75% of the data has been processed" << std::endl;
                reached_three_quarters = true;
            }

            while (ss >> word) {

                //turn word into lowercase
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                //remove spaces from before and after the word
                word = remove_special_characters(remove_whitespace(word));

                bool is_unimportant = false;
                for (const std::string & unimportant_keyword : unimportant_keywords) {
                    if (word == unimportant_keyword) {
                        is_unimportant = true;
                        break;
                    }
                }
                if (is_unimportant) {
                    continue;
                }

                bool keyword_exists = false;
                for (int j = 0; j < distinct_number_of_keywords; j++) {
                    if (keyword_index[j].keyword == word) {
                        keyword_index[j].count++;
                        keyword_exists = true;
                        break;
                    }
                }

                if (!keyword_exists) {
                    keyword_index[distinct_number_of_keywords].keyword = word;
                    keyword_index[distinct_number_of_keywords].count = 1;
                    distinct_number_of_keywords++;
                }
            }
        }

        std::cout << "Keywords detected: " << distinct_number_of_keywords << std::endl;
        std::cout << "Sorting Keywords Descending" << std::endl;
        //now sort the keyword demographics descending
        for (int i = 0; i < distinct_number_of_keywords; i++) {
            for (int j = i + 1; j < distinct_number_of_keywords; j++) {
                //check if it is the same as unimportant keywords if yes, then exit
                if (keyword_index[i].count < keyword_index[j].count) {
                    KeywordIndex temp = keyword_index[i];
                    keyword_index[i] = keyword_index[j];
                    keyword_index[j] = temp;
                }
            }
        }

        //now print and display the keyword demographics
        std::cout << "Most Common 20 Keywords Demographics" << std::endl;
        for (int i = 0; i < 20; i++) {
            std::cout << i + 1 << ". "<< keyword_index[i].keyword << " : " << keyword_index[i].count << std::endl;
        }
}

inline time_t NewsContainer::get_max_date() {
    return max_date;
}

inline void NewsContainer::write_to_file(const std::string& file_path) {
    std::ofstream output_file(file_path);
    void* current = head;
    for (int i = 0; i < size; i++) {
        News* news = get_news_at_memory(current);
        output_file <<  "["  << ((news->is_true)? "TRUE NEWS] Genre: ": "FALSE NEWS] Genre:") << news->genre << " " << std::put_time(localtime(&news->publication_date), "%b %d, %Y") << std::setw(20) << " " << news->title << std::setw(200) << news->content << std::setw(20) << "\n";
        current = move_to_next(current);
    }
    output_file.close();
}

inline void NewsContainer::load_from_file(bool are_true_news) {
    std::string file_path;
    while (true) {
        std::cin >> file_path;
        std::ifstream target_file(file_path);

        if (!target_file.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
        }else {
            target_file.close();
            break;
        }
    }

    load_from_file(file_path, are_true_news);
}


inline void NewsContainer::load_from_file(const std::string& filepath, bool are_true_news) {
    std::ifstream target_file(filepath);

    if (!target_file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }

    std::string line, full_line;

    // Read and ignore the header from the original file
    getline(target_file, line);

    while (getline(target_file, line))
    {
        full_line = line;
        long quote_count = std::count(line.begin(), line.end(), '"');

        // If we have an odd number of quotes, the entry is not complete
        while (quote_count % 2 != 0) {
            std::string next_line;
            if (!getline(target_file, next_line)) break;

            full_line += "\n" + next_line;
            quote_count += std::count(next_line.begin(), next_line.end(), '"');
        }

        std::istringstream ss(full_line);
        std::string title, text, subject, date;

        // Read title
        getline(ss, title, ',');
        if (title.front() == '\"') {
            std::string temp;
            while (title.back() != '\"') {
                getline(ss, temp, ',');
                title += "," + temp;
            }
        }

        getline(ss, text, ',');
        if (text.front() == '\"') {
            std::string temp;
            while (text.back() != '\"') {
                getline(ss, temp, ',');
                text += "," + temp;
            }
        }

        getline(ss, subject, ',');
        getline(ss, date, '\n');

        News news1;
        news1.title = title;
        news1.content = text;
        news1.genre = subject;

        if (news1.genre == "\"politicsnews\"") {
            news1.genre = "\"politics\"";
        }

        struct tm tm = {};
        parse_date(date, tm);
        news1.publication_date = mktime(&tm);
        news1.publication_time_info = *localtime(&news1.publication_date);
        news1.is_true = are_true_news;
        this->insert(news1);
    }
}

inline void NewsContainer::display(){
    void* current = head;
    for (int i = 0; i < size; i++) {
        News* news = get_news_at_memory(current);
        std::cout <<  "["  << ((news->is_true)? "TRUE NEWS] ": "FALSE NEWS] ") << news->genre <<" "<< std::put_time(localtime(&news->publication_date), "%b %d, %Y") << std::setw(10) << " " << news->title << std::setw(200) << news->content << std::setw(20) << "\n";
        current = move_to_next(current);
    }
}

inline void NewsContainer::display_total_number_of_articles() {
    std::cout << "Total Number of Articles: " << size << std::endl;
}

