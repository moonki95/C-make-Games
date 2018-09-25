/*
제목: 빙고 게임 만들기
만든이: 이한주
만든 날짜: 2018-09-25
*/

#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;

enum AI_MODE {EASY = 1, HARD};	// AI 난이도

enum LINE// 빙고 라인 12개
{
	LN_H1, LN_H2, LN_H3, LN_H4, LN_H5,	// 가로 빙고 라인
	LN_V1, LN_V2, LN_V3, LN_V4, LN_V5,	// 세로 빙고 라인
	LN_LT, LN_RT	// 대각선 빙고 라인
};

const int STAR = -1;	// * 표시를 위한 변수 STAR

int main(void)
{
	// 유저, AI 빙고판
	int iNumber[25];
	int AINumber[25];

	// 유저, AI 빙고판 초기화
	for (int i = 0; i < 25; i++)
		AINumber[i] = iNumber[i] = i + 1;

	srand((unsigned)time(NULL));

	// AI 난이도 선택
	int mode;
	while (true)
	{
		system("cls");
		mode;
		cout << "AI 난이도 선택(1:EASY, 2:HARD): ";
		cin >> mode;
		if (mode == 1 || mode == 2)
			break;
	}

	// 빙고판의 순서를 섞어 준다
	int idx1, idx2, temp;
	for (int i = 0; i < 100; i++)
	{
		// 유저의 빙고판
		idx1 = rand() % 25;
		idx2 = rand() % 25;
		temp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = temp;

		// AI의 빙고판
		idx1 = rand() % 25;
		idx2 = rand() % 25;
		temp = AINumber[idx1];
		AINumber[idx1] = AINumber[idx2];
		AINumber[idx2] = temp;
	}

	bool finish = false; //반복문 조건

	int bingoLine = 0, AIbingoLine = 0;	// user와 AI의 빙고 수

	bool userSelect = true; // user입력 판별
	
	while (!finish)
	{
		system("cls");

		// 유저 빙고 출력
		cout << "================User===============" << endl;
		for (int i = 0; i < 25; i++)
		{
			if (iNumber[i] == STAR)
				cout << '*' << '\t';
			else
				cout << iNumber[i] << '\t';

			if ((i + 1) % 5 == 0)
				cout << '\n';
		}

		cout << "User Bingo Line: " << bingoLine << endl << endl;
		if (bingoLine >= 5)

		{
			cout << "User 승리!" << endl;
			break;
		}

		// AI 빙고 출력
		cout << "=================AI================" << endl;
		for (int i = 0; i < 25; i++)
		{
			if (AINumber[i] == STAR)
				cout << '*' << '\t';
			else
				cout << AINumber[i] << '\t';

			if ((i + 1) % 5 == 0)
				cout << '\n';
		}

		cout << "AI Bingo Line: " << AIbingoLine << endl << endl;
		if (AIbingoLine >= 5)
		{
			cout << "AI 승리!" << endl;
			break;
		}
		
		int input;	// 숫자 입력 변수
		
		if (userSelect) // user 선택
		{
			// 숫자 입력
			cout << "숫자를 입력하세요(0 종료)> ";
			cin >> input;

			// 종료조건
			if (input == 0)
				finish = true;

			// 예외 처리
			if (input < 1 || input > 25)
				continue;

			// 유저가 한번 선택 한 후 AI가 선택
			userSelect = false;
		}
		else // AI 선택
		{
			if (mode == EASY)	// 선택하지 않은 수에서 랜덤하게 선택
			{
				int count = 0;
				int arr[25];
				for (int i = 0; i < 25; i++)
				{
					if (AINumber[i] != STAR)
						arr[count++] = AINumber[i];
				}
				input = arr[rand() % count];
			}
				
			if (mode == HARD)	// 가장 빙고 가능성이 높은 라인에서 선택
			{
				int count = 0;
				int max_star = 0;	// 5개 이하중에서 가장 많은 별의 개수
				int line = 0;		// max_star의 라인 (enum LINE에서 선택)

				for (int i = 0; i < 5; i++)
				{
					count = 0;
					for (int j = 0; j < 5; j++)
					{
						// 가로 라인 체크
						if (AINumber[i * 5 + j] == STAR)
						{
							++count;
						}

						if (max_star <= count && count < 5)
						{
							line = i;
							max_star = count;
						}
					}
				}

				for (int i = 0; i < 5; i++)
				{
					count = 0;
					for (int j = 0; j < 5; j++)
					{
						// 세로 라인 체크
						if (AINumber[i + j * 5] == STAR)
						{
							++count;
						}

						if (max_star < count && count < 5)
						{
							line = i + 5;
							max_star = count;
						}
					}
				}

				// 왼쪽 -> 오른쪽 대각선 체크
				count = 0;
				for (int i = 0; i < 25; i += 6)
				{
					if (AINumber[i] == STAR)
					{
						++count;
					}
				}
				if (max_star < count && count < 5)
				{
					line = LN_LT;
					max_star = count;
				}

				// 오른쪽 -> 왼쪽 대각선 체크
				count = 0;
				for (int i = 4; i <= 20; i += 4)
				{
					if (AINumber[i] == STAR)
					{
						++count;
					}
				}
				if (max_star < count && count < 5)
				{
					line = LN_RT;
					max_star = count;
				}

				if (line <= LN_H5) // 가로 줄이 최대 일 경우
				{
					for (int i = 0; i < 5; i++)
					{
						if (AINumber[line * 5 + i] != STAR)
						{
							input = AINumber[line * 5 + i];
							break;
						}
					}
				}
				else if (line <= LN_V5) // 세로 줄이 최대일 경우
				{
					for (int i = 0; i < 5; i++)
					{
						if (AINumber[(line - 5) + i * 5] != STAR)
						{
							input = AINumber[(line - 5) + 5 * i];
							break;
						}
					}
				}
				else if (line == LN_LT) // 왼쪽 -> 오른쪽 대각선이 최대일 경우
				{
					for (int i = 0; i < 25; i += 6)
					{
						if (AINumber[i] != STAR)
						{
							input = AINumber[i];
							break;
						}
					}
				}
				else    // 오른쪽 -> 왼쪽 대각선이 최대일 경우
				{
					for (int i = 4; i <= 20; i += 4)
					{
						if (AINumber[i] != STAR)
						{
							input = AINumber[i];
							break;
						}
					}
				}

			}
			
			userSelect = true; // AI가 선택 후 user가 선택
			cout << "AI 선택: " << input << endl;
			Sleep(2000);
		}
			
		// 유저 중복 체크
		bool bAcc = true;
		for (int i = 0; i < 25; i++)
		{
			if (input == iNumber[i])
			{
				// 숫자를 찾으면 중복이 아니므로
				bAcc = false;
				// *로 바꾸기 위해 STAR로 저장한다
				iNumber[i] = STAR;
				// 더 이상 찾을 필요가 없으므로 break
				break;
			}
		}

		// AI 중복 체크
		bAcc = true;
		for (int i = 0; i < 25; i++)
		{
			if (input == AINumber[i])
			{
				// 숫자를 찾으면 중복이 아니므로
				bAcc = false;
				// *로 바꾸기 위해 STAR로 저장한다
				AINumber[i] = STAR;
				// 더 이상 찾을 필요가 없으므로 break
				break;
			}
		}

		// 빙고 체크
		int star, AIstar;
		bingoLine = 0, AIbingoLine = 0;
		
		// 가로 빙고 체크
		for (int i = 0; i < 5; i++)
		{
			// 유저 빙고 체크
			star = 0;
			for (int j = 0; j < 5; j++)
			{
				if (iNumber[i * 5 + j] == STAR)
					star++;
			}

			if (star == 5)
				bingoLine++;

			// AI 빙고 체크
			AIstar = 0;
			for (int j = 0; j < 5; j++)
			{
				if (AINumber[i * 5 + j] == STAR)
					AIstar++;
			}

			if (AIstar == 5)
				AIbingoLine++;
		}

		// 세로 빙고 체크
		for (int i = 0; i < 5; i++)
		{
			// 유저 빙고 체크
			star = 0;
			for (int j = 0; j < 5; j++)
			{
				if (iNumber[i + j * 5] == STAR)
					star++;
			}

			if (star == 5)
				bingoLine++;

			// AI 빙고 체크
			AIstar = 0;
			for (int j = 0; j < 5; j++)
			{
				if (AINumber[i + j * 5] == STAR)
					AIstar++;
			}

			if (AIstar == 5)
				AIbingoLine++;
		}

		// 대각선(좌상단 -> 우하단) 빙고 체크
		star = 0, AIstar = 0;
		for (int i = 0; i < 25; i+= 6)
		{
			// 유저 빙고 체크
			if (iNumber[i] == STAR)
				star++;

			if (star == 5)
				bingoLine++;

			// AI 빙고체크
			if (AINumber[i] == STAR)
				AIstar++;

			if (AIstar == 5)
				AIbingoLine++;
		}

		// 대각선(우상단 -> 좌하단) 빙고 체크
		star = 0, AIstar = 0;
		for (int i = 4; i <= 20; i += 4)
		{
			// 유저 빙고 체크
			if (iNumber[i] == STAR)
				star++;

			if (star == 5)
				bingoLine++;

			// AI 빙고 체크
			if (AINumber[i] == STAR)
				AIstar++;

			if (AIstar == 5)
				AIbingoLine++;
		}
		
	}

	return 0;
}