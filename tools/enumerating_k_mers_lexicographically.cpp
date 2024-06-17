#include <iostream>
#include <vector>



void permute(std::vector<char> collection, int n, std::string holder){
	if ( n == 0 ){
		std::cout << holder << std::endl;
		return;
	}

	for(int i = 0; i < collection.size(); i++){
		permute(collection, n - 1, holder+collection[i]);
	}
}

int main(){
	
	char l;
	int n;

	std::vector<char> letters;

	while( std::cin.get(l) && l != '\n' ){
		if (l != ' ') {
			letters.push_back(l);
		}
	}

	std::cin >> n;


	permute(letters, n, "");


	return 0;
}