//to not include iostream
#include <string>
#include <vector>
#include <filesystem>

//external libraries
#include <gtkmm.h>

//headers
#include "file.h"
#include "app.h"
#include "file_management.h"

FileManager file_manager = FileManager();
std::string working_dir;
short int chosen_algorithm = 0;
short int chosen_archive = 0;
std::vector <File> list_of_files;
std::string debug_text = "";

MyWindow::MyWindow() {
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
	debugText.set_text(debug_text);
	debugText.set_margin_top(10); debugText.set_margin_bottom(10); debugText.set_margin_start(10); debugText.set_margin_end(10);
	pathText.set_text(u8"Введите путь к файлам:");
	pathText.set_margin_top(10); pathText.set_margin_bottom(10); pathText.set_margin_start(10); pathText.set_margin_end(10);
	algorithmText.set_text(u8"Выберите алгоритм кластеризации:");
	algorithmText.set_margin_top(10); algorithmText.set_margin_bottom(10); algorithmText.set_margin_start(10); algorithmText.set_margin_end(10);
	archiveText.set_text(u8"Выберите тип архивирования:");
	archiveText.set_margin_top(10); archiveText.set_margin_bottom(10); archiveText.set_margin_start(10); archiveText.set_margin_end(10);
	alg1But.set_label(u8"К-средних"); alg2But.set_label(u8"Иерархический"); alg3But.set_label(u8"DBSCAN");
	arch1But.set_label(u8"Без архивации"); arch2But.set_label(u8"Zip архив"); arch3But.set_label(u8"Tar архив");
	alg1But.set_active(true); arch1But.set_active(true);
	alg1But.signal_toggled().connect(sigc::mem_fun(*this, &MyWindow::OnAlg1Click));
	alg2But.signal_toggled().connect(sigc::mem_fun(*this, &MyWindow::OnAlg2Click));
	alg3But.signal_toggled().connect(sigc::mem_fun(*this, &MyWindow::OnAlg3Click));
	arch1But.signal_toggled().connect(sigc::mem_fun(*this, &MyWindow::OnArch1Click));
	arch2But.signal_toggled().connect(sigc::mem_fun(*this, &MyWindow::OnArch2Click));
	arch3But.signal_toggled().connect(sigc::mem_fun(*this, &MyWindow::OnArch3Click));
	alg1But.set_margin_start(10); alg3But.set_margin_end(10);
	arch1But.set_margin_start(10); arch3But.set_margin_end(10);
	//widget attachment
	grid.attach(beginText, 1, 0); grid.attach(pathText, 1, 1); grid.attach(algorithmText, 1, 3); grid.attach(archiveText, 1, 5);
	grid.attach(startButton, 1, 7);
	grid.attach(pathEntry, 1, 2);
	grid.attach(alg1But, 0, 4); grid.attach(alg2But, 1, 4); grid.attach(alg3But, 2, 4);
	grid.attach(arch1But, 0, 6); grid.attach(arch2But, 1, 6); grid.attach(arch3But, 2, 6);
	grid.attach(debugText, 1, 8);
	set_child(grid);
}

void MyWindow::OnStartClick() {
	working_dir = pathEntry.get_text();
	if (working_dir[working_dir.size() - 1] != '/') {
		working_dir = working_dir + '/';
	}
	list_of_files = file_manager.findAllFiles(working_dir);
	file_manager.distributeFiles(list_of_files, working_dir);
}

void MyWindow::OnAlg1Click() { if (alg1But.get_active()) { chosen_algorithm = 0; alg2But.set_active(false); alg3But.set_active(false); } }
void MyWindow::OnAlg2Click() { if (alg2But.get_active()) { chosen_algorithm = 1; alg1But.set_active(false); alg3But.set_active(false); } }
void MyWindow::OnAlg3Click() { if (alg3But.get_active()) { chosen_algorithm = 2; alg1But.set_active(false); alg2But.set_active(false); } }

void MyWindow::OnArch1Click() { if (arch1But.get_active()) { chosen_archive = 0; arch2But.set_active(false); arch3But.set_active(false); } }
void MyWindow::OnArch2Click() { if (arch2But.get_active()) { chosen_archive = 1; arch1But.set_active(false); arch3But.set_active(false); } }
void MyWindow::OnArch3Click() { if (arch3But.get_active()) { chosen_archive = 2; arch1But.set_active(false); arch2But.set_active(false); } }

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.gtkmm.examples.base");
    return app->make_window_and_run<MyWindow>(argc, argv);
}