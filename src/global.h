#pragma once
#include "file_management.h"

//n = none, k = k-means, h = hierarchy, d = dbscan
char chosen_algorithm = 'n';
//n = none, z = zip, t = tar
char chosen_archive = 'n';
FileManager file_manager = FileManager();
std::string working_dir;
std::vector <File> list_of_files;