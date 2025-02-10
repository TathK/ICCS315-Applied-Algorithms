#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <set>

#define MATH_MIN std::numeric_limits<int>::min()
#define MATH_MAX std::numeric_limits<int>::max()
#include <chrono>
#include <fstream>

#include <time.h>

struct timespec allocation_clock_start, allocation_clock_end;
struct timespec coin_toss_clock_start, coin_toss_clock_end;
struct timespec traverse_clock_start, traverse_clock_end;

float total_time_coin_toss;
float total_allocation_time;
float total_traverse_time;

std::random_device rd;  // Non-deterministic random number generator (if available)
std::mt19937 gen(rd()); // Mersenne Twister engine


int better_hash_function(int px, int py) {
    int pn = px;
    int k = 0;
    int d = 0 ;


    // step 2
    while (pn*2 <= py){
        k+=1;
        pn = pn*2;
    }

    // step 3


    rand();
    std::uniform_int_distribution<> dist(0, 2^k);
    int random_num = dist(gen);

}
double uniform_random() {
    return (double)rand() / RAND_MAX;
}
int generate_random(int px, int py) {
    int pn = px, k = 0, d = 0;

    while (pn * 2 <= py) {
        k++;
        pn *= 2;
    }
    while (uniform_random() < pow(1.0 - (double)px / py, pow(2, k))) {
        d++;
    }
    while (1) {
        int m = rand() % (1 << k);
        if (uniform_random() >= pow(1.0 - (double)px / py, m)) {
            return d * (1 << k) + m;
        }
    }
}


int countleading() {
    int i = rand();
    int b = ~i & (i+1);   // this gives a 1 to the left of the trailing 1's
    b--;              // this gets us just the trailing 1's that need counting
    b = (b & 0x55555555) + ((b>>1) & 0x55555555);  // 2 bit sums of 1 bit numbers
    b = (b & 0x33333333) + ((b>>2) & 0x33333333);  // 4 bit sums of 2 bit numbers
    b = (b & 0x0f0f0f0f) + ((b>>4) & 0x0f0f0f0f);  // 8 bit sums of 4 bit numbers
    b = (b & 0x00ff00ff) + ((b>>8) & 0x00ff00ff);  // 16 bit sums of 8 bit numbers
    b = (b & 0x0000ffff) + ((b>>16) & 0x0000ffff); // sum of 16 bit numbers
    return b;
}
int cointoss_test()  {
    int count = 0;
    while ( rand()/static_cast<float>(RAND_MAX) >= 0.5 ) {
        count++;
    }
    return count;

}

void test_cointoss_naive(int n) {
    std::stringstream ss;
    ss << "output/coin_naive/" <<n << ".txt";

    std::vector<double> vec;
    std::ofstream file(ss.str(), std::ios::app);

    for (int j = 0; j < 30; j++) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++)
            cointoss_test();
        auto end = std::chrono::high_resolution_clock::now();
        double tdiff = std::chrono::duration<double>(end - start).count();
        vec.push_back(tdiff);
    }


    for (auto it = vec.begin(); it != vec.end(); it++) {
        file << *it << std::endl;
    }
    file.close();

}
void test_cointoss_fancy(int n) {
    struct timespec start, end;
    std::stringstream ss;
    ss << "output/coin_fancy/" <<n << ".txt";
    std::vector<double> vec;
    std::ofstream file(ss.str(), std::ios::app);

    for (int j = 0; j < 30; j++) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++)
            generate_random(1,2);
        auto end = std::chrono::high_resolution_clock::now();
        double tdiff = std::chrono::duration<double>(end - start).count();
        vec.push_back(tdiff);
    }


    for (auto it = vec.begin(); it != vec.end(); it++) {
        file << *it << std::endl;
    }
    file.close();

}
void test_cointoss_countleading(int n) {
    struct timespec start, end;
    std::stringstream ss;
    ss << "output/coin_leading/" <<n << ".txt";
    std::vector<double> vec;
    std::ofstream file(ss.str(), std::ios::app);

    for (int j = 0; j < 30; j++) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++)
            countleading();
        auto end = std::chrono::high_resolution_clock::now();
        double tdiff = std::chrono::duration<double>(end - start).count();
        vec.push_back(tdiff);
    }


    for (auto it = vec.begin(); it != vec.end(); it++) {
        file << *it << std::endl;
    }
    file.close();

}
void get_distribution() {
    std::vector<int> coin_fancy = std::vector<int>();
    std::vector<int> coin_leading = std::vector<int>();
    std::vector<int> coin_naive = std::vector<int>();

    for (int i = 0; i < 1e7; i++) {
        coin_fancy.push_back(generate_random(1,2));
        coin_leading.push_back(countleading());
        coin_naive.push_back(cointoss_test());
    }

    std::string naive_filename= "output/distribution/naive.txt";
    std::string leading_filename = "output/distribution/leading.txt";
    std::string fancy_filename = "output/distribution/fancy.txt";


    std::ofstream file(naive_filename, std::ios::app);
    for (auto it = coin_naive.begin(); it != coin_naive.end(); it++) {
        file << *it << std::endl;
    }
    file.close();

    std::ofstream file_leading(leading_filename, std::ios::app);
    for (auto it = coin_leading.begin(); it != coin_leading.end(); it++) {
        file_leading << *it << std::endl;
    }
    file_leading.close();

    std::ofstream file_fancy(fancy_filename, std::ios::app);
    for (auto it = coin_fancy.begin(); it != coin_fancy.end(); it++) {
        file_fancy << *it << std::endl;
    }
    file_fancy.close();



}



int main()
{
   for (int i = 0; i < 1e6; i+= 25000) {
       test_cointoss_naive(i);
       test_cointoss_fancy(i);
       test_cointoss_countleading(i);
   }
}
