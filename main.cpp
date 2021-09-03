#include<bits/stdc++.h>
using namespace std;

int dRow[4] = {1, -1, 0, 0};
int dCols[4] = {0, 0, 1, -1};

inline bool valid(int row, int cols, int n, int m){
    return (row >= 0 && row < n && cols >= 0 && cols < m);
}

void print(){
	cout<<"  *********************************************************\n";
	cout<<"  *               WELCOME TO MAZE SOLVER                  *\n";
	cout<<"  *                                                       *\n";
	cout<<"  * Inputs Reqd:                                          *\n";
	cout<<"  *  1. Size of Maze (N x M)                              *\n";
	cout<<"  *  2. Maze containing Start Point [A] and End point[B]  *\n";
	cout<<"  *  3. Walls marked as [#] and passage as [.]            *\n";
	cout<<"  *                                                       *\n";
	cout<<"  * Output:                                               *\n";
	cout<<"  * The program will ouput whether there is a way from    *\n";
	cout<<"  * A to B. If yes, then no of moves and the corresponding*\n";
	cout<<"  * moves will be displayed                               *\n";
	cout<<"  *                                                       *\n";
	cout<<"  * Moves:                                                *\n";
	cout<<"  *       1. Up    [U]                                    *\n";
	cout<<"  *       2. Down  [D]                                    *\n";
	cout<<"  *       3. Left  [L]                                    *\n";
	cout<<"  *       4. Right [R]                                    *\n";
	cout<<"  *********************************************************\n\n";
}

int main() { 
    //ios::sync_with_stdio(0);
    //cin.tie(0); cout.tie(0);
	print();
    int N, M ;
    cout<<"Enter size (NxM): ";
    cin >> N >> M ;
	cout<<"\nEnter Maze: \n";
    vector<vector<char> > v (N, vector<char>(M ));
    vector<vector<bool> > visited(N, vector<bool>(M, 0));
    pair<int, int> start;
    for(int a = 0; a < N; ++a){
        for(int b = 0; b < M; ++b){
            cin >> v[a][b];
            if(v[a][b] == 'A')
                start = make_pair(a, b);
        }
    }
    cout<<"\n";
    list<pair<int, int> > q;
    visited[start.first][start.second] = 1;
    q.push_back(start);
    map<pair<int, int>, pair<pair<int, int>,char> > parent;
    while (!q.empty())
    {
        auto s = q.front();
        int a = s.first, b = s.second;
        q.pop_front();

        for(auto i : dRow){
            for(auto j : dCols){
                if(valid(a+i, b+j, N, M) && (abs(i) != abs(j)) && !visited[a+i][b+j] && (v[a+i][b+j] == '.' || v[a+i][b+j] == 'B') ){
                    char dir;
                    if(i == 1 && j == 0)
                        dir = 'D';
                    if(i == -1 && j == 0)
                        dir = 'U';
                    if(j == 1 && i == 0)
                        dir = 'R';
                    if(j == -1 && i == 0)
                        dir = 'L';

                    parent[make_pair(a+i, b+j)] = make_pair(make_pair(a, b), dir);

                    if(v[a+i][b+j] == 'B'){
                        auto end = make_pair(a+i, b+j);
                        string res = "";
                        while(true){
                            res += parent[end].second;
                            end = parent[end].first;
                            if(end.first == start.first && end.second == start.second){
                                break;
                            }
                        }
                        reverse(res.begin(), res.end()); 
                        cout << "YES\n";
                        cout << res.length() << "\n";
                        cout << res;
                        return 0;
                    }

                    visited[a+i][b+j] = 1;
                    q.push_back(make_pair(a+i, b+j));
                }
            }
        }
    }

    cout << "NO";
}