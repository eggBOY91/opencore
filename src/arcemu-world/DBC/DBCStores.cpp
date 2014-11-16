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

#include "DBCFormat.h"

SERVER_DECL DBCStorage<WorldMapOverlay>				dbcWorldMapOverlayStore;

#ifdef ENABLE_ACHIEVEMENTS
SERVER_DECL DBCStorage<AchievementEntry>			dbcAchievementStore;
SERVER_DECL DBCStorage<AchievementCriteriaEntry>	dbcAchievementCriteriaStore;
#endif

SERVER_DECL DBCStorage <MountCapabilityEntry>		dbcMountCapabilityStore;
SERVER_DECL DBCStorage <MountTypeEntry>				dbcMountTypeStore;

SERVER_DECL DBCStorage <ArmorLocationEntry>         dbcArmorLocationStore;
SERVER_DECL DBCStorage <ItemArmorQualityEntry>      dbcItemArmorQualityStore;
SERVER_DECL DBCStorage <ItemArmorShieldEntry>       dbcItemArmorShieldStore;
SERVER_DECL DBCStorage <ItemArmorTotalEntry>        dbcItemArmorTotalStore;
SERVER_DECL DBCStorage <ItemDamageEntry>            dbcItemDamageAmmoStore;
SERVER_DECL DBCStorage <ItemDamageEntry>            dbcItemDamageOneHandStore;
SERVER_DECL DBCStorage <ItemDamageEntry>            dbcItemDamageOneHandCasterStore;
SERVER_DECL DBCStorage <ItemDamageEntry>            dbcItemDamageRangedStore;
SERVER_DECL DBCStorage <ItemDamageEntry>            dbcItemDamageThrownStore;
SERVER_DECL DBCStorage <ItemDamageEntry>            dbcItemDamageTwoHandStore;
SERVER_DECL DBCStorage <ItemDamageEntry>            dbcItemDamageTwoHandCasterStore;
SERVER_DECL DBCStorage <ItemDamageEntry>            dbcItemDamageWandStore;

SERVER_DECL DBCStorage <LFGDungeonEntry>			dbcLFGDungeonStore;
SERVER_DECL DBCStorage <WorldMapAreaEntry>			dbcWorldMapZoneStore;
SERVER_DECL DBCStorage <VehicleSeatEntry>			dbcVehicleSeatEntry;
SERVER_DECL DBCStorage <VehicleEntry>				dbcVehicleEntry;
SERVER_DECL DBCStorage<CurrencyTypesEntry>			dbcCurrencyTypesStore;
SERVER_DECL DBCStorage<ScalingStatDistributionEntry> dbcScalingStatDistribution;
SERVER_DECL DBCStorage<ScalingStatValuesEntry>		dbcScalingStatValues;
SERVER_DECL DBCStorage<BattlemasterListEntry>		dbcBattlemasterListStore;
SERVER_DECL DBCStorage<ItemLimitCategory>			dbcItemLimitCategory;
SERVER_DECL DBCStorage<AreaGroup>					dbcAreaGroup;
SERVER_DECL DBCStorage<GlyphPropertiesEntry>        dbcGlyphPropertiesStore;
SERVER_DECL DBCStorage<GlyphSlotEntry>              dbcGlyphSlotStore;
SERVER_DECL DBCStorage<BarberShopStyleEntry>		dbcBarberShopStyleStore;
SERVER_DECL DBCStorage<GtBarberShopCostBaseEntry>	dbcBarberShopCostStore;
SERVER_DECL DBCStorage<GemPropertyEntry>			dbcGemProperty;
SERVER_DECL DBCStorage<ItemSetEntry>				dbcItemSet;
SERVER_DECL DBCStorage<Lock>						dbcLock;

