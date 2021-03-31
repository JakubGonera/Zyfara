#pragma once
#include<queue>
#include <vector>
#include <utility>
//Class that handles generating voronoi diagram
class slowvoronoi
{
	private:
		int seed=2137;
	public:
		void set_seed(int val);
		//Single thread voronoi generator - obsolete
		static std::vector<float> slow(int width,int height,int border,std::vector<std::pair<int, int>> points);
		//Multithreaded version and its helper function
		static std::vector<float> multi(int width,int height,int border,std::vector<std::pair<int, int>> points);
		std::vector<float> randbordermulti(int width,int height,int borderL,int borderR,std::vector<std::pair<int, int>> points,std::vector<float>&closestborder);
		//Purely random points generation
		std::vector<std::pair<int, int>> randpoints(int n,int seed,int width,int height, int margin);
		//Poisson Disk Sampling - generating uniformly distributed points
		std::vector<std::pair<int, int>> poisson(int width, int height, int r);
};