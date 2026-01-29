// https://www.acmicpc.net/problem/18500

/*
3% 틀림
- 클러스터의 각 칸에서 가장 적게 떨어질 수 있는 칸 개수를 기준으로 떨어뜨림
- 근데 안 풀림

---------------------------------------------------------------

성공 (미네랄 1 내풀이 참고) : 28ms
- 현재 클러스터의 가장 바닥 좌표 구함
- 현재 클러스터 칸 모두 .으로 비우기
- 바닥 좌표에서 한 칸씩 내려가며 클러스터 각 칸이 x인지 확인
- x인 칸 만나면 끝
- 클러스터 각 칸 순회하며 curX + curH, curY에 x표시

---------------------------------------------------------------

총평
- 미네랄 코드 그대로 냈는데 통과됨;;
- 왜 못 풀었지??
- 아쉽

*/
#include <bits/stdc++.h>

using namespace std;

int r, c, n, h;
char board[101][101];
bool vis[101][101];

// 좌, 우, 상, 하
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

// 정답 출력
void printBoard()
{
    // cout << "\n===================\n";
    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++)
        {
            cout << board[i][j];
        }
        cout << "\n";
    }
    // cout << "\n";
}

// 왼쪽에서 던지기
void fromLeft(int height)
{
    for(int i = 0; i < c; i++)
    {
        if(board[height][i] == 'x')
        {
            board[height][i] = '.';
            return;
        }
    }
}

// 오른쪽에서 던지기
void fromRight(int height)
{
    for(int i = c-1; i >= 0; i--)
    {
        if(board[height][i] == 'x')
        {
            board[height][i] = '.';
            return;
        }
    }
}

// 클러스터 떨어져있으면 떨구기
bool drop(int x, int y)
{
    queue<pair<int, int>> q;
    q.push({x, y});

    vis[x][y] = true;

    int maxX = 0;

    bool isAir = true;

    vector<pair<int,int>> path;
    while(!q.empty())
    {
        auto [curX, curY] = q.front();
        maxX = max(maxX, curX); // 현재 클러스터의 가장 바닥 좌표 구하기
        path.push_back({curX, curY}); // 지나온 경로 저장
        q.pop();

        // 땅에 붙어있으면 공중에 없음
        if(curX == r - 1) isAir = false;

        for(int i = 0; i < 4; i++)
        {
            int nX = curX + dx[i];
            int nY = curY + dy[i];

            if(nX < 0 || nX >= r || nY < 0 || nY >= c) continue;
            if(board[nX][nY] == '.') continue;
            if(vis[nX][nY]) continue;

            vis[nX][nY] = true;
            q.push({nX, nY});
        }
    }

    if(!isAir) return false;

    // 공중에 떠있는 클러스터 떨구기
    // 일단 다 빈칸으로 만들기
    for(auto [curX, curY] : path)
    {
        board[curX][curY] = '.';
    }

    // 한 칸씩 내려가면서 검사할 값
    int curH = 1;
    while(maxX + curH < r)
    {
        bool isPossible = true;
        for(auto [curX , curY] : path)
        {
            if(board[curX+curH][curY] == 'x')
            {
                isPossible = false;
                break;
            }
        }

        if(!isPossible) break;
        curH++;
    }

    curH--;

    // cout << "curH: " << curH << " maxX: " << maxX << "\n";
    // 최종으로 떨구기
    for(auto [curX, curY] : path)
    {
        board[curX + curH][curY] = 'x';
    }

    return true;
}

// 떨어진 클러스터 찾기
void findCluster()
{
    memset(vis, false, sizeof(vis));

    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++)
        {
            if(board[i][j] == 'x' && !vis[i][j])
            {
                // 클러스터 하나 떨구면 끝
                if(drop(i, j)) return;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> r >> c;

    for(int i = 0; i < r; i++)
    {
        string s;
        cin >> s;

        for(int j = 0; j < c; j++)
        {
            board[i][j] = s[j];
        }
    }

    cin >> n;
    for(int order = 0; order < n; order++)
    {
        cin >> h;
        h = r - h; // 높이 형식에 맞춤

        if(order % 2 == 0) fromLeft(h); // 왼쪽에서 던지기
        else fromRight(h);

        findCluster(); // 클러스터 찾기
    }

    printBoard();

    return 0;
}