#include <iostream>
#include<stdio.h>
#include <string>
#include <string.h>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <list>
#include <set>
#include <functional>
using namespace std;
const int inf = 98765432;
#define max(a,b) (a>b ? a:b)
#define min(a,b) (a<b ? a:b)

int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
char way[4] = {'R', 'L', 'D', 'U'};
char A[11][11];
typedef struct vertx {
  int x;
  int y;
  string path;
} vertx;
typedef struct result {
  string path;
  int p_size;
  bool operator < (const result &result2) const {
    return p_size > result2.p_size;
  }
}result;


int main() {
  int T;
  int N, M;
  cin >> T;
  while (T--) {
    queue<vertx> q;
    queue<vertx> path_q;
    set<result> st;
    
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= M; j++) {
        cin >> A[i][j];
        if (A[i][j] == '.') {
          q.push(vertx{i, j, ""});
          
        }
        
      }
    }


    // bfs 구현
    
    while(!q.empty()) { // . 경로 저장된 큐
      vertx v;
      v = q.front();
      q.pop();
      path_q.push(v);
      while (!path_q.empty()) {
        vertx path_front = path_q.front();
        path_q.pop();
        int front_x = path_front.x;
        int front_y = path_front.y;
        
        string front_st = path_front.path;
        int front_len = front_st.length();
        char front_c;
        if (front_len != 0) {
          front_c = front_st[front_len - 1];
        }
        else {
          front_c = '\0';
        }
        if (front_len >= 10) {
          continue;
       }
        for (int i = 0; i < 4; i++) { // 0 = R    1 = L    2 = D    3 = U   
          if (front_c == way[i]) {
            continue;
          }
          else if (front_c == 'R' && i == 1) {
            continue;
          }
          else if (front_c == 'L' && i == 0) {
            continue;
          } 
          else if (front_c == 'D' && i == 3) {
            continue;
          }
          else if (front_c == 'U' && i == 2) {
            continue;
          }
          bool goal = false;
          while (1) {
            if (A[front_x+dx[i]][front_y+dy[i]] == 'O') {
              st.insert({front_st + way[i], (int)front_st.size() + 1});
              goal = true;
              break;
            } 
            else if (A[front_x+dx[i]][front_y+dy[i]] == '#') {
              break;
            }
            else if (front_x + dx[i] == v.x && front_y + dy[i] == v.y) {
              front_x = path_front.x;
              front_y = path_front.y;
              break;
            }
            else {
              front_x += dx[i];
              front_y += dy[i];
            }
          } //while(1)
          
          if ((path_front.x != front_x || path_front.y != front_y) && (goal == false)) { // 처음과 경로가 달라졌을때
            path_q.push(vertx{front_x, front_y, front_st + way[i]}); // 변경 경로와 way push
          }
        }//for 0~4


      } // while path_q

    } // while q
    
    set<result>::iterator it;
    it = st.begin();
    result ans;
    for (it; it != st.end(); it++) {
      ans = *it;
      cout << ans.path << endl;
    }
  }// while T


}