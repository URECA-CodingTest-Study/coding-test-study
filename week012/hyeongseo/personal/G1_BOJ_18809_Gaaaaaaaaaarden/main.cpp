// https://www.acmicpc.net/problem/18809

/*
성공 : 292ms
- 백트래킹, bfs, 완전 탐색

풀이
- 초록색 배양액, 빨간색 배양액 나눠서 백트래킹으로 뿌릴 자리 정하기
- BFS 진행하며 배양액 확산 후 만들 수 있는 꽃 개수 확인

포인트
- 이미 큐에 들어간 곳이 꽃으로 바뀌었을 수 있음!
    - if(garden[curX][curY] == 3) continue;

총평
- 이미 큐에 들어간 곳 꽃으로 바뀌는 코드 추가 안해서 예제 계속 틀림
- 쉬움

*/
#include <bits/stdc++.h>

using namespace std;

int n, m, g, r;

// 0 : 호수
// 1 : 배양액 뿌리기 X
// 2 : 배양액 뿌리기 O
int board[51][51];

// 상, 하, 좌, 우
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// 배양액 뿌릴 수 있는 땅
vector<pair<int, int>> available;

// 배양액 뿌리기로 한 땅인지 확인
// 0 : 빈 곳
// 1 : 초록 배양액
// 2 : 빨간 배양액
int isUsed[2501];

// 배양액 실제 뿌리는 판
int garden[51][51];

// 도달 시간
int dist[51][51];

int ans = 0;

// 배양액 확산 시작
int bfs()
{
    memset(dist, -1, sizeof(dist));
    memset(garden, 0, sizeof(garden));

    // <x, y, 배양액, 도달 시간>
    queue<tuple<int, int>> q;
    int ret = 0; // 꽃 개수
    
    // 배양액 뿌리기
    for(int i = 0; i < (int)available.size(); i++)
    {
        if(isUsed[i] > 0)
        {
            auto [x, y] = available[i];
            dist[x][y] = 0;
            garden[x][y] = isUsed[i];
            q.push({x, y});
        }
    }

    while(!q.empty())
    {
        auto [curX, curY] = q.front();
        q.pop();

        // Point!) 현재 있는 곳 이미 꽃이면 패스
        // 이미 큐에 들어가있었지만 꽃으로 바뀌었을 수도 있음
        if(garden[curX][curY] == 3) continue;

        for(int i = 0; i < 4; i++)
        {
            int nX = curX + dx[i];
            int nY = curY + dy[i];

            if(nX < 0 || nX >= n || nY < 0 || nY >= m) continue; // 범위 확인
            if(board[nX][nY] == 0) continue; // 호수면 불가능
            if(garden[nX][nY] == 3) continue; // 이미 꽃이면 패스

            // 꽃 피울 수 있는지 확인
            // 이미 배양액 뿌려져 있고
            if(garden[nX][nY] > 0)
            {
                // 배양액이 다르고 같은 시간에 도달하면 꽃 피움
                if(dist[curX][curY] + 1 == dist[nX][nY] && garden[curX][curY] != garden[nX][nY])
                {
                    ret++;
                    garden[nX][nY] = 3;
                }
                continue;
            }

            garden[nX][nY] = garden[curX][curY];
            dist[nX][nY] = dist[curX][curY] + 1;

            q.push({nX, nY});
        }
    }

    return ret;
}

// 빨간색 배양액 자리 찾기
void redDfs(int idx, int cnt)
{
    // 빨간색 다 정했으면
    if(cnt == r)
    {
        int ret = bfs();
        ans = max(ans, ret);
        return;
    }

    for(int i = idx; i < (int)available.size(); i++)
    {
        if(isUsed[i] > 0) continue;

        isUsed[i] = 2;
        redDfs(i, cnt + 1);
        isUsed[i] = 0;
    }
}

// 초록색 배양액 자리 찾기
void greenDfs(int idx, int cnt)
{
    // 초록색 자리를 다 정했으면
    if(cnt == g)
    {
        // 빨간색 자리 찾기
        redDfs(0, 0);
        return;
    }

    for(int i = idx; i < (int)available.size(); i++)
    {
        if(isUsed[i] > 0) continue;

        isUsed[i] = 1;
        greenDfs(i, cnt + 1);
        isUsed[i] = 0;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> g >> r;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cin >> board[i][j];

            // 씨앗 뿌릴 수 있는 땅 저장
            if(board[i][j] == 2) available.push_back({i, j});
        }
    }

    greenDfs(0, 0);
    cout << ans << "\n";

    return 0;
}