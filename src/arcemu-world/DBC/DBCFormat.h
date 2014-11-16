/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2008 <http://www.ArcEmu.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "StdAfx.h"

#ifdef ENABLE_ACHIEVEMENTS
const char* AchievementCriteriaFormat="niiiiLiiisixiiixxxxxxxx";

const char* AchievementFormat="niiussiiuiusuu";
#endif

const char* VehicleEntryFormat = "uuffffuuuuuuuufffffffffffffffssssfufuxxx";
const char* areagroupFormat = "uuuuuuuu";
const char* SpellRuneCostFormat="uuuuu";
const char* GlyphPropertiesFormat="niii";
const char* GlyphSlotFormat="nii";
const char* LockFormat = "uuuuuuxxxuuuuuxxxuuuuuxxxxxxxxxxx";
const char* spellcasttimeFormat = "uuxx";
const char* spellradiusFormat = "ufxf";
const char* spelldurationFormat = "uuuu";
const char* factiontemplatedbcFormat = "uuuuuuuuuuuuuu";
const char* creaturespelldataFormat = "uuuuuuuuu";
const char* durabilityqualityFormat = "uf";
const char* durabilitycostsFormat = "uuuuuuuuuuuuuuuuuuuuuuuuuuuuuu";
const char* bankslotpriceformat = "uu";
const char* gtfloatformat = "f";
const char* gtClassfloatformat = "uf";
const char* questxpformat = "uxuuuuuuuux";
const char* questrewrepformat = "ixiiiiiiiii";

const char* mailTemplateEntryFormat = "uss";
const char* summonpropertiesformat = "uuuuuu";

const char* WorldMapOverlayStoreFormat="nxiiiixxxxxxxxx";

const char* wmoareaformat = "uiiixxxxxuuxxxx";
const char* dbcWorldsafelocsfmt = "iifffs";
const char* dbcMountCapabilityStorefmt = "iiixxiii";
const char* dbcMountTypeStorefmt = "iiiiiiiiiiiiiiiiiixxxxxxx";
const char* GuildPerkfmt = "uuu";
const char* ArmorLocationfmt = "nfffff";
const char* ItemArmorQualityfmt="nfffffffi";
const char* ItemArmorShieldfmt="nifffffff";
const char* ItemArmorTotalfmt="niffff";
const char* ItemDamagefmt="nfffffffi";
const char* SpellEffectEntryfmt="xufuuiffiiiiiifiifiiiiiiiix";
const char* SpellShapeshiftFormfmt="uxxiixiiixxiiiiiiiixx";
const char* SpellShapeshiftEntryfmt="uixixx";
const char* SpellAuraOptionsEntryfmt="uuuuu";
const char* SpellAuraRestrictionsEntryfmt="uiiiiiiii";
const char* SpellCastingRequirementsEntryfmt="uixxixi";
const char* SpellCategoriesEntryfmt="uuuuuuu";
const char* SpellClassOptionsEntryfmt="uxiiiix";

const char* SpellCooldownsEntryfmt="uiii";
const char* SpellEquippedItemsEntryfmt="uiii";
const char* SpellInterruptsEntryfmt="uixixi";
const char* SpellLevelsEntryfmt="uiii";

const char* SpellPowerEntryfmt="uiiiixxx";

const char* SpellReagentsEntryfmt="uiiiiiiiiiiiiiiii";
const char* SpellScalingEntryfmt="uiiiiffffffffffi";
const char* SpellTargetRestrictionsEntryfmt="uixiii";
const char* SpellTotemsEntryfmt="uiiii";

const char* classSpellScalefmt="uf";
const char* LFGDungeonFormat = "nxxuuuuuuuxuxxuxuxxxx";
const char* WorldMapZoneFormat = "uuusffffxxxxxx";
const char* VehicleSeatEntryFormat = "uuiffffffffffiiiiiifffffffiiifffiiiiiiiffiiiiixxxxxxxxxxxxxxxxxxxx";

const char* CurrencyTypesEntryFormat = "xnxuxxxxxxx";

const char* scalingstatdistributionformat = "uiiiiiiiiiiuuuuuuuuuuxu";
const char* scalingstatvaluesformat = "iniiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii";

const char* BattlemasterListEntryFormat = "uiiiiiiiiuxxuuuuuuux";
const char* itemlimitcategoryFormat = "uxux";

const char* BarberShopStyleEntryFormat="nxxxxxxi";

const char* BarberShopCostFormat="xf";


const char* ItemSetFormat = "usuuuuuuuuxxxxxxxxxuuuuuuuuuuuuuuuuuu";

const char* EmoteEntryFormat = "uxuuuuxuxuxxxxxxxxx";
	
const char* skilllinespellFormat = "iiiiiiiiiiiiix";
const char* EnchantEntrYFormat = "uxuuuuuuuuuuuusuuuuuuuu";
const char* GemPropertyEntryFormat = "uuuuux";

const char* skilllineentrYFormat = "uusxxxx";

const char* spellentryFormat = "uuuuuuuuuuuxuuuufuuuussssuuuuufuuuuuuuuuuuuuuuuu";

const char* talententryFormat = "uuuuuuuuuxuxxxxuxxx";

const char* talenttabentryFormat = "uxxuuuxxxuu";

const char* talentprimaryspellFormat = "uuux";

const char* spellrangeFormat = "uffffxxx";

const char* randompropsFormat = "uxuuuxxx";

const char* areatableFormat = "uuuuuxxxxxusuxxxxxxxxxxxxx";
const char* itemextendedcostFormat = "uuuuuuuuuuuuuuuuuuuuuuuuuuuxxxx";
const char* factiondbcFormat = "uiuuuuuuuuiiiiuuuuuxxxxsxx";
const char* dbctaxinodeFormat = "uufffxuuuff";
const char* dbctaxipathFormat = "uuuu";
const char* dbctaxipathnodeFormat = "uuuufffuuxx";
const char* creaturefamilyFormat = "ufufuuuuuusx";
const char* charraceFormat = "nxixiixixxxxixsxxxxxixxx";	
const char* charclassFormat = "uuxsxxxxxxxxxx";
const char* mapentryFormat = "nxixxxsixxixiffxixxx";
const char* auctionhousedbcFormat = "uuuux";
const char* itemrandomsuffixformat = "uxxuuuuuuuuuu";
const char* randompropopointsfmt = "iiiiiiiiiiiiiiii";
const char* itemreforgeformat = "uufuu";
const char* chatchannelformat = "uuxsx";
const char* areatriggerformat = "uufffxxxxxxxx";
const char* chartitleFormat = "uxsxux";