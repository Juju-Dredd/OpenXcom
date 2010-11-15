/*
 * Copyright 2010 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "BattleUnit.h"
#include "../Engine/Palette.h"
#include "../Battlescape/Pathfinding.h"

/**
 * Initializes a BattleUnit.
 */
BattleUnit::BattleUnit(RuleUnitSprite *renderRules) : _renderRules(renderRules), _id(0), _pos(Position()), _lastPos(Position()), _direction(0), _status(STATUS_STANDING), _walkPhase(0)
{

}

/**
 *
 */
BattleUnit::~BattleUnit()
{
	
}

/**
 * Returns the BattleUnit's unique ID.
 * @return Unique ID.
 */
int BattleUnit::getId() const
{
	return _id;
}

/**
 * Changes the BattleUnit's unique ID.
 * @param id Unique ID.
 */
void BattleUnit::setId(int id)
{
	_id = id;
}

/**
 * Returns the ruleset for the unit's type.
 * @return Pointer to ruleset.
 */
RuleUnitSprite *const BattleUnit::getRenderRules() const
{
	return _renderRules;
}

/**
 * Changes the BattleUnit's position.
 * @param pos position
 */
void BattleUnit::setPosition(const Position& pos)
{
	_lastPos = _pos;
	_pos = pos;
}

/**
 * Gets the BattleUnit's position.
 * @return position
 */
const Position& BattleUnit::getPosition() const
{
	return _pos;
}

/**
 * Gets the BattleUnit's position.
 * @return position
 */
const Position& BattleUnit::getLastPosition() const
{
	return _lastPos;
}
/**
 * Gets the BattleUnit's destination.
 * @return destination
 */
const Position& BattleUnit::getDestination() const
{
	return _destination;
}

/**
 * Changes the BattleUnit's direction.
 * @param direction
 */
void BattleUnit::setDirection(int direction)
{
	_direction = direction;
}

/**
 * Changes the BattleUnit's direction.
 * @return direction
 */
int BattleUnit::getDirection() const
{
	return _direction;
}

/*
 * Gets the unit's status.
 */
UnitStatus BattleUnit::getStatus()
{
	return _status;
}

void BattleUnit::startWalking(int direction, const Position &destination)
{
	_direction = direction;
	_status = STATUS_WALKING;
	_walkPhase = 0;
	_destination = destination;
}

void BattleUnit::keepWalking()
{
	_walkPhase++;
	if (_walkPhase == 4)
	{
		// we assume we reached our destination tile
		// this is actually a drawing hack, so soldiers are not overlapped by floortiles
		_lastPos = _pos;
		_pos = _destination;
	}
	if (_walkPhase == 8)
	{
		// we officially reached our destination tile
		_status = STATUS_STANDING;
		_walkPhase = 0;
	}
}

int BattleUnit::getWalkingPhase()
{
	return _walkPhase;
}