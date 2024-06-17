#include <iostream>
#include <vector>
using std::cin, std::cout, std::endl;


std::string strip(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}


class BioSeq
{
private:
	std::string sequence;

public:
	std::string id;
	
	size_t length;

	BioSeq(std::string id="", std::string sequence=""){
		this->id = id;
		this->sequence = sequence;
		this->length = sequence.length();
	}

	void append(std::string str){ sequence += str; length += str.length();}
	std::string get(){ return sequence; }
	char charAt(int i) { return (sequence)[i]; }
	bool is_empty(){
		if( strip(id) == "" && strip(sequence) == "" ) return true;
		return false;
	}
	void clear(){
		id.clear();
		sequence.clear();
		length = 0;
	}
      

};


void render_vector(std::vector<int> &v){
	std::cout << "[ ";
	for(int x : v){
		cout << x << ", "; 
	}
	std::cout << "]";
}

bool find(std::vector<int> &v, int n){
	for(int i : v){
		if ( n == i ) return true;
	}

	return false;
}

std::vector<BioSeq> *read_fasta_from_console() {
	std::vector<BioSeq> *sequence_list = new std::vector<BioSeq>();
	std::string line;
	BioSeq current_buffer;

	while(std::getline(cin, line)){
		line = strip(line);
		if(line != ""){

			if(line[0] == '>'){
				if(!current_buffer.is_empty()){
					sequence_list->push_back(current_buffer);
					current_buffer = BioSeq();
				}
				current_buffer.id = line.substr(1);
				continue;
			}

			current_buffer.append(line);
		}	
	}

	if(!current_buffer.is_empty()) sequence_list->push_back(current_buffer);

	return sequence_list;
}


void render_alingment(std::string &s1, std::string &s2, int score, bool show_score=false){
	
}

std::vector<int> check_right_overlap(BioSeq &s, BioSeq &t){
	// std::cout << s.id << " " << s.length <<  " " << s.get() << std::endl;
	// std::cout << t.id << " " << t.length <<  " " << t.get() << std::endl << std::endl;

	std::vector<int> scores;

	for(int i=0; i < s.length; i++){
		int k = i;
		for(int j=0; j < t.length; j++){
			if( s.charAt(k++) != t.charAt(j) ) break;
			if( k == s.length ){
				scores.push_back(s.length - i);
				break;
			}
		}
	}

	return scores;	
}

bool k_order_overlap(BioSeq &s, BioSeq &t, int k){

	for(int i = s.length - k, j=0; i < s.length && j < t.length; i++, j++){
		if(s.charAt(i) != t.charAt(j)) return false;
	}

	return true;
}

int main(int argc, char const *argv[])
{
	int k = 3;
	
	std::vector<BioSeq> &sequence_list = *read_fasta_from_console();

	// for(int i = 0; i < sequence_list.size(); i++){
	// 	std::cout << sequence_list[i].id << std::endl;
	// 	std::cout << sequence_list[i].get() << std::endl;
	// }
	

	// for(int i=0; i < sequence_list.size(); i++){
	// 	for(int j=0; j < sequence_list.size(); j++){
	// 		if(i == j) continue;
	// 		std::vector<int> score = check_right_overlap(sequence_list[i], sequence_list[j]);

	// 		if(find(score, 3)){
	// 			std::cout << sequence_list[i].id << " " << sequence_list[j].id << endl;
	// 		}

	// 	}
	// }

	for(int i=0; i < sequence_list.size(); i++){
		for(int j=0; j < sequence_list.size(); j++){
			if(i == j) continue;

			if(k_order_overlap(sequence_list[i], sequence_list[j], 3)){
				std::cout << sequence_list[i].id << " " << sequence_list[j].id << endl;
			}

		}
	}

	return 0;
}



















