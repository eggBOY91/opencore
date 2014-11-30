/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2008-2012 <http://www.ArcEmu.org/>
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
#include "git_version.h"

uint64 MAKE_NEW_GUID(uint32 l, uint32 e, uint32 h)
{
    return uint64(uint64(l) | (uint64(e) << 32) | (uint64(h) << ((h == 0xF101 || h == 0xF102) ? 48 : 52)));
}

inline uint8 ObfuscateByte( uint8 x ) 
{
	return ( x^0x01 ); //!!obfuscating 0 might crash the client sometimes
}

inline void GUID_un_obfuscate( uint64 &guid )
{
	uint8 *guid_bytes = (uint8 *)&guid;
	for( uint32 i=0;i<8;i++)
		if( guid_bytes[i] )
			guid_bytes[i] = ObfuscateByte( guid_bytes[i] );
}

inline void GUID_un_obfuscate( uint8 guid_bytes[8] )
{
	for( uint32 i=0;i<8;i++)
		if( guid_bytes[i] )
			guid_bytes[i] = ObfuscateByte( guid_bytes[i] );
}

inline void GUID_obfuscate( uint64 &guid )
{
	GUID_un_obfuscate( guid );
}

inline void GUID_obfuscate( uint8 guid_bytes[8] )
{
	for( uint32 i=0;i<8;i++)
		guid_bytes[i] = ObfuscateByte( guid_bytes[i] );
}

LoginErrorCode VerifyName(const char* name, size_t nlen)
{
	const char* p;
	size_t i;

	static const char* bannedCharacters = "\t\v\b\f\a\n\r\\\"\'\? <>[](){}_=+-|/!@#$%^&*~`.,0123456789\0";
	static const char* allowedCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if(sWorld.m_limitedNames)
	{
		if(nlen == 0)
			return E_CHAR_NAME_NO_NAME;
		else if(nlen < 2)
			return E_CHAR_NAME_TOO_SHORT;
		else if(nlen > 12)
			return E_CHAR_NAME_TOO_LONG;

		for(i = 0; i < nlen; ++i)
		{
			p = allowedCharacters;
			for(; *p != 0; ++p)
			{
				if(name[i] == *p)
					goto cont;
			}
			return E_CHAR_NAME_INVALID_CHARACTER;
		cont:
			continue;
		}
	}
	else
	{
		for(i = 0; i < nlen; ++i)
		{
			p = bannedCharacters;
			while(*p != 0 && name[i] != *p && name[i] != 0)
				++p;

			if(*p != 0)
				return E_CHAR_NAME_INVALID_CHARACTER;
		}
	}

	return E_CHAR_NAME_SUCCESS;
}

bool ChatHandler::HandleRenameAllCharacter(const char* args, WorldSession* m_session)
{
	uint32 uCount = 0;
	uint32 ts = getMSTime();
	QueryResult* result = CharacterDatabase.Query("SELECT guid, name FROM characters");
	if(result)
	{
		do
		{
			uint32 uGuid = result->Fetch()[0].GetUInt32();
			const char* pName = result->Fetch()[1].GetString();
			size_t szLen = strlen(pName);

			if(VerifyName(pName, szLen) != E_CHAR_NAME_SUCCESS)
			{
				LOG_DEBUG("renaming character %s, %u", pName, uGuid);
				Player* pPlayer = objmgr.GetPlayer(uGuid);
				if(pPlayer != NULL)
				{
					pPlayer->rename_pending = true;
					pPlayer->GetSession()->SystemMessage("Your character has had a force rename set, you will be prompted to rename your character at next login in conformance with server rules.");
				}

				CharacterDatabase.WaitExecute("UPDATE characters SET forced_rename_pending = 1 WHERE guid = %u", uGuid);
				++uCount;
			}

		}
		while(result->NextRow());
		delete result;
	}

	SystemMessage(m_session, "Procedure completed in %u ms. %u character(s) forced to rename.", getMSTime() - ts, uCount);
	return true;
}

void CapitalizeString(string & arg)
{
	if(arg.length() == 0) return;
	arg[0] = static_cast<char>(toupper(arg[0]));
	for(uint32 x = 1; x < arg.size(); ++x)
		arg[x] = static_cast<char>(tolower(arg[x]));
}

