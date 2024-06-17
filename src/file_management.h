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

void writeToDB(std::string insert) {
	sqlite3* database;
	sqlite3_open("C:/Users/hp/Desktop/Projects VS/ClusterApp/src/SQLite DB.db", &database);
	std::string command = "CREATE TABLE IF NOT EXISTS PREDICTIONS("
		"NUMOFFILES INT NOT NULL, "
		"NUMOFCLUSTERS INT NOT NULL, "
		"CENTERSIZE CHAR(50), "
		"CENTEREXT CHAR(50) );";
	char* error;
	sqlite3_exec(database, command.c_str(), NULL, 0, &error);
	insert = "INSERT INTO PREDICTION (NUMOFFILES, NUMOFCLUSTERS, CENTERSIZE, CENTEREXT) VALUES(" + insert + ");";
	sqlite3_exec(database, insert.c_str(), NULL, 0, &error);
	sqlite3_close(database);
}

void archive(std::string workdir, std::string archive_type) {
	for (const auto& entry : std::filesystem::directory_iterator(workdir)) {
		rename(entry.path().string().c_str(), (entry.path().string() + "." + archive_type).c_str());
	}
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