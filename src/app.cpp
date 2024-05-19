#include <iostream>
#include <gtkmm.h>
#include "app.h"

MyWindow::MyWindow() {
	set_title("File clusterization master");
	set_default_size(700, 500);
	startButton.set_label("Begin Algorithm");
	//startButton.set_margin_top(440); startButton.set_margin_bottom(10);
	startButton.set_margin_start(300); startButton.set_margin_end(300);
	startButton.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::OnStartClick));
	beginText.set_text("This programm allows to automatically sort and cluster large quantities of files.\nBefore starting the algorithm, choose required settings.");
	beginText.set_margin_top(10); beginText.set_margin_bottom(10);
	beginText.set_margin_start(10); beginText.set_margin_end(100);
	grid.attach(beginText, 0, 0);
	grid.attach(startButton, 0, 4);
	set_child(grid);
}

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create("org.gtkmm.examples.base");
  return app->make_window_and_run<MyWindow>(argc, argv);
}