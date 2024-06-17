#include <iostream>
#include <vector>
#include "rfunction.hpp"

struct Field
{
	int score;
	std::string path;
};

void traceback(std::string &s, std::string &t, Field **matrix, int i, int j, std::string path, std::vector<std::string> &traces)
{
	if( i==0 && j==0 ){
		// std::cout << path << std::endl;
		traces.push_back(path);
		return;
	}


	if(matrix[i][j].path[0] == 'h'){
		path += "h";
		traceback(s, t, matrix, i, j-1, path, traces);
		if(!path.empty()) path.pop_back();
	}
	if(matrix[i][j].path[1] == 'c'){
		path += "c";
		traceback(s, t, matrix, i-1, j-1, path, traces);
		if(!path.empty()) path.pop_back();
	}
	if(matrix[i][j].path[2] == 'v'){
		path += "v";
		traceback(s, t, matrix, i-1, j, path, traces);
		if(!path.empty()) path.pop_back();
	}

}


int main()
{
	std::string s, t;
	int nrow, ncol;
	{
		std::vector<BioSeq> v = read_fasta_from_console();
		s = v[0].get();
		t = v[1].get();
		nrow = v[0].length() + 1;
		ncol = v[1].length() + 1;
	}
	

	Field **matrix = new Field*[nrow];


	int delta_, missmatchScore, insertScore, deleteScore;
	int match = 1, missmatch = -1, gap = -1;

	for(int i=0; i < nrow; i++){
		*(matrix+i) = new Field[ncol];
		for(int j=0; j < ncol; j++){
			if (i == 0)
			{
				(*(matrix+i)+j)->score = 0;
				(*(matrix+i)+j)->path = (j == 0) ? "---" : "h--";
			}
			else if (j == 0){
				(*(matrix+i)+j)->score = -1*i;
				(*(matrix+i)+j)->path = "--v";
			}
			else {
				insertScore = (*(matrix+i)+j-1)->score + gap;
				deleteScore = (*(matrix+i-1)+j)->score + gap;

				delta_ = (s[i-1] == t[j-1]) ? match : missmatch;
				missmatchScore = (*(matrix+i-1)+j-1)->score + delta_;

				(*(matrix+i)+j)->score = std::max(std::max(insertScore, deleteScore), missmatchScore);

				if(insertScore > deleteScore && insertScore > missmatchScore) (*(matrix+i)+j)->path = "h--";
				else if(deleteScore > insertScore && deleteScore > missmatchScore) (*(matrix+i)+j)->path = "--v";
				else if(missmatchScore > insertScore && missmatchScore > deleteScore) (*(matrix+i)+j)->path = "-c-";
				else if(insertScore == deleteScore && insertScore > missmatchScore) (*(matrix+i)+j)->path = "h-v";
				else if(deleteScore > insertScore && deleteScore == missmatchScore) (*(matrix+i)+j)->path = "-cv";
				else if(missmatchScore == insertScore && missmatchScore > deleteScore) (*(matrix+i)+j)->path = "hc-";
				else if(missmatchScore == insertScore && missmatchScore == deleteScore) (*(matrix+i)+j)->path = "hcv";
			}
		}
	}


	
	
	// std::cout << s << std::endl;
	// std::cout << t << std::endl;

	// for(int i=0; i < nrow; i++){
	// 	for(int j=0; j < ncol; j++){
	// 		std::cout << matrix[i][j].score << "  ";
	// 	}
	// 	std::cout << std::endl;
	// }

	// for(int i=0; i < nrow; i++){
	// 	for(int j=0; j < ncol; j++){
	// 		std::cout << matrix[i][j].path << "  ";
	// 	}
	// 	std::cout << std::endl;
	// }


	std::vector<std::string> alignment;
	traceback(s, t, matrix, nrow-1, ncol-1, "", alignment);

	std::cout << std::string(40, '-') << std::endl;
	std::cout << "\e[1mScore : " << matrix[nrow-1][ncol-1].score << "\e[0m" << std::endl;
	std::cout << "Edit Distance : " << std::max(nrow, ncol) - std::abs(matrix[nrow-1][ncol-1].score) << std::endl;
	std::cout << "Possible Alignment : " << alignment.size() << std::endl << std::endl;
	std::cout << std::endl;



	std::string newS, newT, showMatch;
	int ptrS, ptrT;
	for(int i=0; i < alignment.size(); i++){
		std::string &path = alignment[i];

		std::cout << "\033[1mAlignment " << i+1 << ":\033[0m" << std::endl;
		// std::cout << path << std::endl;
		
		ptrS = 0;
		ptrT = 0;
		newS = "";
		newT = "";
		// showMatch = "";

		for( int j = path.length(); j >= 0; j--){
			if( path[j] == 'h' ){
				newS += "-";
				newT += t[ptrT++];
				// showMatch += " ";
			}
			else if( path[j] == 'c' ){
				newS +=  (s[ptrS] == t[ptrT]) ? "\e[1;31m" + std::string(1, s[ptrS]) + "\e[0m" : std::string(1, s[ptrS]);
				newT +=  (s[ptrS] == t[ptrT]) ? "\e[1;31m" + std::string(1, t[ptrT]) + "\e[0m" : std::string(1, t[ptrT]);
				// showMatch += (s[ptrS++] == t[ptrT++]) ? "^" : " ";
				ptrS++;
				ptrT++;
			}
			else if( path[j] == 'v' ){
				newS += s[ptrS++];
				newT += "-";
				showMatch += " ";
			}
		}
		 std::cout << newS << std::endl;
		 std::cout << newT << std::endl << std::endl;
		 // std::cout << showMatch << std::endl << std::endl;

	}




	// deleting the allocated memory
	for(int i=0; i < nrow; i++){
		delete[] matrix[i];
	}
	delete[] matrix;
	
	return 0;
}













