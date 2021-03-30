#include "CustomCrew.h"


static bool __attribute__((fastcall)) CrewMember_GetControllable(CrewMember *_this)
{
    bool req = _this->iShipId == 0 && !_this->bDead && !_this->bMindControlled;

    CustomCrewManager *custom = CustomCrewManager::GetInstance();
    auto def = custom->GetDefinition(_this->species);

    auto ex = CM_EX(_this);
    bool ret = (ex->temporaryPowerActive && def.powerDef.tempPower.controllable.enabled) ? def.powerDef.tempPower.controllable.value : def.controllable;
    ex->CalculateStat(CrewStat::CONTROLLABLE, &ret);
    return ret && req;
}

static bool __attribute__((fastcall)) CrewMember_CanSuffocate(CrewMember *_this)
{
    CustomCrewManager *custom = CustomCrewManager::GetInstance();
    auto def = custom->GetDefinition(_this->species);

    auto ex = CM_EX(_this);
    bool ret = (ex->temporaryPowerActive && def.powerDef.tempPower.canSuffocate.enabled) ? def.powerDef.tempPower.canSuffocate.value : def.canSuffocate;
    ex->CalculateStat(CrewStat::CAN_SUFFOCATE, &ret);
    return ret;
}

static bool __attribute__((fastcall)) CrewMember_CanFight(CrewMember *_this)
{
    CustomCrewManager *custom = CustomCrewManager::GetInstance();
    auto def = custom->GetDefinition(_this->species);

    auto ex = CM_EX(_this);
    bool ret = (ex->temporaryPowerActive && def.powerDef.tempPower.canFight.enabled) ? def.powerDef.tempPower.canFight.value : def.canFight;
    ex->CalculateStat(CrewStat::CAN_FIGHT, &ret);
    return ret;
}

static bool __attribute__((fastcall)) CrewMember_CanRepair(CrewMember *_this)
{
    bool req = !_this->intruder && !_this->bDead && _this->crewAnim->status != 3;

    CustomCrewManager *custom = CustomCrewManager::GetInstance();
    auto def = custom->GetDefinition(_this->species);

    auto ex = CM_EX(_this);
    bool ret = (ex->temporaryPowerActive && def.powerDef.tempPower.canRepair.enabled) ? def.powerDef.tempPower.canRepair.value : def.canRepair;
    ex->CalculateStat(CrewStat::CAN_REPAIR, &ret);
    return ret && req;
}

static bool __attribute__((fastcall)) CrewMember_CanSabotage(CrewMember *_this)
{
    bool req = _this->intruder;

    CustomCrewManager *custom = CustomCrewManager::GetInstance();
    auto def = custom->GetDefinition(_this->species);

    auto ex = CM_EX(_this);
    bool ret = (ex->temporaryPowerActive && def.powerDef.tempPower.canSabotage.enabled) ? def.powerDef.tempPower.canSabotage.value : def.canSabotage;
    ex->CalculateStat(CrewStat::CAN_SABOTAGE, &ret);
    return ret && req;
}

static bool __attribute__((fastcall)) CrewMember_CanMan(CrewMember *_this)
{
    bool req = !_this->intruder && _this->fStunTime == 0.f && _this->crewAnim->status != 3;
    CustomCrewManager *custom = CustomCrewManager::GetInstance();
    auto def = custom->GetDefinition(_this->species);

    auto ex = CM_EX(_this);
    bool ret = (ex->temporaryPowerActive && def.powerDef.tempPower.canMan.enabled) ? def.powerDef.tempPower.canMan.value : def.canMan;
    ex->CalculateStat(CrewStat::CAN_MAN, &ret);
    return ret && req;
}


static bool __attribute__((fastcall)) CrewMember_CanBurn(CrewMember *_this)
{
    CustomCrewManager *custom = CustomCrewManager::GetInstance();
    auto def = custom->GetDefinition(_this->species);

    auto ex = CM_EX(_this);
    bool ret = (ex->temporaryPowerActive && def.powerDef.tempPower.canBurn.enabled) ? def.powerDef.tempPower.canBurn.value : def.canBurn;
    ex->CalculateStat(CrewStat::CAN_BURN, &ret);
    return ret;
}

