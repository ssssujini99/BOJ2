import java.util.*;
import java.io.*;

public class Main {

	// N*N 격자의 각 칸에는 바구니가 하나씩 존재, 바구니는 칸 전체를 차지
	// 바구니에 저장할 수 있는 물의 양에는 제한 X
	// A[r][c] = (r, c)에 있는 {바구니에 저장되어 있는 "물의 양"}

	// 모든 행과 열은 연결되어 있음

	// 비바라기 시전 시 -> 하늘에 비구름을 만들 수 있음
	// 비바라기 시전
	// 1 - (N, 1), (N, 2), (N-1, 1), (N-1, 2) 에 비구름 생김

	// 2 -이제 구름에게 이동을 M번 명령
	//// i번째 이동 명령은 (di, si)로 구성 // di: 방향, si: 거리 // 방향 총 8개 (1 ~ 8로 표현)
	// 2.1 모든 구름이 di 방향으로 si칸 이동
	// 2.2 각 구름에서 비가 내려, 구름이 있는 칸의 바구니에 저장된 물의 양이 1 증가
	// 2.3 구름이 모두 사라진다
	// 2.4 (2.2 단계) 에서 물이 증가한 칸 (r,c)에 {물복사버그 마법}을 시전
	//// 2.4.1 {물복사버그 마법}을 사용하면, 대각선 방향으로 거리가 1인 칸에 물이 들어있는 바구니의 수만큼 (r,c)에 있는 바구니의 물의 양 증가
	/////// 이때 경계를 넘어가는 칸은 무시
	// 2.5 바구니에 저장된 물의 양이 2 이상인 모든 칸에 구름이 생기고, 물의 양이 2 줄어든다
	//// 2.5.1 이때 구름이 생기는 칸은 (2.3 단계)에서 구름이 사라진 칸이 아니어야 한다

	// sol: M번의 이동이 모두 끝난 후 바구니에 들어있는 물의 양의 합을 구하기

	// 방향 좌표 idx: 1 ~ 8, (idx: 0 은 제외)
	static int[] dx = {0, 0, -1, -1, -1, 0, 1, 1, 1};
	static int[] dy = {0, -1, -1, 0, 1, 1, 1, 0, -1};

	// 물복사버그 마법 시전 시 쓸 방향 -> 대각선 4방향
	static int[] dxx = {-1, -1, 1, 1};
	static int[] dyy = {-1, 1, -1, 1};

	static int N, M;
	static int[][] arr;
	static ArrayList<mInfo> mInfoAL = new ArrayList<>(); // 이동의 정보

	static ArrayList<Point> windAL = new ArrayList<>(); // 구름들


	public static void main(String[] args) throws IOException {

		init();

		// 초기 구름 값 세팅
		windAL.add(new Point(N-2, 0)); windAL.add(new Point(N-2, 1));
		windAL.add(new Point(N-1, 0)); windAL.add(new Point(N-1, 1));

		for(int i=0; i<M; i++) {
			logic(i);
		}

		int res = countingWater();
		System.out.println(res);
	}

	public static int countingWater() {
		int sum = 0;
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				sum += arr[i][j];
			}
		}
		return sum;
	}

	public static void logic(int orderNum) {

		// 2.1 모든 구름이 di 방향으로 si칸 이동
		movingWind(orderNum);

		// 2.2 각 구름에서 비가 내려, 구름이 있는 칸의 바구니에 저장된 물의 양이 1 증가
		raining();

		// 2.3 구름이 모두 사라진다

		// 2.4 (2.2 단계) 에서 물이 증가한 칸 (r,c)에 {물복사버그 마법}을 시전
		//// 2.4.1 {물복사버그 마법}을 사용하면, 대각선 방향으로 거리가 1인 칸에 물이 들어있는 바구니의 수만큼 (r,c)에 있는 바구니의 물의 양 증가
		/////// 이때 경계를 넘어가는 칸은 무시
		waterCopyBugMagic();

		// 2.5 바구니에 저장된 물의 양이 2 이상인 모든 칸에 구름이 생기고, 물의 양이 2 줄어든다
		//// 2.5.1 이때 구름이 생기는 칸은 (2.3 단계)에서 구름이 사라진 칸이 아니어야 한다
		creatingNewWind();
	}

	public static void creatingNewWind() {
		int[][] exWind = new int[N][N];
		for(int i=0; i<windAL.size(); i++) {
			int x = windAL.get(i).x ; int y = windAL.get(i).y;
			exWind[x][y] = 1;
		}

		windAL.clear();

		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				if (arr[i][j] >= 2 && exWind[i][j] == 0) {
					windAL.add(new Point(i, j)); // 새로운 구름 넣어주기
					arr[i][j] -= 2; // 물의 양 2 감소
				}
			}
		}

	}

	public static void waterCopyBugMagic() {

		for(int i=0; i<windAL.size(); i++) {
			int x = windAL.get(i).x ; int y = windAL.get(i).y;

			int cnt = 0;

			// 대각선 4방향에 물이 들어 있는 바구니가 몇 개인지 체크, 이 때에 경계 체크해야됨
			for(int k=0; k<4; k++) {
				int diagX = x + dxx[k]; int diagY = y + dyy[k];
				if (!(0 <= diagX && diagX < N && 0 <= diagY && diagY < N)) continue; // 범위만족 X -> continue
				if (arr[diagX][diagY] > 0) cnt++;
			}

			arr[x][y] += cnt;
		}
	}

	public static void raining() {

		for(int i=0; i<windAL.size(); i++) {
			int x = windAL.get(i).x ; int y = windAL.get(i).y;
			arr[x][y]++;
		}
	}

	public static void movingWind(int orderNum) {
		int di = mInfoAL.get(orderNum).di; // 방향
		int si = mInfoAL.get(orderNum).si; // 거리

		for(int i=0; i<windAL.size(); i++) {
			int cx = windAL.get(i).x; int cy = windAL.get(i).y;
			int nx = cx; int ny = cy;

			for(int j=0; j<si; j++) {
				nx += dx[di]; ny += dy[di];
				if (nx == N) nx = 0;
				if (nx < 0) nx = N-1;
				if (ny == N) ny = 0;
				if (ny < 0) ny = N-1;
			}

			// 구름 이동 갱신
			windAL.get(i).x = nx; windAL.get(i).y = ny;
		}
	}

	public static void init() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken()); M = Integer.parseInt(st.nextToken());
		arr = new int[N][N];

		for(int i=0; i<N; i++) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<N; j++) {
				arr[i][j] = Integer.parseInt(st.nextToken());
			}
		}

		for(int i=0; i<M; i++) {
			st = new StringTokenizer(br.readLine());
			int di = Integer.parseInt(st.nextToken()); int si = Integer.parseInt(st.nextToken());
			mInfoAL.add(new mInfo(di, si));
		}
	}

	static class Point {
		int x, y;

		Point(int x, int y) {
			this.x = x;
			this.y = y;
		}

		@Override
		public String toString() {
			return x + ", " + y;
		}
	}

	static class mInfo {
		int di; // 방향
		int si; // 거리
		mInfo(int di, int si) {
			this.di = di;
			this.si = si;
		}

		@Override
		public String toString() {
			return di + " " + si;
		}
	}
}
