package baekjoon.dijkstra;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.Scanner;

/**
 * 다잌스트라 사용하여 가중치 구한다음 가중치 있는 노드와 제일 먼 노드를 구한다.
 *
 */

public class BaekJoon_10282 {

    static int N,D,C;
    static ArrayList<int[]>[] list;
    static int[] dist;
    public static void main(String[] args) {

        Scanner sc= new Scanner(System.in);
        int K = sc.nextInt();

        while(K-->0){
            N = sc.nextInt();
            D = sc.nextInt();
            C = sc.nextInt();

            list = new ArrayList[N+1];

            for (int i = 1; i <N+1 ; i++) {
                list[i] = new ArrayList<>();
            }

            for (int i = 0; i < D; i++) {
                int a= sc.nextInt();
                int b= sc.nextInt();
                int s = sc.nextInt();

                list[b].add(new int[]{a,s});
            }



            dist = new int[N+1];
            Arrays.fill(dist,Integer.MAX_VALUE);
            bfs(C);


        }


    }

    private static void bfs(int start) {
        PriorityQueue<int[]> pq = new PriorityQueue<>((a,b) ->a[1]-b[1]);
        dist[start] = 0;

        pq.add(new int[]{start,0});

        while(!pq.isEmpty()){
            int[] cur = pq.poll();
            int now  = cur[0];
            int nowDist=  cur[1];


            if(nowDist > dist[now]) continue;

            for (int[] next : list[now]) {
                int nextNode = next[0];
                int cost = nowDist+next[1];
                if(cost<dist[nextNode]){
                    dist[nextNode] = cost;
                    pq.add(new int[]{nextNode,cost});
                }
            }
        }

        int count = 0;
        int maxTime = 0;
        for (int i = 1; i <dist.length ; i++) {
            if(dist[i]!= Integer.MAX_VALUE){
                count++;
                maxTime = Math.max(maxTime,dist[i]);
            }
        }
        System.out.println(count+ " "+maxTime);
    }
}
