import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

// 로봇은 올리는 위치에만 올릴 수 있고
// 내리는 위치에 도달하면 그 즉시 내린다
// 로봇은 컨베이어벨트위에서 스스로 이동할 수 있다
// 로봇을 올리는 위치에 올리거나 / 로봇이 어떤 칸으로 이동 시 -> 그 칸의 내구도 -1 감소

// 1. 벨트가 칸 위에 있는 로봇과 함께 한 칸 회전
//// 1-1 이 때에도 로봇이 내릴 칸에 위치 시 내려주어야 함
// 2. 가장 먼저 벨트에 올라간 로봇부터, 회전하는 방향으로 한 칸 이동 (이동할 수 없으면 가만히)
//// 로봇이 이동하기 위해서는
//// 2-1 이동하려는 칸에 로봇이 없음
//// 2-2 이동하려는 칸의 내구도가 1 이상 남아있어야 함
// 3. 올리는 위치에 있는 칸의 내구도가 0이 아니면 올리는 위치에 로봇을 올림
// 4. 내구도가 0인 칸의 개수가 K개 이상이라면 과정 종료. 아니면 다시 1번으로 돌아감

// 2 <= N <= 100

// return: 종료되었을 때 몇 번째 단계가 진행중이었는지 구해보자. 첫번째가 1단계

// 1. 자료구조 선정
// 2. 구현하기
// 3. 답 도출

public class Main {

	static int[] arr; // 내구도 정보
	static int[] roInfo; // 해당 인덱스 위치의 로봇 정보
	static Queue<Robot> q = new LinkedList<>();

	public static void main(String[] args) throws IOException {

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = null;
		st = new StringTokenizer(br.readLine());
		int N = Integer.parseInt(st.nextToken());
		int K = Integer.parseInt(st.nextToken());

		arr = new int[2*N];
		roInfo = new int[2*N];
		st = new StringTokenizer(br.readLine());
		for(int i=0; i<2*N; i++) arr[i] = Integer.parseInt(st.nextToken());

		int startIdx = 0; // 올리는 위치
		int res = 0;

		while(true) {

			res++; // 단계 기록

			// 1
			startIdx--; // 로봇과 함께 한 칸 회전, 이때 내리는 위치에 로봇이 있으면 로봇 내려주기
			if (startIdx < 0) startIdx = 2*N - 1;

			Queue<Robot> tmp = new LinkedList<>();
			while(!q.isEmpty()) {
				Robot r = q.poll();
				if (r.posIdx != ((startIdx + N - 1)%(2*N))) tmp.add(r);
				else {
					// 내리는 위치의 로봇이면
					roInfo[(startIdx + N - 1)%(2 * N)] = 0;
				}
			}
			q = tmp;

			// 2
			tmp = new LinkedList<>();
			while(!q.isEmpty()) {
				Robot r = q.poll();
				int nextIdx = (r.posIdx + 1) % (2*N); // 로봇이 이동할 다음 칸의 인덱스

				if (nextIdx == ((startIdx + N - 1)%(2*N)) && arr[nextIdx] >= 1 && roInfo[nextIdx] == 0) {
					// 내리는 위치에 도달 시
					roInfo[r.posIdx] = 0; // 현재 위치 0
					arr[nextIdx] -= 1; // 이동한 위치의 내구도 -1 감소
					// 어차피 내리니까 내리는 위치표시 해 줄 필요 없음
					// 큐에 넣을 필요 없음
				}
				else if (arr[nextIdx] >= 1 && roInfo[nextIdx] == 0) {
					// 이동하는 위치가 내리는 위치는 아니지만 이동할 수 있음
					roInfo[r.posIdx] = 0;
					roInfo[nextIdx] = 1;
					arr[nextIdx] -= 1;
					tmp.add(new Robot(nextIdx));
				}
				else tmp.add(r); // 이동할 수 없으면 가만히
			}
			q = tmp;

			// 3
			if (arr[startIdx] >= 1) {
				roInfo[startIdx] = 1; // 로봇 위치시키기
				arr[startIdx] -= 1; // 내구도 1 감소
				q.add(new Robot(startIdx));
			}

			// 4
			int tmpCnt = 0;
			for(int i=0; i<2*N; i++) {
				if (arr[i] == 0) tmpCnt++;
			}
			if (tmpCnt >= K) break;
		}

		System.out.println(res);
	}

	static class Robot {
		int posIdx; // 로봇이 위치한 idx

		Robot(int posIdx) {
			this.posIdx = posIdx;
		}
	}
}
