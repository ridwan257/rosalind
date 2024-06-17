#include <iostream>
#include <iomanip>

/*
	Couples Genotype -
	1) AA-AA
	2) AA-Aa
	3) AA-aa
	4) Aa-Aa
	5) Aa-aa
	6) aa-aa
*/

int main(){

	int couples_num, offspring = 2;
	float dominant_prob[] = {1, 1, 1, 0.75, 0.5, 0};
	double expected_offspring = 0;

	for(int i=0; i < 6; i++){
		std::cin >> couples_num;
		expected_offspring += offspring * couples_num * dominant_prob[i];
	}


	std::cout << std::setprecision(15) << expected_offspring << std::endl;



	return 0;
}


