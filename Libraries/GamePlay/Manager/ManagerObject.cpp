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
		Vector v = fly->getDir();
		fly->UpdatePosition(Vector{ v.x * Timer::sInit->DeltaTime() * 100, v.y * Timer::sInit->DeltaTime() * 100 });

		if (CollisionBlockWidth(fly->GetArea()))
		{
			if (fly->GetArea().x <= 0) fly->SetArea(-fly->GetArea().x, fly->GetArea().y);
			if (fly->GetArea().x + fly->GetArea().w >= 1440) fly->SetArea(2*1440 - (fly->GetArea().x + fly->GetArea().w), fly->GetArea().y);
			fly->UpdateVector(Vector{ fly->getDir().x, fly->getDir().y * -1 });
			Vector v = fly->getDir();
			fly->UpdatePosition(Vector{ v.x * Timer::sInit->DeltaTime() * 100, v.y * Timer::sInit->DeltaTime() * 100 });
		}
		if (CollisionBlockHeight(fly->GetArea()))
		{
			if (fly->GetArea().y <= 0) fly->SetArea(fly->GetArea().x, -fly->GetArea().y);
			if (fly->GetArea().y + fly->GetArea().h >= 720) fly->SetArea(fly->GetArea().x, 2*720 - (fly->GetArea().y + fly->GetArea().h));
			fly->UpdateVector(Vector{ fly->getDir().x * -1, fly->getDir().y });
			Vector v = fly->getDir();
			fly->UpdatePosition(Vector{ v.x * Timer::sInit->DeltaTime() * 100, v.y * Timer::sInit->DeltaTime() * 100 });
		}

		FlyLinkList->GoNext();
	} 
	FlyLinkList->resetIndex();
}
	

void Manager::ManagerFly() {
	while (!FlyLinkList->setIndex()&& !FlyLinkList->isEmpty())
	{
		Fly* fly =FlyLinkList->getIndex()->getData();
		if (Collision(fly->GetArea(), racKet->GetArea()) && racKet->GetHit()) {

			scored+=FlyLinkList->getIndex()->getData()->Getscore();
			FlyLinkList->deleteNode();
			FlyLinkList->resetIndex();
			break;
		}
		else FlyLinkList->GoNext();
	}
	FlyLinkList->resetIndex();
}
bool Manager::IsEmty() {
	return FlyLinkList->isEmpty();
}
void Manager::Reset() {
	scored = 0;
	while (!FlyLinkList->setIndex() && !FlyLinkList->isEmpty()) {
		FlyLinkList->deleteNode();
		FlyLinkList->GoNext();
	}
}