// https://www.acmicpc.net/problem/17143

// 분류 : 구현, 시뮬레이션

// 성공 : 960ms

/*
문제 접근
- 그냥 빡구현
- 문제 차근차근 읽으면서 정리

---------------------------------------------------------

옛날에 풀었을 때는 152ms 이번에는 960ms
Why??
- 상어 이동 로직에서 정직하게 한 칸씩 이동함
=> 최적화 가능

---------------------------------------------------------

이동 로직 최적화 (챗지피티)
- 이동 주기를 구한다면 불필요한 이동을 줄일 수 있음
    - 이동 주기 : 각 경계 찍고 현재 위치까지 돌아왔을 떄 거친 칸

- 상 / 하 이동 주기 : cycle = 2 * (r - 1)
- 좌 / 우 이동 주기 : cycle = 2 * (c - 1)
- curS %= cycle

- 실행 결과 : 184ms로 줄어듦

---------------------------------------------------------

총평
- 이전에 어른 상어 문제를 풀어서 그런지 어렵지 않게 풂
- 상어가 차례대로 이동할 때에는 새로운 배열 만들어서 거기에 표시하고 마지막에 원본 배열에 복사하기
- 지역 변수 배열은 무조건 초기화하기! (안하면 쓰레기값 들어있음)

*/

#include <bits/stdc++.h>

using namespace std;

int r, c, m;

// 제자리, 상, 하, 우, 좌
int dx[5] = {0, -1, 1, 0, 0};
int dy[5] = {0, 0, 0, 1, -1};

// 상어 구조체
struct Shark
{
    int r, c; // (x, y)
    int s; // 속력
    int d; // 이동 방향
    int z; // 크기

};

Shark sharks[10001];
bool isDeleted[10001]; // 현재 상어가 삭제되었는지 확인
int board[101][101]; // 상어 번호 저장하는 판

int ans = 0;

// 현재 열에서 땅과 가장 가까운 상어 잡기
void catchSharks(int x)
{
    for(int i = 1; i <= r; i++)
    {
        // 빈 칸이면 패스
        if(board[i][x] == 0) continue;

        int curShark = board[i][x]; // 현재 상어 번호
        ans += sharks[curShark].z; // 상어 크기 더함
        isDeleted[curShark] = true; // 상어 삭제
        board[i][x] = 0; // 상어 잡아서 판에서 제거
        
        break;
    }
}

// 상어 이동
void moveSharks()
{
    int newBoard[101][101]; // 새로운 판
    memset(newBoard, 0, sizeof(newBoard)); // 지역 변수라 초기화 필수!!! (이거 때문에 틀렸었음)

    for(int i = 1; i <= m; i++)
    {
        if(isDeleted[i]) continue; // 삭제된 상어면 패스

        auto [curX, curY, curS, curD, curZ] = sharks[i];

        int cycle = 0; // 주기
        if(curD <= 2) cycle = 2 * (r - 1); // 상하 이동
        else cycle = 2 * (c - 1); // 좌우 이동

        curS %= cycle; // 이동 횟수를 주기로 나누기

        // 상어 이동
        while(curS--)
        {
            int nX = curX + dx[curD];
            int nY = curY + dy[curD];

            // 경계 넘어서면 방향 반대로 바꾸기
            if(nX < 1 || nX > r || nY < 1 || nY > c)
            {
                if(curD % 2 == 1) curD++;
                else curD--;

                nX = curX + dx[curD];
                nY = curY + dy[curD];
            }

            curX = nX;
            curY = nY;
        }

        // 이동하려는 칸에 상어 번호
        // 0이면 없음
        int originShark = newBoard[curX][curY];

        // 도착 칸의 상어가 나보다 크면
        // 여기서도 처음에 그냥 originShark > curZ로 해서 틀림
        if(sharks[originShark].z > curZ)
        {
            isDeleted[i] = true; // 현재 이동 상어 삭제
        }

        // 도착 칸의 상어가 나보다 작으면
        else
        {
            isDeleted[originShark] = true;

            // 이동 완료
            newBoard[curX][curY] = i;

            // 상어의 위치, 방향은 바뀔 수 있으므로 다시 업데이트
            sharks[i].r = curX;
            sharks[i].c = curY;
            sharks[i].d = curD;
        }
    }

    // 원본 배열에 이동 결과 복사
    memcpy(board, newBoard, sizeof(board));
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> r >> c >> m;

    for(int i = 1; i <= m; i++)
    {
        int r, c, s, d, z;
        cin >> r >> c >> s >> d >> z;

        sharks[i] = {r, c, s, d, z};
        board[r][c] = i; // 상어 위치 표시
    }

    // 낚시왕이 오른쪽으로 한 칸 이동
    for(int i = 1; i <= c; i++)
    {
        catchSharks(i); // 상어 잡기
        moveSharks(); // 상어 이동
    }

    cout << ans << "\n";

    return 0;
}