SERVER_DECL DBCStorage<SpellRuneCostEntry>			dbcSpellRuneCostEntry;
SERVER_DECL DBCStorage<SpellRadius>					dbcSpellRadius;
SERVER_DECL DBCStorage<SpellCastTime>				dbcSpellCastTime;
SERVER_DECL DBCStorage<SpellEntry>					dbcSpell;
SERVER_DECL DBCStorage<SpellDuration>				dbcSpellDuration;
SERVER_DECL DBCStorage<SpellRange>					dbcSpellRange;
SERVER_DECL DBCStorage<SpellEffectEntry>			dbcSpellEffect;
SERVER_DECL DBCStorage<SpellDifficultyEntry>		dbcSpellDifficulty;
SERVER_DECL DBCStorage<SpellFocusObjectEntry>		dbcSpellFocusObject;
//SERVER_DECL DBCStorage<SpellItemEnchantmentConditionEntry>	dbcSpellItemEnchantmentCondition;
//SERVER_DECL SpellCategoryStore					dbcSpellCategory;
SERVER_DECL DBCStorage<SpellShapeshiftFormEntry>	dbcSpellShapeshiftForm;
SERVER_DECL DBCStorage<SpellAuraOptionsEntry>		dbcSpellAuraOptions;
SERVER_DECL DBCStorage<SpellAuraRestrictionsEntry>	dbcSpellAuraRestrictions;
SERVER_DECL DBCStorage<SpellCastingRequirementsEntry>	dbcSpellCastingRequirements;
SERVER_DECL DBCStorage<SpellCategoriesEntry>		dbcSpellCategories;
SERVER_DECL DBCStorage<SpellClassOptionsEntry>		dbcSpellClassOptions;
SERVER_DECL DBCStorage<SpellCooldownsEntry>			dbcSpellCooldowns;
SERVER_DECL DBCStorage<SpellEquippedItemsEntry>		dbcSpellEquippedItems;
SERVER_DECL DBCStorage<SpellInterruptsEntry>		dbcSpellInterrupts;
SERVER_DECL DBCStorage<SpellLevelsEntry>			dbcSpellLevels;
SERVER_DECL DBCStorage<SpellPowerEntry>				dbcSpellPower;
SERVER_DECL DBCStorage<SpellReagentsEntry>			dbcSpellReagents;
SERVER_DECL DBCStorage<SpellScalingEntry>			dbcSpellScaling;
SERVER_DECL DBCStorage<SpellShapeshiftEntry>		dbcSpellShapeshift;
SERVER_DECL DBCStorage<SpellTargetRestrictionsEntry>	dbcSpellTargetRestrictions;
SERVER_DECL DBCStorage<SpellTotemsEntry>			dbcSpellTotems;
SERVER_DECL DBCStorage<gtClassLevelFloat>			dbcGTSpellScale;

