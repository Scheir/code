#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

struct cord{
  int X;
  int Y;
  int count;
};


/* Input to path_finder
Find closest way from topleft corner to bottom right corner, where walls 'W'
cant be passed.
Maze:
    .W.
    .W.
    ...
  */

int path_finder(string maze) {
  vector<string> vec;
  stringstream ss(maze);
  string temp;
  while(getline(ss, temp, '\n')){
    vec.push_back(temp);
  }
  
  vector<int> dx({0,1,0,-1});
  vector<int> dy({1,0,-1,0});
  queue<cord> q;
  q.push({0,0,0});
  
  //Dijkstra's algorithm
  while(!q.empty()){
    int x = q.front().X;
    int y = q.front().Y;
    int count = q.front().count;
    if(x == vec.size()-1 && y == vec.size()-1){
     return count;
    }
    q.pop();
    for(int i = 0; i < dx.size(); i++){
      int xx = x + dx[i];
      int yy = y + dy[i];
      if(xx >= 0 && yy >= 0 && xx < vec.size() && yy < vec.size() && vec[xx][yy] != 'X' && vec[xx][yy] != 'W'){
        vec[xx][yy] = 'X';
        q.push({xx,yy,count+1});
      }
    }
  }
  
  return -1;
}
