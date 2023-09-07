import java.util.*;
import java.io.*;

public class Main {

	// 파이어볼 방향
	static int[] dirX = {-1, -1, 0, 1, 1, 1, 0, -1};
	static int[] dirY = {0, 1, 1, 1, 0, -1, -1, -1};
	static int[] dirD = {0, 1, 2, 3, 4, 5, 6, 7};

	static int N, M, K;
	static ArrayList<Fireball> al = new ArrayList<>();

	// 1. 파이어볼 이동
	// 이동 끝난 후
	//// 한 칸에 2개 이상의 파이어볼이 있는 경우
	//// 2.1 같은 칸에 있는 파이어볼은 모두 하나로 합쳐짐
	//// 2.2 파이어볼은 4개의 파이어볼로 나누어짐
	//// 2.3 나누어진 파이어볼의 {질량, 속력, 방향} 은 다음과 같음
	//// 2.4 질량이 0인 파이어볼은 소멸

	public static void main(String[] args) throws IOException {

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken()); M = Integer.parseInt(st.nextToken()); K = Integer.parseInt(st.nextToken());

		for(int i=0; i<M; i++) {
			st = new StringTokenizer(br.readLine());
			int r = Integer.parseInt(st.nextToken());
			int c = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int s = Integer.parseInt(st.nextToken());
			int d = Integer.parseInt(st.nextToken());

			al.add(new Fireball(r, c, m, s, d));
		}

		for(int i=0; i<K; i++) {
			// 파이어볼 이동
			movingFireball();

			// 같은 칸에 여러 개의 파이어볼에 대해서 합치기
			sumUp();

		}

		int res = 0;
		for(int i=0; i<al.size(); i++) {
			res += al.get(i).w;
		}
		System.out.println(res);
	}

	// 파이어볼 이동
	public static void movingFireball() {

		ArrayList<Fireball> alTmp = new ArrayList<>();

		for(int i=0; i<al.size(); i++) {
			int cX = al.get(i).r; int cY = al.get(i).c;
			int cW = al.get(i).w; int cS = al.get(i).s; int cD = al.get(i).d;

			int nX = cX; int nY = cY;
			// 다음 좌표 구하기

			for(int j=0; j<cS; j++) {
				// 속력 만큼 방향 이동
				nX += dirX[cD]; nY += dirY[cD];

				if (nX < 1) nX = N;
				if (nX > N) nX = 1;
				if (nY < 1) nY = N;
				if (nY > N) nY = 1;
			}

			alTmp.add(new Fireball(nX, nY, cW, cS, cD));
		}

		al = alTmp;
	}

	// 같은 칸에 여러 개의 파이어볼에 대해서 합치기
	public static void sumUp() {

		HashMap<String, ArrayList<Fireball>> hm = new HashMap<>();
		ArrayList<Fireball> alTmp = new ArrayList<>();

		for(int i=0; i<al.size(); i++) {
			int cX = al.get(i).r; int cY = al.get(i).c;
			int cW = al.get(i).w; int cS = al.get(i).s; int cD = al.get(i).d;

			String key = cX + " " + cY;
			if (hm.containsKey(key)) {
				hm.get(key).add(al.get(i));
			}
			else {
				hm.put(key, new ArrayList<>());
				hm.get(key).add(al.get(i));
			}
		}

		Set<String> keySet = hm.keySet();
		for(String key : keySet) {
			if (hm.get(key).size() == 1) {
				alTmp.add(hm.get(key).get(0));
				continue;
			}

			// 이동이 끝난 뒤 2개 이상의 파이어볼이 있는 칸에 대해서
			// 파이어볼 하나로 합치기
			ArrayList<Fireball> fireballs = hm.get(key);

			String[] srr = key.split(" ");
			int nx = Integer.parseInt(srr[0]); int ny = Integer.parseInt(srr[1]);
			int d1, d2, d3, d4; // 다음 방향들

			int sumW = 0; int sumS = 0;
			for(int i=0; i<fireballs.size(); i++) {
				sumW += fireballs.get(i).w;
				sumS += fireballs.get(i).s;
			}

			int nW = Math.floorDiv(sumW, 5);
			int nS = Math.floorDiv(sumS, fireballs.size());

			boolean dirFlag = findDir(fireballs);
			if (dirFlag == true) {
				d1 = 0; d2 = 2; d3 = 4; d4 = 6;
			}
			else {
				d1 = 1; d2 = 3; d3 = 5; d4 = 7;
			}

			// 새롭게 분화된 4개의 파이어볼 넣기
			if (nW > 0) {
				alTmp.add(new Fireball(nx, ny, nW, nS, d1));
				alTmp.add(new Fireball(nx, ny, nW, nS, d2));
				alTmp.add(new Fireball(nx, ny, nW, nS, d3));
				alTmp.add(new Fireball(nx, ny, nW, nS, d4));
			}

		}

		al = alTmp;
	}

	// 방향이 모두 짝수이거나 모두 홀수이면 -> true 반환
	public static boolean findDir(ArrayList<Fireball> fb) {
		int odd = 0;
		int even = 0;

		for(int i=0; i<fb.size(); i++) {
			if (fb.get(i).d % 2 == 0) even++;
			else odd++;
		}

		if (even == fb.size() || odd == fb.size()) return true;
		else return false;
	}

	static class Fireball {
		int r, c; // { r행, c열 }
		int w; // 질량
		int s; // 속력
		int d; // 방향

		Fireball(int r, int c, int w, int s, int d) {
			this.r = r; this.c = c;
			this.w = w;
			this.s = s;
			this.d = d;
		}

		@Override
		public String toString() {
			return "[" + r + ", " + c + "] | " + "w = " + w + ", s = " + s + ", d = " + d;
		}
	}
}
