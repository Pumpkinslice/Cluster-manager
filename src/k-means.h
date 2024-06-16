#pragma once
#include "global.h"
#include "math_functions.h"
#include "file_management.h"

struct cluster {
	int center_ext;
	unsigned int center_size;
	std::vector <File> files;
};

unsigned int max_size = 0;
unsigned int min_size = 4294967295;
std::vector <std::string> extensions;
std::vector <cluster> clusters;

void find_size_ranges() {
	for (int i = 0; i != list_of_files.size(); i++) {
		if (list_of_files[i].size > max_size) { max_size = list_of_files[i].size; }
		if (list_of_files[i].size < min_size) { min_size = list_of_files[i].size; }
	}
}

void find_ext_ranges() {
	for (int i = 0; i != list_of_files.size(); i++) {
		bool exist = false;
		for (int j = 0; j != extensions.size(); j++) {
			if (extensions[j] == list_of_files[i].extension) {
				exist = true;
				break;
			}
		}
		if (!exist) {
			extensions.push_back(list_of_files[i].extension);
		}
	}
}

//convert extension string into int
int ext_to_int(std::string ext) {
	for (int i = 0; i != extensions.size(); i++) {
		if (extensions[i] == ext) { return i; }
	}
}

//find minimum distance
int min_distance(std::vector <double> distances) {
	int min_dist = 0;
	for (int i = 0; i != distances.size(); i++) {
		if (distances[i] < distances[min_dist]) { min_dist = i; }
	}
	return min_dist;
}

//calculate distance
double distance(File object, cluster center) {
	long int size_diff, ext_diff;
	if (object.size > center.center_size) {
		size_diff = object.size - center.center_size;
	} else {
		size_diff = center.center_size - object.size;
	}
	if (ext_to_int(object.extension) > center.center_ext) {
		ext_diff = ext_to_int(object.extension) - center.center_ext;
	} else {
		ext_diff = center.center_ext - ext_to_int(object.extension);
	}
	return sqrt((size_diff * size_diff) + (ext_diff * ext_diff));
}

std::string print_clusters() {
	std::string output = u8"Созданные кластеры:\n";
	for (int i = 0; i != clusters.size(); i++) {
		output = output + u8"Координаты: X=" + std::to_string(clusters[i].center_ext) + u8" Y=" + std::to_string(clusters[i].center_size) + u8"\nФайлы кластера:\n";
		for (int j = 0; j != clusters[i].files.size(); j++) {
			output = output + clusters[i].files[j].name + u8"\n";
		}
		output = output + u8"\n";
	}
	//cleanup at the end of execution
	max_size = 0; min_size = 4294967295; extensions.clear(); clusters.clear();
	return output;
}

bool repetition(unsigned int target, std::vector <unsigned int> store) {
	bool contains = false;
	//check for repeating actions
	for (int i = 0; i != store.size(); i++) {
		if (target == store[i]) {
			contains = true;
			break;
		}
	}
	if (contains) {
		//check for empty clusters
		for (int i = 0; i != clusters.size(); i++) {
			if (clusters[i].files.size() == 0) {
				contains = false;
				break;
			}
		}
	}
	return contains;
}

//full iteration cycle, returns difference between centers
unsigned int iteration() {
	for (int i = 0; i != clusters.size(); i++) {
		clusters[i].files.clear();
	}
	//E-step, calculate distances
	for (int i = 0; i != list_of_files.size(); i++) {
		std::vector <double> distances;
		for (int j = 0; j != clusters.size(); j++) {
			distances.push_back(distance(list_of_files[i], clusters[j]));
		}
		clusters[min_distance(distances)].files.push_back(list_of_files[i]);
	}
	//tracks difference in center's positions
	unsigned int difference = 0;
	//M-step, adjust centers
	for (int i = 0; i != clusters.size(); i++) {
		if (clusters[i].files.size() != 0) {
			long int mean_size = 0;
			long int mean_ext = 0;
			for (int j = 0; j != clusters[i].files.size(); j++) {
				mean_size = mean_size + clusters[i].files[j].size;
				mean_ext = mean_ext + ext_to_int(clusters[i].files[j].extension);
			}
			mean_size = mean_size / (clusters[i].files.size());
			mean_ext = round_divide(mean_ext, clusters[i].files.size());
			if (clusters[i].center_size > mean_size) {
				difference = difference + clusters[i].center_size - mean_size;
			} else {
				difference = difference + mean_size - clusters[i].center_size;
			}
			if (clusters[i].center_size > mean_ext) {
				difference = difference + clusters[i].center_size - mean_ext;
			}
			else {
				difference = difference + mean_ext - clusters[i].center_size;
			}
			clusters[i].center_size = mean_size;
			clusters[i].center_ext = mean_ext;
		}
	}
	return difference;
}

//Algorithm starts here
std::string K_means_algorithm() {
	//set random centers
	std::thread thread1(find_size_ranges);
	std::thread thread2(find_ext_ranges);
	thread1.join();
	thread2.join();
	int numClusters = 3;
	for (int i = 0; i != numClusters; i++) {
		cluster newCluster;
		newCluster.center_ext = randint(0, extensions.size() - 1);
		newCluster.center_size = randint(min_size, max_size);
		clusters.push_back(newCluster);
	}
	//start iterations
	iteration();
	unsigned short int iteration_counter = 1;
	std::vector <unsigned int> diff_store;
	while (true) {
		unsigned int diff = iteration();
		iteration_counter++;
		if (diff == 0 || repetition(diff, diff_store)) { 
			break; 
		} else {
			diff_store.push_back(diff);
		}
	}
	//reallocate files
	for (int i = 0; i != numClusters; i++) {
		makeDirectory(working_dir, "Cluster" + std::to_string(i + 1));
		for (int j = 0; j != clusters[i].files.size(); j++) {
			moveToDirectory(working_dir, clusters[i].files[j].name + "." + clusters[i].files[j].extension, "Cluster" + std::to_string(i + 1));
		}
	}
	//returns the results for visualisation
	return std::to_string(iteration_counter) + u8" итераций.\n" + print_clusters();
}