#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	srand(time(0));		// ���� �̷� ������ ���� �õ� �� ����

	ofSetVerticalSync(true);	// ���� ����ȭ�� ����� �ֻ����� ���߾� �ʴ� ��� ������ ����
	ofBackground(ofColor::white);	// ��� ������� ����

	/* ��Ʈ ��ó : https://maplestory.nexon.com/Media/Font */
	gamename_font.load("MaplestoryBold.ttf", 50);		// ���� �̸��� ���� ���� ��Ʈ ũ�� 50���� ����
	gamemode_font.load("MaplestoryBold.ttf", 20);		// ���� ��带 ���� ���� ��Ʈ ũ�� 30���� ����
	remain_power_font.load("MaplestoryBold.ttf", 15);	// available_power�� ��Ÿ���� ���� ��Ʈ ũ�� 15�� ����
	result_font.load("MaplestoryBold.ttf", 75);			// ��� ȭ�鿡 ���� ���� ��Ʈ ũ�� 75�� ����
	result_font2.load("MaplestoryBold.ttf", 30);		// ��� ȭ�鿡 ���� ���� ��Ʈ ũ�� 60���� ����

	gamename_string = "Break the Maze";									// ȭ�鿡 ����� ���� �̸� ���ڿ�
	gamemode_string = "1. EASY MODE(5 X 5)	2. HARD MODE(10 X 10)	Q. EXIT";	// ȭ�鿡 ����� ���� ��� ���ڿ�

	result_string = "GAME COMPLETED";	// ��� ȭ�� ��ܿ� ����� ���� �Ϸ� ���ڿ�
	resultX = result_font.stringWidth(result_string);
	resultX = (ofGetWidth() - resultX) / 2;	// �ؽ�Ʈ�� ȭ�� �߾ӿ� �����ϱ� ���� ���

	result_string2 = "Press 'q' or 'Q' to return to the main screen";	// ��� ȭ�鿡 ����� �ȳ� ���ڿ�
	resultX2 = result_font2.stringWidth(result_string2);
	resultX2 = (ofGetWidth() - resultX2) / 2;	// �ؽ�Ʈ�� ȭ�� �߾ӿ� �����ϱ� ���� ���

	gamenameX = gamename_font.stringWidth(gamename_string);
	gamenameX = (ofGetWidth() - gamenameX) / 2;		// �ؽ�Ʈ�� ȭ�� �߾ӿ� �����ϱ� ���� ���

	gamemodeX = gamemode_font.stringWidth(gamemode_string);
	gamemodeX = (ofGetWidth() - gamemodeX) / 2;		// �ؽ�Ʈ�� ȭ�� �߾ӿ� �����ϱ� ���� ���

	main_image.load("images/main.png");		// ���� �̹��� �ε�
	miner_image.load("images/miner.png");	// ĳ���� �̹��� �ε�
	item_image.load("images/item.png");		// ������ �̹��� �ε�
	
	happycat.load("images/happycat.gif");	// ����Ĺ �̹��� �ε�
}