static int __attribute__((fastcall)) CrewMember_GetMaxHealth(CrewMember *_this)
{
    auto ex = CM_EX(_this);
    _this->health.second = ex->CalculateStat(CrewStat::MAX_HEALTH);
    return _this->health.second;
}

static float __attribute__((fastcall)) CrewMember_GetMoveSpeedMultiplier(CrewMember *_this)
{
    auto ex = CM_EX(_this);
    return ex->CalculateStat(CrewStat::MOVE_SPEED_MULTIPLIER);
}

static float __attribute__((fastcall)) CrewMember_GetRepairSpeed(CrewMember *_this)
{
    auto ex = CM_EX(_this);
    return ex->CalculateStat(CrewStat::REPAIR_SPEED_MULTIPLIER);
}

static float __attribute__((fastcall)) CrewMember_GetDamageMultiplier(CrewMember *_this)
{
    auto ex = CM_EX(_this);
    auto def = CustomCrewManager::GetInstance()->GetDefinition(_this->species);
    if (_this->crewAnim->status == 7 && def.rangedDamageMultiplier != 1.f)
    {
        return ex->CalculateStat(CrewStat::RANGED_DAMAGE_MULTIPLIER);
    }
    else
    {
        return ex->CalculateStat(CrewStat::DAMAGE_MULTIPLIER);
    }
}

static bool __attribute__((fastcall)) CrewMember_ProvidesPower(CrewMember *_this)
{
    CustomCrewManager *custom = CustomCrewManager::GetInstance();

    return custom->GetDefinition(_this->species).providesPower;
}

static float __attribute__((fastcall)) CrewMember_FireRepairMultiplier(CrewMember *_this)
{
    auto ex = CM_EX(_this);
    return ex->CalculateStat(CrewStat::FIRE_REPAIR_MULTIPLIER);
}

static bool __attribute__((fastcall)) CrewMember_IsTelepathic(CrewMember *_this)
{
    CustomCrewManager *custom = CustomCrewManager::GetInstance();
    auto def = custom->GetDefinition(_this->species);

    auto ex = CM_EX(_this);
    bool ret = (ex->temporaryPowerActive && def.powerDef.tempPower.isTelepathic.enabled) ? def.powerDef.tempPower.isTelepathic.value : def.isTelepathic;
    ex->CalculateStat(CrewStat::IS_TELEPATHIC, &ret);
    return ret;
}

static float __attribute__((fastcall)) CrewMember_GetSuffocationModifier(CrewMember *_this)
{
    auto ex = CM_EX(_this);
    return ex->CalculateStat(CrewStat::SUFFOCATION_MODIFIER);
}

static bool __attribute__((fastcall)) CrewMember_IsAnaerobic(CrewMember *_this)
{
    CustomCrewManager *custom = CustomCrewManager::GetInstance();
    auto def = custom->GetDefinition(_this->species);

    auto ex = CM_EX(_this);
    bool ret = (ex->temporaryPowerActive && def.powerDef.tempPower.isAnaerobic.enabled) ? def.powerDef.tempPower.isAnaerobic.value : def.isAnaerobic;
    ex->CalculateStat(CrewStat::IS_ANAEROBIC, &ret);
    return ret;
}

static bool __attribute__((fastcall)) CrewMember_HasSpecialPower(CrewMember *_this)
{
    auto ex = CM_EX(_this);

    return ex->hasSpecialPower;
}

static std::pair<float, float> __attribute__((fastcall)) CrewMember_GetPowerCooldown(CrewMember *_this)
{
    auto ex = CM_EX(_this);
    return ex->powerCooldown;
}

static bool __attribute__((fastcall)) CrewMember_PowerReady(CrewMember *_this)
{
    auto ex = CM_EX(_this);

    auto readyState = ex->PowerReady();

    return readyState == PowerReadyState::POWER_READY;
}

