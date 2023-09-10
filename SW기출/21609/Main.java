import java.util.*;
import java.io.*;

public class Main {

	// <블록>: 검정(-1), 무지개(0), 일반(M가지 색상으로 표현, 색은 [1, M] 의 수로 표현)
	// <인접한 칸> : |r1 - r2| + |c1 - c2| = 1 을 만족하는 두 칸 (r1, c1), (r2, c2)

	// <블록 그룹>: 연결된 블록의 집합
	//// 일반 블록이 적어도 1개 있어야 함 + 일반 블록의 색은 모두 같아야 함
	//// 검은색 블록은 포함 X, 무지개 블록은 상관 없음
	//// 그룹에 속한 블록의 개수 >= 2
	//// 임의의 한 블록에서 그룹에 속한 인접한 칸으로 이동해서 그룹에 속한 다른 모든 칸으로 이동할 수 있어야 한다(?) -> 그냥 단순히 다 이어져 있다는 얘기인가?

	// <블록 그룹의 기준 블록>
	//// (무지개 블록이 아닌 블록 중에서) 행의 번호가 가장 작은 블록, 그러한 블록이 여러 개면 열의 번호가 가장 작은 블록

	// <오토 플레이 기능> - 블록 그룹이 존재하는 동안 계속해서 반복되어야 함

	// 1. 크기가 가장 큰 블록 그룹을 찾는다.
	//// 1.1 그러한 블록 그룹이 여러 개이면 포함된 무지개 블록의 수가 가장 많은 블록 그룹,
	//// 1.2 그러한 블록도 여러개라면 {기준 블록}의 행이 가장 큰 것을,
	//// 1.3 그것도 여러개이면 {기준 블록}열이 가장 큰 것을 찾는다

	// 2. 1에서 찾은 블록 그룹의 모든 블록을 제거. 블록 그룹에 포함된 블록의 수를 B라 했을 때, B^2점을 획득함 - OK
	// 3. 격자에 중력이 작용 - OK
	// 4. 격자가 90도 반시계 방향으로 회전 - OK
	// 5. 다시 격자에 중력이 작용 - OK
	//// 5.1 격자에 중력이 작용하면 검은색 블록을 제외한 모든 블록의 행의 번호가 큰 칸으로 이동. - OK
	//// 5.2 이동은 다른 블록이나 격자의 경계를 만나기 전까지 계속 된다 - OK

	// sol1 - 블록 그룹 다 찾기
	// sol2 - 가장 큰 블록 그룹 찾기 - 정렬 조건 구현 (3가지)
	// sol3 - 오토 플레이 기능

	static int N, M; // N: 한 변의 크기, M: 색상의 개수
	static int number; // block의 Numbering
	static int[][] arr;

	static int[] dx = {-1, 1, 0, 0};
	static int[] dy = {0, 0, -1, 1};
	static int[] dd = {0, 1, 2, 3}; // 상, 하, 좌, 우

	public static void main(String[] args) throws IOException {

		init();

		// 오토 플레이는 블록 그룹이 존재하는 동안 계속해서 반복된다

		int res = 0;
		while(true) {

			Group group = findAllBlockGroups();
			if (group == null) break;

			res += removeBlockAndGetScore(group);
			applyGravity();
			rotateReverseClock();
			applyGravity();
		}

		System.out.println(res);
	}

