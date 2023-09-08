import java.util.*;
import java.io.*;

// 1. 토네이도의 이동
// 2. 토네이도 이동 시 모래의 이동
// 토네이도 이동 방향에 따른 모래의 이동 -> { 상, 하, 좌, 우 }


// 0, 1, 2,2, 3,3, 4,4,4, 5,5,5,  6,6,6,6  7,7,7,7  ,...
// 0,0,0,0,0  1,1,1,1,1  2,2,2,2,2,2  3,3,3,3,3,3
// 좌 하 우우 상상 좌좌좌 하하하 우우우우 상상상상

// 좌(0, -1), 하(1, 0), 우(0, 1), 상(-1, 0)

public class Main {

	static Point tornado;
	static int rangeOutOfSand = 0; // 범위 밖으로 벗어난 모래의 양
	static int[][] arr; static int N;
	static int[] dir = {0, 1, 2, 3}; // 순서: { 좌, 하, 우, 상 }
	static int[] dirX = {0, 1, 0, -1};
	static int[] dirY = {-1, 0, 1, 0};

	public static void tornado() {
		int curN = 0;
		int curDuration = 1; // 현재 주기

		while (true) {

			for(int i=0; i<curDuration; i++) {
				tornadoMoving(tornado, curN % 4);
				if (tornado.x == 0 && tornado.y == 0) return;
			}
			curN++;

			for(int i=0; i<curDuration; i++) {
				tornadoMoving(tornado, curN % 4);
				if (tornado.x == 0 && tornado.y == 0) return;
			}
			curN++;

			// 주기 증가
			curDuration++;
		}
	}

	public static void tornadoMoving(Point cp, int dir) {
		int cX = cp.x; int cY = cp.y;
		int nX = cX + dirX[dir]; int nY = cY + dirY[dir];
		tornado.x = nX; tornado.y = nY; tornado.dir = dir;

		if (arr[nX][nY] != 0) {
			// 토네이도가 이동한 칸에 모래가 있으면
			movingSand(cX, cY, nX, nY, dir);
		}
	}

	// 토네이도 이동에 따른 모래의 이동
	public static void movingSand(int px, int py, int cx, int cy, int dir) {

		// 모래의 양 구하기
		int totalSand = arr[cx][cy];
		int sand_5 = (int)(totalSand * 0.05);
		int sand_10 = (int)(totalSand * 0.1);
		int sand_2 = (int)(totalSand * 0.02);
		int sand_7 = (int)(totalSand * 0.07);
		int sand_1 = (int)(totalSand * 0.01);
		int sand_alpha = totalSand - (sand_5 + 2*(sand_10 + sand_2 + sand_7 + sand_1));

		// 토네이도의 이동 : {px, py} -> {cx, cy}
		// 현재 토네이도 방향: dir

		// 수직 방향 2개: 현재 방향 + 1, 현재 방향 + 3
		int nDir1 = (dir + 1) % 4; int nDir2 = (dir + 3) % 4;

		// 알파 좌표 1개
		int x_a = cx + dirX[dir]; int y_a = cy + dirY[dir];
		updateSandArray(sand_alpha, x_a, y_a);

		// 5% 좌표 1개
		int x_5 = cx + 2*dirX[dir]; int y_5 = cy + 2*dirY[dir];
		updateSandArray(sand_5, x_5, y_5);

		//// 방향 다름 케이스들

		// 10% 좌표 2개
		int x_10_1 = x_a + dirX[nDir1]; int y_10_1 = y_a + dirY[nDir1];
		int x_10_2 = x_a + dirX[nDir2]; int y_10_2 = y_a + dirY[nDir2];
		updateSandArray(sand_10, x_10_1, y_10_1);
		updateSandArray(sand_10, x_10_2, y_10_2);

		// 7% 좌표 2개
		int x_7_1 = cx + dirX[nDir1]; int y_7_1 = cy + dirY[nDir1];
		int x_7_2 = cx + dirX[nDir2]; int y_7_2 = cy + dirY[nDir2];
		updateSandArray(sand_7, x_7_1, y_7_1);
		updateSandArray(sand_7, x_7_2, y_7_2);

		// 2% 좌표 2개
		int x_2_1 = cx + 2*dirX[nDir1]; int y_2_1 = cy + 2*dirY[nDir1];
		int x_2_2 = cx + 2*dirX[nDir2]; int y_2_2 = cy + 2*dirY[nDir2];
		updateSandArray(sand_2, x_2_1, y_2_1);
		updateSandArray(sand_2, x_2_2, y_2_2);

		// 1% 좌표 2개
		int x_1_1 = px + dirX[nDir1]; int y_1_1 = py + dirY[nDir1];
		int x_1_2 = px + dirX[nDir2]; int y_1_2 = py + dirY[nDir2];
		updateSandArray(sand_1, x_1_1, y_1_1);
		updateSandArray(sand_1, x_1_2, y_1_2);
	}

	private static void updateSandArray(int sandW, int x, int y) {
		if (checkRange(x, y) == true) {
			arr[x][y] += sandW;
		}
		else {
			rangeOutOfSand += sandW;
		}
	}

	public static boolean checkRange(int x, int y) {
		if (x >= 0 && x < N && y >= 0 && y < N) return true;
		return false;
	}

	public static void main(String[] args) throws IOException {

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		arr = new int[N][N]; tornado = new Point(N/2, N/2, 0);

		for(int i=0; i<N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<N; j++) {
				arr[i][j] = Integer.parseInt(st.nextToken());
			}
		}

		tornado();
		System.out.println(rangeOutOfSand);
	}

	static class Point {
		int x, y, dir;

		Point(int x, int y, int dir) {
			this.x = x;
			this.y = y;
			this.dir = dir;
		}
	}
}
