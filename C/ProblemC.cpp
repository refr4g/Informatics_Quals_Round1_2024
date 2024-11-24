#include <iostream>
#include <vector>
#include <queue>
#include <string>
#define INF 1000000000

using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    
    vector<string>g(n);
    for(int i=0;i<n;i++)
        cin>>g[i];    

    vector<vector<int>>ft(n,vector<int>(m,INF));
    vector<vector<int>>st(n,vector<int>(m,INF));
    queue<pair<int,int>>q1,q2;

    int sx=-1,sy=-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(g[i][j]=='X'){
                ft[i][j]=0;
                q1.push({i,j});
            }else if(g[i][j]=='S'){
                sx=i;
                sy=j;
                st[i][j]=0;
                q2.push({i,j});
            }
        }
    }

    int d[5][2]={{-1,0},{1,0},{0,-1},{0,1},{0,0}};
    while(!q1.empty()){
        int x=q1.front().first,y=q1.front().second;
        q1.pop();
        int t=ft[x][y];
        for(int k=0;k<4;k++){
            int nx=x+d[k][0],ny=y+d[k][1];
            if(nx>=0&&nx<n&&ny>=0&&ny<m){
                if(g[nx][ny]!='*'&&ft[nx][ny]==INF){
                    ft[nx][ny]=t+1;
                    q1.push({nx,ny});
                }
            }
        }
    }

    while(!q2.empty()){
        int x=q2.front().first,y=q2.front().second;
        q2.pop();
        int t=st[x][y];
        for(int k=0;k<5;k++){
            int nx=x+d[k][0],ny=y+d[k][1];
            int nt=t+1;
            if(nx>=0&&nx<n&&ny>=0&&ny<m){
                if(g[nx][ny]!='*'&&st[nx][ny]==INF){
                    if(ft[nx][ny]>nt){
                        st[nx][ny]=nt;
                        q2.push({nx,ny});
                    }
                }
            }
        }
    }

    int res=0;
    for(int i=0; i < n; i++){
        for(int j=0; j < m; j++){
            if(st[i][j] != INF && st[i][j] < ft[i][j]){
                res++;
            }
        }
    }

    cout << res << endl;
    return 0;
}