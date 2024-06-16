#pragma once
#include "file.h"

//n = none, k = k-means, h = hierarchy, d = dbscan
char chosen_algorithm = 'n';
//n = none, z = zip, t = tar
char chosen_archive = 'n';
std::string working_dir;
std::vector <File> list_of_files;