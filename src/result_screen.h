#pragma once

//Shows the results of a chosen algorithm
class ResultScreen : public Gtk::Window {
public:
	Gtk::Label resultText;
	Gtk::Button closeButton;
	Gtk::Grid grid;

	void OnClickClose() {
		this->close();
	}

	ResultScreen(std::string result) {
		//window customization
		set_title(u8"Результаты");
		set_default_size(220, 100);
		//widget customization
		closeButton.set_label(u8"Закончить");
		closeButton.set_margin_start(50); closeButton.set_margin_end(50); closeButton.set_margin_top(20); closeButton.set_margin_bottom(20);
		closeButton.signal_clicked().connect(sigc::mem_fun(*this, &ResultScreen::OnClickClose));
		resultText.set_text(u8"" + result);
		resultText.set_margin_top(10); resultText.set_margin_bottom(10); resultText.set_margin_start(10); resultText.set_margin_end(10);
		//widget attachment
		grid.attach(resultText, 0, 0);
		grid.attach(closeButton, 0, 1);
		set_child(grid);
	}
};