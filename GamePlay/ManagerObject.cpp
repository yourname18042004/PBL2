#include "ManagerObject.h"
#include "LoadMusic.h"
LoadMusic Sound1;

void Manager::Add(Fly a) {
	obJect.push_back(a);
	(obJect.end() - 1)->setPosition(Vector{ (float)(rand() % 1440), (float)(rand() % 720) });
	float goc = (float)(rand() % 360);
	(obJect.end() - 1)->UpdateVector(Vector{ cos(goc),  sin(goc)});
	//random bị trí xuất hiện trên màn hình
}
void Manager::Add(Racket* racKet) {
	this->racKet = racKet;
}
void Manager::Add(HandelEvent* Handel) {// thêm con trỏ sự kiện
	this->Handel = Handel;
}
void Manager::render(SDL_Renderer* renderer) {
	for (int i = 0; i < obJect.size(); i++) {
		obJect[i].Render();
	}
}
int Manager::getSize() { // hàm lấy giá trị vector
	return obJect.size();
}
void Manager::UpdatePositionAndVector() {

	for (int i = 0; i < obJect.size(); i++) {

		//obJect[i].Animation(2); // chuyển động của đối tượng 
		/*
		Vector v, vtmp; //v:vị trí ban đầu; vtmp: vị trí cập nhật theo hàm random
		static int t = 0;// t: biến random

		//tính giá trị x, y của vector của mỗi đối tượng, xu hướng vector của mối đối tượng dịch vào tâm cửa sổ
		v.x = (720 - obJect[i].getPosition().x);
		v.y = (360 - obJect[i].getPosition().y);

		// tính giá trị độ dài vector đó
		float r = sqrt(v.x * v.x + v.y * v.y);
		//tính góc tạo bởi vector đó với trục Ox;
		float phi = atan(v.y / v.x);

		//Nếu x < 0 thì góc phi sẽ được cộng thêm 1 khoảng 180 độ sao cho góc phi muốn tính luôn dương
		if (v.x < 0) phi += pi;
		srand(t++);
		//random 1 góc bất kì trong khoảng -100 đến 80 độ
		double alpha = double(( rand() % 30) - 15);

		// random 2 giá trị x, y của vector vị trí bằng cách lấy góc phi ban đầu cộng với góc được random
		vtmp.x = 0.05 * cos(alpha * pi / 180 + phi);
		vtmp.y = 0.05 * sin(alpha * pi / 180 + phi);

		//cập nhật vị trí cho mỗi đối tượng
		obJect[i].UpdateObject(Vector{ vtmp.x,vtmp.y }, alpha + phi * 180 / pi + 90);
		*/
		//random điểm của mỗi đối tượng trong khoảng từ 50 đến 100 điểm
		obJect[i].Animation(!obJect[i].status);
		obJect[i].UpdateFly();
		obJect[i].UpdateScore( rand() % 50 + 50);
		
	}
	// âm hit con ruồi
	Sound1.addSound("Data//hit3.wav");
	// xử lí va chạm
	//static int hitTimes = 0;
	
	for (int i = 0; i < obJect.size(); i++) {
		if (obJect[i].GetRect().x > 1440 || obJect[i].GetRect().x < 0 ||
			obJect[i].GetRect().y > 720 || obJect[i].GetRect().y < 0)
		{
			//obJect[i].Animation(set);
			obJect[i].status = false;
		}
		//std::cout << obJect[i].status << std::endl;
		if (Collision(racKet->GetRect(), obJect[i].GetRect()) && Handel->BUTTON_LEFT) {
			Sound1.playSound("Data//hit3.wav");
			if(obJect[i].status){
				scored += obJect[i].score;// cộng điểm cho biến điểm
				//hitTimes = 0;
				obJect.erase(obJect.begin() + i);// xoá đối tượng
			//	std::cout << "1 " <<hitTimes << std::endl;
				break;// break nếu đã xoá 1 đối tượng tránh 1 click xoá nhiều đối tượng
			}
			if (!obJect[i].status) {
				//hitTimes += 1;
				//if (hitTimes == 2) { 
					obJect[i].status = true; 
					break;
					//hitTimes = 0; 
					//obJect.erase(obJect.begin() + i);
				//} 
			
			}
			//std::cout << "2 "<<hitTimes << std::endl;
		}
	}
}
