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

#define LEFT_X		212		// �̷��� �»�� �������� X ��ǥ
#define TOP_Y		84		// �̷��� �»�� �������� Y ��ǥ
#define RIGHT_X		812		// �̷��� ���ϴ� �������� X ��ǥ
#define BOTTOM_Y	684		// �̷��� ���ϴ� �������� Y ��ǥ
#define MARGIN		4		// Anti-aliasing�� ���� margin

#define MAZE_LENGTH	(RIGHT_X - LEFT_X)	// ���� �÷��� ȭ�鿡 �׷����� �̷��� �ʺ�(= ����)

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


		/* �̷θ� �ٷ�� �Լ��� */
		void initializeMaze(int game_mode);		// ���� ��忡 ���� �̷� �� ���õ� �������� �ʱ�ȭ�ϴ� �Լ�
		void createMaze(int row, int col);		// recursive backtracking algorithm�� �̿��Ͽ� ���� �̷θ� �����ϴ� �Լ�
		void deinitializeMaze();				// �̷ο� ���õ� �����͵��� �����·� �ǵ����� �Լ�

		void drawGameScreen();	// ���� ȭ���� �׸��� �Լ�

		/* �̷ο� ���������� ���õ� �����͵� */
		vector< vector< char > > maze;	// �̷��� ��Ҹ� ��Ÿ���� 2���� ����
		vector< vector< bool > > visited;	// ���� �̷θ� �����ϱ� ���� ���̴� �湮 ���� ����
		int HEIGHT;		// �̷��� ����(���� ������ ���)
		int WIDTH;		// �̷��� �ʺ�(���� ������ ���)
		int maze_row;	// maze ������ �� ����(�� ����)
		int maze_col;	// maze ������ �� ����(�� ����)
		unsigned int total_wall = 0;		// �̷ο� �����ϴ� ���� �� ����(0�� �Ǹ� ���� ����)

		int step;	// �ſ� �߿��� ��: ȭ�� �󿡼� �̷ΰ� �׷����� �����ϴ� (LEFT_X, TOP_Y)�κ��� maze�� �� ���Ұ� �󸶳� ������ �ִ��� ��Ÿ����.
		int image_size;		// �׸� entity�� �̹��� �ʺ� �� ����
		/* �̷ο� ���������� ���õ� �����͵� */

		/* ���� �������ͽ��� �ٷ�� �Լ��� */
		void initializeGame();
		void deinitializeGame();

		/* ���� �÷��̿� ���õ� �����͵� */
		unsigned int available_power = 0;	// ���� �μ� �� �ִ� Ƚ��
		unsigned int total_energy = 0;		// ���ݱ��� ȹ���� ������ ����: �÷��̾� �ӵ��� �÷���
		int directing = -1;	// ���� ������ �ִ� ����Ű ���� ����

		/* ĳ���͸� �ε巴�� �̵���Ű�� ���� ���� */
		bool sliding = false;	// ĳ���Ͱ� �����̵� �������� �Ǵ��ϴ� �� ����
		int move_x = 0;		// ĳ���Ͱ� �̵��ؾ� �Ѵٸ� ���� ��ġ���� ��ũ�� ���� �̵��� X ��ǥ �Ÿ��� �����س��� �뵵�� ����
		int move_y = 0;		// ĳ���Ͱ� �̵��ؾ� �Ѵٸ� ���� ��ġ���� ��ũ�� ���� �̵��� Y ��ǥ �Ÿ��� �����س��� �뵵�� ����
		int move_direction = -1;	// ĳ���Ͱ� ���� �����̵��ϰ� �ִ� ������ ��Ÿ���� ����

		/* ���� �÷��̿� ���õ� �����͵� */

		ofTrueTypeFont gamename_font;	// ȭ�鿡 ���� �̸��� ����� �� ����� ��Ʈ
		string gamename_string;		// ȭ�鿡 ����� ���ڿ�(���� �̸�)
		float gamenameX;	// ���ڿ��� ȭ�� �߾ӿ� �����ϱ� ���� ����

		ofTrueTypeFont gamemode_font;	// ȭ�鿡 ���� ��带 ����� �� ����� ��Ʈ
		string gamemode_string;		// ȭ�鿡 ����� ���ڿ�(���� ���)
		float gamemodeX;	// ���ڿ��� ȭ�� �߾ӿ� �����ϱ� ���� ����

		ofTrueTypeFont remain_power_font;	// ȭ�鿡 available_power ���� ����� �� ����� ��Ʈ

		ofTrueTypeFont result_font;		// ��� ȭ�鿡 ���ڸ� ����� �� ����� ��Ʈ
		string result_string;	// ȭ�鿡 ����� ���ڿ�
		float resultX;		// ���ڿ��� ȭ�� �߾ӿ� �����ϱ� ���� ����

		ofTrueTypeFont result_font2;	// ��� ȭ�鿡 ���ڸ� ����� �� ����� ��Ʈ
		string result_string2;	// ȭ�鿡 ����� ���ڿ�
		float resultX2;		// ���ڿ��� ȭ�� �߾ӿ� �����ϱ� ���� ����

		ofxGIF::fiGifLoader happycat;	// ����Ĺ�� �׸��� ���� �ֵ�� �ڷᱸ��
		int happycatFrame;	// ����Ĺ gif�� �������� ��Ÿ���� �ε���

		ofImage main_image;		// ���� ȭ���� ���� �̹���
		int screen_mode = MAIN;	// MAIN_SCREEN or EASY_MODE_SCREEN or HARD_MODE_SCREEN ����

		ofImage miner_image;	// ���� ĳ����(����) �̹���
		int minerX;				// �̷ο��� ĳ���Ͱ� ��ġ�� X ��ǥ
		int minerY;				// �̷ο��� ĳ���Ͱ� ��ġ�� Y ��ǥ

		ofImage item_image;		// ���� ������(������ �帵ũ) �̹���
		int itemX;				// �̷ο��� �������� ��ġ�� X ��ǥ
		int itemY;				// �̷ο��� �������� ��ġ�� Y ��ǥ
		
		bool key_lock = false;	// Ű �Է��� �����ϴ� �÷���
		bool easy_mode = false;	// ������ ���� ������� ��Ÿ���� �÷���
		bool hard_mode = false;	// ������ �ϵ� ������� ��Ÿ���� �÷���
};
