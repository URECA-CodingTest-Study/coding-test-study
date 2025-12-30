package week012.yechan.common;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class S1_BOJ_1946_신입사원 {

    static int T, N;
    static List<Employee> list;

    public static void main(String[] args) throws Exception, IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        T = Integer.parseInt(br.readLine());

        for (int i = 0; i < T; i++) {
            list = new ArrayList<>();
            N = Integer.parseInt(br.readLine());
            for (int j = 0; j < N; j++) {
                st = new StringTokenizer(br.readLine());
                int g1 = Integer.parseInt(st.nextToken());
                int g2 = Integer.parseInt(st.nextToken());

                list.add(new Employee(g1, g2));
            }

            // 서류 성적을 기준으로 정렬
            list.sort((a, b) -> a.g1 - b.g1);

            int count = 1;
            int bestInterview = list.get(0).g2;

            // 이미 갈수록 서류 성적은 낮아지기에
            // 면접 점수가 높지않다면 선발 될 수 없음.
            for (int k = 1; k < N; k++) {
                if (list.get(k).g2 < bestInterview) {
                    count++;
                    bestInterview = list.get(k).g2;
                }
            }

            System.out.println(count);

        }

    }

    static class Employee {
        int g1;
        int g2;

        Employee(int g1, int g2) {
            this.g1 = g1;
            this.g2 = g2;
        }
    }
}