#include <iostream>
#include <random>//Mersenne Twister
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <tbb/tbb.h>
#include <ctime>
#include <cstdlib>
#include "csv_data.h"
#include "name_grad.cpp"
#include "grad_name.cpp"

#include "sort.h"

void ArgumentsI(char *argv[]);//this is where the random numbers sort will be placed at
void ArgumentsA(char *argv[]);//this is for the file reading
void Arguments();
void MersenneTwister(int Array2[], int size);
template <typename t>
void writer(char* argv[], t Sorted[], int size);
void writerNum(char *argv[], int Unsortd[], int Sorted[], int size);
template <typename t>
void csvWriter(char *argv[], t data, int size);
template <typename t>
void mergeSort(t in[], t out[], int n);

int main(int argc, char *argv[]) {
	if (argv[2][1] == 'i')
		ArgumentsI(argv);

	else if (argv[2][1] == 'a')
		ArgumentsA(argv);

	else
		Arguments();
}

/* CSV Parser by Nathan Teeter
 *
 * "She may not look like much, but she's got it where it counts, kid.
 * I've added some special modifications myself.
 * But we're a little rushed, so if you'll just get on-board, we'll get outta here."
 * 																- Han Solo (0 BBY)
 */
template <typename t>
std::vector <t> csvParser(const std::string fileName) {
	//local vars
	std::string temp;
	std::string temp2;
	int line = 0;

	//create arr
	std::vector <t> data;

	std::fstream file;
	file.open(fileName);

	if (file.is_open()) {
		//read from the file

		//ignore the first line
		file.ignore(200, '\n');

		while (!file.eof()) {
			line++;
//        	std::cout << "\nLine: " << line;
			//create new csv_data obj of the type specified
			t d;

			//trash
			getline(file, temp, '"');

			//get value
			getline(file, temp, '"');
			d.setName(temp);

			//trash comma
			getline(file, temp, ',');

			//get value
			getline(file, temp, ',');
			d.setDonorStatus(temp);

			//trash
			getline(file, temp, ',');
			if (temp.empty()) {
				getline(file, temp, '\n');
			} else {
				//parse date
				temp.erase(0, 1);
				temp2 = temp;

				getline(file, temp, '"');
				d.setGradDate(temp2 + "," + temp);

				//trash
				getline(file, temp, ',');
				//get inst
				getline(file, temp, '\n');
				d.setInstitution(temp);
			}

			data.push_back(d);
		}
	} else {
		std::cout << "\nThere was an error opening " << fileName;
	}

	return data;
}


/*
 * Merge Sort implementation
 * Params:
 *      in - array read in
 *      out - array to be outputted
 *      len - length of arrays
 *      threads - number of threads
 */
template <typename t>
void mergeSort(t in[], t out[], int len, int threads) {
	// Set number of threads
	tbb::task_scheduler_init init(threads);
	//start the clock
	tbb::tick_count t0 = tbb::tick_count::now();

	MergeSort(in, out, len);

	//end the clock
	tbb::tick_count t1 = tbb::tick_count::now();

	double time = (t1 - t0).seconds();

	if (threads > 1) {
		std::cout << "Time: " << time << " with " << threads << " threads\n";
	} else {
		std::cout << "Time: " << time << " with " << threads << " thread\n";
	}

}

//random number sorter
void ArgumentsI(char *argv[])
{
	int cores = std::stoi(argv[1]);
	int size = std::stoi(argv[3]);

	int *unsortedArray = new int[size];
	int *arrayToSort = new int[size];
	MersenneTwister(unsortedArray, size);


	mergeSort(unsortedArray, arrayToSort, size, cores);

	//
	writerNum(argv, unsortedArray, arrayToSort, size);
	//
}

//file sorter
void ArgumentsA(char *argv[]) {
	int cores = std::stoi(argv[1]);

	if (argv[3][1] == 'n') {
		//mergeSort(unsortedArrayNames, arrayToSortNames, cores);
		//CSV parser
		std::vector <name_grad> in = csvParser <name_grad> (argv[4]);
		name_grad out[in.size()];

		mergeSort(in.data(), out, in.size(), cores);
		csvWriter(argv, out, in.size());
	} else {
		//mergeSort(unsortedArrayNames, arrayToSortNames, cores);
		//CSV parser
		std::vector <grad_name> in = csvParser <grad_name> (argv[4]);
		grad_name out[in.size()];

		mergeSort(in.data(), out, in.size(), cores);
		csvWriter(argv, out, in.size());
	}
}

void Arguments()
{
	std::cout << "Usage: " << "\n\t<cores> -i <length> <unsorted.txt> <sorted.txt> ...--Numbers";
	std::cout << "\n\t<cores> -a [-n=name|-d=date] <read-unsorted-here.txt> <write-sorted-here.txt>> ...--Alumni File";
}

void MersenneTwister(int ArrayToSort[], int size)
{
	srand(time(0));//this will generate a random seed//random # for a random # generator
	//seed
	std::mt19937 generator(rand());//random # for seed

	//distribution
	std::uniform_int_distribution<int> dis(0, size*2);

	//allocating array


	//feeding the array
	int n = 0;
	while (n < size)
	{
		int RN = dis(generator);
		ArrayToSort[n] = RN;
		n++;
	}

}

void writerNum(char *argv[], int Unsortd[], int Sorted[], int size)
{
	std::ofstream outFileUnsorted;
	std::ofstream outFileSorted;

	outFileUnsorted.open(argv[4]);
	outFileSorted.open(argv[5]);

	int n = 0;
	while (n < size)
	{
		outFileSorted << Sorted[n] << "\n";
		outFileUnsorted << Unsortd[n] << "\n";
		n++;
	}
	outFileSorted.close();
	outFileUnsorted.close();
}

template <typename t>
void csvWriter(char *argv[], t data, int size) {
	std::ofstream outFileSorted;
	outFileSorted.open(argv[5]);
	outFileSorted << "Full-name,Donor Status,Graduation Date,Institution" << "\n";

	for (int i = 1; i < size; ++i) {
		outFileSorted << data[i].value() << "\n";
	}
}