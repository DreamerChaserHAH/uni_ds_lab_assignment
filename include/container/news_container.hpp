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
#include "container/news.hpp"

inline void parse_date(const std::string& date_str, struct tm& tm) {
    std::istringstream ss(date_str);
    ss >> std::get_time(&tm, "\"%b %d, %Y\"");
    if (ss.fail()) {
        std::cerr << "Failed to parse date: " << date_str << std::endl;
    }
}

class NewsContainer{
    protected:
        time_t max_date;
  public:
    ///<summary>
    ///The starting pointer from which this container will be able to access
    ///</summary>
    void* head;

    int size;

    NewsContainer(): size(0), head(nullptr), max_date(0) {}

    //an alternative constructor that allows us to set the head pointer
    NewsContainer(int size, void* head, time_t max_date): size(size), head(head), max_date(max_date){}

    virtual ~NewsContainer() = default;

    /// <summary>
    /// filepath: the path of the file we are reading
    /// description: load the data from the designated file into this particular linked list
    /// </summary>
    void load_from_file(const std::string& filepath) {
        std::ifstream current_file(filepath);

        std::string title;
        std::string text;
        std::string subject;
        std::string date;

        /// TODO Implement reading from file after cleaning
        std::ifstream file(filepath);

        while (file.good()) {
            getline(file, title, ',');
            getline(file, text, ',');
            getline(file, subject, ',');
            getline(file, date, '\n');

            if (title == "title")
                continue;
            else if (title == "")
                break;

            News news1;
            news1.title = title;
            news1.content = text;
            if (subject == "worldnews") {
                news1.genre = NewsGenre::WORLD_NEWS;
            }
            else if (subject == "politicsNews") {
                news1.genre = NewsGenre::POLITICS;
            }else {
                news1.genre = NewsGenre::OTHERS;
            }

            struct tm tm = {};
            parse_date(date, tm);
            news1.publication_date = mktime(&tm);
            //this->display_article();
            this->insert(news1);
        }
    }

    /// <summary>
    /// get the maximum date from insertion
    /// </summary>
    [[nodiscard]] time_t get_max_date() {
        return max_date;
    }

    void display_article(){

    }

    virtual void insert(News newNews) = 0;
    virtual void insert_empty() = 0;
    virtual void insert_at_location(News newNews, int location) = 0;
    virtual News* get_at_location(int location) = 0;

    /// <summary>
    /// Put the value at the designated location, overwriting the existing values
    /// </summary>
    virtual void put_at_location(News newNews, int location) = 0;

    /// <summary>
    /// Swap between two elements in the container
    /// </summary>
    virtual void swap_news(int i, int j) = 0;

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
};
