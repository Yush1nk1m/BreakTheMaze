#pragma once

#include "ofMain.h"
#include "ofxGif.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

#define MAIN		0
#define EASY_MODE	1
#define HARD_MODE	2
#define RESULT		3

#define UP		0
#define DOWN	1
#define LEFT	2
#define RIGHT	3

#define LEFT_X		212		// 미로의 좌상단 꼭짓점의 X 좌표
#define TOP_Y		84		// 미로의 좌상단 꼭짓점의 Y 좌표
#define RIGHT_X		812		// 미로의 우하단 꼭짓점의 X 좌표
#define BOTTOM_Y	684		// 미로의 우하단 꼭짓점의 Y 좌표
#define MARGIN		4		// Anti-aliasing을 위한 margin

#define MAZE_LENGTH	(RIGHT_X - LEFT_X)	// 게임 플레이 화면에 그려지는 미로의 너비(= 높이)

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


		/* 미로를 다루는 함수들 */
		void initializeMaze(int game_mode);		// 게임 모드에 따라 미로 및 관련된 변수들을 초기화하는 함수
		void createMaze(int row, int col);		// recursive backtracking algorithm을 이용하여 완전 미로를 구성하는 함수
		void deinitializeMaze();				// 미로와 관련된 데이터들을 원상태로 되돌리는 함수

		void drawGameScreen();	// 게임 화면을 그리는 함수

		/* 미로와 직접적으로 관련된 데이터들 */
		vector< vector< char > > maze;	// 미로의 요소를 나타내는 2차원 벡터
		vector< vector< bool > > visited;	// 완전 미로를 구성하기 위해 쓰이는 방문 여부 벡터
		int HEIGHT;		// 미로의 높이(방의 개수만 고려)
		int WIDTH;		// 미로의 너비(방의 개수만 고려)
		int maze_row;	// maze 벡터의 행 개수(벽 포함)
		int maze_col;	// maze 벡터의 열 개수(벽 포함)
		unsigned int total_wall = 0;		// 미로에 존재하는 벽의 총 개수(0이 되면 게임 종료)

		int step;	// 매우 중요한 값: 화면 상에서 미로가 그려지기 시작하는 (LEFT_X, TOP_Y)로부터 maze의 각 원소가 얼마나 떨어져 있는지 나타낸다.
		int image_size;		// 그릴 entity의 이미지 너비 및 높이
		/* 미로와 직접적으로 관련된 데이터들 */

		/* 게임 스테이터스를 다루는 함수들 */
		void initializeGame();
		void deinitializeGame();

		/* 게임 플레이와 관련된 데이터들 */
		unsigned int available_power = 0;	// 벽을 부술 수 있는 횟수
		unsigned int total_energy = 0;		// 지금까지 획득한 에너지 개수: 플레이어 속도를 올려줌
		int directing = -1;	// 현재 누르고 있는 방향키 종류 저장

		/* 캐릭터를 부드럽게 이동시키기 위한 변수 */
		bool sliding = false;	// 캐릭터가 슬라이딩 상태인지 판단하는 불 변수
		int move_x = 0;		// 캐릭터가 이동해야 한다면 현재 위치에서 스크린 상의 이동한 X 좌표 거리를 저장해놓는 용도의 변수
		int move_y = 0;		// 캐릭터가 이동해야 한다면 현재 위치에서 스크린 상의 이동한 Y 좌표 거리를 저장해놓는 용도의 변수
		int move_direction = -1;	// 캐릭터가 현재 슬라이딩하고 있는 방향을 나타내는 변수

		/* 게임 플레이와 관련된 데이터들 */

		ofTrueTypeFont gamename_font;	// 화면에 게임 이름을 출력할 때 사용할 폰트
		string gamename_string;		// 화면에 출력할 문자열(게임 이름)
		float gamenameX;	// 문자열을 화면 중앙에 정렬하기 위한 변수

		ofTrueTypeFont gamemode_font;	// 화면에 게임 모드를 출력할 때 사용할 폰트
		string gamemode_string;		// 화면에 출력할 문자열(게임 모드)
		float gamemodeX;	// 문자열을 화면 중앙에 정렬하기 위한 변수

		ofTrueTypeFont remain_power_font;	// 화면에 available_power 값을 출력할 때 사용할 폰트

		ofTrueTypeFont result_font;		// 결과 화면에 문자를 출력할 때 사용할 폰트
		string result_string;	// 화면에 출력할 문자열
		float resultX;		// 문자열을 화면 중앙에 정렬하기 위한 변수

		ofTrueTypeFont result_font2;	// 결과 화면에 문자를 출력할 때 사용할 폰트
		string result_string2;	// 화면에 출력할 문자열
		float resultX2;		// 문자열을 화면 중앙에 정렬하기 위한 변수

		ofxGIF::fiGifLoader happycat;	// 해피캣을 그리기 위한 애드온 자료구조
		int happycatFrame;	// 해피캣 gif의 프레임을 나타내는 인덱스

		ofImage main_image;		// 메인 화면의 게임 이미지
		int screen_mode = MAIN;	// MAIN_SCREEN or EASY_MODE_SCREEN or HARD_MODE_SCREEN 저장

		ofImage miner_image;	// 게임 캐릭터(광부) 이미지
		int minerX;				// 미로에서 캐릭터가 위치한 X 좌표
		int minerY;				// 미로에서 캐릭터가 위치한 Y 좌표

		ofImage item_image;		// 게임 아이템(에너지 드링크) 이미지
		int itemX;				// 미로에서 아이템이 위치한 X 좌표
		int itemY;				// 미로에서 아이템이 위치한 Y 좌표
		
		bool key_lock = false;	// 키 입력을 차단하는 플래그
		bool easy_mode = false;	// 게임이 이지 모드임을 나타내는 플래그
		bool hard_mode = false;	// 게임이 하드 모드임을 나타내는 플래그
};
