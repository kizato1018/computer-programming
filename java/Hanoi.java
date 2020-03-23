import java.util.Scanner;

public class Hanoi {
    public static void hanoi(int n, int from, int to, int spare) {
        if(n == 0) return;
        hanoi(n-1, from, spare, to);
        System.out.println( n + " from " + from + " to " + to);
        hanoi(n-1, spare, to, from);
    }
    public static void main(String[] args) {
        int n;
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        hanoi(n, 1, 3, 2);
        scanner.close();
        return;
    }
}