SERVER_DECL DBCStorage<GuildPerkSpellEntry>			dbcGuildPerks;
SERVER_DECL DBCStorage<emoteentry>					dbcEmoteEntry;
SERVER_DECL DBCStorage<AreaTable>					dbcArea;
SERVER_DECL DBCStorage<FactionTemplateDBC>			dbcFactionTemplate;
SERVER_DECL DBCStorage<FactionDBC>					dbcFaction;
SERVER_DECL DBCStorage<EnchantEntry>				dbcEnchant;
SERVER_DECL DBCStorage<RandomProps>					dbcRandomProps;
SERVER_DECL DBCStorage<skilllinespell>				dbcSkillLineSpell;
SERVER_DECL DBCStorage<skilllineentry>				dbcSkillLine;
SERVER_DECL DBCStorage<DBCTaxiNode>					dbcTaxiNode;
SERVER_DECL DBCStorage<DBCTaxiPath>					dbcTaxiPath;
SERVER_DECL DBCStorage<DBCTaxiPathNode>				dbcTaxiPathNode;
SERVER_DECL DBCStorage<AuctionHouseDBC>				dbcAuctionHouse;
SERVER_DECL DBCStorage<TalentEntry>					dbcTalent;
SERVER_DECL DBCStorage<TalentTabEntry>				dbcTalentTab;
SERVER_DECL DBCStorage<TalentPrimarySpellsEntry>	dbcTalentPrimarySpells;
SERVER_DECL DBCStorage<CreatureSpellDataEntry>		dbcCreatureSpellData;
SERVER_DECL DBCStorage<CreatureFamilyEntry>			dbcCreatureFamily;
SERVER_DECL DBCStorage<CharClassEntry>				dbcCharClass;
SERVER_DECL DBCStorage<CharRaceEntry>				dbcCharRace;
SERVER_DECL DBCStorage<MapEntry>					dbcMap;
SERVER_DECL DBCStorage<ItemExtendedCostEntry>		dbcItemExtendedCost;
SERVER_DECL DBCStorage<ItemRandomSuffixEntry>		dbcItemRandomSuffix;
SERVER_DECL DBCStorage<RandomPropertiesPointsEntry>	dbcRandomPropertyPoints;
SERVER_DECL DBCStorage<ItemReforgeEntry>			dbcItemReforge;
SERVER_DECL DBCStorage<gtClassLevelFloat>			dbcCombatRating;
SERVER_DECL DBCStorage<ChatChannelDBC>				dbcChatChannels;
SERVER_DECL DBCStorage<DurabilityQualityEntry>		dbcDurabilityQuality;
SERVER_DECL DBCStorage<DurabilityCostsEntry>		dbcDurabilityCosts;
SERVER_DECL DBCStorage<BankSlotPrice>				dbcBankSlotPrices;
//SERVER_DECL DBCStorage<BankSlotPrice>				dbcStableSlotPrices;
SERVER_DECL DBCStorage<gtClassLevelFloat>			dbcMeleeCrit;
SERVER_DECL DBCStorage<gtClassLevelFloat>			dbcMeleeCritBase;
SERVER_DECL DBCStorage<gtClassLevelFloat>			dbcSpellCrit;
SERVER_DECL DBCStorage<gtClassLevelFloat>			dbcSpellCritBase;
SERVER_DECL DBCStorage<gtClassLevelFloat>			dbcMPRegen;
SERVER_DECL DBCStorage<gtClassLevelFloat>			dbcMPRegenBase;
//SERVER_DECL DBCStorage<gtFloat>						dbcHPRegen;
SERVER_DECL DBCStorage<gtFloat>						dbcHPRegenBase;
SERVER_DECL DBCStorage<AreaTriggerEntry>			dbcAreaTrigger;
SERVER_DECL DBCStorage<QuestXPEntry>				dbcQuestXP;
SERVER_DECL DBCStorage<QuestRewRepEntry>			dbcQuestRewRep;
SERVER_DECL DBCStorage<CharTitlesEntry>				dbcCharTitle;
SERVER_DECL DBCStorage<WorldSafeLocsEntry>			dbcWorldSafeLocs; 
SERVER_DECL DBCStorage<WMOAreaTableEntry>			dbcWMOAreaTable;

SERVER_DECL DBCStorage<MailTemplateEntry>                       dbcMailTemplate;
SERVER_DECL DBCStorage<SummonPropertiesEntry>                   dbcSummonProperties;


template<class T>
bool loader_stub(const char* filename, const char* format, bool ind, T & l, bool loadstrs)
{
	Log.Notice("DBC", "Loading %s.", filename);
	return l.Load(filename, format, ind, loadstrs);	//just to let you know. Format can have 3 values : x(skip),s(str),?(val)
}

#define LOAD_DBC(filename, format, ind, stor, strings) if(!loader_stub(filename, format, ind, stor, strings)) { return false; } 