void WorldSession::CharacterEnumProc(QueryResult* result)
{
struct player_item
{
    uint32 displayid;
	uint8 invtype;
	uint32 enchantment; // added in 2.4
};

    player_item items[INVENTORY_SLOT_BAG_END];
    int8 slot;
    int8 containerslot;
    uint32 i;
    ItemPrototype* proto;
    QueryResult* res;
    uint32 num = 0;
    uint8 race;
    uint32 MaxAvailCharLevel = 0;
    _side = -1;
    has_dk = false;

uint32 packetSize = 0;

if (result)
    packetSize = result->GetRowCount() * 200;
else
    packetSize = 270; // value taken from cmangos

WorldPacket data (SMSG_CHAR_ENUM, packetSize);

ByteBuffer buffer;

data.writeBits(0, 23);
data.writeBit(1);
data.writeBits(result ? result->GetRowCount() : 0, 17);


if (result)
{
    //uint64 guid;
    uint8 Class;
    uint32 playerBytes2;
    //uint32 flags;
    //uint32 banned;
    //uint32 ForceRename;
    Field* fields;
    
    string name;
    uint32 playerBytes;
    uint8 gender;
    uint8 level;
    uint32 zone; // zoneId
    uint32 mapId;
    float x;
    float y;
    float z;
    uint32 guildId;
    uint32 playerFlags;
    uint32 atLoginFlags;
    uint8 skin, face, hairStyle, hairColor, facialHair;

do
{
	//uint8 guid[8];
    fields     = result->Fetch();
    uint64 guid;
	//uint64 oldGuid = fields[0].GetUInt32(); // uint64 or uint32?
	guid = MAKE_NEW_GUID(fields[0].GetUInt32(), 0, 0x000); // 4.3.4
    name       = fields[7].GetString(); // 4.3.4
    race       = fields[2].GetUInt8(); // 4.3.4
    Class      = fields[3].GetUInt8(); // 4.3.4
    gender     = fields[4].GetUInt8(); // 4.3.4

	uint8 guid_a[8];
	*(uint64*)guid_a = MAKE_NEW_GUID(fields[0].GetUInt32(), 0, 0x000);

	uint32 _GID = fields[18].GetUInt32(); // guildId // 4.3.4
    
            uint8 guidb[8];
			*(uint64*)guidb = MAKE_NEW_GUID(_GID, 0, _GID ? uint32(0x1FF) : 0);

	//uint64 guidb = MAKE_NEW_GUID(fields[13].GetUInt32(), 0, guildId ? uint32(0x1FF) : 0);

			uint8 guidb0, guidb1, guidb2, guidb3, guidb4, guidb5, guidb6, guidb7, guid0, guid1, guid2, guid3, guid4, guid5, guid6, guid7;

			guidb0 = guidb[0];
			guidb1 = guidb[1];
			guidb2 = guidb[2];
			guidb3 = guidb[3];
			guidb4 = guidb[4];
			guidb5 = guidb[5];
			guidb6 = guidb[6];
			guidb7 = guidb[7];

			guid0 = guid_a[0];
			guid1 = guid_a[1];
			guid2 = guid_a[2];
			guid3 = guid_a[3];
			guid4 = guid_a[4];
			guid5 = guid_a[5];
			guid6 = guid_a[6];
			guid7 = guid_a[7];


			
	data.writeBit(guid3);
    data.writeBit(guidb1);
    data.writeBit(guidb7);
    data.writeBit(guidb2);
    data.writeBits(uint32(name.length()), 7);
    data.writeBit(guid4);
    data.writeBit(guid7);
    data.writeBit(guidb3);
    data.writeBit(guid5);
    data.writeBit(guidb6);
    data.writeBit(guid1);
    data.writeBit(guidb5);
    data.writeBit(guidb4);
    data.writeBit(fields[15].GetUInt32() & 0x20); // atLoginFlags & 0x20 = AT_LOGIN_FIRST (trinitycore) // not 4.3.4, what to do?
    data.writeBit(guid0);
    data.writeBit(guid2);
    data.writeBit(guid6);
    data.writeBit(guidb0);
			
    
    if(_side < 0)
    		{
				// work out the side
				static uint8 sides[RACE_DRAENEI + 2] = {0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0};
				_side = sides[race];
			}
            
            // Death Knight starting information
    		// Note: To change what level is required to make a dk change the >= 55 to something.
			// For example >=80 would require a level 80 to create a DK
			has_level_55_char = has_level_55_char || (fields[7].GetUInt8() >= 55);
			has_dk = has_dk || (Class == 6);

    
    playerBytes = fields[5].GetUInt32(); // 4.3.4
    playerBytes2 = fields[6].GetUInt32(); // 4.3.4

    skin       = uint8(playerBytes & 0xFF); // 4.3.4
    face       = uint8((playerBytes >> 8) & 0xFF); // 4.3.4
    hairStyle  = uint8((playerBytes >> 16) & 0xFF); // 4.3.4
    hairColor  = uint8((playerBytes >> 24) & 0xFF); // 4.3.4
    facialHair = uint8(playerBytes2 & 0xFF); // 4.3.4
    
    level      = fields[1].GetUInt8(); // 4.3.4
    zone       = fields[12].GetUInt16(); // 4.3.4 // zoneId
    mapId      = uint32(fields[11].GetUInt16()); // 4.3.4
    x          = fields[8].GetFloat(); // 4.3.4
    y          = fields[9].GetFloat(); // 4.3.4
    z          = fields[10].GetFloat(); // 4.3.4
    guildId    = fields[18].GetUInt32(); // 4.3.4
    playerFlags = fields[14].GetUInt32(); // 4.3.4
    //atLoginFlags = fields[15].GetUInt32();
	atLoginFlags = 0; 
    
    uint32 charFlags = 0;
    
    // implement banned flag
    // flags from 3.3.5a, maybe have changed
    
   /* if(atLoginFlags != 0)
    			char_flags |= 0x00002000;	//Character is dead
			if(flags & PLAYER_FLAG_NOHELM)
				char_flags |= 0x00000400;	//Helm not displayed
			if(flags & PLAYER_FLAG_NOCLOAK)
				char_flags |= 0x00000800;	//Cloak not displayed*/
                

    // toDo: show pet
    
    uint32 petDisplayId = 0;
    uint32 petLevel     = 0;
    uint32 petFamily    = 0;
    
    buffer << uint8(Class);
    
    res = CharacterDatabase.Query("SELECT containerslot, slot, entry, enchantments FROM playeritems WHERE ownerguid=%u and containerslot=-1 and slot < 23", Arcemu::Util::GUID_LOPART(guid));

    		memset(items, 0, sizeof(items));
			uint32 enchantid;
			EnchantEntry * enc;
			if(res)
			{
				do 
				{
					containerslot = res->Fetch()[0].GetInt8();
					slot = res->Fetch()[1].GetInt8();
					if( containerslot == -1 && slot < INVENTORY_SLOT_BAG_END && slot >= EQUIPMENT_SLOT_START )
					{
						proto = ItemPrototypeStorage.LookupEntry(res->Fetch()[2].GetUInt32());
						if( proto )
						{
							if( !( slot == EQUIPMENT_SLOT_HEAD && ( playerFlags & ( uint32 )PLAYER_FLAG_NOHELM ) != 0 ) && 
								!( slot == EQUIPMENT_SLOT_BACK && ( playerFlags & ( uint32 )PLAYER_FLAG_NOCLOAK ) != 0 ) ) 
							{
								items[slot].displayid = proto->DisplayInfoID;
								items[slot].invtype = proto->InventoryType;
								// weapon glows
								if( slot == EQUIPMENT_SLOT_MAINHAND || slot == EQUIPMENT_SLOT_OFFHAND )
								{
									// get enchant visual ID
									const char * enchant_field = res->Fetch()[3].GetString();	
									if( sscanf( enchant_field , "%u,0,0;" , (unsigned int *)&enchantid ) == 1 && enchantid > 0 )
									{
										enc = dbcEnchant.LookupEntry( enchantid );
										if( enc != NULL )
											items[slot].enchantment = enc->visual;
										else
											items[slot].enchantment = 0;;
									}
								}
							}
						}
					}
				} while(res->NextRow());
				delete res;
				res = NULL;
			}

			for( i = 0; i < INVENTORY_SLOT_BAG_END; ++i ) //23 * 5 bytes
			{
			    buffer << uint8(items[i].invtype);
				buffer << uint32(items[i].displayid);
                buffer << uint32(items[i].enchantment);
				}

                buffer << uint32(petFamily);
                
				//buffer.WriteByteSeq(guidb[2]);
				buffer.WriteByteSeq(guidb2);

                //buffer << uint8(slot);
				buffer << uint8(0);
                buffer << uint8(hairStyle);
                
				//buffer.WriteByteSeq(guidb[3]);
				buffer.WriteByteSeq(guidb3);
				
                buffer << uint32(petDisplayId);
                buffer << uint32(charFlags);
                buffer << uint8(hairColor);

                //buffer.WriteByteSeq(guid[4]);
				buffer.WriteByteSeq(guid4);

                buffer << uint32(mapId);

                //buffer.WriteByteSeq(guidb[5]);
				buffer.WriteByteSeq(guidb5);

                buffer << float(z);

                //buffer.WriteByteSeq(guidb[6]);
				buffer.WriteByteSeq(guidb6);

                buffer << uint32(petLevel);

                //buffer.WriteByteSeq(guid[3]);
				buffer.WriteByteSeq(guid3);

                buffer << float(y);
                buffer << uint32(0x00000000); // customizationFlag (toDo: implement)
                buffer << uint8(facialHair);

                //buffer.WriteByteSeq(guid[7]);
				buffer.WriteByteSeq(guid7);

                buffer << uint8(gender);
                buffer.append(name.c_str(), name.length());
                buffer << uint8(face);

                /*buffer.WriteByteSeq(guid[0]);
                buffer.WriteByteSeq(guid[2]);
				buffer.WriteByteSeq(guidb[1]);
				buffer.WriteByteSeq(guidb[7]);*/

				buffer.WriteByteSeq(guid0);
				buffer.WriteByteSeq(guid2);
				buffer.WriteByteSeq(guidb1);
				buffer.WriteByteSeq(guidb7);

				buffer << float(x);                                    // X
				buffer << uint8(skin);                                 // Skin
				buffer << uint8(race);                                 // Race
				buffer << uint8(level);                                // Level

				/*buffer.WriteByteSeq(guid[6]);
				buffer.WriteByteSeq(guidb[4]);
				buffer.WriteByteSeq(guidb[0]);
				buffer.WriteByteSeq(guid[5]);
				buffer.WriteByteSeq(guid[1]);*/

				buffer.WriteByteSeq(guid6);
				buffer.WriteByteSeq(guidb4);
				buffer.WriteByteSeq(guidb0);
				buffer.WriteByteSeq(guid5);
				buffer.WriteByteSeq(guid1);

				buffer << uint32(zone);
} while (result->NextRow()); // end do while

data.flushBits();
data.append(buffer);

} // end if

SendPacket(&data);
}

