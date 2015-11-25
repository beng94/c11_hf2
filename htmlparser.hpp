#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <string>
#include <queue>

#include "link.hpp"

class HTMLParser
{
    private:
        std::string url;

    public:
        HTMLParser () = delete;
        HTMLParser (std::string);

        std::queue<Link> parse();
};

#endif
