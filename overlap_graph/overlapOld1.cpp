#include <iostream>
using std::cin, std::cout, std::endl;
using std::string, std::getline;


class Sequence
{	
public:
	string id;
	string *seq;

	Sequence(){
		seq = new string("");
	}

	void set(string str){ *seq += str; }
	string get(){ return *seq; }
	char charAt(int i) { return (*seq)[i]; }
      

};

std::string strip(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) {
        return "";  // String contains only whitespace
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}


Sequence* read_fasta_from_console(int& length) {
    int total_capacity = 50;
    Sequence* data_ptr = new Sequence[total_capacity];
    length = -1;

    string line;
    while (getline(cin, line)) {
        

        if (line[0] == '>') {
            
            if (length + 1 >= total_capacity) {
	            total_capacity += 50;
	            Sequence* new_data_ptr = new Sequence[total_capacity];
	            std::memcpy(new_data_ptr, data_ptr, (length + 1) * sizeof(Sequence));

	            delete[] data_ptr;
	            data_ptr = new_data_ptr;
	        }

            data_ptr[++length].id = line.substr(1);
            
            continue;
        }

        data_ptr[length].set(strip(line));

    }
   	
   	length++;
    
    return data_ptr;
}


void render_alingment(string &s1, string &s2, int score, bool show_score=false){
	int space = s1.length() - score;
	if(show_score) cout << "score : " << score << endl;

	cout << s1 << endl;
	cout << string(space, '-') << s2 << endl;
}

int check_right_overlap(Sequence *s, Sequence *t){
	// cout << s->id + " -"  + s->get()  <<'-' << endl;
	// cout <<  s->seq->length() << endl;

	// cout << t->id + " -"  + t->get() << '-' << endl;
	// cout << t->seq->length() << endl << endl;

	int s_size = s->seq->length();
	int match=0;

	for(int i=0; i < s_size; i++){
		int k = i;

		// cout << endl << "outer-loop k or i = " << k << endl;

		for(int j=0; j < t->seq->length() && k < s_size; j++){

			// cout << "inner-loop = " << k << " " << j << endl;
			
			if( s->charAt(k++) != t->charAt(j) ) break;
			// k++;
		}

		// cout << "breaking inner-loop k = " << k << endl;

		if( k == s_size){
			match = s_size - i;
			break;
		}
	}

	// cout << endl << "offset = " << match << endl;

	return match;
}


int main(int argc, char const *argv[])
{
	
	
	int total;
	int k = 3;
	
	
	Sequence *data = read_fasta_from_console(total);

	// for(int i=0; i<total; i++){
	// 	cout << data[i].id << endl;
	// 	cout << data[i].get() << endl << endl;

	// }
	
	// cout << total << endl;

	for(int i=0; i<total; i++){
		for(int j=0; j<total; j++){
			if(i==j) continue;
			int score = check_right_overlap(data+i, data+j);
			
			if(score == k){
				cout << (data+i)->id << " " << (data+j)->id << endl;
				// render_alingment(*(data+i)->seq, *(data+j)->seq, score, true);

			}

		}
	}

	// for (int i=0; i < total; i++){
	// 	cout << i+1 << ") " << (data+i)->id << endl;
	// 	cout << (data+i)->get() << endl << endl;
	// }
	
	// int i=0, j=1;
	// cout << endl << (data+i)->id << " " << (data+j)->id << endl;

	// int score = check_right_overlap(data+i, data+j);
	// // render_alingment(*(data+i)->seq, *(data+j)->seq, score, true);


	delete[] data;

	return 0;
}

