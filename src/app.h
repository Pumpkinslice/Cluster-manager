#pragma once
#include "global.h"

class MyWindow : public Gtk::Window {
public:
	Gtk::Button startButton;
	Gtk::Entry pathEntry;
	Gtk::Label beginText, pathText, algorithmText, archiveText, debugText;
	Gtk::CheckButton alg1But,alg2But, alg3But, arch2But, arch3But;
	Gtk::Grid grid;

	void OnStartClick() {
		working_dir = pathEntry.get_text();
		if (working_dir.size() != 0) { //failsafe for empty box
			if (working_dir[working_dir.size() - 1] != '/' && working_dir[working_dir.size() - 1] != '\\') { //failsafe for slash at the end
				working_dir = working_dir + '/';
			}
			list_of_files = file_manager.findAllFiles(working_dir);
			file_manager.distributeFiles(list_of_files, working_dir);
		}
	}

	void OnAlg1Click() {
		if (alg1But.get_active()) { 
			chosen_algorithm = 'k';
			alg2But.set_active(false); 
			alg3But.set_active(false); 
		} else if (!alg1But.get_active() && !alg2But.get_active() && !alg3But.get_active()) {
			chosen_algorithm = 'n';
		}
	}

	void OnAlg2Click() {
		if (alg2But.get_active()) {
			chosen_algorithm = 'h';
			alg1But.set_active(false);
			alg3But.set_active(false);
		}
		else if (!alg1But.get_active() && !alg2But.get_active() && !alg3But.get_active()) {
			chosen_algorithm = 'n';
		}
	}

	void OnAlg3Click() {
		if (alg3But.get_active()) {
			chosen_algorithm = 'd';
			alg2But.set_active(false);
			alg1But.set_active(false);
		}
		else if (!alg1But.get_active() && !alg2But.get_active() && !alg3But.get_active()) {
			chosen_algorithm = 'n';
		}
	}

	void OnArch2Click() { 
		if (arch2But.get_active()) { 
			chosen_archive = 'z';
			arch3But.set_active(false); 
		} else if (!arch2But.get_active() && !arch3But.get_active()) {
			chosen_archive = 'n';
		}
	}

	void OnArch3Click() {
		if (arch3But.get_active()) {
			chosen_archive = 't';
			arch2But.set_active(false);
		} else if (!arch2But.get_active() && !arch3But.get_active()) {
			chosen_archive = 'n';
		}
	}

	void debug_print(std::string text) {
		debugText.set_text(text);
	}

	MyWindow() {
		//window customization
		set_title(u8"Мастер кластеризации файлов");
		set_default_size(500, 350);
		//widget customization
		startButton.set_label(u8"Запустить алгоритм");
		startButton.set_margin_start(50); startButton.set_margin_end(50); startButton.set_margin_top(20);
		startButton.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::OnStartClick));
		beginText.set_text(u8"Эта программа позволит вам отсортировать и архивировтаь массивы файлов.\nПеред началом выберите необходимые настройки.");
		beginText.set_justify(Gtk::Justification::CENTER);
		beginText.set_margin_top(10); beginText.set_margin_bottom(10); beginText.set_margin_start(10); beginText.set_margin_end(10);
		debugText.set_margin_top(10); debugText.set_margin_bottom(10); debugText.set_margin_start(10); debugText.set_margin_end(10);
		pathText.set_text(u8"Введите путь к файлам:");
		pathText.set_margin_top(10); pathText.set_margin_bottom(10); pathText.set_margin_start(10); pathText.set_margin_end(10);
		algorithmText.set_text(u8"Выберите алгоритм кластеризации:");
		algorithmText.set_margin_top(10); algorithmText.set_margin_bottom(10); algorithmText.set_margin_start(10); algorithmText.set_margin_end(10);
		archiveText.set_text(u8"Выберите тип архивирования:");
		archiveText.set_margin_top(10); archiveText.set_margin_bottom(10); archiveText.set_margin_start(10); archiveText.set_margin_end(10);
		alg1But.set_label(u8"К-средних"); alg2But.set_label(u8"Иерархический"); alg3But.set_label(u8"DBSCAN");
		arch2But.set_label(u8"Zip архив"); arch3But.set_label(u8"Tar архив");
		alg1But.signal_toggled().connect(sigc::mem_fun(*this, &MyWindow::OnAlg1Click));
		alg2But.signal_toggled().connect(sigc::mem_fun(*this, &MyWindow::OnAlg2Click));
		alg3But.signal_toggled().connect(sigc::mem_fun(*this, &MyWindow::OnAlg3Click));
		arch2But.signal_toggled().connect(sigc::mem_fun(*this, &MyWindow::OnArch2Click));
		arch3But.signal_toggled().connect(sigc::mem_fun(*this, &MyWindow::OnArch3Click));
		alg1But.set_margin_start(10); alg3But.set_margin_end(10);
		arch2But.set_margin_start(10); arch3But.set_margin_end(10);
		//widget attachment
		grid.attach(beginText, 1, 0); grid.attach(pathText, 1, 1); grid.attach(algorithmText, 1, 3); grid.attach(archiveText, 1, 5);
		grid.attach(startButton, 1, 7);
		grid.attach(pathEntry, 1, 2);
		grid.attach(alg1But, 0, 4); grid.attach(alg2But, 1, 4); grid.attach(alg3But, 2, 4);
		grid.attach(arch2But, 0, 6); grid.attach(arch3But, 2, 6);
		grid.attach(debugText, 1, 8);
		set_child(grid);
	}
};