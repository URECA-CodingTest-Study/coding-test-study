package baekjoon.implementation;

import java.util.Scanner;
import java.util.Stack;



public class BaekJoon_2504 {


    /**
     *각 조건에 유의해서 작성
     */
    public static void main(String[] args) {

        Scanner sc=  new Scanner(System.in);
        Stack<Character> stack = new Stack<>();
        String s = sc.nextLine();
        int answer  = 0;
        int temp = 1;
        char prev ;

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);

            if(c=='('){
                stack.push(c);
                temp  *= 2;

            }else if(c=='['){
                stack.push(c);
                temp *= 3;

            }else if(c==']'){
                if (stack.isEmpty() || stack.peek() != '[') {
                    answer = 0;
                    break;
                }else if(s.charAt(i-1)=='['){
                    answer+=temp;

                }
                stack.pop();
                temp /=3;
            }else if (c==')') {
                if (stack.isEmpty() || stack.peek() != '(') {
                    answer = 0;
                    break;
                }else if(s.charAt(i-1)=='('){
                    answer+=temp;

                }
                stack.pop();
                temp/=2;
            }

        }
        if(!stack.isEmpty()) System.out.println(0);
        else System.out.println(answer);

    }
}
