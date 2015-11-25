#include "link.hpp"

Link::Link (std::string url) : url{url} {}

std::string Link::get_url () { return url; }

std::string Link::get_name () { return name; }
