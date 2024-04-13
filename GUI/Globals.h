#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include "Map/Map.h"
#include "Item/item.h"
#include "Serialize/serializeItem.h"
#include "Campaign/campaign.h"

extern std::vector<Map::Map*>* maps;
extern std::vector<item::Item*>* items;
extern std::vector<serializeItem::ItemContainerRecord*>* itemcontainers;
extern campaign::CampaignRecord* currentCampaign;
Identifiable* find(int id, std::vector < Identifiable*>);
#endif