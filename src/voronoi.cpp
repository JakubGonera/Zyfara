#include<bits/stdc++.h>
#include"voronoi.hpp" 
 

float distfrom(std::pair<int, int> a, std::pair<int, int> b, std::pair<int, int> p)
{
	if (a.second == b.second)return p.second - (a.second - b.second) / 2;
	int tg1 = b.second - a.second;
	int tg2 = b.first - a.first;
	int A = -1 * (tg2);
	int B = -1 * (tg1);
	int C = A*(-a.first - b.first) / 2 + B*(-a.second - b.second) / 2;
	float dist = A*p.first + B*p.second + C;
	if (dist < 0)dist *= -1;
	dist /= sqrt(A*A + B*B);
	return dist;
}

std::vector<float> slowvoronoi::slow(int width,int height,int border,std::vector<std::pair<int, int>> points)
{
	std::vector<float> pixels(width*height);
	for (int i = 0; i < width*height; i++)
	{
		int h = i / width;
		int w = i % width;
		int smallestdist = INT_MAX;
		int closest;
		for (int j = 0; j < (int)points.size(); j++)
		{
			int dist = (w - points[j].first)*(w - points[j].first) + (h - points[j].second)*(h - points[j].second);
			if (dist < smallestdist) {
				closest = j;
				smallestdist = dist;
			}
		}
		int secondpoint = 0;
		if (closest == 0)secondpoint = 1;
		float dist = distfrom(points[closest], points[secondpoint], std::make_pair(w, h));
		for (int j = 0; j < (int)points.size(); j++)
		{
			float temp = distfrom(points[closest], points[j], std::make_pair(w, h));
			if (dist > temp)dist = temp;
		}
		if (dist <= border)pixels[i] = 0;
		else pixels[i] = dist;
	}
	return pixels;	
}
std::vector<std::pair<int, int>> slowvoronoi::randpoints(int n,int seed,int width,int height)
{
	std::vector<std::pair<int, int>> p;
	std::srand(seed);
	for(int i = 0; i<n;i++)p.push_back(std::make_pair((std::rand() % width), (std::rand() % height)));
	return p;
}