void WorldSession::HandleCharEnumOpcode(WorldPacket & recv_data)
{
    AsyncQuery * q = new AsyncQuery( new SQLClassCallbackP1<World, uint32>(World::getSingletonPtr(), &World::CharacterEnumProc, GetAccountId()) );
    q->AddQuery("SELECT guid, level, race, class, gender, bytes, bytes2, name, positionX, positionY, positionZ, mapId, zoneId, banned, restState, deathstate, forced_rename_pending, player_flags, guild_data.guildid FROM characters LEFT JOIN guild_data ON characters.guid = guild_data.playerid WHERE acct=%u ORDER BY guid LIMIT 10", GetAccountId());
	CharacterDatabase.QueueAsyncQuery(q);
}

void WorldSession::LoadAccountDataProc(QueryResult* result)
{
	size_t len;
	const char* data;
	char* d;

	if(!result)
	{
		CharacterDatabase.Execute("INSERT INTO account_data VALUES(%u, '', '', '', '', '', '', '', '', '')", _accountId);
		return;
	}

	for(uint32 i = 0; i < 7; ++i)
	{
		data = result->Fetch()[1 + i].GetString();
		len = data ? strlen(data) : 0;
		if(len > 1)
		{
			d = new char[len + 1];
			memcpy(d, data, len + 1);
			SetAccountData(i, d, true, (uint32)len);
		}
	}
}

/*void WorldSession::HandleCharCreateOpcode(WorldPacket & recv_data)
{
	printf("Char create opcode!!");
	CHECK_PACKET_SIZE(recv_data, 10);
	std::string name;
	uint8 race, class_;

	recv_data >> name >> race >> class_;
	recv_data.rpos(0);


	LoginErrorCode res = VerifyName(name.c_str(), name.length());
	if(res != E_CHAR_NAME_SUCCESS)
	{
		OutPacket(SMSG_CHAR_CREATE, 1, &res);
		return;
	}

	res = g_characterNameFilter->Parse(name, false) ? E_CHAR_NAME_PROFANE : E_CHAR_NAME_SUCCESS;
	if(res != E_CHAR_NAME_SUCCESS)
	{
		OutPacket(SMSG_CHAR_CREATE, 1, &res);
		return;
	}

	res = objmgr.GetPlayerInfoByName(name.c_str()) == NULL ? E_CHAR_CREATE_SUCCESS : E_CHAR_CREATE_NAME_IN_USE;
	if(res != E_CHAR_CREATE_SUCCESS)
	{
		OutPacket(SMSG_CHAR_CREATE, 1, &res);
		return;
	}

	res = sHookInterface.OnNewCharacter(race, class_, this, name.c_str()) ? E_CHAR_CREATE_SUCCESS : E_CHAR_CREATE_ERROR;
	if(res != E_CHAR_CREATE_SUCCESS)
	{
		OutPacket(SMSG_CHAR_CREATE, 1, &res);
		return;
	}

	if( class_ == DEATHKNIGHT && !HasFlag(ACCOUNT_FLAG_XPACK_02) )
	{
		OutPacket(SMSG_CHAR_CREATE, 1, CHAR_CREATE_EXPANSION );
		return;
	}

	QueryResult * result = CharacterDatabase.Query("SELECT COUNT(*) FROM banned_names WHERE name = '%s'", CharacterDatabase.EscapeString(name).c_str());
	if(result)
	{
		if(result->Fetch()[0].GetUInt32() > 0)
		{
			// That name is banned!
			OutPacket( SMSG_CHAR_CREATE, 1, CHAR_NAME_PROFANE );
			delete result;
			result = NULL;
			return;
		}
		delete result;
		result = NULL;
	}

	// Check if player got Death Knight already on this realm.
	if(Config.OptionalConfig.GetBoolDefault("ClassOptions" , "DeathKnightLimit" , true) && has_dk
	        && (class_ == DEATHKNIGHT))
	{
		OutPacket(SMSG_CHAR_CREATE, 1, CHAR_CREATE_UNIQUE_CLASS_LIMIT);
		return;
	}

	// loading characters

	//checking number of chars is useless since client will not allow to create more than 10 chars
	//as the 'create' button will not appear (unless we want to decrease maximum number of characters)
	//Zack : well i could create a bot to create a lot of chars
	result = CharacterDatabase.Query( "SELECT COUNT(*) FROM characters WHERE acct = %u", GetAccountId() );
	if( result )
	{
		if( result->Fetch()[0].GetUInt32() >= 10 )
		{
			// We can't make any more characters.
			OutPacket( SMSG_CHAR_CREATE, 1, CHAR_CREATE_SERVER_LIMIT );
			delete result;
			result = NULL;
			return;
		}
		delete result;
		result = NULL;
	}

	Player * pNewChar = objmgr.CreatePlayer(class_);
	pNewChar->SetSession(this);
	if(!pNewChar->Create( recv_data ))
	{
		// failed.
		pNewChar->ok_to_remove = true;
		delete pNewChar;
		OutPacket( SMSG_CHAR_CREATE, 1, CHAR_CREATE_FAILED );
		return;
	}

	//Same Faction limitation only applies to PVP and RPPVP realms :)
	uint32 realmType = sLogonCommHandler.GetRealmType();
	if(!HasGMPermissions() && realmType == REALMTYPE_PVP && _side >= 0 && !sWorld.crossover_chars)  // ceberwow fixed bug
	{
		if((pNewChar->IsTeamAlliance() && (_side == 1)) || (pNewChar->IsTeamHorde() && (_side == 0)))
		{
			pNewChar->ok_to_remove = true;
			delete pNewChar;
			OutPacket(SMSG_CHAR_CREATE, 1, CHAR_CREATE_PVP_TEAMS_VIOLATION);
			return;
		}
	}

	//Check if player has a level 55 or higher character on this realm and allow him to create DK.
	//This check can be turned off in optional.conf
	if(Config.OptionalConfig.GetBoolDefault("ClassOptions" , "DeathKnightPreReq" , false) && !has_level_55_char
	        && (class_ == DEATHKNIGHT))
	{
		pNewChar->ok_to_remove = true;
		delete pNewChar;
		
		OutPacket(SMSG_CHAR_CREATE, 1, CHAR_CREATE_LEVEL_REQUIREMENT);
		return;
	}

	pNewChar->UnSetBanned();
	pNewChar->addSpell(22027);	  // Remove Insignia

	if(pNewChar->getClass() == WARLOCK)
	{
		pNewChar->AddSummonSpell(416, 3110);		// imp fireball
		pNewChar->AddSummonSpell(417, 19505);
		pNewChar->AddSummonSpell(1860, 3716);
		pNewChar->AddSummonSpell(1863, 7814);
	}

	pNewChar->SaveToDB(true);	

	PlayerInfo* pn = new PlayerInfo ;
	pn->guid = pNewChar->GetLowGUID();
	pn->name = strdup(pNewChar->GetName());
	pn->cl = pNewChar->getClass();
	pn->race = pNewChar->getRace();
	pn->gender = pNewChar->getGender();
	pn->acct = GetAccountId();
	pn->m_Group = 0;
	pn->subGroup = 0;
	pn->m_loggedInPlayer = NULL;
	pn->team = pNewChar->GetTeam();
	pn->guild = NULL;
	pn->guildRank = NULL;
	pn->guildMember = NULL;
	pn->lastOnline = UNIXTIME;

	objmgr.AddPlayerInfo(pn);

	pNewChar->ok_to_remove = true;
	delete  pNewChar;

	OutPacket( SMSG_CHAR_CREATE, 1, CHAR_CREATE_SUCCESS );

	sLogonCommHandler.UpdateAccountCount( GetAccountId(), 1 );
}*/

