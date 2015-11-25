#include <string>

class Link
{
    private:
        std::string url;
        std::string name;

    public:
        Link () = delete;
        Link (std::string);

        std::string get_url ();
        std::string get_name ();
};
