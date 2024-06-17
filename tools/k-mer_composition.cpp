#include <iostream>
#include <vector>


struct data{
	std::string polynucleotide;
	int count;

	data(std::string& seq, int n) : polynucleotide(seq), count(n) {}
};

void permute(std::string seq, int n, std::string holder, std::vector<data> &collection){
	if ( n == 0 ){
		data temp = data(holder, 0);
		collection.push_back(temp);
		return;
	}

	for(int i = 0; i < seq.length(); i++){
		permute(seq, n - 1, holder+seq[i], collection);
	}
}

// binary search
int binary_search(const std::vector<data>& v, const std::string& target) {
    int left = 0;
    int right = v.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (v[mid].polynucleotide == target) {
            return mid;
        }
        if (v[mid].polynucleotide < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}


void decompose(std::vector<data>& v, std::string seq, int k_mer){
	int index;

	for( int i = 0; i < seq.length() - k_mer + 1; i++){

		index = binary_search(v, seq.substr(i, k_mer));

		if( index != -1 ){
			v[index].count++;
		}
	}

}




int main(){
	
	std::string sequence;
	int k_mer = 4;

	{
		std::string line;
		std::getline(std::cin, line);
		while(std::getline(std::cin, line)){
			sequence += line;
		}
	}

	std::vector<data> collection;

	permute("ACGT", k_mer, "", collection);

	decompose(collection, sequence, k_mer);
	

	for( auto s : collection){
		// std::cout << s.polynucleotide << "--" << s.count << std::endl;
		std::cout << s.count << " ";
	}

	std::cout << std::endl;

	return 0;
}












