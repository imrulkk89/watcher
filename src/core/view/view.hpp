#include "tabulate/table.hpp"

using namespace std;
using namespace tabulate;

#ifndef VIEW_HPP_
#define VIEW_HPP_

// A singleton class that will be used to display the watched processes
class View
{
private:
    // private constructor
    View();

    Table createHeader();
    Table createNotification();
    Table createProcesses(vector<vector<string>>);

public:
    // static method to get the instance of the class
    static View *getInstance();

    // a drawTable method that takes a vectot of vector of strings and draws a table
    void render(vector<vector<string>>);
};

#endif /* VIEW_HPP_ */