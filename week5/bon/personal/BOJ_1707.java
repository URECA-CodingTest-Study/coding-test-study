package baekjoon.graph;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * 이분그래프 같은 노드레밸끼리 연결되면 안된다.
 * dfs로 들어갈때마다 다른색깔로 표현해줌.
 */
public class BaekJoon_1707 {


    static int K,V,E;
    static List<Integer>[] graph;
    static boolean Biparitie;

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        K = sc.nextInt();

        for (int i = 0; i < K; i++) {

            V = sc.nextInt();
            E = sc.nextInt();

            graph = new ArrayList[V+1];
            for (int j = 1; j <V+1; j++) {
                graph[j] = new ArrayList<>();
            }
            for (int j = 0; j < E; j++) {
                int u = sc.nextInt();
                int v = sc.nextInt();
                graph[u].add(v);
                graph[v].add(u);
            }
            int[] color = new int[V+1];

            Biparitie = true;

            for (int j = 1; j <= V; j++) {
                if(color[j]==0){
                    dfs(color,j,1);
                }

            }

            if(Biparitie) System.out.println("YES");
            else System.out.println("NO");


        }

    }

    static void dfs(int[] color,int index,int c) {
        color[index] = c;

        for (Integer next : graph[index]) {
            if (color[next] == 0) {
                dfs(color, next, -1 * c);
            } else if (color[next] == c)
            {
                Biparitie = false;
                return;
            }

        }

    }
}
