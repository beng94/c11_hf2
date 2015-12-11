#ifndef LINK_H
#define LINK_H

#include <string>
#include <list>

class Link
{
    private:
        std::string url;
        std::string source = "";
        std::string name = "";

    public:
        Link () = delete;
        Link (std::string&, std::string);

        void download_url ();
        std::list<std::string> find_urls();

        std::string get_url () const;
        std::string get_source () const;
        std::string get_name () const;
};

#endif
