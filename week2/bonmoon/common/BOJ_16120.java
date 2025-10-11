

import java.util.Scanner;
import java.util.Stack;

/**
 * A 알파벳이 나온후 스택에 2개의 PP가 있어야한다.
 * 문자열 끝에 A가 출력될 경우 바로 NP 처리
 * 반복문이 다 끝난후 스택에 P 한개만 있으면 PPAP
 * 아닌 경우 NP 처리
 */

public class BaekJoon_16120 {

    static Stack<Character> stack = new Stack<>();
    static String s ;

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        s = sc.nextLine();


        for (int i = 0; i < s.length(); i++) {

            if (s.charAt(i) == 'P') {
                stack.push('P');
            } else if (i != s.length() - 1 && stack.size() >= 2 && s.charAt(i + 1) == 'P') {
                stack.pop();
                stack.pop();
            } else {
                System.out.println("NP");
                return;
            }

        }

        if(stack.size()==1){
            System.out.println("PPAP");
        }else{
            System.out.println("NP");
        }

        System.out.println(stack);
    }
}