	public static void print() {
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				System.out.print(arr[i][j] + " ");
			}
			System.out.println();
		}
	}

	// 찾은 블록 그룹의 모든 블록을 제거. 블록 그룹에 포함된 블록의 수를 B라 했을 때, B^2점을 획득
	public static int removeBlockAndGetScore(Group group) {
		int score = (int)Math.pow(group.pointArrayList.size(), 2);
		ArrayList<Point> apl = group.pointArrayList;
		for(int i=0; i<apl.size(); i++) {
			arr[apl.get(i).x][apl.get(i).y] = -2;
		}
		return score;
	}

	// 격자에 중력이 작용
	// -1은 고정, 움직이지 X
	// -2는 없는 숫자 취급
	public static void applyGravity() {
		for(int i=N-2; i>=0; i--) {
			for(int j=0; j<N; j++) {
				// arr[i][j] 칸이  arr[N-1][j]까지 내려갈 수 있는지 체크
				int k = i;
				while(k+1 < N && arr[k][j] > -1 && arr[k+1][j] == -2) {
					arr[k+1][j] = arr[k][j];
					arr[k][j] = -2;
					k++;
				}
			}
		}
	}

	// 격자가 90도 반시계 방향으로 회전
	public static void rotateReverseClock() {
		int[][] tmp = new int[N][N];
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				tmp[N-1-j][i] = arr[i][j];
			}
		}

		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				arr[i][j] = tmp[i][j];
			}
		}
	}


	// 블록 그룹 다 찾기
	public static Group findAllBlockGroups() {

		ArrayList<Group> ag = new ArrayList<>();
		// 블록 그룹의 가능한 케이스: {1 ~ M} 개
		for(int i=1; i<=M; i++) {
			// 현재 arr 에서 0과 색깔이 i인 블록들 다 체크
			ArrayList<Point> apl = findAllRainbowsAndColor(i);

			// 모든 0의 좌표들에서 인접한 가능한 무지개 블록 다 체크
			int[][] tmpArr = new int[N][N];
			int nearRainbowsCnt = checkNearRainbows(i, tmpArr, apl);// tmpArr에다가 무지개와 인접한 색깔 i인 블록들 다 1로 체크

			// 덩어리들 idx 남기기
			int[][] tmpInfoArr = new int[N][N]; // tmpInfoArr: idx를 남기는 배열
			int idxCnt = giveIdxToBlockGroups(tmpArr, tmpInfoArr); // idxCnt: 총 만들어진 그룹 개수

			// 만들어 진 덩어리들 중 가장 블록 수가 많은 블록 그룹 구하기 -> 해당 블록에 일반 블록이 있는지 확인해야함
			Group group = findMaxCntOfBlockGroups(idxCnt, tmpInfoArr);
			if(group == null || group.pointArrayList.size() <= 1) continue;

			// ArrayList에 해당 블록 그룹 넣기
			ag.add(group);
		}

		Collections.sort(ag);
		if (ag.size() == 0) return null;
		return ag.get(0);
	}


	// 만들어 진 덩어리들 중 가장 블록 수가 많은 블록 그룹 구하기 -> 해당 블록에 일반 블록이 있는지 확인해야함
	public static Group findMaxCntOfBlockGroups(int idxCnt, int[][] tmpInfoArr) {

		ArrayList<Group> ag = new ArrayList<>();

		for(int k=1; k<=idxCnt; k++) {

			Group group = new Group();
			ArrayList<Point> ap = new ArrayList<>();

			for(int i=0; i<N; i++) {
				for(int j=0; j<N; j++) {
					if (tmpInfoArr[i][j] == k) {
						ap.add(new Point(i, j));
					}
				}
			}

			Collections.sort(ap);
			group.pointArrayList = ap;
			if (group.containsGeneralBlock() == false) continue;
			// 그룹에 일반 블록이 적어도 하나 포함한다면
			Point standartPoint = ap.get(0);
			group.standardPoint = standartPoint;
			group.rainbowCnt = group.countRainbowCnt();
			ag.add(group);
		}

		Collections.sort(ag);
		if (ag.size() == 0) return null;
		return ag.get(0);
	}

	public static int giveIdxToBlockGroups(int[][] tmpArr, int[][] tmpInfoArr) {

		// tmpArr의 정보를 이용해 tmpInfoArr에다가 idx 표시

		number = 0;
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				if (tmpArr[i][j] == 1 && tmpInfoArr[i][j] == 0) {
					tmpInfoArr[i][j] = ++number;
					findBlockGroupsDfs(i, j, number, tmpArr, tmpInfoArr);
				}
			}
		}

		return number;
	}

	public static void findBlockGroupsDfs(int x, int y, int number, int[][] tmpArr, int[][] tmpInfoArr) {

		for(int i=0; i<4; i++) {
			int nx = x + dx[i]; int ny = y + dy[i];
			if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
				if (tmpArr[nx][ny] == 1 && tmpInfoArr[nx][ny] == 0) {
					tmpInfoArr[nx][ny] =  number;
					findBlockGroupsDfs(nx, ny, number, tmpArr, tmpInfoArr);
				}
			}
		}

	}

	public static int checkNearRainbows(int color, int[][] tmpArr, ArrayList<Point> apl) {

		int cnt = 0;

		Queue<Point> queue = new LinkedList<>();

		for(int i=0; i<apl.size(); i++) {
			tmpArr[apl.get(i).x][apl.get(i).y] = 1;
			queue.add(apl.get(i));
			cnt++;
		}

		while(!queue.isEmpty()) {
			Point p = queue.poll();
			for(int i=0; i<4; i++) {
				int nx = p.x + dx[i]; int ny = p.y + dy[i];
				if (!(nx >= 0 && nx < N && ny >= 0 && ny < N)) continue; // 범위 out 시
				if (arr[nx][ny] == color && tmpArr[nx][ny] == 0) {
					tmpArr[nx][ny] = 1;
					cnt++;
					queue.add(new Point(nx, ny));
				}
			}
		}

		return cnt;
	}

	public static ArrayList<Point> findAllRainbowsAndColor(int color) {
		ArrayList<Point> al = new ArrayList<>();
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				if (arr[i][j] == 0 || arr[i][j] == color) al.add(new Point(i, j));
			}
		}
		return al;
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
	}


	static class Point implements Comparable<Point> {
		int x, y;

		Point(int x, int y) {
			this.x = x;
			this.y = y;
		}

		// 블록 그룹의 {기준 블록} 을 맨 앞으로
		// <블록 그룹의 기준 블록>
		//// (무지개 블록이 아닌 블록 중에서) 행의 번호가 가장 작은 블록, 그러한 블록이 여러 개면 열의 번호가 가장 작은 블록
		@Override
		public int compareTo(Point o) {
			if (arr[x][y] != 0 && arr[o.x][o.y] != 0) {
				if (this.x != o.x) {
					return this.x < o.x ? -1 : 1;
				}
				return this.y < o.y ? -1 : 1;
			}
			else if (arr[x][y] != 0 && arr[o.x][o.y] == 0) {
				return -1;
			}
			else if (arr[x][y] == 0 && arr[o.x][o.y] != 0) {
				return 1;
			}
			else return 0;
		}
	}

	static class Group implements Comparable<Group> {

		ArrayList<Point> pointArrayList;
		int rainbowCnt;
		Point standardPoint;

		Group() {
			pointArrayList = new ArrayList<>();
		}

		public int countRainbowCnt() {
			int cnt = 0;
			for(int i=0; i<pointArrayList.size(); i++) {
				if (arr[pointArrayList.get(i).x][pointArrayList.get(i).y] == 0) cnt++;
			}
			return cnt;
		}

		public boolean containsGeneralBlock() {
			for(int i=0; i<pointArrayList.size(); i++) {
				if (arr[pointArrayList.get(i).x][pointArrayList.get(i).y] > 0) return true;
			}
			return false;
		}

		// 1. 크기가 가장 큰 블록 그룹을 찾는다.
		//// 1.1 그러한 블록 그룹이 여러 개이면 포함된 무지개 블록의 수가 가장 많은 블록 그룹,
		//// 1.2 그러한 블록도 여러개라면 {기준 블록}의 행이 가장 큰 것을,
		//// 1.3 그것도 여러개이면 {기준 블록}열이 가장 큰 것을 찾는다

		@Override
		public int compareTo(Group o) {
			if (this.pointArrayList.size() != o.pointArrayList.size()) {
				return this.pointArrayList.size() > o.pointArrayList.size() ? -1 : 1;
			}
			if (this.rainbowCnt != o.rainbowCnt) {
				return this.rainbowCnt > o.rainbowCnt ? -1 : 1;
			}
			if (this.standardPoint.x != o.standardPoint.x) {
				return this.standardPoint.x > o.standardPoint.x ? -1 : 1;
			}
			if (this.standardPoint.y != o.standardPoint.y) {
				return this.standardPoint.y > o.standardPoint.y ? -1 : 1;
			}
			return 0;
		}
	}
}
