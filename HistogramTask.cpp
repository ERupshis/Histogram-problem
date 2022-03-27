#include <iostream>
#include <string>
#include <vector>
#include <numeric>

//////////////////////////////////////////////////////////////////
/// HISTOGRAM NAIVE O(N^2), OPTIMAL O(N)
//////////////////////////////////////////////////////////////////
/// Find the largest rectangle that can be limited by histogram.
///
/////////////////////////////////////////////////////////////////
///
///          X                   9
///          X                   8
///    X     X  X     X          7
///    X  X  X  X     X          6
///    X  X  X  X  X  X     X    5
///    X  X  X  X  X  X     X    4
///    X  X  X  X  X  X  X  X    3
/// X  X  X  X  X  X  X  X  X    2
/// X  X  X  X  X  X  X  X  X    1
/// 0  1  2  3  4  5  6  7  8    0


// NAIVE SOLUTION
/*
int main()
{
	std::vector<int> histogram{ 2, 7, 6, 9, 7, 5, 7, 3, 5 };

	int max = 0;
	for (int i = 0; i < histogram.size(); ++i)
	{
		int sub_height = std::numeric_limits<int>::max();
		for (int j = i; j < histogram.size(); ++j)
		{
			if (sub_height > histogram[j])
				sub_height = histogram[j];

			int area = (j - i + 1) * sub_height;
			if (max < area)
				max = area;
			
		}
	}

	std::cout << max << '\n';
}*/


#include <stack>
/// OPTIMAL SOLUTION
int main()
{
	std::vector<int> histogram{ 2, 7, 6, 9, 7, 5, 7, 3, 5 };

	// Search of left and right borders are absolutely identical. 
	// By this cycles we define indexes of columns that will limit rectangle with height equal to histogram[i].
	// rectangle with height = histogram[0] will be limited by left border of histogram which is not included in our list. that's why
	// we suppose this index = -1. To right border definition we are taking into account right not reachable border idx that is equal to histogram size.

	std::stack<std::pair<int, int>> left_border; //define left borders
	std::vector<int> left_borders(histogram.size(), -1); // -1 - index of border right before first element in histogram

	if (!histogram.empty())
		left_border.push({ 0, histogram[0] });

	for (int i = 1; i < histogram.size(); ++i)
	{
		while (!left_border.empty() && histogram[i] < left_border.top().second)
		{
			left_border.pop();
		}

		if (left_border.empty())
			left_borders[i] = -1;
		else
			left_borders[i] = left_border.top().first;
		
		left_border.push({ i, histogram[i] });
	}

	std::stack<std::pair<int, int>> right_border; //define right borders
	std::vector<int> right_borders(histogram.size(), histogram.size()); // 9 - index of border right after last element in histogram

	if (!histogram.empty())
		left_border.push({ 0, histogram[0] });

	for (int i = histogram.size(); i > 0; --i)
	{
		while (!right_border.empty() && histogram[i - 1] < right_border.top().second)
		{
			right_border.pop();
		}

		if (right_border.empty())
			right_borders[i - 1] = histogram.size();
		else
			right_borders[i - 1] = right_border.top().first;

		right_border.push({ i - 1, histogram[i - 1] });
	}

	std::vector<int> res; // result vector of rectangle areas that are limited by i column height
	int max_area = 0;
	for (int i = 0; i < histogram.size(); ++i)
	{
		// area = column-limiter height * (right_border_idx - left_border_idx - 1)
		int area = histogram[i] * (right_borders[i] - left_borders[i] - 1);
		if (area > max_area)
			max_area = area;

		res.push_back(area); 
	}

	std::cout << max_area << '\n';
}