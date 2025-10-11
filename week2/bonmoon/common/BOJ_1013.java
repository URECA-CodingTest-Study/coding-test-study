/**
 * 주어진 수식이 문자열 정규식으로 된 표현이기때문에 입력받은 문자열과 주어진 문자열 식을
 * 비교하여 YES or No 판별
 * 정규식 모르고 헤매다가 정규식관련함수 mathces를 사용하여 해결
 */

import java.util.Scanner;

public class BaekJoon_1013 {

    public static void main(String[] args) {


        Scanner sc= new Scanner(System.in);

        int T = sc.nextInt();
        sc.nextLine();
        String pattern = "(100+1+|01)+";

        for (int i = 0; i < T; i++) {
            String s = sc.nextLine();

            if(s.matches(pattern)){
                System.out.println("YES");
            }else{
                System.out.println("NO");
            }
        }
    }
}
