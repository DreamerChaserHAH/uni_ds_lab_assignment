//
// Created by Victor Mak on 18/02/2025.
//

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>

bool is_normal_character(const char& s) {
    return !(s >= 'A' && s <= 'Z') && !(s >= 'a' && s <= 'z') && !(s >= '0' && s <= '9') && s != ' ' && s != '\'' && s != '(' && s != ')' && s != ',' && s != '.' && s != ':' && s != ';' && s != '?' && s != '!';
}

std::string remove_whitespace(const std::string& input) {
    std::string result = input;
    result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
    return result;
}

bool is_unwanted_char(char c) {
    // Define the characters you want to remove
    return c == '\"';
}

std::string remove_unwanted_chars(const std::string& input) {
    std::string result = input;
    result.erase(std::remove_if(result.begin(), result.end(), is_unwanted_char), result.end());
    return result;
}

std::string remove_random_character(const std::string& input) {
    std::string result = input;
    result.erase(std::remove_if(result.begin(), result.end(), is_normal_character), result.end());
    return result;
}

bool parse_date(const std::string& date_str) {
    struct tm tm = {};
    std::istringstream ss(date_str);
    ss >> std::get_time(&tm, "%b %d, %Y");
    if (ss.fail()) {
        std::istringstream ss2(date_str);
        ss2 >> std::get_time(&tm, "%d-%b-%y");
        if (ss2.fail()) {
            std::cerr << "Failed to parse date: " << date_str << std::endl;
            return false;
        }
        return true;
    }
    return true;
}


std::string trim(const std::string& input) {
    auto start = input.begin();
    while (start != input.end() && std::isspace(*start)) {
        start++;
    }

    auto end = input.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return {start, end + 1};
}

void clean_csv(std::string input_file_path, std::string output_file_path) {
    std::ifstream target_file(input_file_path);
    std::ofstream output_file(output_file_path);

    if (!target_file.is_open() || !output_file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }

    int day, year;
    std::string month;
    std::string previous_date;

    std::string line, full_line;
    // Write the header to the new CSV file
    output_file << "Title,Text,Subject,Date\n";

    // Read and ignore the header from the original file
    getline(target_file, line);
    while (getline(target_file, line))
    {

        full_line = line;
        // Check if we need to read more lines to complete the entry
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
        title = remove_random_character(remove_unwanted_chars(trim(title)));

        // Read text
        getline(ss, text, ',');
        if (text.front() == '\"') {
            std::string temp;
            while (text.back() != '\"') {
                getline(ss, temp, ',');
                text += "," + temp;
            }
        }
        text = remove_random_character(remove_unwanted_chars(trim(text)));
        // Read subject
        getline(ss, subject, ',');

        subject = remove_unwanted_chars(trim(subject));
        if (subject != "worldnews" && subject != "politicsNews" && subject != "others") {
            if (subject == "left-news" || subject == "politics" || subject == "Government News") {
                subject = "politicsNews";
            }
            else if (subject == "Middle-east" || subject == "US_News") {
                subject = "worldnews";
            }else {
                subject = "others";
            }
        }
        // Read date
        getline(ss, date, '\n');
        date = remove_unwanted_chars(trim(date));

        if (title.empty() || text.empty() || subject.empty() || date.empty()) {
            continue;
        }

        bool parse_date_success = parse_date(date);
        if (!parse_date_success) {
            //parsing date failed
            date = previous_date;
        }

        previous_date = date;
        // Write cleaned data to new CSV file
        output_file << "\"" << title << "\",\"" << text << "\",\"" << subject << "\",\"" << date << "\"\n";

        // Print to console (optional)
        //std::cout << newTitle << "\t" << newText << "\t" << subject << "\t" << newDate << std::endl;
    }

    // Close files
    target_file.close();
    output_file.close();
}

int main() {
    std::cout << "cleaning true file...\n";
    clean_csv("../data/uncleaned/true.csv", "../data/cleaned/true.csv");
    std::cout << "cleaning false file...\n";
    clean_csv("../data/uncleaned/fake.csv", "../data/cleaned/fake.csv");
    return 0;
}
