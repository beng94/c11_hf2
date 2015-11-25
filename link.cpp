#include <curl/curl.h>

#include "link.hpp"

Link::Link (std::string url) : url{url}
{
    download_url();
}

bool Link::operator< (const Link& rhs) const
{
    return url > rhs.url;
}

//From stackoverflow
static size_t write_callback (void *contents, size_t size,
                              size_t nmemb, void* userp)
{
    size_t new_size = size * nmemb;
    ((std::string*)userp)->append((char*)contents, new_size);

    return new_size;
}

void Link::download_url () const
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &source);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
}

std::string Link::get_url () { return url; }

std::string Link::get_name () { return name; }

std::string Link::get_source () { return source; }
