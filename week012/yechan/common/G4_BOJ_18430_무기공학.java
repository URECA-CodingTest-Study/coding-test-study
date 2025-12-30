package week012.yechan.common;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class G4_BOJ_18430_무기공학 {
    static int[][] map;
    static int[][] visited;
    static int[][][] boo = {
        {{0,0},{-1,0},{0,-1}}, // 위, 왼
        {{0,0},{-1,0},{0,1}},  // 위, 오
        {{0,0},{1,0},{0,-1}},  // 아래, 왼
        {{0,0},{1,0},{0,1}},   // 아래, 오
    };
    static int N, M;
    static int answer = 0;
    
    public static void main(String[] args) throws IOException {
        
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());

        map = new int[N][M];
        visited = new int[N][M];

        for(int i=0; i<N; i++){
            st = new StringTokenizer(br.readLine());
            for(int j=0; j<M; j++){
                map[i][j] = Integer.parseInt(st.nextToken());
            }
        }

        dfs(0,0,0);

        System.out.println(answer);
    }

    private static void dfs(int y, int x, int score) {
        
        if(x == M){
            dfs(y+1, 0, score);
            return;
        }

        if(y == N){
            answer = Math.max(answer, score);
            return;
        }

        // 이 칸에는 아무것도 안 놓는 경우
        dfs(y, x+1, score);

        // 이 칸에 놓는 경우
        if(visited[y][x] == 0){
            for(int k=0; k<4; k++){
                boolean possible = true;
                for(int d=0; d<3; d++){
                    int ny = y + boo[k][d][0];
                    int nx = x + boo[k][d][1];

                    if(ny<0 || nx < 0 || ny>=N || nx >= M || visited[ny][nx] == 1) {
                        possible=false;
                        break;
                    }
                }

                if(possible){
                    int addscore = 0;

                    for(int d=0; d<3; d++){
                        int ny = y + boo[k][d][0];
                        int nx = x + boo[k][d][1];

                        visited[ny][nx] = 1;

                        if(d==0) addscore += map[ny][nx] * 2;
                        else addscore += map[ny][nx];
                    }

                    dfs(y, x+1, score+addscore);

                    for(int d=0; d<3; d++){
                        int ny = y + boo[k][d][0];
                        int nx = x + boo[k][d][1];
                        visited[ny][nx] = 0;
                    }

                }

                
            }
        }

    }

}
