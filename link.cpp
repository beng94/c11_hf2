#include <curl/curl.h>
#include <regex>
#include <iostream>

#include "link.hpp"

Link::Link (std::string url) : url{url}
{
    download_url();
}

//From stackoverflow
static size_t write_callback (void *contents, size_t size,
                              size_t nmemb, void* userp)
{
    size_t new_size = size * nmemb;
    ((std::string*)userp)->append((char*)contents, new_size);

    return new_size;
}

void Link::download_url ()
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &source);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    /*std::regex r_nav("(<nav.*>)");
    std::smatch m;
    while (std::regex_search(source, m, r_nav))
    {
        std::regex r_end("(<\/nav>)");
        std::smatch b;
        std::regex_search(source, b, r_end);
        source = source.substr(0, m.position()) +
                 source.substr(b.position() + b.length(), source.length() - b.position());
        //std::cout << m.str() << std::endl;
        //std::cout << b.str() << std::endl;
        //getchar();
        //std::cout << source << std::endl;
        //getchar();
    }*/
    //std::cout << source << std::endl;
    //getchar();
}

std::list<std::string> Link::find_urls ()
{
    std::list<std::string> new_links;

    std::regex r ("<\\s*A\\s+[^>]*href\\s*=\\s*\"([^\"]*)", std::regex::icase);
    const std::sregex_token_iterator end;
    for(std::sregex_token_iterator i(source.cbegin(), source.cend(), r, 1);
        i != end; ++i)
    {
        if(std::find(new_links.begin(), new_links.end(), *i) == new_links.end())
            new_links.push_front(*i);
    }

    return new_links;
}

std::string Link::get_url () const { return url; }

std::string Link::get_source ()
{
    return source;
}
