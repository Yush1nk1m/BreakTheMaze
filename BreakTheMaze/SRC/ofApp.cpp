#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	srand(time(0));		// 랜덤 미로 생성을 위해 시드 값 설정

	ofSetVerticalSync(true);	// 수직 동기화로 모니터 주사율에 맞추어 초당 출력 프레임 설정
	ofBackground(ofColor::white);	// 배경 흰색으로 설정

	/* 폰트 출처 : https://maplestory.nexon.com/Media/Font */
	gamename_font.load("MaplestoryBold.ttf", 50);		// 게임 이름을 쓰기 위한 폰트 크기 50으로 설정
	gamemode_font.load("MaplestoryBold.ttf", 20);		// 게임 모드를 쓰기 위한 폰트 크기 30으로 설정
	remain_power_font.load("MaplestoryBold.ttf", 15);	// available_power를 나타내기 위한 폰트 크기 15로 설정
	result_font.load("MaplestoryBold.ttf", 75);			// 결과 화면에 쓰기 위한 폰트 크기 75로 설정
	result_font2.load("MaplestoryBold.ttf", 30);		// 결과 화면에 쓰기 위한 폰트 크기 60으로 설정

	gamename_string = "Break the Maze";									// 화면에 출력할 게임 이름 문자열
	gamemode_string = "1. EASY MODE(5 X 5)	2. HARD MODE(10 X 10)	Q. EXIT";	// 화면에 출력할 게임 모드 문자열

	result_string = "GAME COMPLETED";	// 결과 화면 상단에 출력할 게임 완료 문자열
	resultX = result_font.stringWidth(result_string);
	resultX = (ofGetWidth() - resultX) / 2;	// 텍스트를 화면 중앙에 정렬하기 위한 계산

	result_string2 = "Press 'q' or 'Q' to return to the main screen";	// 결과 화면에 출력할 안내 문자열
	resultX2 = result_font2.stringWidth(result_string2);
	resultX2 = (ofGetWidth() - resultX2) / 2;	// 텍스트를 화면 중앙에 정렬하기 위한 계산

	gamenameX = gamename_font.stringWidth(gamename_string);
	gamenameX = (ofGetWidth() - gamenameX) / 2;		// 텍스트를 화면 중앙에 정렬하기 위한 계산

	gamemodeX = gamemode_font.stringWidth(gamemode_string);
	gamemodeX = (ofGetWidth() - gamemodeX) / 2;		// 텍스트를 화면 중앙에 정렬하기 위한 계산

	main_image.load("images/main.png");		// 메인 이미지 로드
	miner_image.load("images/miner.png");	// 캐릭터 이미지 로드
	item_image.load("images/item.png");		// 아이템 이미지 로드
	
	happycat.load("images/happycat.gif");	// 해피캣 이미지 로드
}

