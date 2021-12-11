#include "SmokeHandler.h"
using namespace smartHouse;

void SmokeHandler::HandleEvent(shared_ptr<Event> spEvent)
{
	//handle event
	std::cout << std::endl << "---Received event from SmokeSensor: Handling the event now!---" << std::endl;
	std::cout << "Time: " << std::ctime(&(spEvent->GetTimestamp())); //'ctime' converts time_t value to string - format: Www Mmm dd hh:mm:ss yyyy
	std::cout << "Type: " << spEvent->GetType() << std::endl;
	std::cout << "Floor: " << spEvent->GetLocation().GetFloor().Get() << std::endl;
	std::cout << "Room: " << spEvent->GetLocation().GetRoom().Get() << std::endl;
	std::cout << "Payload: " << spEvent->GetPayload() << std::endl;
	std::cout << "---End event handling.---" << std::endl << std::endl;
}

