#include"voronoi.hpp" 
#include <thread>
#include <cmath>
#include<cstdlib>

void slowvoronoi::set_seed(int val)
{
	seed=val;
}
float distfrom(std::pair<int, int> a, std::pair<int, int> b, std::pair<int, int> p)
{
	if(a==b)return 14102137.0;
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

std::vector<float>kly(int width,int height,std::vector<float>pixels)
{
	std::vector<bool>vis(height*width,0);
	std::queue<int> q;
	for(int i=0;i<height*width;i++)
	{
		if(!(pixels[i]))
		{
			q.push(i);
			vis[i]=1;
			break;
		}
	}
	int p=1,m=2;
	while(!q.empty())
	{
		int i=q.front();
		q.pop();
		int x=i%width,y=i/height;
		int white=0;
		for(int j=-1;j<2;j++)
			for(int k=-1;k<2;k++)
				if(-1<x+j and x+j<width and -1<y+k and y+k<height)
				{
					if(pixels[width*(y+k)+x+j]==0)white++;
					if(!vis[width*(y+k)+x+j])
					{
						vis[width*(y+k)+x+j]=1;
						q.push(width*(y+k)+x+j);
						
					}
				}		
		if( ((rand())%(m*9)<p*white )and pixels[i])
		{
			pixels[i]=0;
		}
		//if(white==0)pixels[i]=69.0;
	}
	return pixels;
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
	return pixels;//kly(width,height,pixels);	
}

void randborderinloop(int l,int r,int width,std::vector<std::vector<int>>*border,std::vector<std::pair<int, int>> *points,std::vector<float> *pixels,std::vector<float>*closestborder)
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
		(*pixels)[i]=69;
		(*closestborder)[i]=1410692137;
		for (int j = 0; j < (int)(*points).size(); j++)
		{
			float temp = distfrom((*points)[closest], (*points)[j], std::make_pair(w, h));
			int y=std::min(closest,j);
			int z=std::max(closest,j);
			if((*closestborder)[i]>temp-(*border)[y][z])(*closestborder)[i]=temp-(*border)[y][z];
			dist=std::min(temp,dist);
		}
		
		if((*pixels)[i])(*pixels)[i]=dist;
	}
}

std::vector<float> slowvoronoi::randbordermulti(int width,int height,int borderL,int borderR,std::vector<std::pair<int, int>> points,std::vector<float>&closestborder)
{
	srand(seed);
	std::vector<float> pixels(width*height);
	int m = width*height/12;
	std::vector<std::vector<int>>border(points.size(),(std::vector<int>(points.size())));
	for(int i=0;i<(int)points.size();i++)
		for(int j=0;j<(int)points.size();j++)
			border[i][j]= borderL+(rand()%(borderR-borderL+1));
	//for(int j=0;j<points.size();j++)border[4][j]=borderR;
	std::vector<std::thread> threadVec;
	for (int i=0;i<12;i++)
	{
		threadVec.push_back(std::thread(randborderinloop,i*m,(i+1)*m,width,&border,&points,&pixels,&closestborder));
	}
	for (auto&x:threadVec)
	{
		x.join();
	}
	std::thread thrd(randborderinloop,12*m,width*height,width,&border,&points,&pixels,&closestborder);
	thrd.join();
	return pixels;
}

std::vector<std::pair<int, int>> slowvoronoi::randpoints(int n,int seed,int width,int height, int margin)
{
	std::vector<std::pair<int, int>> p;
	srand(slowvoronoi::seed);
	for(int i = 0; i<n;i++)
		p.push_back({ (std::rand() % (width + 2 * margin) - margin), (std::rand() % (height + 2 * margin) - margin) });
	return p;
}

std::vector<std::pair<int, int>> slowvoronoi::poisson(int width, int height, int r)
{
	//Robert Bridson's Poisson Disk Sampling algorithm - running O(n)
	int k = 30; //number of points generated before moving on
	std::vector<std::pair<int, int>> points;
	srand(seed);
	
	int gridSideLength = (float)(r + 1) / sqrt(2);
	std::vector<std::vector<int>> grid(width / gridSideLength + 2, std::vector<int>(height / gridSideLength + 2, -1));

	std::queue<int> activeList;
	std::pair<int, int> firstPoint = { std::rand() % width , std::rand() % height };
	grid[firstPoint.first / gridSideLength + 1][firstPoint.second / gridSideLength + 1] = 0;
	points.push_back(firstPoint);
	activeList.push(0);

	while (!activeList.empty()) {
		int pointIndex = activeList.front();
		activeList.pop();

		std::pair<int, int> gridIndex;
		gridIndex.first = points[pointIndex].first < 0 ? 0 : points[pointIndex].first / gridSideLength + 1;
		gridIndex.second = points[pointIndex].second < 0 ? 0 : points[pointIndex].second / gridSideLength + 1;
		
		for (int i = 0; i < k; i++)
		{
			double theta = ((double)std::rand() / (double)RAND_MAX) * 6.283185;
			double radius = r + ((double)std::rand() / (double)RAND_MAX) * r;
			std::pair<int, int> newPoint = { points[pointIndex].first + std::sin(theta) * radius, points[pointIndex].second + std::cos(theta) * radius };
			
			std::pair<int, int> newGridIndex;
			newGridIndex.first = newPoint.first < 0 ? newPoint.first / gridSideLength : newPoint.first / gridSideLength + 1;
			newGridIndex.second = newPoint.second < 0 ? newPoint.second / gridSideLength : newPoint.second / gridSideLength + 1;

			bool collision = false;

			if (newGridIndex.first < 0 || newGridIndex.second < 0 || newGridIndex.first > grid.size() - 1 || newGridIndex.second > grid[0].size() - 1 ) {
				collision = true;
			}

			for (int x = -2; x < 2; x++)
			{
				if (collision)
					break;
				for (int y = -2; y < 2; y++)
				{	
					if (x == 0 && y == 0) {
						if (grid[newGridIndex.first][newGridIndex.second] != -1) {
							collision = true;
							break;
						}
					}
					else if (!collision) {
						if (newGridIndex.first + x >= 0 && newGridIndex.second + y >= 0 && newGridIndex.first + x < grid.size() && newGridIndex.second + y < grid[0].size()) {
							if (grid[newGridIndex.first + x][newGridIndex.second + y] == -1) {
								continue;
							}
							else {
								int neighbourIndex = grid[newGridIndex.first + x][newGridIndex.second + y];
								int xDiff = std::abs(points[neighbourIndex].first - newPoint.first);
								int yDiff = std::abs(points[neighbourIndex].second - newPoint.second);
								if (sqrt(xDiff * xDiff + yDiff * yDiff) < r) {
									collision = true;
									break;
								}
							}
						}
					}
					
				}
			}
			if (!collision) {
				points.push_back(newPoint);
				grid[newGridIndex.first][newGridIndex.second] = points.size() - 1;
				activeList.push(points.size() - 1);
			}
		}
	}
	return points;
}
