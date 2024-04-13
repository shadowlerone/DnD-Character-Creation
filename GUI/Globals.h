#ifndef GLOBALS_H
#define GLOBALS_H

#include "Campaign/campaign.h"
#include "Item/item.h"
#include "Map/Map.h"
#include "Serialize/serializeItem.h"
#include <vector>

extern std::vector<Map::Map*>* maps;
extern std::vector<item::Item*>* items;
extern std::vector<serializeItem::ItemContainerRecord*>* itemcontainers;
extern campaign::CampaignRecord* currentCampaign;
Identifiable* find(int id, std::vector < Identifiable*>);
#endif