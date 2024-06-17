#pragma once
#include "global.h"
#include "result_screen.h"
#include "file_management.h"
#include "clusterization.h"

//Main menu of this programm
class MenuScreen : public Gtk::Window {
public:
	Gtk::Button startButton, searchButton;
	Gtk::Entry pathEntry, numberEntry;
	Gtk::Label beginText, pathText, algorithmText, archiveText, numberText, anchor;
	Gtk::CheckButton alg1But,alg2But, alg3But, arch2But, arch3But;
	Gtk::Grid grid;

	void OnStartClick() {
		working_dir = pathEntry.get_text();
		if (working_dir.size() != 0) { //failsafe for empty box
			if (working_dir[working_dir.size() - 1] != '/' && working_dir[working_dir.size() - 1] != '\\') { //failsafe for slash at the end
				working_dir = working_dir + '/';
			}
			std::string results;
			list_of_files = findAllFiles(working_dir);
			if (chosen_algorithm == 'n') {
				distributeFiles(list_of_files, working_dir);
			} else if (chosen_algorithm == 'k') {
				results = K_means_algorithm(std::stoi(numberEntry.get_text()));
			} else if (chosen_algorithm == 'h') {

			} else if (chosen_algorithm == 'd') {

			}
			if (chosen_archive == 'z') {
				archive(working_dir, "zip");
			} else if (chosen_archive == 't') {
				archive(working_dir, "tar");
			}
			list_of_files.clear(); //memory cleanup
			Gtk::Application::create("org.gtkmm.examples.base")->make_window_and_run<ResultScreen>(0, nullptr, results);
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

	MenuScreen() {
		//window customization
		set_title(u8"Мастер кластеризации файлов");
		set_default_size(300, 350);
		//widget customization
		startButton.set_label(u8"Запустить алгоритм");
		startButton.set_margin_start(50); startButton.set_margin_end(50); startButton.set_margin_top(20); startButton.set_margin_bottom(20);
		startButton.signal_clicked().connect(sigc::mem_fun(*this, &MenuScreen::OnStartClick));
		searchButton.set_label(u8"\U0001F50E"); searchButton.set_margin_start(10);
		beginText.set_text(u8"Эта программа позволит вам отсортировать и архивировать массивы файлов.\nПеред началом выберите необходимые настройки.");
		beginText.set_justify(Gtk::Justification::CENTER);
		beginText.set_margin_top(10); beginText.set_margin_bottom(10); beginText.set_margin_start(10); beginText.set_margin_end(10);
		pathText.set_text(u8"Введите путь к файлам:");
		pathText.set_margin_top(10); pathText.set_margin_bottom(10); pathText.set_margin_start(10); pathText.set_margin_end(10);
		algorithmText.set_text(u8"Выберите алгоритм кластеризации:");
		algorithmText.set_margin_top(10); algorithmText.set_margin_bottom(10); algorithmText.set_margin_start(10); algorithmText.set_margin_end(10);
		archiveText.set_text(u8"Выберите тип архивирования:");
		archiveText.set_margin_top(10); archiveText.set_margin_bottom(10); archiveText.set_margin_start(10); archiveText.set_margin_end(10);
		alg1But.set_label(u8"К-средних"); alg2But.set_label(u8"Иерархический"); alg3But.set_label(u8"DBSCAN");
		arch2But.set_label(u8"Zip архив"); arch3But.set_label(u8"Tar архив");
		alg1But.signal_toggled().connect(sigc::mem_fun(*this, &MenuScreen::OnAlg1Click));
		alg2But.signal_toggled().connect(sigc::mem_fun(*this, &MenuScreen::OnAlg2Click));
		alg3But.signal_toggled().connect(sigc::mem_fun(*this, &MenuScreen::OnAlg3Click));
		arch2But.signal_toggled().connect(sigc::mem_fun(*this, &MenuScreen::OnArch2Click));
		arch3But.signal_toggled().connect(sigc::mem_fun(*this, &MenuScreen::OnArch3Click));
		alg1But.set_margin_start(10); alg3But.set_margin_end(10);
		arch2But.set_margin_start(10); arch3But.set_margin_end(10);
		pathEntry.set_margin_end(10);
		numberText.set_text(u8"Количество кластеров для К-средних:");
		numberText.set_margin_top(10); numberText.set_margin_bottom(10); numberText.set_margin_start(10); numberText.set_margin_end(10);
		numberEntry.set_margin_end(10);
		//widget attachment
		grid.attach(anchor, 0, 1);
		grid.attach(searchButton, 0, 2);
		grid.attach(pathText, 1, 1); grid.attach(algorithmText, 1, 3); grid.attach(archiveText, 1, 5);
		grid.attach_next_to(beginText, anchor, Gtk::PositionType::TOP, 3, 1);
		grid.attach_next_to(pathEntry, pathText, Gtk::PositionType::BOTTOM, 2, 1);
		grid.attach(numberText, 1, 7); grid.attach(numberEntry, 2, 7);
		grid.attach(startButton, 1, 8);
		grid.attach(alg1But, 0, 4); grid.attach(alg2But, 1, 4); grid.attach(alg3But, 2, 4);
		grid.attach(arch2But, 0, 6); grid.attach(arch3But, 2, 6);
		set_child(grid);
	}
};