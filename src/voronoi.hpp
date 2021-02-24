#pragma once
#include <vector>
#include <utility>

class slowvoronoi
{
	public:
		static std::vector<float> slow(int width,int height,int border,std::vector<std::pair<int, int>> points);
		static std::vector<float> multi(int width,int height,int border,std::vector<std::pair<int, int>> points);
		static std::vector<std::pair<int, int>> randpoints(int n,int seed,int width,int height, int margin);
};