void WorldSession::HandleCharCreateOpcode(WorldPacket & recv_data)
{
	CHECK_PACKET_SIZE(recv_data, 10);
	std::string name;
	uint8 race, class_;

	recv_data >> name >> race >> class_;
	recv_data.rpos(0);


	LoginErrorCode res = VerifyName(name.c_str(), name.length());
	if(res != E_CHAR_NAME_SUCCESS)
	{
		OutPacket(SMSG_CHAR_CREATE, 1, &res);
		return;
	}

	res = g_characterNameFilter->Parse(name, false) ? E_CHAR_NAME_PROFANE : E_CHAR_NAME_SUCCESS;
	if(res != E_CHAR_NAME_SUCCESS)
	{
		OutPacket(SMSG_CHAR_CREATE, 1, &res);
		return;
	}

	res = objmgr.GetPlayerInfoByName(name.c_str()) == NULL ? E_CHAR_CREATE_SUCCESS : E_CHAR_CREATE_NAME_IN_USE;
	if(res != E_CHAR_CREATE_SUCCESS)
	{
		OutPacket(SMSG_CHAR_CREATE, 1, &res);
		return;
	}

	res = sHookInterface.OnNewCharacter(race, class_, this, name.c_str()) ? E_CHAR_CREATE_SUCCESS : E_CHAR_CREATE_ERROR;
	if(res != E_CHAR_CREATE_SUCCESS)
	{
		OutPacket(SMSG_CHAR_CREATE, 1, &res);
		return;
	}

	QueryResult* result = CharacterDatabase.Query("SELECT COUNT(*) FROM banned_names WHERE name = '%s'", CharacterDatabase.EscapeString(name).c_str());
	if(result)
	{
		if(result->Fetch()[0].GetUInt32() > 0)
		{
			// That name is banned!
			OutPacket(SMSG_CHAR_CREATE, 1, CHAR_NAME_PROFANE);
			delete result;
			return;
		}
		delete result;
	}

	// Check if player got Death Knight already on this realm.
	if(Config.OptionalConfig.GetBoolDefault("ClassOptions" , "DeathKnightLimit" , true) && has_dk
	        && (class_ == DEATHKNIGHT))
	{
		OutPacket(SMSG_CHAR_CREATE, 1, CHAR_CREATE_UNIQUE_CLASS_LIMIT);
		return;
	}

	// loading characters

	// Check the number of characters, so we can't make over 10.
	// They're able to manage to create >10 sometimes, not exactly sure how ..

	result = CharacterDatabase.Query("SELECT COUNT(*) FROM characters WHERE acct = %u", GetAccountId());
	if(result)
	{
		if(result->Fetch()[0].GetUInt32() >= 10)
		{
			// We can't make any more characters.
			OutPacket(SMSG_CHAR_CREATE, 1, CHAR_CREATE_SERVER_LIMIT);
			delete result;
			return;
		}
		delete result;
	}

	Player* pNewChar = objmgr.CreatePlayer(class_);
	pNewChar->SetSession(this);
	if(!pNewChar->Create(recv_data))
	{
		// failed.
		pNewChar->ok_to_remove = true;
		delete pNewChar;
		OutPacket(SMSG_CHAR_CREATE, 1, CHAR_CREATE_FAILED);
		return;
	}

	//Same Faction limitation only applies to PVP and RPPVP realms :)
	uint32 realmType = sLogonCommHandler.GetRealmType();
	if(!HasGMPermissions() && realmType == REALMTYPE_PVP && _side >= 0 && !sWorld.crossover_chars)  // ceberwow fixed bug
	{
		if((pNewChar->IsTeamAlliance() && (_side == 1)) || (pNewChar->IsTeamHorde() && (_side == 0)))
		{
			pNewChar->ok_to_remove = true;
			delete pNewChar;
			OutPacket(SMSG_CHAR_CREATE, 1, CHAR_CREATE_PVP_TEAMS_VIOLATION);
			return;
		}
	}

	//Check if player has a level 55 or higher character on this realm and allow him to create DK.
	//This check can be turned off in optional.conf
	if(Config.OptionalConfig.GetBoolDefault("ClassOptions" , "DeathKnightPreReq" , false) && !has_level_55_char
	        && (class_ == DEATHKNIGHT))
	{
		pNewChar->ok_to_remove = true;
		delete pNewChar;
		/*
		WorldPacket data(1);
		data.SetOpcode(SMSG_CHAR_CREATE);
		data << (uint8)56 + 1; // This errorcode is not the actual one. Need to find a real error code.
		SendPacket( &data );
		*/
		OutPacket(SMSG_CHAR_CREATE, 1, CHAR_CREATE_LEVEL_REQUIREMENT);
		return;
	}

	pNewChar->UnSetBanned();
	pNewChar->addSpell(22027);	  // Remove Insignia

	if(pNewChar->getClass() == WARLOCK)
	{
		pNewChar->AddSummonSpell(416, 3110);		// imp fireball
		pNewChar->AddSummonSpell(417, 19505);
		pNewChar->AddSummonSpell(1860, 3716);
		pNewChar->AddSummonSpell(1863, 7814);
	}

	pNewChar->SaveToDB(true);

	PlayerInfo* pn = new PlayerInfo ;
	pn->guid = pNewChar->GetLowGUID();
	pn->name = strdup(pNewChar->GetName());
	pn->cl = pNewChar->getClass();
	pn->race = pNewChar->getRace();
	pn->gender = pNewChar->getGender();
	pn->acct = GetAccountId();
	pn->m_Group = 0;
	pn->subGroup = 0;
	pn->m_loggedInPlayer = NULL;
	pn->team = pNewChar->GetTeam();
	pn->guild = NULL;
	pn->guildRank = NULL;
	pn->guildMember = NULL;
	pn->lastOnline = UNIXTIME;
	objmgr.AddPlayerInfo(pn);

	pNewChar->ok_to_remove = true;
	delete  pNewChar;

	OutPacket(SMSG_CHAR_CREATE, 1, CHAR_CREATE_SUCCESS);

	sLogonCommHandler.UpdateAccountCount(GetAccountId(), 1);
}



