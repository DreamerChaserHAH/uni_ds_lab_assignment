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

struct GenreIndex {
    std::string genre_name;
    int count;
};

struct KeywordIndex {
    std::string keyword;
    int count;
};

class NewsContainer{
    protected:
        time_t max_date;
  public:
    ///<summary>
    ///The starting pointer from which this container will be able to access
    ///</summary>
    void* head;
    int size;

    GenreIndex* genre_index;

    int distinct_number_of_genres;

    NewsContainer(): size(0), head(nullptr), max_date(0), genre_index(new GenreIndex[30]) {}

    //an alternative constructor that allows us to set the head pointer
    NewsContainer(int size, void* head, time_t max_date): size(size), head(head), max_date(max_date){}

    virtual ~NewsContainer() = default;

    void update_distincts(News* newNews) {

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

    void update_distincts(News* oldNews, News* newNews) {
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

    long get_genre_critiera_value(News* news) {
        for (int gi = 0; gi < distinct_number_of_genres; gi++) {
            std::string current_genre_name = genre_index[gi].genre_name;
            if (genre_index[gi].genre_name == news->genre) {
                return gi;
            }
        }
    }

    long get_criteria_value(News* news, CRITERIA criteria) {
        switch (criteria) {
            case GENRE:
                return get_genre_critiera_value(news);
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

    void display_keyword_demographics() {
        int distinct_number_of_keywords = 0;
        KeywordIndex* keyword_index = new KeywordIndex[10000];

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

        std::cout << "Sorting Keywords Descending" << std::endl;
        //now sort the keyword demographics descending
        for (int i = 0; i < distinct_number_of_keywords; i++) {
            for (int j = i + 1; j < distinct_number_of_keywords; j++) {
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
            std::cout << keyword_index[i].keyword << " : " << keyword_index[i].count << std::endl;
        }
    }

    /// <summary>
    /// filepath: the path of the file we are reading
    /// description: load the data from the designated file into this particular linked list
    /// </summary>
    void load_from_file(const std::string& filepath, bool are_true_news) {
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
            int quote_count = std::count(line.begin(), line.end(), '"');

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

    /// <summary>
    /// get the maximum date from insertion
    /// </summary>
    [[nodiscard]] time_t get_max_date() {
        return max_date;
    }

    /// <summary>
    /// Display all elements contained inside the container
    /// </summary>
    void display(){
        void* current = head;
        std::cout  << "Publication Date" << std::setw(20) << "Title" << std::setw(200) << "Content" << std::setw(200) << "Genre" << std::setw(20) << std::endl;
        for (int i = 0; i < size; i++) {
            News* news = get_news_at_memory(current);
            std::cout <<  "["  << ((news->is_true)? "TRUE NEWS] Genre: ": "FALSE NEWS] Genre:") << news->genre <<" "<< std::put_time(localtime(&news->publication_date), "%b %d, %Y") << std::setw(20) << " " << news->title << std::setw(200) << news->content << std::setw(20) << "\n";
            current = move_to_next(current);
        }
    }

    /// <summary>
    /// Write the elements into a file
    /// </summary>
    void write_to_file(const std::string& file_path) {
        std::ofstream output_file(file_path);
        void* current = head;
        for (int i = 0; i < size; i++) {
            News* news = get_news_at_memory(current);
            output_file <<  "["  << ((news->is_true)? "TRUE NEWS] Genre: ": "FALSE NEWS] Genre:") << news->genre << " " << std::put_time(localtime(&news->publication_date), "%b %d, %Y") << std::setw(20) << " " << news->title << std::setw(200) << news->content << std::setw(20) << "\n";
            current = move_to_next(current);
        }
        output_file.close();
    }

    virtual void insert(News newNews) = 0;
    virtual void insert_empty() = 0;
    virtual void insert_at_location(News newNews, int location) = 0;
    virtual void delete_at_location(int location) = 0;

    virtual News* get_at_location(int location) = 0;
    virtual void* get_node_at_location(int location) = 0;

    virtual void overwrite_at_position(NewsContainer* value_container, int starting_location) = 0;
    /// <summary>
    /// Put the value at the designated location, overwriting the existing values
    /// </summary>
    virtual void put_at_location(News newNews, int location) = 0;

    /// <summary>
    /// Swap between two elements in the container
    /// </summary>
    virtual void swap_news(int i, int j) = 0;

    static void swap_news(News* news1, News* news2) {
        News temp = *news1;
        *news1 = *news2;
        *news2 = temp;
    }

    /// <summary>
    /// get the last element in the container
    /// </summary>
    virtual void* get_tail() = 0;

    /// <summary>
    /// get the news at the memory location
    /// </summary>
    virtual News* get_news_at_memory(void* memory) = 0;

    /// <summary>
    /// move to next pointer
    /// </summary>
    virtual void* move_to_next(void* current) = 0;

    /// <summary>
    /// move to previous pointer
    /// </summary>
    virtual void* move_to_prev(void* previous) = 0;

    /// <summary>
    /// Split the container from the left exclusive of the midpoint
    /// </summary>
    virtual void* split_left(int mid_point) = 0;

    /// <summary>
    /// Split the container from the right exclusive of the midpoint
    /// </summary>
    virtual void* split_right(int mid_point) = 0;

    /// <summary>
    /// Create a container of the same type with the same amount of elements
    /// </summary>
    virtual void* allocate_empty_copy() = 0;

    /// <summary>
    /// Allocate Empty Container of the same type
    /// </summary>
    virtual void* allocate_empty() = 0;
};
