#pragma once

#include <ctime>
#include <sstream>
#include <string>

namespace LibMFCUtil
{
	class Stopwatch
	{
	public:
		Stopwatch() {}
		~Stopwatch() {}

		void Start() {
			begin = clock();
		}

		void End() {
			end = clock();
		}

		std::wstring GetTimeString() {
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			std::wostringstream strs;
			strs << elapsed_secs;
			std::wstring str = strs.str() + L"\n";
			return str;
		}

		clock_t begin = 0;
		clock_t end = 0;
	};
}