#pragma once

class MyWindow : public Gtk::Window {
public:
	MyWindow();
	Gtk::Button startButton;
	Gtk::Label beginText;
	//Gtk::Box hbox;
	Gtk::Grid grid;

	void OnStartClick() {
		if (startButton.get_label() == "Begin Algorithm") {
			startButton.set_label("End Algorithm");
		} else {
			startButton.set_label("Begin Algorithm");
		}
	}
};