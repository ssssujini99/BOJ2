import java.util.*;
import java.io.*;

public class Main {

	static int[][] arr;
	static int[] lrr;
	static int N, Q;
	static int maxNearCnt = 0, tmpCnt = 0;

	static int[] d = {0, 1, 2, 3}; // 상, 하, 좌, 우
	static int[] dx = {-1, 1, 0, 0};
	static int[] dy = {0, 0, -1, 1};
	static int[][] ch;

	public static void main(String[] args) throws IOException {

		init();

		for(int i=0; i<lrr.length; i++) {
			rotate(lrr[i]);
			decreaseIce();
		}

		System.out.println(countingIce());

		for(int i=0; i<(int)Math.pow(2, N); i++) {
			for(int j=0; j<(int)Math.pow(2, N); j++) {
				if (arr[i][j] > 0 && ch[i][j] == 0) {
					tmpCnt = 0;
					ch[i][j] = 1;
					dfs(i, j);
					maxNearCnt = Math.max(maxNearCnt, tmpCnt);
				}
			}
		}

		System.out.println(maxNearCnt);
	}

	// 남아있는 얼음 중 가장 큰 덩어리가 차지하는 칸의 개수 구하는 함수 -> dfs
	// 얼음이 있는 칸이 얼음이 있는 칸과 인접해 있으면 -> 두 칸은 연결되어 있다고 본다
	private static void dfs(int x, int y) {

		tmpCnt++;

		for(int i=0; i<4; i++) {
			int nx = x + dx[i]; int ny = y + dy[i];

			if (0 <= nx && nx < (int)Math.pow(2, N) && 0 <= ny && ny < (int)Math.pow(2, N)) {
				if (arr[nx][ny] > 0 && ch[nx][ny] == 0) {
					ch[nx][ny] = 1;
					dfs(nx, ny);
				}
			}
		}
	}

	// 부분 격자 90도 회전시키는 함수
	public static void rotate(int L) {
		// 2^L * 2^L 의 부분격자에 있는 칸 90도 회전시키기
		int len = (int)Math.pow(2, L);

		for(int i=0; i<(int)Math.pow(2, N); i+=len) {
			for(int j=0; j<(int)Math.pow(2, N); j+=len) {

				int[][] tmp = new int[len][len];
				for(int k=0; k<len; k++) {
					for(int l=0; l<len; l++) {
						tmp[l][len-1-k] = arr[i+k][j+l];
					}
				}
				for(int k=0; k<len; k++) {
					for(int l=0; l<len; l++) {
						arr[i+k][j+l] = tmp[k][l];
					}
				}
			}
		}

	}

	// 인접한 칸에 3개 이상의 얼음이 없는 경우 얼음 -1 감소시키는 함수 -> 구현
	public static void decreaseIce() {

		int[][] tmp = new int[(int)Math.pow(2, N)][(int)Math.pow(2, N)];

		for(int i=0; i<(int)Math.pow(2, N); i++) {
			for(int j=0; j<(int)Math.pow(2, N); j++) {
				// 칸 (i, j)에 대해서
				if (arr[i][j] == 0) continue;

				int cnt = 0;
				// 상, 하, 좌, 우 방향 체크
				for(int k=0; k<4; k++) {
					int dirX = i + dx[k]; int dirY = j + dy[k];
					if (0 <= dirX && dirX < (int)Math.pow(2, N) && 0 <= dirY && dirY < (int)Math.pow(2, N)) {
						if (arr[dirX][dirY] > 0) cnt++;
					}
				}

				// 얼음이 있는 인접한 칸이 2 이하일 경우 -> 얼음 감소시키기
				if (cnt <= 2) tmp[i][j] = 1;
			}
		}

		for(int i=0; i<(int)Math.pow(2, N); i++) {
			for(int j=0; j<(int)Math.pow(2, N); j++) {
				arr[i][j] -= tmp[i][j];
			}
		}

	}

	// 남아있는 얼음들의 합을 구하는 함수 -> 구현
	public static int countingIce() {

		int sum = 0;
		for(int i=0; i<(int)Math.pow(2, N); i++) {
			for(int j=0; j<(int)Math.pow(2, N); j++) {
				if (arr[i][j] > 0) sum += arr[i][j];
			}
		}
		return sum;
	}



	private static void init() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		Q = Integer.parseInt(st.nextToken());
		arr = new int[(int)Math.pow(2, N)][(int)Math.pow(2, N)];
		lrr = new int[Q];
		ch = new int[(int)Math.pow(2, N)][(int)Math.pow(2, N)];

		for(int i=0; i<(int)Math.pow(2, N); i++) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<(int)Math.pow(2, N); j++) {
				arr[i][j] = Integer.parseInt(st.nextToken());
			}
		}

		st = new StringTokenizer(br.readLine());
		for(int i=0; i<Q; i++) {
			lrr[i] = Integer.parseInt(st.nextToken());
		}
	}
}
