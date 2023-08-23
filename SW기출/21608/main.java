import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

public class Main {

	public static int[][] info = new int[441][5];
	public static int[][] map = new int[21][21];
	public static int[] order = new int[401];
	public static int N;

	public static void main(String[] args) throws IOException {
		// 1. 비어있는 칸 중에서 좋아하는 학생이 인접한 칸에 가장 많은 칸으로 자리를 정한다.
		// 2. 1을 만족하는 칸이 여러 개이면, 인접한 칸 중에서 비어있는 칸이 가장 많은 칸으로 자리를 정한다.
		// 3. 2를 만족하는 칸도 여러 개인 경우에는 행의 번호가 가장 작은 칸으로, 그러한 칸도 여러 개이면 열의 번호가 가장 작은 칸으로 자리를 정한다.

		// 3 <= N <= 20

		// 1 - 입력받기
		// 2 - 자리 배치하기
		// 3 - 만족도 총 합 구하기

		// 1 - 입력받기
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = null;
		N = Integer.parseInt(br.readLine());
		for(int i=0; i<N*N; i++) {
			st = new StringTokenizer(br.readLine());
			int num = Integer.parseInt(st.nextToken());
			info[num][0] = num; order[i] = num;
			for(int j=1; j<=4; j++) info[num][j] = Integer.parseInt(st.nextToken());
		}

		// 2- 자리 배치하기
		for(int i=0; i<N*N; i++) {
			int num = order[i];

			ArrayList<Node> al = new ArrayList<>();
			for(int j=0; j<N; j++) {
				for(int k=0; k<N; k++) {
					if (map[j][k] == 0) {
						int likeCnt = countLikeCnt(j, k, num);
						int emptyCnt = countEmptyCnt(j, k);
						al.add(new Node(j, k, likeCnt, emptyCnt));
					}
				}
			}

			Collections.sort(al);
			map[al.get(0).x][al.get(0).y] = num; // num 자리배치
		}



		// 3 - 만족도 총 합 구하기
		int ans = 0;
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				ans += (int)Math.pow(10, countLikeCnt(i, j, map[i][j])-1);
			}
		}
		System.out.println(ans);
	}

	public static int countLikeCnt(int x, int y, int num) {
		int res = 0;
		if (x-1 >= 0 && (map[x-1][y] == info[num][1] || map[x-1][y] == info[num][2] || map[x-1][y] == info[num][3] || map[x-1][y] == info[num][4])) res++;
		if (x+1 < N && (map[x+1][y] == info[num][1] || map[x+1][y] == info[num][2] || map[x+1][y] == info[num][3] || map[x+1][y] == info[num][4])) res++;
		if (y-1 >= 0 && (map[x][y-1] == info[num][1] || map[x][y-1] == info[num][2] || map[x][y-1] == info[num][3] || map[x][y-1] == info[num][4])) res++;
		if (y+1 < N && (map[x][y+1] == info[num][1] || map[x][y+1] == info[num][2] || map[x][y+1] == info[num][3] || map[x][y+1] == info[num][4])) res++;

		return res;
	}

	public static int countEmptyCnt(int x, int y) {
		int res = 0;
		if (x-1 >= 0 && map[x-1][y] == 0) res++;
		if (x+1 < N && map[x+1][y] == 0) res++;
		if (y-1 >= 0 && map[x][y-1] == 0) res++;
		if (y+1 < N && map[x][y+1] == 0) res++;

		return res;
	}

	static class Node implements Comparable<Node> {
		int x, y;
		int likeCnt; // 해당 칸 x,y에서 인접한 칸에 좋아하는 학생이 몇 명인지
		int emptyCnt; // 해당 칸 x,y에서 인접한 칸 중 비어있는 칸의 수

		Node(int x, int y, int likeCnt, int emptyCnt) {
			this.x = x; this.y = y;
			this.likeCnt = likeCnt;
			this.emptyCnt = emptyCnt;
		}

		@Override
		public int compareTo(Node o) {
			if (this.likeCnt != o.likeCnt) {
				return this.likeCnt > o.likeCnt ? -1 : 1;
			}

			// this.likeCnt == o.likeCnt
			if (this.emptyCnt != o.emptyCnt) {
				return this.emptyCnt > o.emptyCnt ? -1 : 1;
			}

			// this.likeCnt == o.likeCnt && this.emptyCnt == o.emptyCnt
			if (this.x != o.x) {
				return this.x < o.x ? -1 : 1;
			}

			return this.y < o.y ? -1 : 1;
		}
	}
}