void WorldSession::HandleCharDeleteOpcode(WorldPacket & recv_data)
{
	CHECK_PACKET_SIZE(recv_data, 8);
	uint8 fail = E_CHAR_DELETE_SUCCESS;

	uint64 guid;
	recv_data >> guid;

	if(objmgr.GetPlayer((uint32)guid) != NULL)
	{
		// "Char deletion failed"
		fail = E_CHAR_DELETE_FAILED;
	}
	else
	{
		fail = DeleteCharacter((uint32)guid);
	}
	OutPacket(SMSG_CHAR_DELETE, 1, &fail);
}

uint8 WorldSession::DeleteCharacter(uint32 guid)
{
	PlayerInfo* inf = objmgr.GetPlayerInfo(guid);
	if(inf != NULL && inf->m_loggedInPlayer == NULL)
	{
		QueryResult* result = CharacterDatabase.Query("SELECT name FROM characters WHERE guid = %u AND acct = %u", (uint32)guid, _accountId);
		if(!result)
			return E_CHAR_DELETE_FAILED;

		string name = result->Fetch()[0].GetString();
		delete result;

		if(inf->guild)
		{
			if(inf->guild->GetGuildLeader() == inf->guid)
				return E_CHAR_DELETE_FAILED_GUILD_LEADER;
			else
				inf->guild->RemoveGuildMember(inf, NULL);
		}

		for(int i = 0; i < NUM_CHARTER_TYPES; ++i)
		{
			Charter* c = objmgr.GetCharterByGuid(guid, (CharterTypes)i);
			if(c != NULL)
				c->RemoveSignature((uint32)guid);
		}


		for(int i = 0; i < NUM_ARENA_TEAM_TYPES; ++i)
		{
			ArenaTeam* t = objmgr.GetArenaTeamByGuid((uint32)guid, i);
			if(t != NULL && t->m_leader == guid)
				return E_CHAR_DELETE_FAILED_ARENA_CAPTAIN;
			if(t != NULL)
				t->RemoveMember(inf);
		}

		/*if( _socket != NULL )
			sPlrLog.write("Account: %s | IP: %s >> Deleted player %s", GetAccountName().c_str(), GetSocket()->GetRemoteIP().c_str(), name.c_str());*/

		sPlrLog.writefromsession(this, "deleted character %s (GUID: %u)", name.c_str(), (uint32)guid);

		CharacterDatabase.WaitExecute("DELETE FROM characters WHERE guid = %u", (uint32)guid);

		Corpse* c = objmgr.GetCorpseByOwner((uint32)guid);
		if(c)
			CharacterDatabase.Execute("DELETE FROM corpses WHERE guid = %u", c->GetLowGUID());

		CharacterDatabase.Execute("DELETE FROM playeritems WHERE ownerguid=%u", (uint32)guid);
		CharacterDatabase.Execute("DELETE FROM gm_tickets WHERE playerguid = %u", (uint32)guid);
		CharacterDatabase.Execute("DELETE FROM playerpets WHERE ownerguid = %u", (uint32)guid);
		CharacterDatabase.Execute("DELETE FROM playerpetspells WHERE ownerguid = %u", (uint32)guid);
		CharacterDatabase.Execute("DELETE FROM tutorials WHERE playerId = %u", (uint32)guid);
		CharacterDatabase.Execute("DELETE FROM questlog WHERE player_guid = %u", (uint32)guid);
		CharacterDatabase.Execute("DELETE FROM playercooldowns WHERE player_guid = %u", (uint32)guid);
		CharacterDatabase.Execute("DELETE FROM mailbox WHERE player_guid = %u", (uint32)guid);
		CharacterDatabase.Execute("DELETE FROM social_friends WHERE character_guid = %u OR friend_guid = %u", (uint32)guid, (uint32)guid);
		CharacterDatabase.Execute("DELETE FROM social_ignores WHERE character_guid = %u OR ignore_guid = %u", (uint32)guid, (uint32)guid);
		CharacterDatabase.Execute("DELETE FROM character_achievement WHERE guid = '%u' AND achievement NOT IN (457, 467, 466, 465, 464, 463, 462, 461, 460, 459, 458, 1404, 1405, 1406, 1407, 1408, 1409, 1410, 1411, 1412, 1413, 1415, 1414, 1416, 1417, 1418, 1419, 1420, 1421, 1422, 1423, 1424, 1425, 1426, 1427, 1463, 1400, 456, 1402)", (uint32)guid);
		CharacterDatabase.Execute("DELETE FROM character_achievement_progress WHERE guid = '%u'", (uint32)guid);
		CharacterDatabase.Execute("DELETE FROM playerspells WHERE GUID = '%u'", guid);
		CharacterDatabase.Execute("DELETE FROM playerdeletedspells WHERE GUID = '%u'", guid);
		CharacterDatabase.Execute("DELETE FROM playerreputations WHERE guid = '%u'", guid);
		CharacterDatabase.Execute("DELETE FROM playerskills WHERE GUID = '%u'", guid);

		/* remove player info */
		objmgr.DeletePlayerInfo((uint32)guid);
		return E_CHAR_DELETE_SUCCESS;
	}
	return E_CHAR_DELETE_FAILED;
}

