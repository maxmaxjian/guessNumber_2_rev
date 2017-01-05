#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <unordered_map>
#include <utility>

namespace std {
    template<>
    struct hash<std::pair<int,int>> {
	size_t operator()(const std::pair<int,int> & p) const {
	    return std::hash<int>()(p.first)^std::hash<int>()(p.second);
	}
    };
}

class solution {
public:
    int getMoneyAmount(int n) {
	std::vector<int> cands;
	for (int k = 1; k <= n; k++)
	    cands.push_back(k+std::max(compute(1,k-1), compute(k+1,n)));
	std::copy(cands.begin(), cands.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
	return *std::min_element(cands.begin(), cands.end());
    }
    
private:
    std::unordered_map<std::pair<int,int>, int> dict;
    
    int compute(int i, int j) {
	if (dict.find(std::make_pair(i,j)) == dict.end())
	    dict[std::make_pair(i,j)] = compute_impl(i,j);
	return dict[std::make_pair(i,j)];
    }

    int compute_impl(int i, int j) {	
	if (i >= j)
	    return 0;
	else {
	    std::vector<int> cands;
	    for (int k = i; k <= j; k++) {
		cands.push_back(k+std::max(compute(i,k-1), compute(k+1,j)));
	    }
	    std::cout << "i = " << i << ", j = " << j << ":\t";
	    std::copy(cands.begin(), cands.end(), std::ostream_iterator<int>(std::cout, " "));
	    std::cout << std::endl;
	    dict[std::make_pair(i,j)] = *std::max_element(cands.begin(), cands.end());

	    return dict[std::make_pair(i,j)];
	}
    }
};


int main() {
    int num = 4;

    solution soln;
    int minmax = soln.getMoneyAmount(num);
    std::cout << "The amount of money needed to guarantee a win is:\n"
	      << minmax << std::endl;
}
