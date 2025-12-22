// https://www.acmicpc.net/problem/18430

// 분류 : 백트래킹
// 성공 : 백트래킹

/*
문제 접근
- 여러가지 경우의 수를 계산하는 문제여서 "백트래킹"이라고 생각함
- 백트래킹 시 유지되어야 하는 값 (x, y, 현재 합)

--------------------------------------------------

성공
- dfs 진행하며 현재 칸이 아직 사용되지 않았으면
- 가능한 ㄱ자 후보 확인한 후 dfs 진행
- 만약 가능하지 않다면 바로 다음칸으로 패스

--------------------------------------------------

총평
- 조금 고민했었지만 어렵지 않았음
- dfs 시작 전에 좌표 조정 (y가 끝이면 x++, y = 0) 완료하면 8ms
- dfs 시작 후 좌표 조정하면 16ms

*/ 


#include <bits/stdc++.h>

using namespace std;

int n, m;

int board[7][7];

bool isUsed[7][7]; // 현재 칸을 사용했는지

int ans = 0;

// 범위 밖인지 확인
bool isPossible(int x, int y)
{
    if(x < 0 || x >= n || y < 0 || y >= m) return false;
    if(isUsed[x][y]) return false;

    return true;
}

// 상, 하, 좌, 우
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// ㄱ자 만들 수 있는 좌표 위치
int dir[4][2] = {
    {0, 2},
    {0, 3},
    {1, 2},
    {1, 3}
};

void dfs(int x, int y, int sum)
{
    bool tmpIsUsed[7][7];
    memcpy(tmpIsUsed, isUsed, sizeof(tmpIsUsed));

    // y좌표 넘으면 x, y좌표 조정
    if(y >= m)
    {
        x++;
        y = 0;
    }

    // 모든 칸을 순회했으면 값 비교
    if(x >= n)
    {
        ans = max(ans, sum);
        return;
    }

    // 현재 칸 아직 사용안됐으면
    if(!isUsed[x][y])
    {
        for(int i = 0; i < 4; i++)
        {
            int tmp = 0;
            bool can = true;
            isUsed[x][y] = true;

            for(int j = 0; j < 2; j++)
            {
                int curDir = dir[i][j];
                int nX = x + dx[curDir];
                int nY = y + dy[curDir];

                // 현재 ㄱ자를 선택하지 못하면 break
                if(!isPossible(nX, nY))
                {
                    can = false;
                    break;
                }

                isUsed[nX][nY] = true;
                tmp += board[nX][nY];
            }

            // ㄱ자 가능하면 dfs
            if(can) dfs(x, y + 1, sum + board[x][y] * 2 + tmp);
            memcpy(isUsed, tmpIsUsed, sizeof(isUsed));
        }
    }

    // 다음 칸 dfs
    dfs(x, y + 1, sum);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cin >> board[i][j];
        }
    }

    dfs(0, 0, 0);

    cout << ans << "\n";

    return 0;
}