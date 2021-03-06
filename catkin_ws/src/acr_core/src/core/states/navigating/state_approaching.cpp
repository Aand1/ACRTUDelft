#include "state_approaching.hpp"

#include "../interacting/state_concreteInteraction.cpp"

State_Approaching::State_Approaching() { }

State* State_Approaching::update() {
	if(State_Navigating::backToIdle()) {
		return new State_Idle();
	}
	if(!isnan(SensorData::pointOfInterest())) {
			if(!SensorData::isFree(U_FRONT_TOP)) {
			return new State_ConcreteInteraction();
		}
		float angle = SensorData::pointOfInterest();
		
		SensorData::sendTwist(-angle * TURN_SPEED, MOVE_SPEED);
		return this;
	} else {
		return new State_Idle();
	}
}

void State_Approaching::switchTo() {
	ROS_INFO("Switched to State_Approaching"); 
	ROS_INFO("Superbehaviour: State_Navigating"); 
}

void State_Approaching::switchFrom() {
	SensorData::sendTwist(0.f, 0.f); // stop turning!
}
