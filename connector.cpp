#include "connector.hpp"
#include "link.hpp"

#include <iostream>
#include <regex>

Connector::Connector (std::string root) : root{root, ""} {}

static void trim (std::string& url)
{
    // Remove everything after '#'
    std::size_t hash_pos = url.find_first_of('#');
    if (hash_pos != std::string::npos)
    {
        url = url.substr(0, hash_pos);
    }
}

void Connector::parse_urls (const std::string& root, std::list<std::string>& list)
{
    auto i = std::begin(list);
    while (i != std::end(list))
    {
        std::string url = *i;
        trim(url);
        if (url[0] == '/')
        {
            if(url[url.length()-1] == '/')
                *i = this->root.get_url() + (url.c_str() + 1);
            else
                *i = this->root.get_url() + url.substr(1, url.length() -1);
        }
        else if (url[url.length()-1] == '/')
        {
            *i = url.substr(0, url.length() -1);
        }
        // Standalone url
        else if (std::regex_match(url, std::regex(".*:\/\/.*")))
        {
        }
        else
        {
            *i = root + '/' + url;
        }

        ++i;
    }
}

static bool is_file (const std::string& url)
{
    //It should match the file type
    return std::regex_match(url, std::regex(".*[.].*[\/].*[.](.*)"));
}

static bool is_outlink (const std::string& url, const std::string& root)
{
    return !std::regex_match(url, std::regex(root + ".*"));
}

static std::string trunc_name (const std::string& root, const std::string& name)
{
    std::regex r_root(root + "(.*)");
    std::smatch match;

    if(std::regex_match(name, match, r_root))
    {
        return match[1];
    }

    return name;
}

void Connector::foo (Link& root, const int& max_depth)
{
    depth++;

    /* Új linkek keresése .*/
    std::list<std::string> new_links = root.find_urls();
    std::cout << root.get_url() << " " << new_links.size() <<  " ";

    /* JavaScript és mailto linkek eltávolítása. */
    new_links.remove_if(
            [] (const std::string& s)
            {
                return s[0] == '#' ||
                       s.length() <= 1 ||
                       std::regex_match(s, std::regex("mailto.*"));

            }
    );
    std::cout << new_links.size() << " ";

    /* Már meglátogatott linkek eltávolítása. */
    parse_urls(root.get_url(), new_links);
    new_links.remove_if(
        [this] (const std::string& s)
        {
            return visited.find(s) != visited.end();
        }
    );
    std::cout << new_links.size() << std::endl;
    for(auto s: new_links)
    {
        std::cout << s << std::endl;
    }

    visited.insert(root.get_url());
    for (auto s: new_links)
    {
        visited.insert(s);

        if(is_file(s))
        {
            if ((flags & Connector::Flag::file) == 0) continue;

            std::cout << "file\n";
            graph.add_flag(s, NodeFlag(file));
        }
        if (is_outlink(s, this->root.get_url()))
        {
            if((flags & Connector::Flag::outlink) == 0 ) continue;

            graph.add_flag(s, NodeFlag(outlink));
        }

        graph.insert(root.get_name(), trunc_name(this->root.get_url(), s));
    }

    for(auto s: new_links)
    {
        /* Hozzáadom az új linket, ha hamis a rekurzió leállási feltétele,
         * az oldalon belüli link és nem fájl-ra mutat. */
        if (depth <= max_depth &&
            !is_outlink(s, root.get_url()) &&
            !is_file(s))
        {
            Link new_l(s, root.get_url());
            foo(new_l, max_depth);
        }
    }

    depth--;
}

/* Be lehet vele állítani, hogy a kimeneti dot fájl-ban megjelentjenek-e
 * a fájlok, illetve a kifelé mutató linkek. */
void Connector::add_output_flag (Connector::Flag f)
{
    flags |= f;
}

void Connector::discover (const int& max_depth)
{
    foo(root, max_depth);
}

void Connector::gen_dot(const std::string fname)
{
    graph.print(fname);
}
