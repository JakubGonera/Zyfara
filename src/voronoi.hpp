#pragma once
#include<queue>
#include <vector>
#include <utility>

class slowvoronoi
{
	private:
		int seed=1234;
	public:
		void set_seed(int val);
		static std::vector<float> slow(int width,int height,int border,std::vector<std::pair<int, int>> points);
		static std::vector<float> multi(int width,int height,int border,std::vector<std::pair<int, int>> points);
		std::vector<float> randbordermulti(int width,int height,int borderL,int borderR,std::vector<std::pair<int, int>> points,std::vector<float>&closestborder);
		std::vector<std::pair<int, int>> randpoints(int n,int seed,int width,int height, int margin);
		std::vector<std::pair<int, int>> poisson(int width, int height, int r);
};