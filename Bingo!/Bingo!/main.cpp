/*
제목: 빙고 게임 만들기
만든이: 이한주
만든 날짜: 2018-09-20
*/

#include <iostream>
#include <ctime>

using namespace std;

const int STAR = -1;

int main(void)
{
	// 1 ~ 25로 빙고판 초기화
	int iNumber[25] = {};

	for (int i = 0; i < 25; i++)
		iNumber[i] = i + 1;

	srand((unsigned)time(NULL));

	// 빙고판의 순서를 섞어 준다
	int idx1, idx2, temp;
	for (int i = 0; i < 100; i++)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;
		temp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = temp;
	}

	bool finish = false;

	int bingoLine = 0;
	
	while (!finish)
	{
		system("cls");
		// 빙고 출력
		for (int i = 0; i < 25; i++)
		{
			if (iNumber[i] == STAR)
				cout << '*' << '\t';
			else
				cout << iNumber[i] << '\t';

			if ((i + 1) % 5 == 0)
				cout << '\n';
		}

		
		cout << "Bingo Line: " << bingoLine << endl;
		if (bingoLine == 5)
			break;
		
		cout << "숫자를 입력하세요(0 종료)> ";
		int input;
		cin >> input;

		// 종료조건
		if (input == 0)
			finish = true;
		
		// 예외 처리
		if (input < 1 || input > 25)
			continue;
		

		// 중복 체크
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

		// 빙고 체크
		int star;
		bingoLine = 0;
		
		// 가로 빙고 체크
		for (int i = 0; i < 5; i++)
		{
			star = 0;
			for (int j = 0; j < 5; j++)
			{
				if (iNumber[i * 5 + j] == STAR)
					star++;
			}

			if (star == 5)
				bingoLine++;
		}

		// 세로 빙고 체크
		for (int i = 0; i < 5; i++)
		{
			star = 0;
			for (int j = 0; j < 5; j++)
			{
				if (iNumber[i + j * 5] == STAR)
					star++;
			}

			if (star == 5)
				bingoLine++;
		}

		// 대각선(좌상단 -> 우하단) 빙고 체크
		star = 0;
		for (int i = 0; i < 25; i+= 6)
		{
			if (iNumber[i] == STAR)
				star++;

			if (star == 5)
				bingoLine++;
		}

		// 대각선(우상단 -> 좌하단) 빙고 체크
		star = 0;
		for (int i = 4; i <= 20; i += 4)
		{
			if (iNumber[i] == STAR)
				star++;

			if (star == 5)
				bingoLine++;
		}
		
	}

	return 0;
}