#include <string>

class Connector
{
    private:
        std::string root;

    public:
        Connector () = delete;
        Connector (std::string);

        void discover (int);
        void display ();
};
