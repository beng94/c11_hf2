#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <string>
#include <set>

#include "link.hpp"

class HTMLParser
{
    private:
        std::string source;

    public:
        HTMLParser () = delete;
        HTMLParser (std::string);

        std::set<Link> parse();
};

#endif
