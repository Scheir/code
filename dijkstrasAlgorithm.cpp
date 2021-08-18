/*
  Dijkstra's algorithm example
  You are at start location [0, 0] in mountain area of NxN and you can only move in one of the four cardinal directions
  (i.e. North, East, South, West). Return minimal number of climb rounds to target location [N-1, N-1]. 
  Number of climb rounds between adjacent locations is defined as difference of location altitudes (ascending or descending).
  Maze:
  "700000\n"
  "077770\n"
  "077770\n"
  "077770\n"
  "077770\n"
  "000007";
*/

#include <iostream>
#include <functional>
#include <string>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

struct cord{
  int X = 0;
  int Y = 0;
  int count = 0;
};


int path_finder(string maze) {
  cout << "NEW " << endl;
  vector<string> vec;
  stringstream ss(maze);
  string temp;
  while(getline(ss, temp, '\n')){
    vec.push_back(temp);
  }
  
  vector<int> dx({0,1,0,-1});
  vector<int> dy({1,0,-1,0});
  auto comp = [](cord a, cord b){
    return a.count > b.count;
  };
  priority_queue<cord,vector<cord>,decltype(comp)> q(comp);
  vector<vector<bool>> vb(vec.size(), vector<bool>(vec.size(), false));
  q.push({0,0,0});
  
  int count = 0;
  //Dijkstra's algorithm
  while(!q.empty()){
    int x = q.top().X;
    int y = q.top().Y;
    count = q.top().count;
    vb[x][y] = true;
    if(x == vec.size()-1 && y == vec.size()-1){
     return count;
    }
    q.pop();
    for(int i = 0; i < dx.size(); i++){
      int xx = x + dx[i];
      int yy = y + dy[i];
      if(xx >= 0 && yy >= 0 && xx < vec.size() && yy < vec.size() && !vb[xx][yy]){
        int next = vec[xx][yy]-'0';
        int cur = vec[x][y]-'0';
        q.push({xx,yy,count+(abs(next-cur))});
      }
    }
  }
  
  return count;
}
