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

#include "news.hpp"

void parse_date(const std::string& date_str, struct tm& tm) {
    std::istringstream ss(date_str);
    ss >> std::get_time(&tm, "\"%b %d, %Y\"");
    if (ss.fail()) {
        std::cerr << "Failed to parse date: " << date_str << std::endl;
    }
}

class NewsContainer{
  public:
    ///<summary>
    ///The starting pointer from which this container will be able to access
    ///</summary>
    void* head;

    int size;

    NewsContainer(): size(0), head(nullptr) {}

    //an alternative constructor that allows us to set the head pointer
    NewsContainer(int size, void* head): size(size), head(head){}

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
            else {
                news1.genre = NewsGenre::POLITICS;
            }

            struct tm tm = {};
            parse_date(date, tm);
            news1.publication_date = mktime(&tm);
            //this->display_article();
            this->insert(news1);
        }
    }

    void display_article(){

    }

    virtual void insert(News newNews) = 0;
    virtual void insert_at_location(News newNews, int location) = 0;
    virtual News* get_at_location(int location) = 0;

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
};
