package baekjoon.dijkstra;

import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Scanner;


/**
 * 다음 좌표가 느낌표일때, 처음 이해한건 방향을 무조건 90도로 꺾고 큐에 넣어야하는줄알았는데
 * 느낌표인 자리에 거울을 무조건 설치하는게 아니라 거울을 설치 안하고 가던 방향대로 쭉 직진해도 되는걸 몰랐었다.
 * 상당히 헷갈려 문제를 오래 붙잡고 있었음
 */
public class BaekJoon_2151 {

    static int N;
    static char[][] grid;


    static int[] dy = {-1, 1, 0, 0};
    static int[] dx = {0, 0, -1, 1};

    static int min = Integer.MAX_VALUE;

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        grid = new char[N][N];
        sc.nextLine();

        int[] doors = new int[4]; // startY, startX, endY, endX
        int idx = 0;

        for (int i = 0; i < N; i++) {
            String s = sc.nextLine();
            for (int j = 0; j < N; j++) {
                grid[i][j] = s.charAt(j);
                if (grid[i][j] == '#') {
                    doors[idx++] = i;
                    doors[idx++] = j;
                }
            }
        }

        bfs(doors[0], doors[1], doors[2], doors[3]);
        System.out.println(min);
    }

    private static void bfs(int startY, int startX, int endY, int endX) {
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> a[3] - b[3]);
        boolean[][][] visited = new boolean[N][N][4];

        // 시작 위치에서 4방향으로 모두 탐색 시작
        for (int dir = 0; dir < 4; dir++) {
            pq.add(new int[]{startY, startX, dir, 0});
            visited[startY][startX][dir] = true;
        }

        while (!pq.isEmpty()) {
            int[] cur = pq.poll();
            int y = cur[0];
            int x = cur[1];
            int dir = cur[2];
            int mirrorCount = cur[3];

            if (y == endY && x == endX) {
                min = Math.min(min, mirrorCount);
            }

            int ny = y + dy[dir];
            int nx = x + dx[dir];

            if (ny >= 0 && nx >= 0 && ny < N && nx < N && grid[ny][nx] != '*') {

                // 직진
                if (!visited[ny][nx][dir]) {
                    visited[ny][nx][dir] = true;
                    pq.add(new int[]{ny, nx, dir, mirrorCount});
                }

                // 거울 설치 가능
                if (grid[ny][nx] == '!') {
                    if (dir < 2) {
                        for (int nd = 2; nd < 4; nd++) {
                            if (!visited[ny][nx][nd]) {
                                visited[ny][nx][nd] = true;
                                pq.add(new int[]{ny, nx, nd, mirrorCount + 1});
                            }
                        }
                    } else {
                        for (int nd = 0; nd < 2; nd++) {
                            if (!visited[ny][nx][nd]) {
                                visited[ny][nx][nd] = true;
                                pq.add(new int[]{ny, nx, nd, mirrorCount + 1});
                            }
                        }
                    }
                }

            }
        }
    }
}
