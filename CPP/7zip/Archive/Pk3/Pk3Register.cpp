// Pk3Register.cpp

#include "StdAfx.h"
#include "../../Common/RegisterArc.h"
#include "Pk3Handler.h"


static IInArchive *CreateArc() { return new NArchive::NPk3::CHandler; }
#ifndef EXTRACT_ONLY
static IOutArchive *CreateArcOut() { return new NArchive::NPk3::CHandler; }
#else
#define CreateArcOut 0
#endif

static CArcInfo g_ArcInfo =
  { L"pk3", L"pk3", 0, 0xB3, { 0x9F, 0xC5, 0x8D, 0x48 }, 4, false, CreateArc, CreateArcOut };

REGISTER_ARC(Pk3)
