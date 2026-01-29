// https://www.acmicpc.net/problem/13459

/*
첫 시도 성공 : 208ms (백트래킹)
- 각 보드를 상, 하, 좌, 우 기울이며 백트래킹 진행
- 10회 넘으면 실패
- 파란 공 빠지면 리턴
- 빨간 공만 빠지면 성공
- 아니면 백트래킹 진행

실행 시간 느린 이유
=> memcpy()로 전체 보드를 계속 복사
=> 상, 하, 좌, 우 4방향 다 직접 한 칸씩 이동
=> 끝났는지 검사할 때 전체 판 순회해서 성공 / 실패 여부 판단

------------------------------------------------------------

최적화 : 0ms (BFS) - 챗지피티
- 전체 보드를 움직일 필요 없음
- <빨간 X, 빨간 Y, 파란 X, 파란 Y> 상태만 저장
- 보드에는 공 위치 표시 X, 장애물, 출구만 표시
- 만약 빨강, 파랑 위치가 겹치면 이동한 거리를 보고 뭐가 더 먼저 나와야하는지 계산

-------------------------------------------------------------

총평
- 왜 BFS 풀이를 생각해내지 못했을까?
- 역시 백트래킹은 풀면서도 시간 걱정됐는데 역시 느렸음
- 앞으로 기울이기 문제 나오면 풀이 떠올려보자

*/

#include <bits/stdc++.h>

using namespace std;

char board[11][11];

int n, m;
int rX, rY, bX, bY;

bool vis[11][11][11][11]; // 빨간 공 위치, 파란 공 위치 방문 여부

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int ans = 0;

pair<int, int> moveBall(int x, int y, int d)
{
    while(true)
    {
        int nX = x + dx[d];
        int nY = y + dy[d];

        // 다음 칸이 벽이면 여기서 멈춰야 함
        if(board[nX][nY] == '#') break;

        x = nX;
        y = nY;

        // 구멍에 빠지면 멈춰야 함
        if(board[x][y] == 'O') break;
    }

    return {x, y};
}

void bfs()
{
    // <빨강X, 빨강Y, 파랑X, 파랑Y, 이동 횟수>
    queue<tuple<int, int, int, int, int>> q;
    q.push({rX, rY, bX, bY, 0});

    vis[rX][rY][bX][bY] = true;

    while(!q.empty())
    {
        auto [cRx, cRy, cBx, cBy, cnt] = q.front();
        q.pop();

        if(cnt >= 10) continue;

        for(int i = 0; i < 4; i++)
        {
            auto [nRx, nRy] = moveBall(cRx, cRy, i);
            auto [nBx, nBy] = moveBall(cBx, cBy, i);

            // 파란색 빠지면 실패
            if(board[nBx][nBy] == 'O') continue;

            // 빨간색만 빠지면 끝
            else if(board[nRx][nRy] == 'O')
            {
                ans = 1;
                return;
            }

            // 빨간공, 파란공이 겹치면
            // 더 많이 이동한 공을 한 칸 뒤로 보낸다.
            if(nRx == nBx && nRy == nBy)
            {
                int rDist = abs(cRx - nRx) + abs(cRy - nRy);
                int bDist = abs(cBx - nBx) + abs(cBy - nBy);

                if(rDist > bDist)
                {
                    nRx -= dx[i];
                    nRy -= dy[i];
                }

                else
                {
                    nBx -= dx[i];
                    nBy -= dy[i];
                }
            }

            // 이미 방문했으면 패스
            if(vis[nRx][nRy][nBx][nBy]) continue;

            vis[nRx][nRy][nBx][nBy] = true;
            q.push({nRx, nRy, nBx, nBy, cnt + 1});
        }
    }

}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m;

    for(int i = 0; i < n; i++)
    {
        string s;
        cin >> s;

        for(int j = 0; j < m; j++)
        {
            board[i][j] = s[j];

            if(board[i][j] == 'R')
            {
                rX = i;
                rY = j;
                board[i][j] = '.';
            }

            else if(board[i][j] == 'B')
            {
                bX = i;
                bY = j;
                board[i][j] = '.';
            }
        }
    }

    bfs();

    cout << ans << "\n";

    return 0;
}


