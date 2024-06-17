#include<iostream>

using std::cin;
using std::cout;
using std::endl;

#define LENGTH 100


// c(n) = m(n-1)
// m(n) = m(n-1) + c(n-1) - c(n-k)
// total = m(n) + c(n)

unsigned long int mortal_rabit(int n, int k){
    if(n==1) return 1;

    unsigned long int mature[n];
    unsigned long int total, old;
    mature[0] = 0;
    mature[1] = 1;

    for(int i=2; i < n; i++){
        if(i - k < 0) old = 0;
        else if ( i-k == 0 ) old = 1;
        else old = mature[i-k-1];

        mature[i] = mature[i-2] + mature[i-1] - old;
    }

    return mature[n-1] + mature[n-2];
}

uint64_t total_rabit(int n, int k, uint64_t *memory){
    if( n == -1 ) return 1;
    if ( memory[n] != 0 ) return memory[n];
    
    memory[n] = total_rabit(n-1, k, memory) + total_rabit(n-2, k, memory);
    if( n >= k ) memory[n] -= total_rabit(n-k-1, k, memory);
    
    return memory[n];  
}

int main(int argc, char* argv[])
{   
    uint64_t chache[LENGTH];
    for(int i=0; i<LENGTH; i++){
        chache[i] = 0;
    }
    chache[0] = 1;
    chache[1] = 1;

    int n, k;


    // cout << mature(n-1, k, chache) + chache[n-2] << endl;
    
    if(argc < 5){
        std::cerr << "not enough input!" << endl;
        return -1;
    }

    int i = 1;
    while(i<argc){
        if(!strcmp("-n", argv[i])){
            n = std::stoi(argv[i+1]);
            i += 2;
            continue;
        }
        if(!strcmp("-k", argv[i])){
            k = std::stoi(argv[i+1]);
            i += 2;
            continue;
        }
        i++;
    }
    
    if (n <= 0 || n > 100 || k <= 0 || k > 20) {
        std::cerr << "not valied input!" << endl;
        return -1;
    }
    if (n==1){
        cout << 1 << endl;
        return 0;
    }
    
    switch (n)
    {
    case 1:
        cout << "mortal rabit : " << 1 << endl;
        cout << "total rabit : " << total_rabit(n-1, k, chache) << endl << endl;
        return 0;
    default:
        cout << "mortal rabit : " << mortal_rabit(n, k) << endl;
        cout << "total rabit : " << total_rabit(n-1, k, chache) << endl << endl;
        return 0;
    }

    ;
    

    return 0;
}