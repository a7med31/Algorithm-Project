import java.sql.Array;
import java.util.Arrays;
import java.util.Scanner;

class Main {

  // efficiently calculate number of steps
  public static long getMinMovesHelper(long[] dp, int n) {
    long res = -1;
    if (dp[n] != -1) return dp[n];
    res = getMinMovesHelper(dp, n - 1) + 2 * getMinMovesHelper(dp, n - 2) + 1;
    dp[n] = res;
    return res;
  }

  // initialization to some important variables during getMinMoves
  public static long getMinMoves(int n) {
    long[] dp = new long[n + 1];
    Arrays.fill(dp, -1);
    dp[0] = 0;
    if (n >= 1) {
      dp[1] = 1;
    }
    if (n >= 2) {
      dp[2] = 2;
    }
    return getMinMovesHelper(dp, n);
  }

  public static long getMinMovesBase(int n) {
    if (n % 2 == 0) {
      return ((long) Math.pow(2, n + 1) - 2) / 3;
    }else{
      return ((long) Math.pow(2, n + 1) - 1) / 3;
    }
  }

  // count leading zeros in number like 0 will result in 32
  public static int countLeadingZeros(int value) {
    int res = 0;
    while (value > 0) {
      value /= 2;
      res++;
    }
    return 32 - res;
  }

  // to print the array
  public static void printArr(int[] arr) {
    System.out.print("[ ");
    for (int n : arr) {
      System.out.print(n + ", ");
    }
    System.out.println("]");
  }

  // to print the steps with min number of steps
  public static int calculateAndPrintSteps(int n) {
    int i = 1, onCount = 0;
    int[] switches = new int[n];
    printArr(switches);

    for (i = 1, onCount = 0; onCount < n; i++) {
      int index = n + countLeadingZeros(i & ~(i - 1)) - 32;
      switches[index] ^= 1; // Toggle
      onCount += switches[index] != 0 ? switches[index] : -1; // Either increment or decrement
      printArr(switches);
    }
    return i - 1;
  }

  public static void main(String[] args) {
    int n = 1;
    System.out.print("Please enter number of switches: ");
    Scanner input = new Scanner(System.in); // Create a Scanner object
    n = input.nextInt(); // Read user input

    System.out.println(
      "Number of switches using Dynamic Programming: " + getMinMoves(n)
    );
    System.out.println(
      "Number of switches using Constant Time: " + getMinMovesBase(n)
    );
    boolean printSwitches = false;
    System.out.print("Do you want to print steps[1=Yes]: ");
    printSwitches = input.nextInt() == 1;
    input.close();
    if (printSwitches) {
      int res = calculateAndPrintSteps(n);

      System.out.println(
        "The number of count using the printing method: " + res
      );
      System.out.println("They Match :)");
    }
  }
}