//--------------------------------------------------------------
void ofApp::update(){
	if (screen_mode == RESULT && ofGetElapsedTimeMillis() % 3) {
		happycatFrame++;
		if (happycatFrame > happycat.pages.size() - 1) happycatFrame = 0;
	}

	if (sliding && (easy_mode || hard_mode)) {

		if (move_direction == LEFT) {	// 왼쪽으로 슬라이딩 중인 경우
			move_x -= (step / 10) + (2 * available_power);	// miner를 왼쪽으로 (step / 10) + (2 * available_power) 픽셀 슬라이딩함
			if (LEFT_X + (minerX * step) + move_x <= LEFT_X + ((minerX - 2) * step)) {	// (현재 실제 위치) + move_x <= (미래의 위치)
				key_lock = false;		// 키 잠금 해제
				move_direction = -1;	// 슬라이딩 방향 초기화
				minerX -= 2;			// miner의 좌표 실제로 이동
				move_x = 0;				// move_x 초기화
				sliding = false;		// sliding 초기화
			}
		}
		else if (move_direction == RIGHT) {	// 오른쪽으로 슬라이딩 중인 경우
			move_x += (step / 10) + (2 * available_power);	// miner를 오른쪽으로 (step / 10) + (2 * available_power)픽셀 슬라이딩함
			if (LEFT_X + (minerX * step) + move_x >= LEFT_X + ((minerX + 2) * step)) {	// (현재 실제 위치) + move_x >= (미래의 위치)
				key_lock = false;		// 키 잠금 해제
				move_direction = -1;	// 슬라이딩 방향 초기화
				minerX += 2;			// miner의 좌표 실제로 이동
				move_x = 0;				// move_x 초기화
				sliding = false;		// sliding 초기화
			}
		}
		else if (move_direction == UP) {	// 위로 슬라이딩 중인 경우
			move_y -= (step / 10) + (2 * available_power);
			if (TOP_Y + (minerY * step) + move_y <= TOP_Y + ((minerY - 2) * step)) {	// (현재 실제 위치) + move_y <= (미래의 위치)
				key_lock = false;		// 키 잠금 해제
				move_direction = -1;	// 슬라이딩 방향 초기화
				minerY -= 2;			// miner의 좌표 실제로 이동
				move_y = 0;				// move_y 초기화
				sliding = false;		// sliding 초기화
			}
		}
		else if (move_direction == DOWN) {
			move_y += (step / 10) + (2 * available_power);
			if (TOP_Y + (minerY * step) + move_y >= TOP_Y + ((minerY + 2) * step)) {	// (현재 실제 위치) + move_y >= (미래의 위치)
				key_lock = false;		// 키 잠금 해제
				move_direction = -1;	// 슬라이딩 방향 초기화
				minerY += 2;			// miner의 좌표 실제로 이동
				move_y = 0;				// move_y 초기화
				sliding = false;		// sliding 초기화
			}
		}

		if (!sliding) {	// 위 조건문을 통과한 후 sliding이 false가 되었다면 위치의 갱신이 이루어진 것이다
			if (minerX == itemX && minerY == itemY) {	// 캐릭터가 아이템을 획득하면
				total_energy++;		// 현재까지 획득한 에너지 개수 1 증가
				available_power++;	// 현재 갖고 있는 벽 부수기 횟수 1 증가
				
				do {	// 랜덤한 위치에 아이템 다시 생성
					itemY = rand() % maze_row;	// 아이템의 행 위치 생성
					itemX = rand() % maze_col;	// 아이템의 열 위치 생성
				} while (itemY % 2 == 0 ||	// 2로 나누어 떨어지는 위치엔 벽이 있음
					itemX % 2 == 0 ||	// 2로 나누어 떨어지는 위치엔 벽이 있음
					(itemY == minerY && itemX == minerX));	// 캐릭터와 완전히 위치가 겹칠 수 없음
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(ofColor::darkGray);	// 화면 테두리 색깔
	ofDrawRectangle(0, 0, 1024, 50);	// 화면 상단 테두리
	ofDrawRectangle(0, 0, 50, 768);	// 화면 좌측 테두리
	ofDrawRectangle(0, 718, 1024, 50);	// 화면 하단 테두리
	ofDrawRectangle(974, 0, 50, 768);	// 화면 우측 테두리


	if (screen_mode == MAIN) {	// 메인 화면 그리기
		ofSetColor(255);	// 이미지 출력을 위한 색 설정
		/* 메인 화면 이미지 출력 */
		main_image.draw(50, 90, 924, 588);

		ofSetColor(ofColor::black);	// 문자열은 검정색으로 출력

		/* 게임 이름 문자열 출력 */
		gamename_font.drawString(gamename_string, gamenameX, 105);	// 화면 중앙에 정렬하여 게임 이름 출력
		
		/* 게임 모드 문자열 출력 */
		gamemode_font.drawString(gamemode_string, gamemodeX, 710);	// 화면 중앙에 정렬하여 게임 모드 출력

	}
	else if (screen_mode == EASY_MODE || screen_mode == HARD_MODE) {		// 이지 모드 또는 하드 모드일 시
		drawGameScreen();		// 게임 플레이 화면을 그린다
	}
	else if (screen_mode == RESULT) {
		ofSetColor(ofColor::lightGoldenRodYellow);	// 화면 테두리 색깔
		ofDrawRectangle(0, 0, 1024, 50);	// 화면 상단 테두리
		ofDrawRectangle(0, 0, 50, 768);	// 화면 좌측 테두리
		ofDrawRectangle(0, 718, 1024, 50);	// 화면 하단 테두리
		ofDrawRectangle(974, 0, 50, 768);	// 화면 우측 테두리
		
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

		if (key == 'q' || key == 'Q') {	// q/Q 입력을 받으면
			switch (screen_mode) {		// 현재 스크린 상태에 따라 다르게 처리한다
			case MAIN:	// 메인 화면이면
				ofExit();		// 게임 종료
			case EASY_MODE:	// 게임 플레이 화면이면
				deinitializeMaze();		// 미로와 관련된 정보 제거
				deinitializeGame();		// 게임과 관련된 정보 제거
				screen_mode = MAIN;		// 메인 화면으로 변경
				easy_mode = false;		// 이지 모드임을 나타내는 플래그 비활성화
				break;
			case HARD_MODE:	// 게임 플레이 화면이면
				deinitializeMaze();		// 미로와 관련된 정보 제거
				deinitializeGame();		// 게임과 관련된 정보 제거
				screen_mode = MAIN;		// 메인 화면으로 변경
				hard_mode = false;		// 하드 모드임을 나타내는 플래그 비활성화
				break;
			case RESULT:	// 결과 화면이면
				screen_mode = MAIN;		// 메인 화면으로 변경
				break;
			}

			return;
		}

		if (key == '1' && screen_mode == MAIN) {	// '1'을 누르면 이지 모드로 게임 시작
			initializeMaze(EASY_MODE);	// 미로 정보 초기화
			initializeGame();	// 게임과 관련된 정보 초기화
			easy_mode = true;	// 이지 모드임을 나타내는 플래그 활성화
			screen_mode = EASY_MODE;	// 스크린을 이지 모드로 변경

			return;

		}

		if (key == '2' && screen_mode == MAIN) {
			initializeMaze(HARD_MODE);
			initializeGame();	// 게임과 관련된 정보 초기화
			hard_mode = true;	// 하드 모드임을 나타내는 플래그 활성화
			screen_mode = HARD_MODE;	// 스크린을 하드 모드로 변경

			return;
		}

		if (key == OF_KEY_LEFT && (easy_mode || hard_mode)) {	// 게임 중 왼쪽 방향키를 누르고 있으면
			directing = LEFT;	// 왼쪽을 향하고 있다고 표시
			return;
		}
		if (key == OF_KEY_RIGHT && (easy_mode || hard_mode)) {	// 게임 중 오른쪽 방향키를 누르고 있으면
			directing = RIGHT;	// 오른쪽을 향하고 있다고 표시
			return;
		}
		if (key == OF_KEY_UP && (easy_mode || hard_mode)) {		// 게임 중 위쪽 방향키를 누르고 있으면
			directing = UP;		// 위를 향하고 있다고 표시
			return;
		}
		if (key == OF_KEY_DOWN && (easy_mode || hard_mode)) {	// 게임 중 아래쪽 방향키를 누르고 있으면
			directing = DOWN;	// 아래를 향하고 있다고 표시
			return;
		}

		if (key == ' ' && directing != -1 && available_power > 0) {	// 스페이스 바를 누르는 순간 키보드로 어딘가 향하고 있으며, available_power가 1 이상인 경우
			switch (directing) {
			case LEFT:
				if (maze[minerY][minerX - 1] == '|') {	// 좌측에 있는 게 세로 벽이면
					maze[minerY][minerX - 1] = ' ';		// 벽을 허물고
					total_wall--;	// 벽의 개수를 1 감소한 후
					available_power--;	// available_power를 1 감소한다
				}
				break;
			case RIGHT:
				if (maze[minerY][minerX + 1] == '|') {	// 우측에 있는 게 세로 벽이면
					maze[minerY][minerX + 1] = ' ';		// 벽을 허물고
					total_wall--;	// 벽의 개수를 1 감소한 후
					available_power--;	// available_power를 1 감소한다
				}
				break;
			case UP:
				if (maze[minerY - 1][minerX] == '-') {	// 위에 있는 게 가로 벽이면
					maze[minerY - 1][minerX] = ' ';		// 벽을 허물고
					total_wall--;	// 벽의 개수를 1 감소한 후
					available_power--;	// available_power를 1 감소한다
				}
				break;
			case DOWN:
				if (maze[minerY + 1][minerX] == '-') {	// 아래에 있는 게 세로 벽이면
					maze[minerY + 1][minerX] = ' ';		// 벽을 허물고
					total_wall--;	// 벽의 개수를 1 감소한 후
					available_power--;	// available_power를 1 감소한다
				}
				break;
			}

			if (total_wall == 0) {	// 게임 완료 조건: 모든 벽을 허문 경우
				deinitializeGame();		// 정보 초기화
				deinitializeMaze();		// 정보 초기화
				screen_mode = RESULT;	// 결과 화면으로 전환
				easy_mode = false;
				hard_mode = false;
			}
		}

	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (!key_lock) {
		if (key == OF_KEY_LEFT && (easy_mode || hard_mode)) {	// 왼쪽 방향키를 떼면
			directing = -1;		// 아무 방향도 향하지 않고 있다고 표시하고
			if (maze[minerY][minerX - 1] == ' ') {	// 만약 벽이 존재하지 않으면
				//minerX -= 2;	// 이동 가능하면 캐릭터를 이동
				move_x = -(step / 10) - (2 * available_power);	// 좌측 방향으로 슬라이딩하기 위해 miner의 x축 이동 거리를 -(step / 10) - (2 * available_power)로 설정
				move_y = 0;		// y축 이동 거리는 0이 됨
				move_direction = LEFT;		// 좌측으로 슬라이딩한다는 표시, update()에 알림
				key_lock = true;	// 다른 키 입력을 무시
				sliding = true;		// 슬라이딩 중임을 나타냄
			}
			return;
		}

		if (key == OF_KEY_RIGHT && (easy_mode || hard_mode)) {	// 오른쪽 방향키를 떼면
			directing = -1;		// 아무 방향도 향하지 않고 있다고 표시하고
			if (maze[minerY][minerX + 1] == ' ') {	// 만약 벽이 존재하지 않으면
				//minerX += 2;	// 이동 가능하면 캐릭터를 이동
				move_x = (step / 10) + (2 * available_power);		// 우측 방향으로 슬라이딩하기 위해 miner의 x축 이동 거리를 (step / 10) + (2 * available_power)로 설정
				move_y = 0;		// y축 이동 거리는 0이 됨
				move_direction = RIGHT;		// 우측으로 슬라이딩한다는 표시, update()에 알림
				key_lock = true;	// 다른 키 입력을 무시
				sliding = true;		// 슬라이딩 중임을 나타냄
			}
			return;
		}

		if (key == OF_KEY_UP && (easy_mode || hard_mode)) {		// 위쪽 방향키를 떼면
			directing = -1;		// 아무 방향도 향하지 않고 있다고 표시하고
			if (maze[minerY - 1][minerX] == ' ') {
				//minerY -= 2;	// 이동 가능하면 캐릭터를 이동
				move_x = 0;		// x축 이동 거리는 0이 됨
				move_y = -(step / 10) - (2 * available_power);	// 위 방향으로 슬라이딩하기 위해 miner의 y축 이동 거리를 -(step / 10) - (2 * available_power)로 설정 
				move_direction = UP;	// 위로 슬라이딩한다는 표시, update()에 알림
				key_lock = true;	// 다른 키 입력을 무시
				sliding = true;		// 슬라이딩 중임을 나타냄
			}
			return;
		}

		if (key == OF_KEY_DOWN && (easy_mode || hard_mode)) {	// 아래쪽 방향키를 떼면
			directing = -1;		// 아무 방향도 향하지 않고 있다고 표시하고
			if (maze[minerY + 1][minerX] == ' ') {
				//minerY += 2;	// 이동 가능하면 캐릭터를 이동
				move_x = 0;		// x축 이동 거리는 0이 됨
				move_y = (step / 10) + (2 * available_power);		// 아래 방향으로 슬라이딩하기 위해 miner의 y축 이동 거리를 (step / 10) + (2 * available_power)로 설정
				move_direction = DOWN;	// 아래로 슬라이딩한다는 표시, update()에 알림
				key_lock = true;	// 다른 키 입력을 무시
				sliding = true;		// 슬라이딩 중임을 나타냄
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
		HEIGHT = 5;		// 미로의 높이(방 개수) 설정
		WIDTH = 5;		// 미로의 너비(방 개수) 설정

		maze_row = HEIGHT * 2 + 1;	// maze 벡터의 행 개수 유도
		maze_col = WIDTH * 2 + 1;	// maze 벡터의 열 개수 유도

		maze.resize(maze_row, vector<char>(maze_col, '+'));		// 미로의 모든 원소를 모서리('+')로 초기화
		
		/* 외벽은 부술 수 없으므로 '+'로 유지, 외벽을 제외한 원소를 방(' '), 가로 벽('-'), 세로 벽('|')으로 초기화 */
		for (int r = 1; r < maze_row - 1; r++) {	// 외벽의 행 인덱스는 0 또는 maze_row - 1이므로 이를 제외하고 반복
			for (int c = 1; c < maze_col - 1; c++) {	// 외벽의 열 인덱스는 0 또는 maze_col - 1이므로 이를 제외하고 반복
				if (r % 2 != 0 && c % 2 != 0) maze[r][c] = ' '; // 방(' ') 조건
				else if (r % 2 != 0 && c % 2 == 0) {
					maze[r][c] = '|';    // 세로 벽('|') 조건
					total_wall++;	// 미로 내의 벽 개수를 1 증가
				}

				else if (r % 2 == 0 && c % 2 != 0) {
					maze[r][c] = '-';    // 가로 벽('-') 조건
					total_wall++;	// 미로 내의 벽 개수를 1 증가
				}
			}
		}

		visited.resize(maze_row, vector< bool >(maze_col, false));	// 방문 여부를 나타내는 2차원 벡터 초기화
		createMaze(1, 1);	// 재귀적으로 완전 미로 구성

		return;
	}

	if (game_mode == HARD_MODE) {
		HEIGHT = 10;	// 미로의 높이(방 개수) 설정
		WIDTH = 10;		// 미로의 너비(방 개수) 설정

		maze_row = HEIGHT * 2 + 1;	// maze 벡터의 행 개수 유도
		maze_col = WIDTH * 2 + 1;	// maze 벡터의 열 개수 유도

		maze.resize(maze_row, vector<char>(maze_col, '+'));		// 미로의 모든 원소를 모서리('+')로 초기화

		/* 외벽은 부술 수 없으므로 '+'로 유지, 외벽을 제외한 원소를 방(' '), 가로 벽('-'), 세로 벽('|')으로 초기화 */
		for (int r = 1; r < maze_row - 1; r++) {	// 외벽의 행 인덱스는 0 또는 maze_row - 1이므로 이를 제외하고 반복
			for (int c = 1; c < maze_col - 1; c++) {	// 외벽의 열 인덱스는 0 또는 maze_col - 1이므로 이를 제외하고 반복
				if (r % 2 != 0 && c % 2 != 0) maze[r][c] = ' '; // 방(' ') 조건

				else if (r % 2 != 0 && c % 2 == 0) {
					maze[r][c] = '|';    // 세로 벽('|') 조건
					total_wall++;	// 미로 내의 벽 개수를 1 증가
				}
				
				else if (r % 2 == 0 && c % 2 != 0) {
					maze[r][c] = '-';    // 가로 벽('-') 조건
					total_wall++;	// 미로 내의 벽 개수를 1 증가
				}
			}
		}

		visited.resize(maze_row, vector< bool >(maze_col, false));	// 방문 여부를 나타내는 2차원 벡터 초기화
		createMaze(1, 1);	// 재귀적으로 완전 미로 구성
		return;
	}
}

void ofApp::createMaze(int row, int col) {

	visited[row][col] = true;	// 이번 노드가 방문되었음을 표시

	int direction[4] = { UP, DOWN, LEFT, RIGHT };   // 0: 상, 1: 하, 2: 좌, 3: 우 | 랜덤 미로 생성을 위한 createMaze() 함수에서 사용될 방향 정보
	random_shuffle(direction, direction + 4);	// 다음에 방문할 방향의 순서 무작위로 섞기

	for (int option = 0; option < 4; ++option) {	// direction의 인덱스

		switch (direction[option]) {	// direction의 원소를 순서대로 본다

		case UP:	// 위 방향으로
			if (row - 2 >= 0 && !visited[row - 2][col]) {	// 접근 가능한지 판단하고
				maze[row - 1][col] = ' ';	// 벽을 없앤 후
				total_wall--;	// 벽의 총 개수를 1 감소하고
				createMaze(row - 2, col);	// 재귀적으로 위쪽 방에 대해 다시 한번 이 과정을 수행한다
			}
			break;

		case DOWN:	// 아래 방향으로
			if (row + 2 < maze_row && !visited[row + 2][col]) {	// 접근 가능한지 판단하고
				maze[row + 1][col] = ' ';	// 벽을 없앤 후
				total_wall--;	// 벽의 총 개수를 1 감소하고
				createMaze(row + 2, col);	// 재귀적으로 아래쪽 방에 대해 다시 한번 이 과정을 수행한다
			}
			break;

		case LEFT:	// 왼쪽 방향으로
			if (col - 2 >= 0 && !visited[row][col - 2]) {	// 접근 가능한지 판단하고
				maze[row][col - 1] = ' ';	// 벽을 없앤 후
				total_wall--;	// 벽의 총 개수를 1 감소하고
				createMaze(row, col - 2);	// 재귀적으로 왼쪽 방에 대해 다시 한번 이 과정을 수행한다
			}
			break;

		case RIGHT:	// 오른쪽 방향으로
			if (col + 2 < maze_col && !visited[row][col + 2]) {	// 접근 가능한지 판단하고
				maze[row][col + 1] = ' ';	// 벽을 없앤 후
				total_wall--;	// 벽의 총 개수를 1 감소하고
				createMaze(row, col + 2);	// 재귀적으로 오른쪽 방에 대해 다시 한번 이 과정을 수행한다
			}
			break;
		}

	}
}

void ofApp::deinitializeMaze() {
	maze.clear();	// maze를 초기 상태(빈 벡터)로 되돌리기
	visited.clear();	// 방문 여부를 나타내는 벡터를 초기 상태(빈 벡터)로 되돌리기
	HEIGHT = 0;		// 미로와 관련된 변수 0(NULL)으로 설정
	WIDTH = 0;		// 미로와 관련된 변수 0(NULL)으로 설정
	maze_row = 0;	// 미로와 관련된 변수 0(NULL)으로 설정
	maze_col = 0;	// 미로와 관련된 변수 0(NULL)으로 설정
	total_wall = 0;		// 미로와 관련된 변수 0(NULL)으로 설정
}

void ofApp::drawGameScreen() {
	/* 미로의 테두리를 그린다 */
	ofSetColor(ofColor::black);		// 선 색깔은 검정색으로 설정
	ofSetLineWidth(10);				// 선 굵기는 10으로 설정

	ofDrawLine(LEFT_X - MARGIN, TOP_Y, RIGHT_X + MARGIN, TOP_Y);			// 상단 테두리
	ofDrawLine(LEFT_X, TOP_Y - MARGIN, LEFT_X, BOTTOM_Y + MARGIN);		// 좌측 테두리
	ofDrawLine(LEFT_X - MARGIN, BOTTOM_Y, RIGHT_X + MARGIN, BOTTOM_Y);	// 하단 테두리
	ofDrawLine(RIGHT_X, TOP_Y - MARGIN, RIGHT_X, BOTTOM_Y + MARGIN);		// 우측 테두리

	/* 미로의 벽들을 그린다 */
	step = MAZE_LENGTH / (maze_col - 1);	// 매우 중요한 값: 화면 상에서 미로가 그려지기 시작하는 (LEFT_X, TOP_Y)로부터 maze의 각 원소가 얼마나 떨어져 있는지 나타낸다.
	// ex: maze[r][c]의 화면 상의 위치는 (LEFT_X + (step * c), TOP_Y + (step * r))
	// ex: 한 행의 방이 5개면 미로의 열은 11개이고, 왼쪽 모서리에서 오른쪽 모서리까지 10번 건너 뛰어야 한다.

	for (int r = 0, penY = TOP_Y, penX = LEFT_X; r < maze_row - 1; r++, penX = LEFT_X, penY += step) {	// penX: 선을 그릴 커서가 위치하는 X 좌표, penY: 선을 그릴 커서가 위치하는 Y 좌표
		for (int c = 0; c < maze_col - 1; c++, penX += step) {
			if (maze[r][c] == '-') ofDrawLine(penX - step - MARGIN, penY, penX + step + MARGIN, penY);	// 가로 벽 그리기
			if (maze[r][c] == '|') ofDrawLine(penX, penY - step - MARGIN, penX, penY + step + MARGIN);	// 세로 벽 그리기
		}
	}

	/* 게임의 entities(character, item, available_power)을 그린다 */
	ofSetColor(255);	// 이미지를 그리기 위해 색을 255으로 설정
	image_size = step + (4 * MARGIN);	// 그릴 entity의 이미지 너비 및 높이
	
	item_image.draw(LEFT_X + (itemX * step) - (image_size / 2), TOP_Y + (itemY * step) - (image_size / 2), image_size, image_size);		// 아이템을 그린다
	if (!sliding) {		// 캐릭터가 슬라이딩 중이 아니면
		miner_image.draw(LEFT_X + (minerX * step) - (image_size / 2), TOP_Y + (minerY * step) - (image_size / 2), image_size, image_size);	// 캐릭터를 좌표에 즉시 그린다
	}
	else {		// 캐릭터가 슬라이딩 중이면
		miner_image.draw(LEFT_X + (minerX * step) - (image_size / 2) + move_x, TOP_Y + (minerY * step) - (image_size / 2) + move_y, image_size, image_size);	// 캐릭터를 이전 좌표에 move_x, move_y를 추가한 중간 지점에 그린다
	}
	ofSetColor(ofColor::red);
	remain_power_font.drawString("POWER: " + ofToString(available_power), RIGHT_X + 15, BOTTOM_Y - 15);		// 실시간으로 available_power의 값을 출력한다

	if (directing == -1) return;
	else if (directing == LEFT) ofDrawArrow(ofVec3f(LEFT_X + (minerX * step), TOP_Y + (minerY * step)), ofVec3f(LEFT_X + (minerX * step) - (MARGIN * 10), TOP_Y + (minerY * step)), 10);	// 캐릭터가 향하고 있는 방향으로 화살표를 그린다
	else if (directing == RIGHT) ofDrawArrow(ofVec3f(LEFT_X + (minerX * step), TOP_Y + (minerY * step)), ofVec3f(LEFT_X + (minerX * step) + (MARGIN * 10), TOP_Y + (minerY * step)), 10);	// 캐릭터가 향하고 있는 방향으로 화살표를 그린다
	else if (directing == UP) ofDrawArrow(ofVec3f(LEFT_X + (minerX * step), TOP_Y + (minerY * step)), ofVec3f(LEFT_X + (minerX * step), TOP_Y + (minerY * step) - (MARGIN * 10)), 10);		// 캐릭터가 향하고 있는 방향으로 화살표를 그린다
	else if (directing == DOWN) ofDrawArrow(ofVec3f(LEFT_X + (minerX * step), TOP_Y + (minerY * step)), ofVec3f(LEFT_X + (minerX * step), TOP_Y + (minerY * step) + (MARGIN * 10)), 10);	// 캐릭터가 향하고 있는 방향으로 화살표를 그린다
}

void ofApp::initializeGame() {
	available_power = 0;	// 벽을 부술 수 있는 횟수 0으로 초기화
	total_energy = 0;		// 현재까지 획득한 에너지 개수 0으로 초기화
	minerX = minerY = 1;	// 캐릭터의 초기 위치를 (1, 1)로 고정
	
	do {	// 미로의 방 위치에 있고 캐릭터의 위치와 겹치지 않는 좌표 생성
		itemY = rand() % maze_row;	// 아이템의 행 위치 생성
		itemX = rand() % maze_col;	// 아이템의 열 위치 생성
	} while (itemY % 2 == 0 ||	// 2로 나누어 떨어지는 위치엔 벽이 있음
			 itemX % 2 == 0 ||	// 2로 나누어 떨어지는 위치엔 벽이 있음
			(itemY == minerY && itemX == minerX));	// 캐릭터와 완전히 위치가 겹칠 수 없음
}

void ofApp::deinitializeGame() {
	available_power = 0;	// 벽을 부술 수 있는 횟수 0으로 초기화
	total_energy = 0;		// 현재까지 획득한 에너지 개수 0으로 초기화
	minerX = minerY = 1;	// 캐릭터의 초기 위치로 초기화
	easy_mode = hard_mode = false;	// 게임 모드 초기화
}