//--------------------------------------------------------------
void ofApp::update(){
	if (screen_mode == RESULT && ofGetElapsedTimeMillis() % 3) {
		happycatFrame++;
		if (happycatFrame > happycat.pages.size() - 1) happycatFrame = 0;
	}

	if (sliding && (easy_mode || hard_mode)) {

		if (move_direction == LEFT) {	// �������� �����̵� ���� ���
			move_x -= (step / 10) + (2 * available_power);	// miner�� �������� (step / 10) + (2 * available_power) �ȼ� �����̵���
			if (LEFT_X + (minerX * step) + move_x <= LEFT_X + ((minerX - 2) * step)) {	// (���� ���� ��ġ) + move_x <= (�̷��� ��ġ)
				key_lock = false;		// Ű ��� ����
				move_direction = -1;	// �����̵� ���� �ʱ�ȭ
				minerX -= 2;			// miner�� ��ǥ ������ �̵�
				move_x = 0;				// move_x �ʱ�ȭ
				sliding = false;		// sliding �ʱ�ȭ
			}
		}
		else if (move_direction == RIGHT) {	// ���������� �����̵� ���� ���
			move_x += (step / 10) + (2 * available_power);	// miner�� ���������� (step / 10) + (2 * available_power)�ȼ� �����̵���
			if (LEFT_X + (minerX * step) + move_x >= LEFT_X + ((minerX + 2) * step)) {	// (���� ���� ��ġ) + move_x >= (�̷��� ��ġ)
				key_lock = false;		// Ű ��� ����
				move_direction = -1;	// �����̵� ���� �ʱ�ȭ
				minerX += 2;			// miner�� ��ǥ ������ �̵�
				move_x = 0;				// move_x �ʱ�ȭ
				sliding = false;		// sliding �ʱ�ȭ
			}
		}
		else if (move_direction == UP) {	// ���� �����̵� ���� ���
			move_y -= (step / 10) + (2 * available_power);
			if (TOP_Y + (minerY * step) + move_y <= TOP_Y + ((minerY - 2) * step)) {	// (���� ���� ��ġ) + move_y <= (�̷��� ��ġ)
				key_lock = false;		// Ű ��� ����
				move_direction = -1;	// �����̵� ���� �ʱ�ȭ
				minerY -= 2;			// miner�� ��ǥ ������ �̵�
				move_y = 0;				// move_y �ʱ�ȭ
				sliding = false;		// sliding �ʱ�ȭ
			}
		}
		else if (move_direction == DOWN) {
			move_y += (step / 10) + (2 * available_power);
			if (TOP_Y + (minerY * step) + move_y >= TOP_Y + ((minerY + 2) * step)) {	// (���� ���� ��ġ) + move_y >= (�̷��� ��ġ)
				key_lock = false;		// Ű ��� ����
				move_direction = -1;	// �����̵� ���� �ʱ�ȭ
				minerY += 2;			// miner�� ��ǥ ������ �̵�
				move_y = 0;				// move_y �ʱ�ȭ
				sliding = false;		// sliding �ʱ�ȭ
			}
		}

		if (!sliding) {	// �� ���ǹ��� ����� �� sliding�� false�� �Ǿ��ٸ� ��ġ�� ������ �̷���� ���̴�
			if (minerX == itemX && minerY == itemY) {	// ĳ���Ͱ� �������� ȹ���ϸ�
				total_energy++;		// ������� ȹ���� ������ ���� 1 ����
				available_power++;	// ���� ���� �ִ� �� �μ��� Ƚ�� 1 ����
				
				do {	// ������ ��ġ�� ������ �ٽ� ����
					itemY = rand() % maze_row;	// �������� �� ��ġ ����
					itemX = rand() % maze_col;	// �������� �� ��ġ ����
				} while (itemY % 2 == 0 ||	// 2�� ������ �������� ��ġ�� ���� ����
					itemX % 2 == 0 ||	// 2�� ������ �������� ��ġ�� ���� ����
					(itemY == minerY && itemX == minerX));	// ĳ���Ϳ� ������ ��ġ�� ��ĥ �� ����
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(ofColor::darkGray);	// ȭ�� �׵θ� ����
	ofDrawRectangle(0, 0, 1024, 50);	// ȭ�� ��� �׵θ�
	ofDrawRectangle(0, 0, 50, 768);	// ȭ�� ���� �׵θ�
	ofDrawRectangle(0, 718, 1024, 50);	// ȭ�� �ϴ� �׵θ�
	ofDrawRectangle(974, 0, 50, 768);	// ȭ�� ���� �׵θ�


	if (screen_mode == MAIN) {	// ���� ȭ�� �׸���
		ofSetColor(255);	// �̹��� ����� ���� �� ����
		/* ���� ȭ�� �̹��� ��� */
		main_image.draw(50, 90, 924, 588);

		ofSetColor(ofColor::black);	// ���ڿ��� ���������� ���

		/* ���� �̸� ���ڿ� ��� */
		gamename_font.drawString(gamename_string, gamenameX, 105);	// ȭ�� �߾ӿ� �����Ͽ� ���� �̸� ���
		
		/* ���� ��� ���ڿ� ��� */
		gamemode_font.drawString(gamemode_string, gamemodeX, 710);	// ȭ�� �߾ӿ� �����Ͽ� ���� ��� ���

	}
	else if (screen_mode == EASY_MODE || screen_mode == HARD_MODE) {		// ���� ��� �Ǵ� �ϵ� ����� ��
		drawGameScreen();		// ���� �÷��� ȭ���� �׸���
	}
	else if (screen_mode == RESULT) {
		ofSetColor(ofColor::lightGoldenRodYellow);	// ȭ�� �׵θ� ����
		ofDrawRectangle(0, 0, 1024, 50);	// ȭ�� ��� �׵θ�
		ofDrawRectangle(0, 0, 50, 768);	// ȭ�� ���� �׵θ�
		ofDrawRectangle(0, 718, 1024, 50);	// ȭ�� �ϴ� �׵θ�
		ofDrawRectangle(974, 0, 50, 768);	// ȭ�� ���� �׵θ�
		
		ofSetColor(255);
		for (int i = 1; i <= 17; i++) {
			for (int j = 0; j <= 5; j++)
				happycat.pages[happycatFrame].draw(50 * i, 50 + 100 * j);
		}

		ofSetColor(ofColor::black);
		result_font.drawString(result_string, resultX, 120);
		result_font2.drawString(result_string2, resultX2, 618);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (!key_lock) {

		if (key == 'q' || key == 'Q') {	// q/Q �Է��� ������
			switch (screen_mode) {		// ���� ��ũ�� ���¿� ���� �ٸ��� ó���Ѵ�
			case MAIN:	// ���� ȭ���̸�
				ofExit();		// ���� ����
			case EASY_MODE:	// ���� �÷��� ȭ���̸�
				deinitializeMaze();		// �̷ο� ���õ� ���� ����
				deinitializeGame();		// ���Ӱ� ���õ� ���� ����
				screen_mode = MAIN;		// ���� ȭ������ ����
				easy_mode = false;		// ���� ������� ��Ÿ���� �÷��� ��Ȱ��ȭ
				break;
			case HARD_MODE:	// ���� �÷��� ȭ���̸�
				deinitializeMaze();		// �̷ο� ���õ� ���� ����
				deinitializeGame();		// ���Ӱ� ���õ� ���� ����
				screen_mode = MAIN;		// ���� ȭ������ ����
				hard_mode = false;		// �ϵ� ������� ��Ÿ���� �÷��� ��Ȱ��ȭ
				break;
			case RESULT:	// ��� ȭ���̸�
				screen_mode = MAIN;		// ���� ȭ������ ����
				break;
			}

			return;
		}

		if (key == '1' && screen_mode == MAIN) {	// '1'�� ������ ���� ���� ���� ����
			initializeMaze(EASY_MODE);	// �̷� ���� �ʱ�ȭ
			initializeGame();	// ���Ӱ� ���õ� ���� �ʱ�ȭ
			easy_mode = true;	// ���� ������� ��Ÿ���� �÷��� Ȱ��ȭ
			screen_mode = EASY_MODE;	// ��ũ���� ���� ���� ����

			return;

		}

		if (key == '2' && screen_mode == MAIN) {
			initializeMaze(HARD_MODE);
			initializeGame();	// ���Ӱ� ���õ� ���� �ʱ�ȭ
			hard_mode = true;	// �ϵ� ������� ��Ÿ���� �÷��� Ȱ��ȭ
			screen_mode = HARD_MODE;	// ��ũ���� �ϵ� ���� ����

			return;
		}

		if (key == OF_KEY_LEFT && (easy_mode || hard_mode)) {	// ���� �� ���� ����Ű�� ������ ������
			directing = LEFT;	// ������ ���ϰ� �ִٰ� ǥ��
			return;
		}
		if (key == OF_KEY_RIGHT && (easy_mode || hard_mode)) {	// ���� �� ������ ����Ű�� ������ ������
			directing = RIGHT;	// �������� ���ϰ� �ִٰ� ǥ��
			return;
		}
		if (key == OF_KEY_UP && (easy_mode || hard_mode)) {		// ���� �� ���� ����Ű�� ������ ������
			directing = UP;		// ���� ���ϰ� �ִٰ� ǥ��
			return;
		}
		if (key == OF_KEY_DOWN && (easy_mode || hard_mode)) {	// ���� �� �Ʒ��� ����Ű�� ������ ������
			directing = DOWN;	// �Ʒ��� ���ϰ� �ִٰ� ǥ��
			return;
		}

		if (key == ' ' && directing != -1 && available_power > 0) {	// �����̽� �ٸ� ������ ���� Ű����� ��� ���ϰ� ������, available_power�� 1 �̻��� ���
			switch (directing) {
			case LEFT:
				if (maze[minerY][minerX - 1] == '|') {	// ������ �ִ� �� ���� ���̸�
					maze[minerY][minerX - 1] = ' ';		// ���� �㹰��
					total_wall--;	// ���� ������ 1 ������ ��
					available_power--;	// available_power�� 1 �����Ѵ�
				}
				break;
			case RIGHT:
				if (maze[minerY][minerX + 1] == '|') {	// ������ �ִ� �� ���� ���̸�
					maze[minerY][minerX + 1] = ' ';		// ���� �㹰��
					total_wall--;	// ���� ������ 1 ������ ��
					available_power--;	// available_power�� 1 �����Ѵ�
				}
				break;
			case UP:
				if (maze[minerY - 1][minerX] == '-') {	// ���� �ִ� �� ���� ���̸�
					maze[minerY - 1][minerX] = ' ';		// ���� �㹰��
					total_wall--;	// ���� ������ 1 ������ ��
					available_power--;	// available_power�� 1 �����Ѵ�
				}
				break;
			case DOWN:
				if (maze[minerY + 1][minerX] == '-') {	// �Ʒ��� �ִ� �� ���� ���̸�
					maze[minerY + 1][minerX] = ' ';		// ���� �㹰��
					total_wall--;	// ���� ������ 1 ������ ��
					available_power--;	// available_power�� 1 �����Ѵ�
				}
				break;
			}

			if (total_wall == 0) {	// ���� �Ϸ� ����: ��� ���� �㹮 ���
				deinitializeGame();		// ���� �ʱ�ȭ
				deinitializeMaze();		// ���� �ʱ�ȭ
				screen_mode = RESULT;	// ��� ȭ������ ��ȯ
				easy_mode = false;
				hard_mode = false;
			}
		}

	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (!key_lock) {
		if (key == OF_KEY_LEFT && (easy_mode || hard_mode)) {	// ���� ����Ű�� ����
			directing = -1;		// �ƹ� ���⵵ ������ �ʰ� �ִٰ� ǥ���ϰ�
			if (maze[minerY][minerX - 1] == ' ') {	// ���� ���� �������� ������
				//minerX -= 2;	// �̵� �����ϸ� ĳ���͸� �̵�
				move_x = -(step / 10) - (2 * available_power);	// ���� �������� �����̵��ϱ� ���� miner�� x�� �̵� �Ÿ��� -(step / 10) - (2 * available_power)�� ����
				move_y = 0;		// y�� �̵� �Ÿ��� 0�� ��
				move_direction = LEFT;		// �������� �����̵��Ѵٴ� ǥ��, update()�� �˸�
				key_lock = true;	// �ٸ� Ű �Է��� ����
				sliding = true;		// �����̵� ������ ��Ÿ��
			}
			return;
		}

		if (key == OF_KEY_RIGHT && (easy_mode || hard_mode)) {	// ������ ����Ű�� ����
			directing = -1;		// �ƹ� ���⵵ ������ �ʰ� �ִٰ� ǥ���ϰ�
			if (maze[minerY][minerX + 1] == ' ') {	// ���� ���� �������� ������
				//minerX += 2;	// �̵� �����ϸ� ĳ���͸� �̵�
				move_x = (step / 10) + (2 * available_power);		// ���� �������� �����̵��ϱ� ���� miner�� x�� �̵� �Ÿ��� (step / 10) + (2 * available_power)�� ����
				move_y = 0;		// y�� �̵� �Ÿ��� 0�� ��
				move_direction = RIGHT;		// �������� �����̵��Ѵٴ� ǥ��, update()�� �˸�
				key_lock = true;	// �ٸ� Ű �Է��� ����
				sliding = true;		// �����̵� ������ ��Ÿ��
			}
			return;
		}

		if (key == OF_KEY_UP && (easy_mode || hard_mode)) {		// ���� ����Ű�� ����
			directing = -1;		// �ƹ� ���⵵ ������ �ʰ� �ִٰ� ǥ���ϰ�
			if (maze[minerY - 1][minerX] == ' ') {
				//minerY -= 2;	// �̵� �����ϸ� ĳ���͸� �̵�
				move_x = 0;		// x�� �̵� �Ÿ��� 0�� ��
				move_y = -(step / 10) - (2 * available_power);	// �� �������� �����̵��ϱ� ���� miner�� y�� �̵� �Ÿ��� -(step / 10) - (2 * available_power)�� ���� 
				move_direction = UP;	// ���� �����̵��Ѵٴ� ǥ��, update()�� �˸�
				key_lock = true;	// �ٸ� Ű �Է��� ����
				sliding = true;		// �����̵� ������ ��Ÿ��
			}
			return;
		}

		if (key == OF_KEY_DOWN && (easy_mode || hard_mode)) {	// �Ʒ��� ����Ű�� ����
			directing = -1;		// �ƹ� ���⵵ ������ �ʰ� �ִٰ� ǥ���ϰ�
			if (maze[minerY + 1][minerX] == ' ') {
				//minerY += 2;	// �̵� �����ϸ� ĳ���͸� �̵�
				move_x = 0;		// x�� �̵� �Ÿ��� 0�� ��
				move_y = (step / 10) + (2 * available_power);		// �Ʒ� �������� �����̵��ϱ� ���� miner�� y�� �̵� �Ÿ��� (step / 10) + (2 * available_power)�� ����
				move_direction = DOWN;	// �Ʒ��� �����̵��Ѵٴ� ǥ��, update()�� �˸�
				key_lock = true;	// �ٸ� Ű �Է��� ����
				sliding = true;		// �����̵� ������ ��Ÿ��
			}
			return;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::initializeMaze(int game_mode) {
	
	if (game_mode == EASY_MODE) {
		HEIGHT = 5;		// �̷��� ����(�� ����) ����
		WIDTH = 5;		// �̷��� �ʺ�(�� ����) ����

		maze_row = HEIGHT * 2 + 1;	// maze ������ �� ���� ����
		maze_col = WIDTH * 2 + 1;	// maze ������ �� ���� ����

		maze.resize(maze_row, vector<char>(maze_col, '+'));		// �̷��� ��� ���Ҹ� �𼭸�('+')�� �ʱ�ȭ
		
		/* �ܺ��� �μ� �� �����Ƿ� '+'�� ����, �ܺ��� ������ ���Ҹ� ��(' '), ���� ��('-'), ���� ��('|')���� �ʱ�ȭ */
		for (int r = 1; r < maze_row - 1; r++) {	// �ܺ��� �� �ε����� 0 �Ǵ� maze_row - 1�̹Ƿ� �̸� �����ϰ� �ݺ�
			for (int c = 1; c < maze_col - 1; c++) {	// �ܺ��� �� �ε����� 0 �Ǵ� maze_col - 1�̹Ƿ� �̸� �����ϰ� �ݺ�
				if (r % 2 != 0 && c % 2 != 0) maze[r][c] = ' '; // ��(' ') ����
				else if (r % 2 != 0 && c % 2 == 0) {
					maze[r][c] = '|';    // ���� ��('|') ����
					total_wall++;	// �̷� ���� �� ������ 1 ����
				}

				else if (r % 2 == 0 && c % 2 != 0) {
					maze[r][c] = '-';    // ���� ��('-') ����
					total_wall++;	// �̷� ���� �� ������ 1 ����
				}
			}
		}

		visited.resize(maze_row, vector< bool >(maze_col, false));	// �湮 ���θ� ��Ÿ���� 2���� ���� �ʱ�ȭ
		createMaze(1, 1);	// ��������� ���� �̷� ����

		return;
	}

	if (game_mode == HARD_MODE) {
		HEIGHT = 10;	// �̷��� ����(�� ����) ����
		WIDTH = 10;		// �̷��� �ʺ�(�� ����) ����

		maze_row = HEIGHT * 2 + 1;	// maze ������ �� ���� ����
		maze_col = WIDTH * 2 + 1;	// maze ������ �� ���� ����

		maze.resize(maze_row, vector<char>(maze_col, '+'));		// �̷��� ��� ���Ҹ� �𼭸�('+')�� �ʱ�ȭ

		/* �ܺ��� �μ� �� �����Ƿ� '+'�� ����, �ܺ��� ������ ���Ҹ� ��(' '), ���� ��('-'), ���� ��('|')���� �ʱ�ȭ */
		for (int r = 1; r < maze_row - 1; r++) {	// �ܺ��� �� �ε����� 0 �Ǵ� maze_row - 1�̹Ƿ� �̸� �����ϰ� �ݺ�
			for (int c = 1; c < maze_col - 1; c++) {	// �ܺ��� �� �ε����� 0 �Ǵ� maze_col - 1�̹Ƿ� �̸� �����ϰ� �ݺ�
				if (r % 2 != 0 && c % 2 != 0) maze[r][c] = ' '; // ��(' ') ����

				else if (r % 2 != 0 && c % 2 == 0) {
					maze[r][c] = '|';    // ���� ��('|') ����
					total_wall++;	// �̷� ���� �� ������ 1 ����
				}
				
				else if (r % 2 == 0 && c % 2 != 0) {
					maze[r][c] = '-';    // ���� ��('-') ����
					total_wall++;	// �̷� ���� �� ������ 1 ����
				}
			}
		}

		visited.resize(maze_row, vector< bool >(maze_col, false));	// �湮 ���θ� ��Ÿ���� 2���� ���� �ʱ�ȭ
		createMaze(1, 1);	// ��������� ���� �̷� ����
		return;
	}
}

void ofApp::createMaze(int row, int col) {

	visited[row][col] = true;	// �̹� ��尡 �湮�Ǿ����� ǥ��

	int direction[4] = { UP, DOWN, LEFT, RIGHT };   // 0: ��, 1: ��, 2: ��, 3: �� | ���� �̷� ������ ���� createMaze() �Լ����� ���� ���� ����
	random_shuffle(direction, direction + 4);	// ������ �湮�� ������ ���� �������� ����

	for (int option = 0; option < 4; ++option) {	// direction�� �ε���

		switch (direction[option]) {	// direction�� ���Ҹ� ������� ����

		case UP:	// �� ��������
			if (row - 2 >= 0 && !visited[row - 2][col]) {	// ���� �������� �Ǵ��ϰ�
				maze[row - 1][col] = ' ';	// ���� ���� ��
				total_wall--;	// ���� �� ������ 1 �����ϰ�
				createMaze(row - 2, col);	// ��������� ���� �濡 ���� �ٽ� �ѹ� �� ������ �����Ѵ�
			}
			break;

		case DOWN:	// �Ʒ� ��������
			if (row + 2 < maze_row && !visited[row + 2][col]) {	// ���� �������� �Ǵ��ϰ�
				maze[row + 1][col] = ' ';	// ���� ���� ��
				total_wall--;	// ���� �� ������ 1 �����ϰ�
				createMaze(row + 2, col);	// ��������� �Ʒ��� �濡 ���� �ٽ� �ѹ� �� ������ �����Ѵ�
			}
			break;

		case LEFT:	// ���� ��������
			if (col - 2 >= 0 && !visited[row][col - 2]) {	// ���� �������� �Ǵ��ϰ�
				maze[row][col - 1] = ' ';	// ���� ���� ��
				total_wall--;	// ���� �� ������ 1 �����ϰ�
				createMaze(row, col - 2);	// ��������� ���� �濡 ���� �ٽ� �ѹ� �� ������ �����Ѵ�
			}
			break;

		case RIGHT:	// ������ ��������
			if (col + 2 < maze_col && !visited[row][col + 2]) {	// ���� �������� �Ǵ��ϰ�
				maze[row][col + 1] = ' ';	// ���� ���� ��
				total_wall--;	// ���� �� ������ 1 �����ϰ�
				createMaze(row, col + 2);	// ��������� ������ �濡 ���� �ٽ� �ѹ� �� ������ �����Ѵ�
			}
			break;
		}

	}
}

void ofApp::deinitializeMaze() {
	maze.clear();	// maze�� �ʱ� ����(�� ����)�� �ǵ�����
	visited.clear();	// �湮 ���θ� ��Ÿ���� ���͸� �ʱ� ����(�� ����)�� �ǵ�����
	HEIGHT = 0;		// �̷ο� ���õ� ���� 0(NULL)���� ����
	WIDTH = 0;		// �̷ο� ���õ� ���� 0(NULL)���� ����
	maze_row = 0;	// �̷ο� ���õ� ���� 0(NULL)���� ����
	maze_col = 0;	// �̷ο� ���õ� ���� 0(NULL)���� ����
	total_wall = 0;		// �̷ο� ���õ� ���� 0(NULL)���� ����
}

void ofApp::drawGameScreen() {
	/* �̷��� �׵θ��� �׸��� */
	ofSetColor(ofColor::black);		// �� ������ ���������� ����
	ofSetLineWidth(10);				// �� ����� 10���� ����

	ofDrawLine(LEFT_X - MARGIN, TOP_Y, RIGHT_X + MARGIN, TOP_Y);			// ��� �׵θ�
	ofDrawLine(LEFT_X, TOP_Y - MARGIN, LEFT_X, BOTTOM_Y + MARGIN);		// ���� �׵θ�
	ofDrawLine(LEFT_X - MARGIN, BOTTOM_Y, RIGHT_X + MARGIN, BOTTOM_Y);	// �ϴ� �׵θ�
	ofDrawLine(RIGHT_X, TOP_Y - MARGIN, RIGHT_X, BOTTOM_Y + MARGIN);		// ���� �׵θ�

	/* �̷��� ������ �׸��� */
	step = MAZE_LENGTH / (maze_col - 1);	// �ſ� �߿��� ��: ȭ�� �󿡼� �̷ΰ� �׷����� �����ϴ� (LEFT_X, TOP_Y)�κ��� maze�� �� ���Ұ� �󸶳� ������ �ִ��� ��Ÿ����.
	// ex: maze[r][c]�� ȭ�� ���� ��ġ�� (LEFT_X + (step * c), TOP_Y + (step * r))
	// ex: �� ���� ���� 5���� �̷��� ���� 11���̰�, ���� �𼭸����� ������ �𼭸����� 10�� �ǳ� �پ�� �Ѵ�.

	for (int r = 0, penY = TOP_Y, penX = LEFT_X; r < maze_row - 1; r++, penX = LEFT_X, penY += step) {	// penX: ���� �׸� Ŀ���� ��ġ�ϴ� X ��ǥ, penY: ���� �׸� Ŀ���� ��ġ�ϴ� Y ��ǥ
		for (int c = 0; c < maze_col - 1; c++, penX += step) {
			if (maze[r][c] == '-') ofDrawLine(penX - step - MARGIN, penY, penX + step + MARGIN, penY);	// ���� �� �׸���
			if (maze[r][c] == '|') ofDrawLine(penX, penY - step - MARGIN, penX, penY + step + MARGIN);	// ���� �� �׸���
		}
	}

	/* ������ entities(character, item, available_power)�� �׸��� */
	ofSetColor(255);	// �̹����� �׸��� ���� ���� 255���� ����
	image_size = step + (4 * MARGIN);	// �׸� entity�� �̹��� �ʺ� �� ����
	
	item_image.draw(LEFT_X + (itemX * step) - (image_size / 2), TOP_Y + (itemY * step) - (image_size / 2), image_size, image_size);		// �������� �׸���
	if (!sliding) {		// ĳ���Ͱ� �����̵� ���� �ƴϸ�
		miner_image.draw(LEFT_X + (minerX * step) - (image_size / 2), TOP_Y + (minerY * step) - (image_size / 2), image_size, image_size);	// ĳ���͸� ��ǥ�� ��� �׸���
	}
	else {		// ĳ���Ͱ� �����̵� ���̸�
		miner_image.draw(LEFT_X + (minerX * step) - (image_size / 2) + move_x, TOP_Y + (minerY * step) - (image_size / 2) + move_y, image_size, image_size);	// ĳ���͸� ���� ��ǥ�� move_x, move_y�� �߰��� �߰� ������ �׸���
	}
	ofSetColor(ofColor::red);
	remain_power_font.drawString("POWER: " + ofToString(available_power), RIGHT_X + 15, BOTTOM_Y - 15);		// �ǽð����� available_power�� ���� ����Ѵ�

	if (directing == -1) return;
	else if (directing == LEFT) ofDrawArrow(ofVec3f(LEFT_X + (minerX * step), TOP_Y + (minerY * step)), ofVec3f(LEFT_X + (minerX * step) - (MARGIN * 10), TOP_Y + (minerY * step)), 10);	// ĳ���Ͱ� ���ϰ� �ִ� �������� ȭ��ǥ�� �׸���
	else if (directing == RIGHT) ofDrawArrow(ofVec3f(LEFT_X + (minerX * step), TOP_Y + (minerY * step)), ofVec3f(LEFT_X + (minerX * step) + (MARGIN * 10), TOP_Y + (minerY * step)), 10);	// ĳ���Ͱ� ���ϰ� �ִ� �������� ȭ��ǥ�� �׸���
	else if (directing == UP) ofDrawArrow(ofVec3f(LEFT_X + (minerX * step), TOP_Y + (minerY * step)), ofVec3f(LEFT_X + (minerX * step), TOP_Y + (minerY * step) - (MARGIN * 10)), 10);		// ĳ���Ͱ� ���ϰ� �ִ� �������� ȭ��ǥ�� �׸���
	else if (directing == DOWN) ofDrawArrow(ofVec3f(LEFT_X + (minerX * step), TOP_Y + (minerY * step)), ofVec3f(LEFT_X + (minerX * step), TOP_Y + (minerY * step) + (MARGIN * 10)), 10);	// ĳ���Ͱ� ���ϰ� �ִ� �������� ȭ��ǥ�� �׸���
}

void ofApp::initializeGame() {
	available_power = 0;	// ���� �μ� �� �ִ� Ƚ�� 0���� �ʱ�ȭ
	total_energy = 0;		// ������� ȹ���� ������ ���� 0���� �ʱ�ȭ
	minerX = minerY = 1;	// ĳ������ �ʱ� ��ġ�� (1, 1)�� ����
	
	do {	// �̷��� �� ��ġ�� �ְ� ĳ������ ��ġ�� ��ġ�� �ʴ� ��ǥ ����
		itemY = rand() % maze_row;	// �������� �� ��ġ ����
		itemX = rand() % maze_col;	// �������� �� ��ġ ����
	} while (itemY % 2 == 0 ||	// 2�� ������ �������� ��ġ�� ���� ����
			 itemX % 2 == 0 ||	// 2�� ������ �������� ��ġ�� ���� ����
			(itemY == minerY && itemX == minerX));	// ĳ���Ϳ� ������ ��ġ�� ��ĥ �� ����
}

void ofApp::deinitializeGame() {
	available_power = 0;	// ���� �μ� �� �ִ� Ƚ�� 0���� �ʱ�ȭ
	total_energy = 0;		// ������� ȹ���� ������ ���� 0���� �ʱ�ȭ
	minerX = minerY = 1;	// ĳ������ �ʱ� ��ġ�� �ʱ�ȭ
	easy_mode = hard_mode = false;	// ���� ��� �ʱ�ȭ
}