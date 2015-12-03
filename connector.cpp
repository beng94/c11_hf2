#include "connector.hpp"
#include "link.hpp"

#include <iostream>
#include <regex>

Connector::Connector (std::string root) : root{root} {}

static bool mailto (const std::string& url)
{
    std::regex r_mail("mailto.*");
    return std::regex_match(url, r_mail);
}

void Connector::parse_urls (const std::string& root, std::list<std::string>& list)
{
    auto i = std::begin(list);
    while (i != std::end(list))
    {
        std::string url = *i;
        if (url[0] == '#' || url.length() == 1)
        {
            i = list.erase(i);
            continue;
        }
        else if (url[0] == '/')
        {
            if(url[url.length()-1] == '/')
                *i = this->root.get_url() + (url.c_str() + 1);
            else
                *i = this->root.get_url() + url.substr(1, url.length() -1);
        }
            //*i = this->root.get_url() + (url.c_str() + 1) + '/';
        else if (mailto(url))
        {
            i = list.erase(i);
            continue;
        }
        else if (url[url.length()-1] == '/')
        {
            *i = url.substr(0, url.length() -1);
        }
        else if (std::regex_match(url, std::regex(".*:\/\/.*")))
        {
        }
        else
        {
            *i = root + url;
        }

        ++i;
    }
}

static bool same_page (const std::string& link, const std::string& root)
{
    std::regex r(root + ".*");
    return std::regex_match(link, r);
}

void Connector::foo (Link& root, const int& max_depth)
{
    depth++;
    std::cout << depth << std::endl;

    std::list<std::string> new_links = root.find_urls();
    std::cout << root.get_url() << " " << new_links.size() <<  " ";
    parse_urls(root.get_url(), new_links);
    std::cout << new_links.size() << " ";
    //TODO: remove multiple itemsi
    new_links.remove_if(
        [this] (const std::string& s)
        {
            // remove links, that we've alredy visited
            return visited.find(s) != visited.end();
        }
    );
    std::cout << new_links.size() << std::endl;
    getchar();

    visited.insert(root.get_url());
    for (auto s: new_links)
    {
        visited.insert(s);
        graph.insert(root.get_url(), s);
        //std::cout << s << std::endl;
    }

    for(auto s: new_links)
    {
        if (depth <= max_depth && same_page(s, root.get_url()))
        {
            Link new_l(s);
            foo(new_l, max_depth);
        }
    }

    depth--;
}

void Connector::discover (const int& max_depth)
{
    foo(root, max_depth);
}

void Connector::gen_dot(const std::string fname)
{
    graph.print(fname);
}