bool LoadDBCs()
{
	LOAD_DBC("DBC/WorldMapOverlay.dbc", WorldMapOverlayStoreFormat, true, dbcWorldMapOverlayStore, true);

#ifdef ENABLE_ACHIEVEMENTS
	LOAD_DBC("DBC/Achievement.dbc", AchievementFormat, true, dbcAchievementStore, true);
	LOAD_DBC("DBC/Achievement_Criteria.dbc", AchievementCriteriaFormat, true, dbcAchievementCriteriaStore, true);
#endif
	LOAD_DBC("DBC/WMOAreaTable.dbc", wmoareaformat, true, dbcWMOAreaTable, false);

	LOAD_DBC("DBC/WorldSafeLocs.dbc",dbcWorldsafelocsfmt,true,dbcWorldSafeLocs, false);

	LOAD_DBC("DBC/MountCapability.dbc",dbcMountCapabilityStorefmt,false,dbcMountCapabilityStore, false);

	LOAD_DBC("DBC/MountType.dbc",dbcMountTypeStorefmt,false,dbcMountTypeStore, false);

	LOAD_DBC("DBC/GuildPerkSpells.dbc",GuildPerkfmt,false,dbcGuildPerks, false);

	LOAD_DBC("DBC/ArmorLocation.dbc",ArmorLocationfmt,false,dbcArmorLocationStore, false);

	LOAD_DBC("DBC/ItemArmorQuality.dbc",ItemArmorQualityfmt,false,dbcItemArmorQualityStore, false);

	LOAD_DBC("DBC/ItemArmorShield.dbc",ItemArmorShieldfmt,false,dbcItemArmorShieldStore, false);

	LOAD_DBC("DBC/ItemArmorTotal.dbc",ItemArmorTotalfmt,false,dbcItemArmorTotalStore, false);


	LOAD_DBC("DBC/ItemDamageAmmo.dbc",ItemDamagefmt,false,dbcItemDamageAmmoStore, false);

	LOAD_DBC("DBC/ItemDamageOneHand.dbc",ItemDamagefmt,false,dbcItemDamageOneHandStore, false);

	LOAD_DBC("DBC/ItemDamageOneHandCaster.dbc",ItemDamagefmt,false,dbcItemDamageOneHandCasterStore, false);

	LOAD_DBC("DBC/ItemDamageRanged.dbc",ItemDamagefmt,false,dbcItemDamageRangedStore, false);

	LOAD_DBC("DBC/ItemDamageThrown.dbc",ItemDamagefmt,false,dbcItemDamageThrownStore, false);

	LOAD_DBC("DBC/ItemDamageTwoHand.dbc",ItemDamagefmt,false,dbcItemDamageTwoHandStore, false);

	LOAD_DBC("DBC/ItemDamageTwoHandCaster.dbc",ItemDamagefmt,false,dbcItemDamageTwoHandCasterStore, false);

	LOAD_DBC("DBC/ItemDamageWand.dbc",ItemDamagefmt,false,dbcItemDamageWandStore, false);


	LOAD_DBC("DBC/SpellEffect.dbc",SpellEffectEntryfmt,false,dbcSpellEffect, false);

	LOAD_DBC("DBC/SpellShapeshiftForm.dbc",SpellShapeshiftFormfmt,false,dbcSpellShapeshiftForm, false);

	LOAD_DBC("DBC/SpellShapeshift.dbc",SpellShapeshiftEntryfmt,false,dbcSpellShapeshift, false);

	LOAD_DBC("DBC/SpellAuraOptions.dbc",SpellAuraOptionsEntryfmt,false,dbcSpellAuraOptions, false);

	LOAD_DBC("DBC/SpellAuraRestrictions.dbc",SpellAuraRestrictionsEntryfmt,false,dbcSpellAuraRestrictions, false);

	LOAD_DBC("DBC/SpellCastingRequirements.dbc",SpellCastingRequirementsEntryfmt,false,dbcSpellCastingRequirements, false);

	LOAD_DBC("DBC/SpellCategories.dbc",SpellCategoriesEntryfmt,false,dbcSpellCategories, false);

	LOAD_DBC("DBC/SpellClassOptions.dbc",SpellClassOptionsEntryfmt,false,dbcSpellClassOptions, false);

	LOAD_DBC("DBC/SpellCooldowns.dbc",SpellCooldownsEntryfmt,false,dbcSpellCooldowns, false);

	LOAD_DBC("DBC/SpellEquippedItems.dbc",SpellEquippedItemsEntryfmt,false,dbcSpellEquippedItems, false);

	LOAD_DBC("DBC/SpellInterrupts.dbc",SpellInterruptsEntryfmt,false,dbcSpellInterrupts, false);

	LOAD_DBC("DBC/SpellLevels.dbc",SpellLevelsEntryfmt,false,dbcSpellLevels, false);

	LOAD_DBC("DBC/SpellPower.dbc",SpellPowerEntryfmt,false,dbcSpellPower, false);

	LOAD_DBC("DBC/SpellReagents.dbc",SpellReagentsEntryfmt,false,dbcSpellReagents, false);

	LOAD_DBC("DBC/SpellScaling.dbc",SpellScalingEntryfmt,false,dbcSpellScaling, false);

	LOAD_DBC("DBC/SpellTargetRestrictions.dbc",SpellTargetRestrictionsEntryfmt,false,dbcSpellTargetRestrictions, false);

	LOAD_DBC("DBC/SpellTotems.dbc",SpellTotemsEntryfmt,false,dbcSpellTotems, false);

	LOAD_DBC("DBC/gtSpellScaling.dbc", classSpellScalefmt, false, dbcGTSpellScale, true);

	LOAD_DBC("DBC/LFGDungeons.dbc",LFGDungeonFormat,false,dbcLFGDungeonStore, false);

	LOAD_DBC("DBC/WorldMapArea.dbc",WorldMapZoneFormat,false,dbcWorldMapZoneStore, false);

	LOAD_DBC("DBC/Vehicle.dbc",VehicleEntryFormat,true,dbcVehicleEntry, false);

	LOAD_DBC("DBC/VehicleSeat.dbc",VehicleSeatEntryFormat,true,dbcVehicleSeatEntry, false);

	LOAD_DBC("DBC/CurrencyTypes.dbc",CurrencyTypesEntryFormat,true,dbcCurrencyTypesStore, false);

	LOAD_DBC("DBC/ScalingStatDistribution.dbc",scalingstatdistributionformat,true,dbcScalingStatDistribution, false);

	LOAD_DBC("DBC/ScalingStatValues.dbc",scalingstatvaluesformat,true,dbcScalingStatValues, false);

	LOAD_DBC("DBC/BattlemasterList.dbc", BattlemasterListEntryFormat, true, dbcBattlemasterListStore, true);

	LOAD_DBC("DBC/ItemLimitCategory.dbc", itemlimitcategoryFormat, true, dbcItemLimitCategory, true);

	LOAD_DBC("DBC/AreaGroup.dbc", areagroupFormat, true, dbcAreaGroup, true);

	LOAD_DBC("DBC/SpellRuneCost.dbc", SpellRuneCostFormat, true, dbcSpellRuneCostEntry, true);

	LOAD_DBC("DBC/GlyphProperties.dbc", GlyphPropertiesFormat, true, dbcGlyphPropertiesStore, true);

	LOAD_DBC("DBC/GlyphSlot.dbc", GlyphSlotFormat, true, dbcGlyphSlotStore, true);

	LOAD_DBC("DBC/BarberShopStyle.dbc", BarberShopStyleEntryFormat, true, dbcBarberShopStyleStore, true);

	LOAD_DBC("DBC/gtBarberShopCostBase.dbc", BarberShopCostFormat, false, dbcBarberShopCostStore, true);

	LOAD_DBC("DBC/ItemSet.dbc", ItemSetFormat, true, dbcItemSet, true);

	LOAD_DBC("DBC/Lock.dbc", LockFormat, true, dbcLock, false);

	LOAD_DBC("DBC/EmotesText.dbc", EmoteEntryFormat, true, dbcEmoteEntry, false);

	LOAD_DBC("DBC/SkillLineAbility.dbc", skilllinespellFormat, false, dbcSkillLineSpell, false);

	LOAD_DBC("DBC/SpellItemEnchantment.dbc", EnchantEntrYFormat, true, dbcEnchant, true);

	LOAD_DBC("DBC/GemProperties.dbc", GemPropertyEntryFormat, true, dbcGemProperty, false);

	LOAD_DBC("DBC/SkillLine.dbc", skilllineentrYFormat, true, dbcSkillLine, true);

	LOAD_DBC("DBC/Spell.dbc", spellentryFormat, true, dbcSpell, true);

	LOAD_DBC("DBC/Talent.dbc", talententryFormat, true, dbcTalent, false);

	LOAD_DBC("DBC/TalentTab.dbc", talenttabentryFormat, true, dbcTalentTab, false);
	LOAD_DBC("DBC/TalentTreePrimarySpells.dbc", talentprimaryspellFormat, true, dbcTalentPrimarySpells, false);

	LOAD_DBC("DBC/SpellCastTimes.dbc", spellcasttimeFormat, true, dbcSpellCastTime, false);

	LOAD_DBC("DBC/SpellRadius.dbc", spellradiusFormat, true, dbcSpellRadius, false);

	LOAD_DBC("DBC/SpellRange.dbc", spellrangeFormat, true, dbcSpellRange, false);

	LOAD_DBC("DBC/SpellDuration.dbc", spelldurationFormat, true, dbcSpellDuration, false);

	LOAD_DBC("DBC/ItemRandomProperties.dbc", randompropsFormat, true, dbcRandomProps, false);

	LOAD_DBC("DBC/AreaTable.dbc", areatableFormat, true, dbcArea, true);

	LOAD_DBC("DBC/FactionTemplate.dbc", factiontemplatedbcFormat, true, dbcFactionTemplate, false);

	LOAD_DBC("DBC/ItemExtendedCost.db2", itemextendedcostFormat, true, dbcItemExtendedCost, false);

	LOAD_DBC("DBC/Faction.dbc", factiondbcFormat, true, dbcFaction, true);

	LOAD_DBC("DBC/TaxiNodes.dbc", dbctaxinodeFormat, false, dbcTaxiNode, false);

	LOAD_DBC("DBC/TaxiPath.dbc", dbctaxipathFormat, false, dbcTaxiPath, false);

	LOAD_DBC("DBC/TaxiPathNode.dbc", dbctaxipathnodeFormat, false, dbcTaxiPathNode, false);

	LOAD_DBC("DBC/CreatureSpellData.dbc", creaturespelldataFormat, true, dbcCreatureSpellData, false);

	LOAD_DBC("DBC/CreatureFamily.dbc", creaturefamilyFormat, true, dbcCreatureFamily, true);

	LOAD_DBC("DBC/ChrRaces.dbc", charraceFormat, true, dbcCharRace, true);

	LOAD_DBC("DBC/ChrClasses.dbc", charclassFormat, true, dbcCharClass, true);

	LOAD_DBC("DBC/Map.dbc", mapentryFormat, true, dbcMap, true);

	LOAD_DBC("DBC/AuctionHouse.dbc", auctionhousedbcFormat, true, dbcAuctionHouse, false);

	LOAD_DBC("DBC/ItemRandomSuffix.dbc", itemrandomsuffixformat, true, dbcItemRandomSuffix, false);

	LOAD_DBC("DBC/RandPropPoints.dbc", randompropopointsfmt, true, dbcRandomPropertyPoints, false);

	LOAD_DBC("DBC/ItemReforge.dbc", itemreforgeformat, true, dbcItemReforge, false);

	LOAD_DBC("DBC/gtCombatRatings.dbc", gtClassfloatformat, false, dbcCombatRating, false);

	LOAD_DBC("DBC/ChatChannels.dbc", chatchannelformat, true, dbcChatChannels, true);

	LOAD_DBC("DBC/DurabilityQuality.dbc", durabilityqualityFormat, true, dbcDurabilityQuality, false);

	LOAD_DBC("DBC/DurabilityCosts.dbc", durabilitycostsFormat, true, dbcDurabilityCosts, false);

	LOAD_DBC("DBC/BankBagSlotPrices.dbc", bankslotpriceformat, true, dbcBankSlotPrices, false);

	//LOAD_DBC("DBC/StableSlotPrices.dbc", bankslotpriceformat, true, dbcStableSlotPrices, false);

	LOAD_DBC("DBC/gtChanceToMeleeCrit.dbc", gtClassfloatformat, false, dbcMeleeCrit, false);

	LOAD_DBC("DBC/gtChanceToMeleeCritBase.dbc", gtClassfloatformat, false, dbcMeleeCritBase, false);

	LOAD_DBC("DBC/gtChanceToSpellCrit.dbc", gtClassfloatformat, false, dbcSpellCrit, false);

	LOAD_DBC("DBC/gtChanceToSpellCritBase.dbc", gtClassfloatformat, false, dbcSpellCritBase, false);

	LOAD_DBC("DBC/gtRegenMPPerSpt.dbc", gtClassfloatformat, false, dbcMPRegenBase, false); //it's not a mistake.

	//LOAD_DBC("DBC/gtOCTRegenHP.dbc", gtfloatformat, false, dbcHPRegen, false); //it's not a mistake.

	LOAD_DBC("DBC/AreaTrigger.dbc", areatriggerformat, true, dbcAreaTrigger, true);

	LOAD_DBC("DBC/QuestXP.dbc", questxpformat, false, dbcQuestXP, true);

	LOAD_DBC("DBC/QuestFactionReward.dbc", questrewrepformat, false, dbcQuestRewRep, true);

	LOAD_DBC("DBC/CharTitles.dbc", chartitleFormat, true, dbcCharTitle, true);

	LOAD_DBC("DBC/MailTemplate.dbc", mailTemplateEntryFormat, true, dbcMailTemplate, true);

	LOAD_DBC("DBC/SummonProperties.dbc", summonpropertiesformat, true, dbcSummonProperties, false);

	return true;
}

