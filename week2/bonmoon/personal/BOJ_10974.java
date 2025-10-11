
import java.util.Scanner;

/**
 * 백트래킹을 이용해  모든 순열 을 구한다.
 */
public class BaekJoon_10974 {
    static boolean[] back;
    static int N ;
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        N = sc.nextInt();
        back= new boolean[N];
        per(0,new int[N]);
    }

    private static void per(int depth, int[] arr) {

        if(depth==N){
            for (int i : arr) {
                System.out.print(i+" ");
            }
            System.out.println();
            return ;
        }

        for (int i = 0; i < arr.length ; i++) {

            if(!back[i]){
                back[i] = true;
                arr[depth] = i+1;
                per(depth+1,arr);
                back[i] = false;
            }


        }

    }
}
