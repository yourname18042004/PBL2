#include <Manager/ManagerObject.h>
#include <Load/LoadMusic.h>

LoadMusic hit;

Manager::Manager() {
	FlyLinkList = new ObjectLinkList<Fly>();
}
void Manager::Add(Fly* a) {
	FlyLinkList->push(a);
}
void Manager::Add(Racket* racKet) {
	this->racKet = racKet;
}

void Manager::Add(float* timegame)
{
	this->timegame = timegame;
}

void Manager::ReadMap(SDL_Renderer* renderer, const char* path)
{
	ReadFile(FlyLinkList, renderer, timegame, path);
}

void Manager::Update(bool set, int& heart, bool autorun, float *timegame) {
	UpdatePositionAndVector();
	FlyLinkList->resetIndex();
	ManagerFly(set, heart, autorun, timegame);
	if (!autorun) {
		racKet->UpdatePositionOfMouse();
	}
	else {

	}
	racKet->UpdateRacket();
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
		
		fly->move();

		FlyLinkList->GoNext();
	} 
	FlyLinkList->resetIndex();
}

void Manager::ManagerFly(bool set, int& heart, bool Autorun, float *timegame) {
	if (set) {
		while (!FlyLinkList->setIndex() && !FlyLinkList->isEmpty()) {
			if (!Autorun) {
				Fly* fly = FlyLinkList->getIndex()->getData();
				if (Collision(fly->GetArea(), racKet->GetArea()) && racKet->GetHit()) {
					if (!FlyLinkList->getIndex()->getData()->status) {
						heart--; // tru mang
						break;
					}
					else {
						//hit.addSound("Data//hit3.wav");
						scored += FlyLinkList->getIndex()->getData()->Getscore();
						FlyLinkList->deleteNode();
						FlyLinkList->resetIndex();
						break;
					}
				}
				if (CollisionBlockWidth(fly->GetArea()) || CollisionBlockHeight(fly->GetArea())) {
					scored -= FlyLinkList->getIndex()->getData()->Getscore();
					if (scored < 0) scored = 0;
					FlyLinkList->deleteNode();
					FlyLinkList->resetIndex();
					break;
					}
				}
			else {
					if (FlyLinkList->getIndex()->getData()->TimeLand(timegame)) {
						racKet->Updateifautorun(FlyLinkList->getIndex()->getData()->GetEnd());
						if (Collision(racKet->GetArea(), FlyLinkList->getIndex()->getData()->GetArea())) {
							racKet->AutoHit();
							scored += FlyLinkList->getIndex()->getData()->Getscore();
							FlyLinkList->deleteNode();
							FlyLinkList->resetIndex();
							break;
						}
					}
				}
				FlyLinkList->GoNext();
			}
			FlyLinkList->resetIndex();
		}
	
}
bool Manager::IsEmty() {
	return FlyLinkList->isEmpty();
}
void Manager::Reset() {
	scored = 0;
		while (!FlyLinkList->setIndex() && !FlyLinkList->isEmpty()) {
			FlyLinkList->deleteNode();
			FlyLinkList->resetIndex();
		}
}


