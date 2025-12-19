// https://www.acmicpc.net/problem/1946

// 문제 잘못 읽음;;
// 입력 성적 X => 순위 O

#include <bits/stdc++.h>

using namespace std;

int t, n;

vector<pair<int, int>> scores;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;

    while(t--)
    {
        cin >> n;

        scores.clear();
        for(int i = 0; i < n; i++)
        {
            int test1, test2;
            cin >> test1 >> test2;

            scores.push_back({test1, test2});
        }

        // 서류 순위 기준으로 오름차순 정렬
        sort(scores.begin(), scores.end());

        int ans = 0;
        int maxRank = 100001; // 현재 면접 최고 순위

        // 차례대로 순회하며 내 면접 순위보다 높은 면접 순위를 가진 지원자가 나오면 합격
        for(int i = 0; i < n; i++)
        {
            auto [test1, test2] = scores[i];

            if(test2 < maxRank)
            {
                ans++;
                maxRank = test2;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}