#pragma once
#include "file.h"

void moveToDirectory(std::string workdir, std::string file_name, std::string folder) {
	rename((workdir + file_name).c_str(), (workdir + folder + "/" + file_name).c_str());
}

void makeDirectory(std::string workdir, std::string folder_name) {
	std::filesystem::create_directory(workdir + folder_name);
}

std::vector<File> findAllFiles(std::string workdir) {
	std::vector<File> list_of_files;
	//find all files in a given directory
	for (const auto& entry : std::filesystem::directory_iterator(workdir)) {
		File file;
		file.name = "";
		file.extension = "";
		bool name_to_extension = true;
		//parse path to get file name and extension
		for (int i = workdir.size(); i != entry.path().string().size(); i++) {
			if (entry.path().string()[i] != '.') {
				if (name_to_extension) {
					file.name += entry.path().string()[i];
				} else {
					file.extension += entry.path().string()[i];
				}
			} else {
				name_to_extension = false;
			}
		}
		file.size = std::filesystem::file_size(entry.path());
		list_of_files.push_back(file);
	}
	return list_of_files;
}

//if none algorithms are selected
void distributeFiles(std::vector<File> list_of_files, std::string workdir) {
	//create all necesary directories
	for (int i = 0; i != list_of_files.size(); i++) {
		makeDirectory(workdir, list_of_files[i].extension);
	}
	//move files there depending on their extension
	for (int i = 0; i != list_of_files.size(); i++) {
		moveToDirectory(workdir, list_of_files[i].name + "." + list_of_files[i].extension, list_of_files[i].extension);
	}
}