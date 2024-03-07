#include <iostream>
#include <tree/tree.h>
#include <ctime>
#include <chrono>
#include <vector>

#define SEC_IN_MILLISEC 1000 

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

int main() {
    my_set g{ 3,5,6,3,2,5,7 };
    g.print();
    std::cout << std::endl;
    set_iter it = g.begin();
    while (it!=g.end() && it.has_next()) {
        std::cout << (*it)->data<< " ";
        it.next();
    }

    
    //std::chrono::time_point<std::chrono::system_clock> start, end;
    //double sum = 0;
    //erase and find
    ////my_set set;
    //std::vector<int> vec;
    //for (size_t i = 0; i < 10000; ++i) {
    //    //set.insert(lcg());
    //    vec.push_back(lcg());
    //}
    //for (size_t g = 0; g < 1000; ++g) {
    //    start = std::chrono::system_clock::now();
    //    std::find(vec.begin(), vec.end(), lcg());
    //    std::remove(vec.begin(), vec.end(), lcg());
    //    //set.insert(lcg());
    //    //set.erase(lcg());
    //    end = std::chrono::system_clock::now();
    //    std::chrono::duration<double> elapsed_seconds = end - start;
    //    sum += elapsed_seconds.count();
    //}

    //insert
    //for (size_t g = 0; g < 100; ++g) {
    //    start = std::chrono::system_clock::now();
    //    my_set set;
    //    //std::vector<int> vec;
    //    for (size_t i = 0; i < 100000; ++i) {
    //        set.insert(lcg());
    //        //vec.push_back(lcg());
    //    }
    //    end = std::chrono::system_clock::now();
    //    std::chrono::duration<double> elapsed_seconds = end - start;
    //    sum += elapsed_seconds.count();
    //}
    
    //search
    //my_set set;
    //std::vector<int> vec;
    //for (size_t i = 0; i < 10000; ++i) {
    //    //set.insert(lcg());
    //    vec.push_back(lcg());
    //}
    //for (size_t g = 0; g < 1000; ++g) {
    //    start = std::chrono::system_clock::now();
    //    std::find(vec.begin(), vec.end(), lcg());
    //    //set.contains(lcg());
    //    end = std::chrono::system_clock::now();
    //    std::chrono::duration<double> elapsed_seconds = end - start;
    //    sum += elapsed_seconds.count();
    //}
    //std::cout << "elapsed time: " << (sum/1000)*SEC_IN_MILLISEC << "\n";
	return 0;
}