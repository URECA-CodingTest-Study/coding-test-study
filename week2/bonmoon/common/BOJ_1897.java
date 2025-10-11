
import java.util.*;

/**
 * 각 단어에서 알파벳이 추가될때 Hashset에 담아놓은 단어장에 포함되어있는지 확인 한 후 큐에 다시 추가
 * 중복된 단어가 큐에 들어갈 수 있으니 큐에 추가된 단어 셋을 만들어 중복 관리
 */
public class BaekJoon_1897 {


    static Set<String> dic = new HashSet<>();
    static int d;
    static String word;
    static int len;
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        d = sc.nextInt();
        sc.nextLine();
        word = sc.nextLine();

        for (int i = 0; i < d; i++) {

            dic.add(sc.nextLine());
        }

        System.out.println(dic);

        String answer = bfs();
        System.out.println(answer);
    }

    private static String bfs(){
        Queue<String> queue = new LinkedList<>();
        Set<String> visited = new HashSet<>();

        queue.add(word);
        visited.add(word);

        String lastWord=word;

        while(!queue.isEmpty()){
            String poll = queue.poll();
            lastWord = poll;

            for(char c ='a'; c <='z'; c++){
                for (int i = 0; i <= poll.length(); i++) {
                    StringBuilder sb = new StringBuilder(poll);
                    sb.insert(i,c);
                    String insert = sb.toString();

                    if(dic.contains(insert) && !visited.contains(insert)){
                        queue.add(insert);
                        visited.add(insert);
                        //System.out.println(insert);
                    }
                }
            }
        }

        return lastWord;
    }
}
