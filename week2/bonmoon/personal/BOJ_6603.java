
import java.util.Scanner;

/**
 * dfs를 돌때 반복문 시작점을 잘 이해해야한다.
 */

public class BaekJoon_6603 {


    static int K;
    static int S;
    static int[] arr;
    static boolean[] visited;

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);


        while(true){
            K = sc.nextInt();

            if(K==0) break;

            arr = new int[K];
            visited = new boolean[K];

            for (int i = 0; i < K; i++) {
                arr[i] = sc.nextInt();
            }

            dfs(0, 0, new int[6]);
            System.out.println();
        }


    }

    private static void dfs(int start, int depth, int[] list) {
        if (depth == 6) {

            for (int i = 0; i < 6; i++) {
                System.out.print(list[i]+" ");
            }
            System.out.println();
            return;
        }


        for (int i = start; i < K; i++) {
            if (!visited[i]) {
                visited[i] = true;
                list[depth] = arr[i];
                dfs(i+1,depth + 1, list);
                visited[i] = false;
            }
        }


    }
}
