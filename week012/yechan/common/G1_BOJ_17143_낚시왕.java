package week012.yechan.common;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class G1_BOJ_17143_낚시왕 {
     static int R, C, M;
    static List<Shark> sharks;
    static List<Shark> answer;

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        R = Integer.parseInt(st.nextToken());
        C = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());

        sharks = new ArrayList<>();
        answer = new ArrayList<>();

        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(br.readLine());
            int r = Integer.parseInt(st.nextToken());
            int c = Integer.parseInt(st.nextToken());
            int s = Integer.parseInt(st.nextToken());
            int d = Integer.parseInt(st.nextToken());
            int z = Integer.parseInt(st.nextToken());

            sharks.add(new Shark(r, c, s, d, z));
        }

        for (int col = 1; col <= C; col++) {

            // 1. 낚시
            catchShark(col);

            // 2. 상어 이동
            sharks = moveSharks(sharks);

        }

        int result = 0;
        // 잡은 상어 크기 총합
        for(Shark s : answer){
            result += s.z;
        }

        System.out.println(result);

    }

    static List<Shark> moveSharks(List<Shark> sharks) {
        Shark[][] newMap = new Shark[R + 1][C + 1]; // 1-index 사용 추천

        for (Shark sh : sharks) {
            int r = sh.r, c = sh.c, s = sh.s, d = sh.d;

            // 1) 속력 줄이기
            if (d == 1 || d == 2)
                s %= (R - 1) * 2;
            else
                s %= (C - 1) * 2;

            // 2) s번 이동하면서 방향 전환
            for (int i = 0; i < s; i++) {
                if (d == 1) { // 위
                    if (r == 1) {
                        d = 2;
                        r++;
                    } else
                        r--;
                } else if (d == 2) { // 아래
                    if (r == R) {
                        d = 1;
                        r--;
                    } else
                        r++;
                } else if (d == 3) { // 오른쪽
                    if (c == C) {
                        d = 4;
                        c--;
                    } else
                        c++;
                } else { // 왼쪽(4)
                    if (c == 1) {
                        d = 3;
                        c++;
                    } else
                        c--;
                }
            }

            // 3) newMap에 배치 (충돌 처리)
            Shark moved = new Shark(r, c, sh.s, d, sh.z); // ⚠️ s는 원래 속력 유지(문제 요구)
            if (newMap[r][c] == null || newMap[r][c].z < moved.z) {
                newMap[r][c] = moved;
            }
        }

        // 4) newMap에 남은 상어들만 리스트로 재구성
        List<Shark> next = new ArrayList<>();
        for (int i = 1; i <= R; i++) {
            for (int j = 1; j <= C; j++) {
                if (newMap[i][j] != null)
                    next.add(newMap[i][j]);
            }
        }
        return next;
    }

    private static void catchShark(int col) {
        Shark target = null;

        // 1. 같은 열에서 가장 위에 있는 상어 찾기
        for (Shark s : sharks) {
            if (s.c == col) {
                if (target == null || s.r < target.r) {
                    target = s;
                }
            }
        }

        // 2. 잡을 상어가 있으면
        if (target != null) {
            answer.add(target);
            sharks.remove(target);
        }
    }

    static class Shark {
        int r, c, s, d, z;

        Shark(int r, int c, int s, int d, int z) {
            this.r = r;
            this.c = c;
            this.s = s;
            this.d = d;
            this.z = z;
        }
    }
}
