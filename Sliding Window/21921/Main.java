import java.io.*;
import java.util.*;

public class Main {
	public static void main(String[] args) throws IOException {

		// X일 동안 가장 많이 들어온 {방문자 수}와 {기간이 몇 개}
		int N, X; int[] arr; StringTokenizer st; int[] arrSum;
		int maxN; int maxLen;

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		X = Integer.parseInt(st.nextToken());

		arr = new int[N]; arrSum = new int[N];
		st = new StringTokenizer(br.readLine());
		for(int i=0; i<N; i++) arr[i] = Integer.parseInt(st.nextToken());
		arrSum[0] = arr[0];
		for(int i=1; i<N; i++) arrSum[i] = arr[i] + arrSum[i-1];

		maxN = arrSum[X-1]; maxLen = 1;
		for(int i=X; i<N; i++) {
			int tmpN = arrSum[i]-arrSum[i-X];
			if (tmpN > maxN) {
				maxN = tmpN; maxLen = 1;
			}
			else if (tmpN == maxN) maxLen++;
		}

		if (maxN == 0) System.out.println("SAD");
		else System.out.println(maxN + "\n" + maxLen);
	}
}
