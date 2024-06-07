//to not include iostream
#include <string>
#include <vector>
#include <filesystem>

//external libraries
#include <gtkmm.h>
#include <sqlite3.h>
#include <zlib.h>

//headers
#include "app.h"
#include "global.h"

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.gtkmm.examples.base");
    return app->make_window_and_run<MyWindow>(argc, argv);
}