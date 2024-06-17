#include <iostream>
using std::cout;
using std::endl;

char* dna = (char *) malloc(10);
char* motif = (char *) malloc(6);



int get_index(char* str, int st, char ch){
	int n = strlen(str);

	for(int i=st; i<n; i++){
		if(str[i] == ch){
			return i;
		}
	}

	return -1;
}

int solve(int i, int j, int* ans){
 if(i==strlen(motif) || j==strlen(dna) || (i!=0 && j==0)){
 	for(int k=0; k<3; k++){
 		cout << *(ans+k);
 	}
 	return 0;
 }

 int index = get_index(dna, j; motif[i]);
 if(index != -1){
 	
 }
}


int main()
{
	strcpy(dna, "AAGCGC");
	strcpy(motif, "AGC");

	int ans = {-1, -1, -1};

	solve(0, 0, &ans);

	return 0;
}
