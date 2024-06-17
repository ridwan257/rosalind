#include <iostream>
#include <vector>
#include "rfunction.hpp"


bool search(const std::string &target, const std::string &query){
	for(int i=0; i < target.length() - query.length() + 1; i++){
		for(int j=0; j < query.length(); j++){
			if(target[i+j] != query[j]) break;
			if( j == query.length()-1 ) return true;
		}
	}

	return false;
}

int main(){

	std::vector<BioSeq> sequences = read_fasta_from_console();
	std::string start = sequences[0].get();

	for(int i=1; i < sequences.size(); i++){
		if( start.length() > sequences[i].length() ) start = sequences[i].get();
	}

	for(int k_mer=start.length(); k_mer > 1; k_mer--){
		for(int i=0; i < start.length() - k_mer + 1; i++){
			std::string motif = start.substr(i, k_mer);
			
			for(int j=0; j < sequences.size(); j++){
				if(!search(sequences[j].get(), motif)) break;

				if ( j == sequences.size()-1 ){
					std::cout << motif << std::endl;
					return 0;
				}
			}
	
		}
	}


	return 0;
}