#include <iostream>
#include <vector>

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
    size_t len;

public:
    std::string id;

    BioSeq(std::string id="", std::string sequence=""){
        this->id = id;
        this->sequence = sequence;
        this->len = sequence.length();
    }

    void append(std::string str){ sequence += str; len += str.length();}
    std::string get(){ return sequence; }
    char charAt(int i) { return (sequence)[i]; }
    size_t length() { return len; }
    bool is_empty(){
        if( strip(id) == "" && strip(sequence) == "" ) return true;
        return false;
    }
    void clear(){
        id.clear();
        sequence.clear();
        len = 0;
    }
};

std::vector<BioSeq> *read_fasta_from_console() {
    std::vector<BioSeq> *sequence_list = new std::vector<BioSeq>();
    std::string line;
    BioSeq current_buffer;

    while(std::getline(std::cin, line)){
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


bool k_order_overlap(BioSeq &s, BioSeq &t, int k){
    for(int i = s.length() - k, j=0; i < s.length() && j < t.length(); i++, j++){
        if(s.charAt(i) != t.charAt(j)) return false;
    }
    return true;
}

int main(int argc, char const *argv[])
{
    int k = 3;
    std::vector<BioSeq> &sequence_list = *read_fasta_from_console();


    for(int i=0; i < sequence_list.size(); i++){
        for(int j=0; j < sequence_list.size(); j++){
            if(i == j) continue;

            if(k_order_overlap(sequence_list[i], sequence_list[j], 3)){
                std::cout << sequence_list[i].id << " " << sequence_list[j].id << std::endl;
            }
        }
    }

    return 0;
}