uint32 *SpellEntry::GetSpellGroupType()
{
	return SpellGroupType;
}

uint32 SpellEntry::GetRequiresSpellFocus()
{
	if( SpellTargetRestrictionsId )
	{
		SpellCastingRequirementsEntry *str = dbcSpellCastingRequirements.LookupEntryForced( SpellTargetRestrictionsId );
		if( str )
			return str->RequiresSpellFocus;
	}
	return 0;
}

uint32 *SpellEntry::GetTotem()
{
	if( SpellTotemsId )
	{
		SpellTotemsEntry *ste =dbcSpellTotems.LookupEntryForced( SpellTotemsId );
		if( ste )
			return ste->Totem;
	}
	return 0;
}

int32 *SpellEntry::GetReagent()
{
	if( SpellReagentsId )
	{
		SpellReagentsEntry *sre = dbcSpellReagents.LookupEntryForced( SpellReagentsId );
		if( sre )
			return &sre->Reagent[0];
	}
	return 0;
}

uint32 *SpellEntry::GetReagentCount()
{
	if( SpellReagentsId )
	{
		SpellReagentsEntry *sre =dbcSpellReagents.LookupEntryForced( SpellReagentsId );
		if( sre )
			return sre->ReagentCount;
	}
	return 0;
}

int32 SpellEntry::GetEquippedItemClass()
{
	if( SpellEquippedItemsId )
	{
		SpellEquippedItemsEntry *see =dbcSpellEquippedItems.LookupEntryForced( SpellEquippedItemsId );
		if( see )
			return see->EquippedItemClass;
	}
	return -1;
}

int32 SpellEntry::GetEquippedItemSubClass()
{
	if( SpellEquippedItemsId )
	{
		SpellEquippedItemsEntry *see =dbcSpellEquippedItems.LookupEntryForced( SpellEquippedItemsId );
		if( see )
			return see->EquippedItemSubClass;
	}
	return -1;
}

uint32 SpellEntry::GetRequiredItemFlags()
{
	if( SpellEquippedItemsId )
	{
		SpellEquippedItemsEntry *see =dbcSpellEquippedItems.LookupEntryForced( SpellEquippedItemsId );
		if( see )
			return see->RequiredItemFlags;
	}
	return 0;
}

uint32 SpellEntry::GetDispelType()
{
	if( SpellCategoriesId )
	{
		SpellCategoriesEntry *sce = dbcSpellCategories.LookupEntryForced( SpellCategoriesId );
		if( sce )
			return sce->DispelType;
	}
	return 0;
}
