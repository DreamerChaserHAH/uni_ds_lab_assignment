//
// Created by Victor Mak on 23/02/2025.
//

#include "container/news_container.hpp"
#include "container/news.hpp"

bool News::is_greater_than(News& news, CRITERIA criteria, NewsContainer* news_container) {
    switch (criteria) {
        case GENRE:
            return news_container->get_genre_critiera_value(this) > news_container->get_genre_critiera_value(&news);
        case PUBLICATION_DATE:
            return (get_year() > news.get_year()) ? true: (get_year() == news.get_year()? get_date_in_year() > news.get_date_in_year(): false);
        case IS_TRUE_NEWS:
            return is_true > news.is_true;
        default:
            return false;
    }
}

bool News::is_lower_than(News &news, CRITERIA criteria, NewsContainer *news_container) {
    switch (criteria) {
        case GENRE:
            return news_container->get_genre_critiera_value(this) < news_container->get_genre_critiera_value(&news);
        case PUBLICATION_DATE:
            return (get_year() < news.get_year()) ? true: (get_year() == news.get_year()? get_date_in_year() < news.get_date_in_year(): false);
        case IS_TRUE_NEWS:
            return is_true < news.is_true;
        default:
            return false;
    }
}

bool News::is_equal_or_greater_than(News &news, CRITERIA criteria, NewsContainer *news_container) {
    switch (criteria) {
        case GENRE:
            return news_container->get_genre_critiera_value(this) >= news_container->get_genre_critiera_value(&news);
        case PUBLICATION_DATE:
            return (get_year() > news.get_year()) ? true: (get_year() == news.get_year() ? get_date_in_year() >= news.get_date_in_year(): false);
        case IS_TRUE_NEWS:
            return is_true >= news.is_true;
        default:
            return false;
    }
}

bool News::is_equal_or_lower_than(News &news, CRITERIA criteria, NewsContainer *news_container) {
    switch (criteria) {
        case GENRE:
            return news_container->get_genre_critiera_value(this) <= news_container->get_genre_critiera_value(&news);
        case PUBLICATION_DATE:
            return (get_year() < news.get_year()) ? true: (get_year() == news.get_year() ? get_date_in_year() <= news.get_date_in_year(): false);
        case IS_TRUE_NEWS:
            return is_true <= news.is_true;
        default:
            return false;
    }
}