static void __attribute__((fastcall)) CrewMember_ResetPower(CrewMember *_this)
{
    auto ex = CM_EX(_this);

    CustomCrewManager *custom = CustomCrewManager::GetInstance();
    auto jumpCooldown = custom->GetDefinition(_this->species).powerDef.jumpCooldown;

    if (jumpCooldown == ActivatedPowerDefinition::JUMP_COOLDOWN_FULL)
    {
        ex->powerCooldown.first = ex->powerCooldown.second;
    }
    else if (jumpCooldown == ActivatedPowerDefinition::JUMP_COOLDOWN_RESET)
    {
        ex->powerCooldown.first = 0;
    }

}

static void __attribute__((fastcall)) CrewMember_ActivatePower(CrewMember *_this)
{
    auto ex = CM_EX(_this);

    ex->PreparePower();
}

void SetupVTable(CrewMember *crew)
{
    void** vtable = *(void***)crew;

    DWORD dwOldProtect, dwBkup;
    VirtualProtect(&vtable[0], sizeof(void*) * 57, PAGE_EXECUTE_READWRITE, &dwOldProtect);

    vtable[23] = (void*)&CrewMember_GetControllable;
    vtable[25] = (void*)&CrewMember_CanFight;
    vtable[26] = (void*)&CrewMember_CanRepair;
    vtable[27] = (void*)&CrewMember_CanSabotage;
    vtable[28] = (void*)&CrewMember_CanMan;
    vtable[31] = (void*)&CrewMember_CanSuffocate;
    vtable[32] = (void*)&CrewMember_CanBurn;
    vtable[33] = (void*)&CrewMember_GetMaxHealth;
    vtable[40] = (void*)&CrewMember_GetMoveSpeedMultiplier;
    vtable[41] = (void*)&CrewMember_GetRepairSpeed;
    vtable[42] = (void*)&CrewMember_GetDamageMultiplier;
    vtable[43] = (void*)&CrewMember_ProvidesPower;
    vtable[45] = (void*)&CrewMember_FireRepairMultiplier;
    vtable[46] = (void*)&CrewMember_IsTelepathic;
    vtable[47] = (void*)&CrewMember_GetPowerCooldown;
    vtable[48] = (void*)&CrewMember_PowerReady;
    vtable[49] = (void*)&CrewMember_ActivatePower;
    vtable[50] = (void*)&CrewMember_HasSpecialPower;
    vtable[51] = (void*)&CrewMember_ResetPower;
    vtable[52] = (void*)&CrewMember_GetSuffocationModifier;
    vtable[55] = (void*)&CrewMember_IsAnaerobic;

    VirtualProtect(&vtable[0], sizeof(void*) * 57, dwOldProtect, &dwBkup);
}



HOOK_METHOD_PRIORITY(CrewMember, constructor, 500, (CrewBlueprint& bp, int shipId, bool intruder, CrewAnimation* animation) -> void)
{
    super(bp, shipId, intruder, animation);

    CustomCrewManager *custom = CustomCrewManager::GetInstance();

    if (custom->IsRace(species) && !IsDrone())
    {
        SetupVTable(this);
        health.first = GetMaxHealth();
    }
}



static bool __attribute__((fastcall)) CrewAnimation_CustomDeath(CrewAnimation *_this)
{
    CustomCrewManager *custom = CustomCrewManager::GetInstance();
    if (!custom->IsRace(_this->race)) return false;
    return custom->GetDefinition(_this->race).hasCustomDeathAnimation;
}

void SetupVTable(CrewAnimation *anim)
{
    void** vtable = *(void***)anim;

    DWORD dwOldProtect, dwBkup;
    VirtualProtect(&vtable[0], sizeof(void*) * 12, PAGE_EXECUTE_READWRITE, &dwOldProtect);

    vtable[12] = (void*)&CrewAnimation_CustomDeath;

    VirtualProtect(&vtable[0], sizeof(void*) * 12, dwOldProtect, &dwBkup);
}



HOOK_METHOD_PRIORITY(CrewAnimation, constructor, 500, (int shipId, const std::string& race, Pointf unk, bool hostile) -> void)
{
    super(shipId, race, unk, hostile);

    CustomCrewManager *custom = CustomCrewManager::GetInstance();
    if (custom->IsRace(race) && !bDrone)
    {
        SetupVTable(this);
    }
}




