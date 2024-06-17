//to not include iostream
#include <string>
#include <vector>
#include <filesystem>
#include <thread>

//external libraries
#include <gtkmm.h>
#include <sqlite3.h>
#include <zlib.h>

//headers
#include "result_screen.h"
#include "app.h"
#include "global.h"
#include "clusterization.h"
#include "file_management.h"

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.gtkmm.examples.base");
    return app->make_window_and_run<MenuScreen>(argc, argv);
}