void WorldSession::HandleCharRenameOpcode(WorldPacket & recv_data)
{
	WorldPacket data(SMSG_CHAR_RENAME, recv_data.size() + 1);

	uint64 guid;
	string name;
	recv_data >> guid >> name;

	PlayerInfo* pi = objmgr.GetPlayerInfo((uint32)guid);
	if(pi == 0) return;

	QueryResult* result = CharacterDatabase.Query("SELECT forced_rename_pending FROM characters WHERE guid = %u AND acct = %u",
	                      (uint32)guid, _accountId);
	if(result == 0)
	{
		delete result;
		return;
	}
	delete result;

	// Check name for rule violation.

	LoginErrorCode err = VerifyName(name.c_str(), name.length());
	if(err != E_CHAR_NAME_SUCCESS)
	{
		data << uint8(err);
		data << guid << name;
		SendPacket(&data);
		return;
	}

	QueryResult* result2 = CharacterDatabase.Query("SELECT COUNT(*) FROM banned_names WHERE name = '%s'", CharacterDatabase.EscapeString(name).c_str());
	if(result2)
	{
		if(result2->Fetch()[0].GetUInt32() > 0)
		{
			// That name is banned!
			data << uint8(E_CHAR_NAME_PROFANE);
			data << guid << name;
			SendPacket(&data);
		}
		delete result2;
	}

	// Check if name is in use.
	if(objmgr.GetPlayerInfoByName(name.c_str()) != NULL)
	{
		data << uint8(E_CHAR_CREATE_NAME_IN_USE);
		data << guid << name;
		SendPacket(&data);
		return;
	}

	// correct capitalization
	CapitalizeString(name);
	objmgr.RenamePlayerInfo(pi, pi->name, name.c_str());

	sPlrLog.writefromsession(this, "a rename was pending. renamed character %s (GUID: %u) to %s.", pi->name, pi->guid, name.c_str());

	// If we're here, the name is okay.
	free(pi->name);
	pi->name = strdup(name.c_str());
	CharacterDatabase.WaitExecute("UPDATE characters SET name = '%s' WHERE guid = %u", name.c_str(), (uint32)guid);
	CharacterDatabase.WaitExecute("UPDATE characters SET forced_rename_pending = 0 WHERE guid = %u", (uint32)guid);

	data << uint8(E_RESPONSE_SUCCESS) << guid << name;
	SendPacket(&data);
}


void WorldSession::HandlePlayerLoginOpcode(WorldPacket & recv_data)
{
    //CHECK_PACKET_SIZE(recv_data, 8); // do we need this?
	//uint64 playerGuid = *(uint8*)playerGuid;

	LOG_DEBUG("WORLD: Recvd Player Logon Message");

	//recv_data >> playerGuid; // this is the GUID selected by the player

	// 15595
	uint8 playerGuid[8];
	
	playerGuid[2] = recv_data.readBit();
    playerGuid[3] = recv_data.readBit();
    playerGuid[0] = recv_data.readBit();
    playerGuid[6] = recv_data.readBit();
    playerGuid[4] = recv_data.readBit();
    playerGuid[5] = recv_data.readBit();
    playerGuid[1] = recv_data.readBit();
    playerGuid[7] = recv_data.readBit();

    recv_data.ReadByteSeq(playerGuid[2]);
    recv_data.ReadByteSeq(playerGuid[7]);
    recv_data.ReadByteSeq(playerGuid[0]);
    recv_data.ReadByteSeq(playerGuid[3]);
    recv_data.ReadByteSeq(playerGuid[5]);
    recv_data.ReadByteSeq(playerGuid[6]);
    recv_data.ReadByteSeq(playerGuid[1]);
    recv_data.ReadByteSeq(playerGuid[4]);

	uint64 pGuid = *(uint64*)playerGuid;

	if(objmgr.GetPlayer((uint32)playerGuid) != NULL || m_loggingInPlayer || _player)
	{
		// A character with that name already exists 0x3E
		uint8 respons = E_CHAR_LOGIN_DUPLICATE_CHARACTER;
		OutPacket(SMSG_CHARACTER_LOGIN_FAILED, 1, &respons);
		return;
	}

	// we make sure the guid is the correct one
	//printf("guid: %d\n", Arcemu::Util::GUID_LOPART(pGuid));

	AsyncQuery* q = new AsyncQuery(new SQLClassCallbackP0<WorldSession>(this, &WorldSession::LoadPlayerFromDBProc));
	q->AddQuery("SELECT guid,class FROM characters WHERE guid = %u AND forced_rename_pending = 0",Arcemu::Util::GUID_LOPART(pGuid)); // 0
	CharacterDatabase.QueueAsyncQuery(q);
}

void WorldSession::LoadPlayerFromDBProc(QueryResultVector & results)
{
	if(results.size() < 1)
	{
		uint8 respons = E_CHAR_LOGIN_NO_CHARACTER;
		OutPacket(SMSG_CHARACTER_LOGIN_FAILED, 1, &respons);
		return;
	}

	QueryResult* result = results[0].result;
	if(! result)
	{
		Log.Error("WorldSession::LoadPlayerFromDBProc", "Player login query failed!");
		uint8 respons = E_CHAR_LOGIN_NO_CHARACTER;
		OutPacket(SMSG_CHARACTER_LOGIN_FAILED, 1, &respons);
		return;
	}

	Field* fields = result->Fetch();

	uint64 playerGuid = fields[0].GetUInt64();
	uint8 _class = fields[1].GetUInt8();

	Player* plr = NULL;

	switch(_class)
	{
		case WARRIOR:
			plr = new Warrior(playerGuid);
			break;
		case PALADIN:
			plr = new Paladin(playerGuid);
			break;
		case HUNTER:
			plr = new Hunter(playerGuid);
			break;
		case ROGUE:
			plr = new Rogue(playerGuid);
			break;
		case PRIEST:
			plr = new Priest(playerGuid);
			break;
		case DEATHKNIGHT:
			plr = new DeathKnight(playerGuid);
			break;
		case SHAMAN:
			plr = new Shaman(playerGuid);
			break;
		case MAGE:
			plr = new Mage(playerGuid);
			break;
		case WARLOCK:
			plr = new Warlock(playerGuid);
			break;
		case DRUID:
			plr = new Druid(playerGuid);
			break;
	}

	if(plr == NULL)
	{
		Log.Error("WorldSession::LoadPlayerFromDBProc", "Class %u unknown!", _class);
		uint8 respons = E_CHAR_LOGIN_NO_CHARACTER;
		OutPacket(SMSG_CHARACTER_LOGIN_FAILED, 1, &respons);
		return;
	}

	plr->SetSession(this);

	m_bIsWLevelSet = false;

	Log.Debug("WorldSession", "Async loading player %u", (uint32)playerGuid);
	m_loggingInPlayer = plr;
	plr->LoadFromDB((uint32)playerGuid);
}

