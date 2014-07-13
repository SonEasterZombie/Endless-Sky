/* Mission.h
Copyright (c) 2014 by Michael Zahniser

Endless Sky is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

Endless Sky is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.
*/

#ifndef MISSION_H_
#define MISSION_H_

#include "DataFile.h"

#include <ostream>
#include <string>

class DistanceMap;
class GameData;
class Planet;



class Mission {
public:
	static Mission Cargo(const GameData &data, const Planet *source, const DistanceMap &distance);
	static Mission Passenger(const GameData &data, const Planet *source, const DistanceMap &distance);
	
	
public:
	void Load(const DataFile::Node &node, const GameData &data);
	void Save(std::ostream &out, const std::string &tag = "mission") const;
	
	const std::string &Name() const;
	const Planet *Destination() const;
	
	const std::string &Cargo() const;
	int CargoSize() const;
	int Passengers() const;
	int Payment() const;
	
	const std::string &Description() const;
	const std::string &SuccessMessage() const;
	
	
private:
	std::string name;
	const Planet *destination = nullptr;
	
	std::string cargo;
	int cargoSize = 0;
	int passengers = 0;
	int payment = 0;
	
	std::string description;
	std::string successMessage;
};



#endif
