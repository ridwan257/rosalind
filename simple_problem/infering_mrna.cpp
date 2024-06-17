#include <iostream>

/*
UUU F      CUU L      AUU I      GUU V
UUC F      CUC L      AUC I      GUC V
UUA L      CUA L      AUA I      GUA V
UUG L      CUG L      AUG M      GUG V
UCU S      CCU P      ACU T      GCU A
UCC S      CCC P      ACC T      GCC A
UCA S      CCA P      ACA T      GCA A
UCG S      CCG P      ACG T      GCG A
UAU Y      CAU H      AAU N      GAU D
UAC Y      CAC H      AAC N      GAC D
UAA Stop   CAA Q      AAA K      GAA E
UAG Stop   CAG Q      AAG K      GAG E
UGU C      CGU R      AGU S      GGU G
UGC C      CGC R      AGC S      GGC G
UGA Stop   CGA R      AGA R      GGA G
UGG W      CGG R      AGG R      GGG G
*/

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t");
    if (start == std::string::npos) return "";

    size_t end = str.find_last_not_of(" \t");
    return str.substr(start, end - start + 1);
}

int hash_func(char aa){
	int acsi_value = static_cast<int>(aa);

	if(acsi_value > 88)  acsi_value--;
	if(acsi_value > 85)  acsi_value--;
	if(acsi_value > 79)  acsi_value--;
	if(acsi_value > 74)  acsi_value--;
	if(acsi_value > 66)  acsi_value--;
	
	acsi_value -= 65;

	return acsi_value;
}


int main(){
    // codon count in alphabetic order
    const int codon_count[] = {4, 2, 2, 2, 2, 4, 2, 3, 2, 6, 1, 2, 4, 2, 6, 6, 4, 4, 1, 2};
    const int stop_codon = 3;
    std::string oligopeptide;
    int64_t count = 1;
    int64_t mod_factor = 1000000;

    while(std::getline(std::cin, oligopeptide)){
        oligopeptide = trim(oligopeptide);
        if(oligopeptide.length()!=0) {
            for(int i=0; i < oligopeptide.length(); i++){
                count *= codon_count[ hash_func(oligopeptide[i]) ];
                while(count >= mod_factor){
                    count -= mod_factor;
                }   
            }
        }
    }

    count *= stop_codon;
    while(count >= mod_factor){
        count -= mod_factor;
    }

    std::cout << count << std::endl;

    return 0;
}