void WorldSession::FullLogin(Player* plr)
{
	Log.Debug("WorldSession", "Fully loading player %u", plr->GetLowGUID());

	SetPlayer(plr);
	m_MoverWoWGuid.Init(plr->GetGUID());

	MapMgr* mgr = sInstanceMgr.GetInstance(plr);
	if(mgr && mgr->m_battleground)
	{
		// Don't allow player to login into a bg that has ended or is full
		if(mgr->m_battleground->HasEnded() == true ||
		        mgr->m_battleground->HasFreeSlots(plr->GetTeamInitial(), mgr->m_battleground->GetType() == false))
		{
			mgr = NULL;
		}
	}

	// Trying to log to an instance that doesn't exist anymore?
	if(!mgr)
	{
		if(!IS_INSTANCE(plr->m_bgEntryPointMap))
		{
			plr->m_position.x = plr->m_bgEntryPointX;
			plr->m_position.y = plr->m_bgEntryPointY;
			plr->m_position.z = plr->m_bgEntryPointZ;
			plr->m_position.o = plr->m_bgEntryPointO;
			plr->m_mapId = plr->m_bgEntryPointMap;
		}
		else
		{
			plr->m_position.x = plr->GetBindPositionX();
			plr->m_position.y = plr->GetBindPositionY();
			plr->m_position.z = plr->GetBindPositionZ();
			plr->m_position.o = 0;
			plr->m_mapId = plr->GetBindMapId();
		}
	}

	//printf("COPYING TO MOVEMENT ARRAY\n");
	
	// copy to movement array
	movement_packet[0] = m_MoverWoWGuid.GetNewGuidMask();
	memcpy(&movement_packet[1], m_MoverWoWGuid.GetNewGuid(), m_MoverWoWGuid.GetNewGuidLen());

	//printf("STARTING WORLD PRELOAD\n");

	// world preload
	uint32 VMapId;
	float VO;
	float VX;
	float VY;
	float VZ;

	// GMs should start on GM Island and be bound there
	if(HasGMPermissions() && plr->m_FirstLogin && sWorld.gamemaster_startonGMIsland)
	{
		VMapId = 1;
		VO = 0;
		VX = 16222.6f;
		VY = 16265.9f;
		VZ = 14.2085f;

		plr->m_position.x = VX;
		plr->m_position.y = VY;
		plr->m_position.z = VZ;
		plr->m_position.o = VO;
		plr->m_mapId = VMapId;

		plr->SetBindPoint(plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ(), plr->GetMapId(), plr->GetZoneId());
	}
	else
	{
		VMapId = plr->GetMapId();
		VO = plr->GetOrientation();
		VX = plr->GetPositionX();
		VY = plr->GetPositionY();
		VZ = plr->GetPositionZ();
	}

	WorldPacket data (SMSG_LOGIN_VERIFY_WORLD, 20); // 4.3.4
	data << VMapId;
	data << VX;
	data << VY;
	data << VZ;
	data << VO;
	SendPacket(&data);

	//printf("SMSG_LOGIN_VERIFY_WORLD\n");

	//StackWorldPacket<20> datab(SMSG_FEATURE_SYSTEM_STATUS);


	//datab.Initialize(SMSG_FEATURE_SYSTEM_STATUS);
	
	WorldPacket datax(SMSG_FEATURE_SYSTEM_STATUS, 7); // 4.3.4

    datax << uint8(2);                                       // status
    datax << uint32(1);                                      // Scrolls of Ressurection?
    datax << uint32(1);
    datax << uint32(2);
    datax << uint32(0);
    datax.writeBit(true);
    datax.writeBit(true);
    datax.writeBit(false);
    datax.writeBit(true);
    datax.writeBit(false);
    datax.writeBit(false);                                   // enable(1)/disable(0) voice chat interface in client
	datax.flushBits();
    datax << uint32(1);
    datax << uint32(0);
    datax << uint32(10);
    datax << uint32(60);

	SendPacket(&datax);

	//printf("SMSG_FEATURE_SYSTEM_STATUS\n");


	WorldPacket dataldm(SMSG_LEARNED_DANCE_MOVES, 4 + 4); // trinitycore 4.3.4
	dataldm << uint64(0);
	SendPacket(&dataldm);
	//printf("SMSG_LEARNED_MOVES\n");

	plr->UpdateAttackSpeed();

	// Make sure our name exists (for premade system)
	PlayerInfo* info = objmgr.GetPlayerInfo(plr->GetLowGUID());

	if(info == NULL)
	{
		info = new PlayerInfo;
		info->cl = plr->getClass();
		info->gender = plr->getGender();
		info->guid = plr->GetLowGUID();
		info->name = strdup(plr->GetName());
		info->lastLevel = plr->getLevel();
		info->lastOnline = UNIXTIME;
		info->lastZone = plr->GetZoneId();
		info->race = plr->getRace();
		info->team = plr->GetTeam();
		info->guild = NULL;
		info->guildRank = NULL;
		info->guildMember = NULL;
		info->m_Group = NULL;
		info->subGroup = 0;
		objmgr.AddPlayerInfo(info);
	}
	plr->m_playerInfo = info;
	if(plr->m_playerInfo->guild)
	{
		plr->SetGuildId(plr->m_playerInfo->guild->GetGuildId());
		plr->SetGuildRank(plr->m_playerInfo->guildRank->iId);
	}

	info->m_loggedInPlayer = plr;

	// account data == UI config
	SendAccountDataTimes(PER_CHARACTER_CACHE_MASK);

	// Set TIME OF LOGIN
	CharacterDatabase.Execute("UPDATE characters SET online = 1 WHERE guid = %u" , plr->GetLowGUID());

	bool enter_world = true;

	// Find our transporter and add us if we're on one.
	if(plr->transporter_info.guid != 0)
	{
		Transporter* pTrans = objmgr.GetTransporter(Arcemu::Util::GUID_LOPART(plr->transporter_info.guid));
		if(pTrans)
		{
			if(plr->IsDead())
			{
				plr->ResurrectPlayer();
				plr->SetHealth(plr->GetMaxHealth());
				plr->SetPower(POWER_TYPE_MANA, plr->GetMaxPower(POWER_TYPE_MANA));
			}

			float c_tposx = pTrans->GetPositionX() + plr->transporter_info.x;
			float c_tposy = pTrans->GetPositionY() + plr->transporter_info.y;
			float c_tposz = pTrans->GetPositionZ() + plr->transporter_info.z;

			if(plr->GetMapId() != pTrans->GetMapId())	   // loaded wrong map
			{
				plr->SetMapId(pTrans->GetMapId());

				StackWorldPacket<20> dataw(SMSG_NEW_WORLD); // 15595
				dataw << c_tposx;
				dataw << plr->GetOrientation();
				dataw << c_tposz;
				dataw << pTrans->GetMapId();
				dataw << c_tposy;

				SendPacket(&dataw);

				// shit is sent in worldport ack.
				enter_world = false;
			}

			plr->SetPosition(c_tposx, c_tposy, c_tposz, plr->GetOrientation(), false);
			plr->m_CurrentTransporter = pTrans;
			pTrans->AddPlayer(plr);
		}
	}

	Log.Debug("Login", "Player %s logged in.", plr->GetName());

	sWorld.incrementPlayerCount(plr->GetTeam());

	//printf("you should be logged in now");

	if(plr->m_FirstLogin)
	{
		uint32 introid = plr->info->introid;

		OutPacket(SMSG_TRIGGER_CINEMATIC, 4, &introid); // 4.3.4

		// what the fuck is this anyway?
		/*if(sWorld.m_AdditionalFun)    //cebernic: tells people who 's newbie :D
		{
			const int classtext[] = {0, 5, 6, 8, 9, 11, 0, 4, 3, 7, 0, 10};
			sWorld.SendLocalizedWorldText(true, "{65}", classtext[(uint32)plr->getClass() ] , plr->GetName() , (plr->IsTeamHorde() ? "{63}" : "{64}"));
		}*/

	}


	LOG_DETAIL("WORLD: Created new player for existing players (%s)", plr->GetName());

	// Login time, will be used for played time calc
	plr->m_playedtime[2] = uint32(UNIXTIME);

	// disabled
	//Issue a message telling all guild members that this player has signed on
	/*if(plr->IsInGuild())
	{
		Guild* pGuild = plr->m_playerInfo->guild;
		if(pGuild)
		{
			WorldPacket data(SMSG_GUILD_EVENT, 50); // do we need that much? // shoud work on 4.3.4

			data << uint8(GUILD_EVENT_MOTD);
			data << uint8(1);

			if(pGuild->GetMOTD())
				data << pGuild->GetMOTD();
			else
				data << uint8(0);

			SendPacket(&data);

			pGuild->LogGuildEvent(GUILD_EVENT_HASCOMEONLINE, 1, plr->GetName());
		}
	}*/

	// !!!! UNCOMMENT THESE ONCE THEY WORK PROPERLY !!!!
    // don't send this, it's a sandbox, they're not updated
	// Send online status to people having this char in friendlist
	//_player->Social_TellFriendsOnline(); // this should work on 4.3.4
	// send friend list (for ignores)
	//_player->Social_SendFriendList(7); // this should work on 4.3.4

	plr->SendDungeonDifficulty(); // 15595
	plr->SendRaidDifficulty();    // 15595

	//plr->SendEquipmentSetList(); // not sure 4.3.4

#ifndef GM_TICKET_MY_MASTER_COMPATIBLE
	GM_Ticket* ticket = objmgr.GetGMTicketByPlayer(_player->GetGUID());
	if(ticket != NULL)
	{
		//Send status change to gm_sync_channel
		Channel* chn = channelmgr.GetChannel(sWorld.getGmClientChannel().c_str(), _player);
		if(chn)
		{
			std::stringstream ss;
			ss << "GmTicket:" << GM_TICKET_CHAT_OPCODE_ONLINESTATE;
			ss << ":" << ticket->guid;
			ss << ":1";
			chn->Say(_player, ss.str().c_str(), NULL, true);
		}
	}
#endif

	// disabled useless messages
//#ifdef WIN32
	//_player->BroadcastMessage("Server: %sArcEmu %s - %s-Windows-%s", MSG_COLOR_WHITE, BUILD_TAG, CONFIG, ARCH);
//#else
	//_player->BroadcastMessage("Server: %sArcEmu %s - %s-%s", MSG_COLOR_WHITE, BUILD_TAG, PLATFORM_TEXT, ARCH);
//#endif

	// Revision
	//_player->BroadcastMessage("Build hash: %s%s", MSG_COLOR_CYAN, BUILD_HASH_STR);
	// Bugs
	//_player->BroadcastMessage("Bugs: %s%s", MSG_COLOR_SEXHOTPINK, BUGTRACKER);
	// Recruiting message
	//_player->BroadcastMessage(RECRUITING);
	// Shows Online players, and connection peak
	//_player->BroadcastMessage("Online Players: %s%u |rPeak: %s%u|r Accepted Connections: %s%u",
	//                          MSG_COLOR_SEXGREEN, sWorld.GetSessionCount(), MSG_COLOR_SEXBLUE, sWorld.PeakSessionCount, MSG_COLOR_SEXBLUE, sWorld.mAcceptedConnections);

	// Shows Server uptime
	//_player->BroadcastMessage("Server Uptime: |r%s", sWorld.GetUptimeString().c_str());

	// server Message Of The Day
	SendMOTD();

	// disabled for now
	//Set current RestState
	//if(plr->m_isResting)
		// We are resting at an inn , turn on Zzz
		//plr->ApplyPlayerRestState(true);

	// disable everything that is not useful in a sandbox :D
	//Calculate rest bonus if there is time between lastlogoff and now
	/*if(plr->m_timeLogoff > 0 && plr->getLevel() < plr->GetMaxLevel())	// if timelogoff = 0 then it's the first login
	{
		uint32 currenttime = uint32(UNIXTIME);
		uint32 timediff = currenttime - plr->m_timeLogoff;

		//Calculate rest bonus
		if(timediff > 0)
			plr->AddCalculatedRestXP(timediff);
	}

	if(info->m_Group)
		info->m_Group->Update();*/

	if(enter_world && !_player->GetMapMgr())
		plr->AddToWorld();

	sHookInterface.OnFullLogin(_player);

	objmgr.AddPlayer(_player);
}

