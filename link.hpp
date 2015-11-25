#ifndef LINK_H
#define LINK_H

#include <string>

class Link
{
    private:
        std::string url;
        std::string name;

    public:
        Link () = delete;
        Link (std::string);

        bool operator< (const Link&) const;

        std::string get_url ();
        std::string get_name ();
};

#endif
