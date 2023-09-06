import java.io.*;
import java.util.*;

public class Main {

	public static void main(String[] args) throws IOException {

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();

		StringTokenizer st = null;
		st = new StringTokenizer(br.readLine());
		int N = Integer.parseInt(st.nextToken());
		int M = Integer.parseInt(st.nextToken());

		int[] arr = new int[N];
		int[] brr = new int[M];

		st = new StringTokenizer(br.readLine());
		for(int i=0; i<N; i++) arr[i] = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(br.readLine());
		for(int i=0; i<M; i++) brr[i] = Integer.parseInt(st.nextToken());

		Arrays.sort(arr);
		Arrays.sort(brr);

		int p1 = 0; int p2 = 0;
		while(p1 < arr.length && p2 < brr.length) {
			if (arr[p1] <= brr[p2]) {
				sb.append(arr[p1++] + " ");
			}
			else {
				sb.append(brr[p2++] + " ");
			}
		}
		while(p1 < arr.length) sb.append(arr[p1++] + " ");
		while(p2 < brr.length) sb.append(brr[p2++] + " ");

		System.out.println(sb);
	}
}
