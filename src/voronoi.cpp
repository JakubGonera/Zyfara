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