/*
#include <bits/stdc++.h>

using namespace std;

int n, m;

char board[11][11];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int ans = 0;

int rX, rY, bX, bY, gX, gY;
void printBoard()
{
    cout << "\n========================\n";
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// 위로 기울이기
void moveUp()
{
    for(int i = 1; i < n - 1; i++)
    {
        for(int j = 1; j < m - 1; j++)
        {
            if(board[i][j] == 'R' || board[i][j] == 'B')
            {
                char cur = board[i][j];
                board[i][j] = '.';

                int x = i;
                int y = j;

                while(board[x][y] == '.')
                {
                    x += dx[0];
                    y += dy[0];
                }

                if(board[x][y] != 'O' && board[x+1][y] != 'O') board[x+1][y] = cur;
            }
        }
    }
}


// 아래로 기울이기
void moveDown()
{
    for(int i = n - 2; i >= 1; i--)
    {
        for(int j = 1; j < m - 1; j++)
        {
            if(board[i][j] == 'R' || board[i][j] == 'B')
            {
                char cur = board[i][j];
                board[i][j] = '.';

                int x = i;
                int y = j;

                while(board[x][y] == '.')
                {
                    x += dx[1];
                    y += dy[1];
                }

                if(board[x][y] != 'O' && board[x-1][y] != 'O') board[x-1][y] = cur;
            }
        }
    }
}

// 왼쪽으로 기울이기
void moveLeft()
{
    for(int i = 1; i < m - 1; i++)
    {
        for(int j = 1; j < n - 1; j++)
        {
            if(board[j][i] == 'R' || board[j][i] == 'B')
            {
                char cur = board[j][i];
                board[j][i] = '.';

                int x = j;
                int y = i;

                while(board[x][y] == '.')
                {
                    x += dx[2];
                    y += dy[2];
                }

                if(board[x][y] != 'O' && board[x][y+1] != 'O') board[x][y+1] = cur;
            }
        }
    }
}

// 오른쪽으로 기울이기
void moveRight()
{
    for(int i = m - 2; i >= 1; i--)
    {
        for(int j = 1; j < n - 1; j++)
        {
            if(board[j][i] == 'R' || board[j][i] == 'B')
            {
                char cur = board[j][i];
                board[j][i] = '.';

                int x = j;
                int y = i;

                while(board[x][y] == '.')
                {
                    x += dx[3];
                    y += dy[3];
                }

                if(board[x][y] != 'O' && board[x][y-1] != 'O') board[x][y-1] = cur;
            }
        }
    }
}

int isFinish()
{
    bool rFound = false;
    bool bFound = false;

    // r이 없고 b가 남아 있으면 성공
    for(int i = 1; i < n - 1; i++)
    {
        for(int j = 1; j < m - 1; j++)
        {
            if(board[i][j] == 'R') rFound = true;
            else if(board[i][j] == 'B') bFound = true;
        }
    }

    if(!bFound) return -1;
    else if(!rFound)
    {
        ans = 1;
        return 0;
    }
    else return 1;
}
void dfs(int cnt)
{
    int result = isFinish();
    
    if(ans == 1) return;
    if(result <= 0) return;

    // 일단 10번 이동하면 끝
    if(cnt == 10) return;

    char newBoard[11][11];
    memcpy(newBoard, board, sizeof(newBoard)); // 원본 저장
    moveUp();
    // cout << "상";
    // printBoard();
    dfs(cnt+1);

    memcpy(board, newBoard, sizeof(board)); // 원상 복구
    moveDown();
    // cout << "하";
    // printBoard();
    dfs(cnt+1);

    memcpy(board, newBoard, sizeof(board)); // 원상 복구
    moveLeft();
    // cout << "좌";
    // printBoard();
    dfs(cnt+1);

    memcpy(board, newBoard, sizeof(board)); // 원상 복구
    moveRight();
    // cout << "우";
    // printBoard();
    dfs(cnt+1);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for(int i = 0; i < n; i++)
    {
        string s;
        cin >> s;

        for(int j = 0; j < m; j++)
        {
            board[i][j] = s[j];
        }
    }

    dfs(0);

    cout << ans << "\n";

    return 0;
}
*/