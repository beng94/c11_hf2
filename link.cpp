#include "link.hpp"

Link::Link (std::string url) : url{url} {}

bool Link::operator< (const Link& rhs) const
{
    return url > rhs.url;
}

std::string Link::get_url () { return url; }

std::string Link::get_name () { return name; }
