#include <iostream>
#include <conio.h> // Windows에서 키 입력(getch)을 받기 위해 필요하다고 함
#include <windows.h> // Sleep 함수를 위해 필요하다고 함


//Void 사용 및 문구 출력기능 사용
void IntroMessage()
{
    std::cout << "강의 4일차 과제용 게임" << std::endl;
    Sleep(2000);
}


//맵 크기결정 (상수 사용)
const int MAP_SIZE = 8;

//맵 크기 초기화(변수 사용)
int X = 0;
int Y = 0;

//초기 플레이어 위치 결정
int PlayerX = 0;
int PlayerY = 0;

//초기 플레이어 체력 공격력 방어력 결정
int PlayerHP = 10;
int PlayerATK = 3;
int PlayerDEF = 1;

//초기 적 위치 결정
int EnemyX = 7;
int EnemyY = 7;

//초기 적 체력 결정 공격력 방어력 결정
int EnemyHP = 10;
int EnemyATK = 2;
int EnemyDEF = 1;



//플레이어 공격력과 적의 공격력 계산(사칙연산)
int PlayerDamage(int PlayerATK, int EnemyDEF)
{
    int PlayerDamage = PlayerATK - EnemyDEF;
    if (PlayerDamage < 0) PlayerDamage = 0;
    return PlayerDamage;
}

//적의 공격력 계산
int EnemyDamage(int EnemyATK, int PlayerDEF)
{
    int EnemyDamage = EnemyATK - PlayerDEF;
    if (EnemyDamage < 0) EnemyDamage = 0;
    return EnemyDamage;
}



//맵 그리기(for문 및 if elseif사용)
void DrawingMap()
{

    for (int Y = 0; Y < MAP_SIZE; Y++)
    {
        for (int X = 0; X < MAP_SIZE; X++)
        {
            if (X == PlayerX && Y == PlayerY) std::cout << "@";
          
            else if(X == EnemyX && Y == EnemyY && EnemyHP > 0) std::cout << "Z";
           
            else std::cout << ".";
                
            
        }

        if (Y == 1) std::cout << "\t [ PLAYER HP : " << PlayerHP << " ATK : " << PlayerATK<< " DEF : " << PlayerDEF << "]";
        if (Y == 2) std::cout << "\t [ ENEMY  HP : " << EnemyHP << " ATK : " << EnemyATK << " DEF : " << EnemyDEF << "]";
        if (Y == 3 && EnemyHP <= 0) std::cout << "\t  (적 처치 완료!)";
        if (Y == 7) std::cout << "\t 이동은 (W, A, S, D), 플레이어는 @, 적은 Z";
        std::cout << "\n";
    }
    
}

//키 입력받기
char InputMoveKey()
{
   return _getch();
}

//키 입력에 따라 플레이어 좌표 수정
void Moveplayer(char input)
{
    int nextX = PlayerX;
    int nextY = PlayerY;

    if (input == 'w') nextY--;
    if (input == 's') nextY++;
    if (input == 'a') nextX--;
    if (input == 'd') nextX++;

    if (nextX < 0 || nextX >= MAP_SIZE || nextY < 0 || nextY >= MAP_SIZE) {
        return; // 맵 밖으로 나가려고 하면 아무것도 안 함 (이동 취소)
    }

    if (nextX == EnemyX && nextY == EnemyY)
    {
        if (EnemyHP > 0 && PlayerHP > 0)
        {

            EnemyHP = EnemyHP - PlayerDamage(PlayerATK, EnemyDEF);
            PlayerHP = PlayerHP - EnemyDamage(EnemyATK, PlayerDEF);
 
        }
        else if (EnemyHP == 0)
        {
            PlayerX = nextX;
            PlayerY = nextY;
        }
        else if (PlayerHP == 0)
        {
            return;
        }
    }
    else {
        PlayerX = nextX;
        PlayerY = nextY;
    }

}



//지속적인 맵그리기 반복(While 사용)
void DrawConsistMap()
{
    while (true)
    {
        system("cls"); // 화면을 깨끗이 지운다고 함
        DrawingMap();
        char key = InputMoveKey(); // 키를 받아서 변수에 저장한다고 함
        Moveplayer(key);           // 그 변수를 이동 함수에 전달
    }
}



int main()
{
    
    IntroMessage();
    DrawConsistMap();

    return 0;

}


