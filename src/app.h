#pragma once

class MyWindow : public Gtk::Window {
public:
	MyWindow();
	Gtk::Button startButton;
	Gtk::Entry pathEntry;
	Gtk::Label beginText, pathText, algorithmText, archiveText, debugText;
	Gtk::CheckButton alg1But, alg2But, alg3But, arch1But, arch2But, arch3But;
	Gtk::Grid grid;

	void OnStartClick();
	void OnAlg1Click(); void OnAlg2Click(); void OnAlg3Click();
	void OnArch1Click(); void OnArch2Click(); void OnArch3Click();
};