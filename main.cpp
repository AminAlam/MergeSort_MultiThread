# include <iostream>
# include "MergeSort.h"
# include <chrono>
# include <string>
# include <fstream>
# include <vector>

int main(){
    int NumThreads = 0;
    unsigned long int temp = 0;
    int SizeOfArray = 0;
    std::vector<unsigned long int> array;
    std::string SizeOfArray_pathOfFile;

	std:: cout << "Please enter the number of threads (power of 2, i.e 2,4,8,16 and 32 ...):" << std:: endl;
	std:: cin >> NumThreads;
	std:: cout << "If you want to make a random array for sorting please enter an integer as size of the array, otherwise please enter the path of .txt file wich contatins desired numbers to be sorted.:" << std:: endl;
	std:: cin >> SizeOfArray_pathOfFile;


	if (isNumber(SizeOfArray_pathOfFile))
		SizeOfArray = stoul(SizeOfArray_pathOfFile);
	else{
		std::ifstream infile(SizeOfArray_pathOfFile);
		while (infile >> temp){			
		    array.push_back(temp);
		}
		SizeOfArray = array.size();
	}

    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    MySort(array.data(), SizeOfArray, NumThreads);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    
    duration<double, std::milli> time_span = t2 - t1;

    std:: cout << "Time consumed: " << time_span.count() << "mS \n" << std::endl;
    int index = 0;
    std::ofstream myfile("output.txt");
     if(myfile.is_open())
    {
        do{            
            myfile<<array[index]<< std::endl;
            index++;
        }while(index < SizeOfArray);
        myfile.close();
    }
    else std::cerr<<"Unable to open file";
    std:: cout << "Sorted numbers were listed in output.txt" << std::endl;
    return 0;
}