# pragma once

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

// header file of usefull utility functions not included in stl

namespace util
{
	template <typename T> int sgn(T val)
	{
		// https://stackoverflow.com/a/4609795
		return (T(0) < val) - (val < T(0));
	}

	inline void progressBar(float percentage)
	{
		// https://stackoverflow.com/a/14539953
		int val= (int) (percentage * 100);
	    int lpad = (int) (percentage * PBWIDTH);
	    int rpad = PBWIDTH - lpad;
	    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
	    fflush(stdout); 
	}
}