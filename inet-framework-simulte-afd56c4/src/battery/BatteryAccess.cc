/*
 * BatteryAccess.cc
 *
 *  Created on: Aug 26, 2009
 *      Author: Karl Wessel
 */

#include "BatteryAccess.h"

#include <cassert>

#include "FindModule.h"

BatteryAccess::BatteryAccess():
	BaseModule(),
	battery(NULL),
	deviceID(-1)
{}

BatteryAccess::BatteryAccess(unsigned stacksize):
	BaseModule(stacksize),
	battery(NULL),
	deviceID(-1)
{}

void BatteryAccess::registerWithBattery(const std::string& name, int numAccounts)
{
	//battery = FindModule<BaseBattery*>::findSubModule(findHost()); // deprecated command
    validate = true;

	if(!battery) {
		//opp_warning("No battery module defined!");
		error("No battery module defined!");
	} else {
		deviceID = battery->registerDevice(name, numAccounts);
	}
}

void BatteryAccess::draw(DrawAmount& amount, int account)
{
	if(!battery)
		return;

	battery->draw(deviceID, amount, account);
}

void BatteryAccess::drawCurrent(double amount, int account)
{
	if(!battery)
		return;

	DrawAmount val(DrawAmount::CURRENT, amount);
	battery->draw(deviceID, val, account);
}

void BatteryAccess::drawEnergy(double amount, int account)
{
	if(!battery)
		return;

	DrawAmount val(DrawAmount::ENERGY, amount);
	battery->draw(deviceID, val, account);
}