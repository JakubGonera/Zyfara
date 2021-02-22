#include"voronoi.hpp" 
#include <thread>
#include <cmath>

float distfrom(std::pair<int, int> a, std::pair<int, int> b, std::pair<int, int> p)
{
	int tg1 = b.second - a.second;
	int tg2 = b.first - a.first;
	int A = -1 * (tg2);
	int B = -1 * (tg1);
	int C = A * (-a.first - b.first) / 2 + B * (-a.second - b.second) / 2;
	float dist = A * p.first + B * p.second + C;
	if (dist < 0)dist *= -1;
	dist /= sqrt(A * A + B * B);
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

void inloop(int l,int r,int width,int border,std::vector<std::pair<int, int>> *points,std::vector<float> *pixels)
{
	for(int i = l;i<r;i++)
	{
		int h = i / width;
		int w = i % width;
		int smallestdist = INT_MAX;
		int closest;
		for (int j = 0; j < (int)(*points).size(); j++)
		{
			int dist = (w - (*points)[j].first)*(w - (*points)[j].first) + (h - (*points)[j].second)*(h - (*points)[j].second);
			if (dist < smallestdist) {
				closest = j;
				smallestdist = dist;
			}
		}
		int secondpoint = 0;
		if (closest == 0)secondpoint = 1;
		float dist = distfrom((*points)[closest], (*points)[secondpoint], std::make_pair(w, h));
		for (int j = 0; j < (int)(*points).size(); j++)
		{
			float temp = distfrom((*points)[closest], (*points)[j], std::make_pair(w, h));
			if (dist > temp)dist = temp;
		}
		if (dist <= border)(*pixels)[i] = 0;
		else (*pixels)[i] = dist;
	}
}

std::vector<float> slowvoronoi::multi(int width,int height,int border,std::vector<std::pair<int, int>> points)
{
	std::vector<float> pixels(width*height);
	int m = width*height/12;
	std::vector<std::thread> threadVec;
	for (int i = 0; i < 12; i++)
	{

		threadVec.push_back(std::thread(inloop,i*m,(i+1)*m,width,border,&points,&pixels));
	}
	for (auto& x : threadVec)
	{
		x.join();
	}
	std::thread thrd(inloop,12*m,width*height,width,border,&points,&pixels);
	thrd.join();
	return pixels;	
}

std::vector<std::pair<int, int>> slowvoronoi::randpoints(int n,int seed,int width,int height, int margin)
{
	std::vector<std::pair<int, int>> p;
	std::srand(seed);
	for(int i = 0; i<n;i++)
		p.push_back({ (std::rand() % (width + 2 * margin) - margin), (std::rand() % (height + 2 * margin) - margin) });
	return p;
}