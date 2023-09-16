#include <Manager/ManagerObject.h>
#include <Load/LoadMusic.h>
Manager::Manager() {
	FlyLinkList = new ObjectLinkList<Fly>();
}
void Manager::Add(Fly* a) {
	FlyLinkList->push(a);
}
void Manager::Add(Racket* racKet) {
	this->racKet = racKet;
}
void Manager::Add(HandelEvent* Handel) {// thêm con trỏ sự kiện
	
}
void Manager::Update() {
	UpdatePositionAndVector();

	FlyLinkList->resetIndex();
	racKet->UpdatePositionOfMouse();
	racKet->UpdateRacket();
	ManagerFly();
}

void Manager::render(SDL_Renderer* renderer) {

	while (!FlyLinkList->setIndex()&& !FlyLinkList->isEmpty())
	{
		FlyLinkList->getIndex()->getData()->Render();
		FlyLinkList->GoNext();
	}
	FlyLinkList->resetIndex();
	racKet->Render();
}
int Manager::getSize() { // hàm lấy giá trị vector
	return 0;// obJect.size();
}
void Manager::UpdatePositionAndVector() {
	while (!FlyLinkList->setIndex() && !FlyLinkList->isEmpty())
	{
		FlyLinkList->getIndex()->getData()->UpdateFly();
		Fly* fly = FlyLinkList->getIndex()->getData();

		if (CollisionBlockWidth(fly->GetArea())) fly->UpdateVector(Vector{ fly->getDir().x, fly->getDir().y * -1 });
		if (CollisionBlockHeight(fly->GetArea())) fly->UpdateVector(Vector{ fly->getDir().x * -1, fly->getDir().y});

		Vector v = fly->getDir();
		fly->UpdatePosition(Vector{ v.x * Timer::sInit->DeltaTime(), v.y * Timer::sInit->DeltaTime()});

		FlyLinkList->GoNext();
	}
	FlyLinkList->resetIndex();
}
	

void Manager::ManagerFly() {
	while (!FlyLinkList->setIndex()&& !FlyLinkList->isEmpty())
	{
		Fly* fly =FlyLinkList->getIndex()->getData();
		if (Collision(fly->GetArea(), racKet->GetArea()) && racKet->GetHit()) {
			FlyLinkList->deleteNode();
			FlyLinkList->resetIndex();
			break;
		}
		else FlyLinkList->GoNext();
	}
	FlyLinkList->resetIndex();
}
