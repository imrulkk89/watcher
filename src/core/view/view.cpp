#include "view.hpp"

View:: View()
{
    // constructor
}

// implementation of the singleton class
View *View::getInstance()
{
    static View* instance = new View();
    return instance;
}

Table View::createHeader()
{
    Table header;
    // add a row to the header table
    header.add_row({"Watcher 👀"});

    // set the header table style
    header.format()
        .font_align(FontAlign::center)
        .font_style({FontStyle::bold})
        .border_top("")
        .border_bottom("")
        .border_left("")
        .border_right("")
        .corner("")
        .background_color(Color::blue)
        .font_color(Color::white)
        .font_style({FontStyle::bold});

    return header;
}

Table View::createNotification()
{
    Table notification;
    // add a row to the header table
    notification.add_row({"config file directory","<project_root>/config/watchdog.json"});
    notification.add_row({"log files directory","<project_root>/logs/*"});

    // set the header table style
    notification.format()
        .border_top("")
        .border_bottom("")
        .border_left("")
        .border_right("")
        .corner("");
    
    // make the first column left aligned and bold
    notification.column(0).format()
        .font_align(FontAlign::left)
        .font_style({FontStyle::bold});
    
    // make the second column right aligned
    notification.column(1).format()
        .font_align(FontAlign::right)
        .font_style({FontStyle::italic});

    return notification;
}

Table View::createProcesses(vector<vector<string>> tableData)
{
    cout << "DEBUG: createProcesses called" << endl;
    // create a table
    Table processes;

    // format table
    processes.format()
        .border_top("")
        .border_bottom("")
        .border_left("")
        .border_right("")
        .font_align(FontAlign::center)
        .corner("");

    // add column headers
    processes.add_row({"Process Name", "PID", "MEM(kb)", "CPU(%)", "Status"});

    // format the first row background color to green
    processes[0].format()
        .font_color(Color::white)
        .font_background_color(Color::green)
        .font_align(FontAlign::center);

    // loop through process names
    for (int i = 0; i < tableData.size(); i++)
    {
        // add row to table
        processes.add_row({tableData[i][0], tableData[i][1], tableData[i][2], tableData[i][3], tableData[i][4]});
    }

    return processes;
}

void View::render(vector<vector<string>> tableData)
{
    Table viewport;

    viewport.add_row({this->createHeader()});
    viewport.add_row({this->createProcesses(tableData)});
    viewport.add_row({this->createNotification()});

    viewport.format()
        .font_style({FontStyle::bold})
        .border_top("")
        .border_bottom("")
        .border_left("")
        .border_right("")
        .corner("")
        .font_align(FontAlign::center);

    // make the first row background color blue
    viewport[0].format().font_color(Color::white).font_background_color(Color::blue).font_align(FontAlign::center);

    // make the last row background color red
    viewport[2].format().font_color(Color::white).font_background_color(Color::red).font_align(FontAlign::center);


// if system is linux, clear the screen
#ifdef __linux__
    system("clear");
#endif
#ifdef __APPLE__
    system("clear");
#endif
#ifdef _WIN32
    system("cls");
#endif

    // print the processes table
    std::cout << viewport << std::endl;
}