bool ChatHandler::HandleRenameCommand(const char* args, WorldSession* m_session)
{
	// prevent buffer overflow
	if(strlen(args) > 100)
		return false;

	char name1[100];
	char name2[100];

	if(sscanf(args, "%s %s", name1, name2) != 2)
		return false;

	if(VerifyName(name2, strlen(name2)) != E_CHAR_NAME_SUCCESS)
	{
		RedSystemMessage(m_session, "That name is invalid or contains invalid characters.");
		return true;
	}

	string new_name = name2;
	PlayerInfo* pi = objmgr.GetPlayerInfoByName(name1);
	if(pi == 0)
	{
		RedSystemMessage(m_session, "Player not found with this name.");
		return true;
	}

	if(objmgr.GetPlayerInfoByName(new_name.c_str()) != NULL)
	{
		RedSystemMessage(m_session, "Player found with this name in use already.");
		return true;
	}

	objmgr.RenamePlayerInfo(pi, pi->name, new_name.c_str());

	free(pi->name);
	pi->name = strdup(new_name.c_str());

	// look in world for him
	Player* plr = objmgr.GetPlayer(pi->guid);
	if(plr != 0)
	{
		plr->SetName(new_name);
		BlueSystemMessageToPlr(plr, "%s changed your name to '%s'.", m_session->GetPlayer()->GetName(), new_name.c_str());
		plr->SaveToDB(false);
	}
	else
	{
		CharacterDatabase.WaitExecute("UPDATE characters SET name = '%s' WHERE guid = %u", CharacterDatabase.EscapeString(new_name).c_str(), (uint32)pi->guid);
	}

	GreenSystemMessage(m_session, "Changed name of '%s' to '%s'.", name1, name2);
	sGMLog.writefromsession(m_session, "renamed character %s (GUID: %u) to %s", name1, pi->guid, name2);
	sPlrLog.writefromsession(m_session, "GM renamed character %s (GUID: %u) to %s", name1, pi->guid, name2);
	return true;
}

// We do not do anything with this opcode...
void WorldSession::HandleLoadScreenOpcode(WorldPacket & recv_data)
{
	// empty opcode
	// printf("LOAD SCREEN OPCODE\n");
	uint32 mapId;

	recv_data >> mapId;
	recv_data.readBit();
}
