#pragma once


class slowvoronoi
{
	public:
		std::vector<float> slow(int width,int height,int border,std::vector<std::pair<int, int>> points);
		std::vector<std::pair<int, int>> randpoints(int n,int seed,int width,int height);
};