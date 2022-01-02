#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>

namespace dj {

/* Split a string by delimiter
   Returns a Vector
*/
	std::vector<std::string> split(std::string str, std::string delim) {
		std::vector<std::string> tmpCont;
		std::string tmpStr = str;
		size_t pos = 0, prevPos = 0;
		while (1) {
			pos = str.find(delim, prevPos);
			if (pos == str.npos) {
				tmpCont.push_back(str.substr(prevPos));
				return tmpCont;
			}
			
			tmpCont.push_back(str.substr(prevPos, pos - prevPos));
			prevPos = pos + delim.length();
		}
		return tmpCont;
	}

	template<typename T>
	std::vector<T> split(std::string str, std::string delim) {
		std::vector<T> tmpCont;
		std::istringstream ss;
		std::string tmpStr = str;
		size_t pos = 0, prevPos = 0;
		T S;
		while (1) {
			pos = str.find(delim, prevPos);
			if (pos == str.npos) {
				ss.clear();
				ss.str(str.substr(prevPos));
				ss >> S;
				tmpCont.push_back(S);
				return tmpCont;
			}

			ss.clear();
			ss.str(str.substr(prevPos, pos - prevPos));
			ss >> S;
			tmpCont.push_back(S);
			prevPos = pos + delim.length();
		}
		return tmpCont;
	}
	
	// Print 1D Vector
	template <typename T> void printVec1(std::vector<T> V, std::string sep = "") {
		for (uint i = 0; i < V.size(); i++)
			std::cout << V.at(i) << sep;
	}
	
	// Print 2D Vector
	template <typename T> void printVec2(std::vector<T> V, std::string sep = "") {
		for (uint i = 0; i < V.size(); i++)
			for (uint j = 0; j < V.size(); j++)
				std::cout << V.at(i).at(j) << sep;
	}

	// floor division like python
	inline int floor_division(double a, double b, double ifZero = 0) {
		if (b != 0)
			return (a - fmod(a, b)) / b;
		else
			return ifZero;
	}
	
	/* Function which mimics array_split function from numpy.
	   Returns a Vector of Vectors*/
	template <typename T>
	std::vector<std::vector<T>> array_split(std::vector<T> arr, uint n) {
		std::vector<std::vector<T>> f;
		std::vector<T> e;
		uint i, j, l = arr.size(), I = 0;
		f = {}, e = {};
		for (i = 0; i < l % n; i++) {
			e = {};
			for (j = 0; j < floor_division(l, n) + 1; j++)
				e.push_back(arr[I + j]);
			I += j;
			f.push_back(e);
		}
		for (i = 0; i < n - l % n; i++) {
			e = {};
			for (j = 0; j < floor_division(l, n); j++)
				e.push_back(arr[I + j]);
			I += j;
			f.push_back(e);
		}
		return f;
	}

	template<typename T>
	bool contains(std::vector<T> vec, T ele) {
		for( T &i : vec )
			if(i == ele)
				return true;
		return false;
	}

	template<typename T>
	int index(std::vector<T> vec, T ele) {
		for(uint i=0; i<vec.size(); i++)
			if (vec.at(i) == ele)
				return i;
		return -1;
	}

	template<typename T>
	int indexOfKey(std::vector<std::pair<T, uint>> vec, T key) {
		for(uint i=0; i<vec.size(); i++)
			if (vec.at(i).first == key)
				return i;
		return -1;
	}

	template<typename T>
	std::vector<std::pair<T, uint>> count(std::vector<T> vec) {
		std::pair<T, uint> pair;
		std::vector<std::pair<T, uint>> returnVec;
		int I;
		for(uint i=0; i<vec.size(); i++) {
			if(returnVec.empty()) {
				pair.first = vec.at(i);
				pair.second = 1;
				returnVec.push_back(pair);
			}
			else {
				I = indexOfKey(returnVec, vec.at(i));
				if(I >= 0) {
					returnVec.at(I).second += 1;
				}
				else {
					pair.first = vec.at(i);
					pair.second = 1;
					returnVec.push_back(pair);
				}
			}
		}
		return returnVec;
	}
	
	// Timer class for timing
	class Timer {
	public:
		Timer() {
			m_StartTimer = std::chrono::high_resolution_clock::now();
		}
		
		~Timer() {
			m_StopTimer = std::chrono::high_resolution_clock::now();

			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(m_StopTimer)
				.time_since_epoch().count();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimer)
				.time_since_epoch().count();

			m_duration = end - start;
			auto d = getTime();
			std::cout << d << " (us)\n" << d * 1e-3 << " (ms)\n" << d * 1e-6 << " (s)\n";
		}

		long long getTime() {
			return m_duration;
		}
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimer, m_StopTimer;
		long long m_duration;
	};
} // namespace dj
