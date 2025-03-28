#pragma once

#include "json.hpp"

#include "Database/DatabaseFactory.h"

namespace Chargenode
{
	inline nlohmann::json config;
	inline bool isDebug{ false };

	inline int counter = 0;

	inline std::unique_ptr<IDatabaseConnector> ChargenodeDB;

	inline std::unique_ptr<IDatabaseConnector> permissionsDB;

	inline std::unique_ptr<IDatabaseConnector> pointsDB;

}