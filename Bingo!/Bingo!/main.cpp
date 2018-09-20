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

	}

	return 0;
}