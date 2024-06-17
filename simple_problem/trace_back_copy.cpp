#include <iostream>
#include <vector>


class myString : public std::string {
public:
    myString() : std::string() {}
    myString(const char* s) : std::string(s) {}
    myString(const std::string &s) : std::string(s) {}

    myString strip() {
        size_t first = find_first_not_of(" \t\n\r");
        if (first == std::string::npos) {
            return "";
        }
        size_t last = find_last_not_of(" \t\n\r");
        return myString(substr(first, last - first + 1));
    }

    char endChar(){ return at(length()-1); }
};

void rstrip(std::string &str){
	size_t first = str.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) {
             return;
        }
        size_t last = str.find_last_not_of(" \t\n\r");
        str = str.substr(first, last - first + 1);
}

std::vector<std::vector<std::string>> trace;

int distance(myString &s, myString &t, int i, int j, std::vector<std::vector<int>> &memory){
	if ( memory[i][j] != -1 ) return memory[i][j];



	int insertScore = 1 + distance(s, t, i, j-1, memory);
	int deleteScore = 1 + distance(s, t, i-1, j, memory);

	int delta_ = ( s[i-1] == t[j-1] ) ? 0 : 1;
	int missmatchScore = delta_ + distance(s, t, i-1, j-1, memory);

	memory[i][j] = std::min(std::min(insertScore, deleteScore), missmatchScore);

	if(insertScore < deleteScore && insertScore < missmatchScore) trace[i-1][j-1] = "h--";
	else if(deleteScore < insertScore && deleteScore < missmatchScore) trace[i-1][j-1] = "--v";
	else if(missmatchScore < insertScore && missmatchScore < deleteScore) trace[i-1][j-1] = "-c-";
	else if(insertScore == deleteScore && insertScore < missmatchScore) trace[i-1][j-1] = "h-v";
	else if(deleteScore < insertScore && deleteScore == missmatchScore) trace[i-1][j-1] = "-cv";
	else if(missmatchScore == insertScore && missmatchScore < deleteScore) trace[i-1][j-1] = "hc-";
	else if(missmatchScore == insertScore && missmatchScore == deleteScore) trace[i-1][j-1] = "hcv";

	return memory[i][j];
}

int main(){
	myString s, t, line;
	bool hello = false;

	


	while(std::getline(std::cin, line)){
		line = line.strip();
		if(line != ""){
			if(line[0] == '>'){
				hello = !hello;
				continue;
			}
			if (hello) s += line;
			else t += line;
		}
	}

	// std::cout << s << std::endl;
	// std::cout << t << std::endl;

	std::vector<std::vector<int>> chache(s.length()+1, std::vector<int>(t.length()+1));
	for(int i=0; i < s.length()+1; i++){
		for(int j=0; j < t.length()+1; j++){

			if( i == 0 ) chache[i][j] = j;
			else if ( j== 0 ) chache[i][j] = i;
			else chache[i][j] = -1;

		}
	}

	trace = std::vector<std::vector<std::string>>(s.length(), std::vector<std::string>(t.length()));

	

	std::cout << distance(s, t, s.length(), t.length(), chache) << std::endl; 

	for(int i=0; i < s.length()+1; i++){
		for(int j=0; j < t.length()+1; j++){
			std::cout << chache[i][j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	for(int i=0; i < s.length(); i++){
		for(int j=0; j < t.length(); j++){
			// std::cout << ((trace[i][j] == "") ? 'o' : 'x') << " ";
			std::cout << trace[i][j] << " ";
		}
		std::cout << std::endl;
	}


	return 0;
}





















