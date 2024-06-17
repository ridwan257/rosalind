#include <iostream>
#include <vector>

void mystrip(std::string &str){
	size_t first = str.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) {
             return;
        }
        size_t last = str.find_last_not_of(" \t\n\r");
        str = str.substr(first, last - first + 1);
}

int distance(std::string &s, std::string &t, int i, int j, std::vector<std::vector<int>> &memory){
	if ( memory[i][j] != -1 ) return memory[i][j];

	int insertScore = 1 + distance(s, t, i, j-1, memory);
	int deleteScore = 1 + distance(s, t, i-1, j, memory);
	int missmatchScore = ( ( s[i-1] == t[j-1] ) ? 0 : 1 ) + distance(s, t, i-1, j-1, memory);

	memory[i][j] = std::min(std::min(insertScore, deleteScore), missmatchScore);

	return memory[i][j];
}

int main(){
	std::string s, t, line;
	bool hello = false;

	while(std::getline(std::cin, line)){
		mystrip(line);
		if(line != ""){
			if(line[0] == '>'){
				hello = !hello;
				continue;
			}
			if (hello) s += line;
			else t += line;
		}
	}

	std::vector<std::vector<int>> chache(s.length()+1, std::vector<int>(t.length()+1));
	for(int i=0; i < s.length()+1; i++){
		for(int j=0; j < t.length()+1; j++){
			if( i == 0 ) chache[i][j] = j;
			else if ( j== 0 ) chache[i][j] = i;
			else chache[i][j] = -1;

		}
	}

	std::cout << distance(s, t, s.length(), t.length(), chache) << std::endl;

	return 0;
}





















