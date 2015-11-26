#include <regex>
#include <iostream>

#include "htmlparser.hpp"

HTMLParser::HTMLParser (std::string source) : source{source} {}

std::set<Link> HTMLParser::parse ()
{
    std::set<Link> new_links;

    std::regex r ("<\\s*A\\s+[^>]*href\\s*=\\s*\"(http[^\"]*)\"\\s", std::regex::icase);
    const std::sregex_token_iterator end;
    for(std::sregex_token_iterator i(source.cbegin(), source.cend(), r, 1);
        i != end; ++i)
    {
        Link new_l(*i);
        new_links.insert(new_l);
    }

    return new_links;
}
