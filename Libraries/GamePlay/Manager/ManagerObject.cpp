#include <Manager/ManagerObject.h>
#include <Load/LoadMusic.h>
LoadMusic Sound1;

void Manager::Add(Fly a) {
	/*obJect.push_back(a);
	(obJect.end() - 1)->UpdateObject(Vector{ (float)(rand() % 1000), (float)(rand() % 500 ) });
	float goc = (float)(rand() % 360);
	(obJect.end() - 1)->UpdateVector(Vector{ cos(goc),  sin(goc)});*/
	//random bị trí xuất hiện trên màn hình
}
void Manager::Add(Racket* racKet) {
	//this->racKet = racKet;
}
void Manager::Add(HandelEvent* Handel) {// thêm con trỏ sự kiện
	//this->Handel = Handel;
}
void Manager::render(SDL_Renderer* renderer) {
	/*for (int i = 0; i < obJect.size(); i++) {
		obJect[i].Render();
	}*/
}
int Manager::getSize() { // hàm lấy giá trị vector
	return 0;// obJect.size();
}
void Manager::UpdatePositionAndVector() {

	/*for (int i = 0; i < obJect.size(); i++) {
		obJect[i].Animation(!obJect[i].status);
		obJect[i].UpdateFly();
		obJect[i].UpdateScore(100);
	}*/
	// xử lí va chạm
	//for(int i = 0;i <obJect.size();i++){
	//	if (Collision(racKet->GetRect(), obJect[i].GetRect()) && Handel->BUTTON_LEFT) {
	//		Sound1.addSound("Data//hit3.wav");
	//		if(obJect[i].status){
	//			scored += obJect[i].score;// cộng điểm cho biến điểm
	//			obJect.erase(obJect.begin() + i);// xoá đối tượng
	//			break;// break nếu đã xoá 1 đối tượng tránh 1 click xoá nhiều đối tượng
	//		}
	//		else{
	//			obJect[i].status = true; 
	//			break;
	//		}
	//	}
	//}
}
