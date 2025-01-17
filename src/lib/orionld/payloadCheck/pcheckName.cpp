/*
*
* Copyright 2019 FIWARE Foundation e.V.
*
* This file is part of Orion-LD Context Broker.
*
* Orion-LD Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion-LD Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion-LD Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* orionld at fiware dot org
*
* Author: Ken Zangelin
*/
#include "logMsg/logMsg.h"                                       // LM_*
#include "logMsg/traceLevels.h"                                  // Lmt*

#include "orionld/common/orionldError.h"                         // orionldError
#include "orionld/payloadCheck/pcheckName.h"                     // Own interface



// -----------------------------------------------------------------------------
//
// pcheckName -
//
bool pcheckName(char* name, char** detailsPP)
{
  if (name == NULL)
  {
    *detailsPP = (char*) "empty name";
    return false;
  }

  for (; *name != 0; ++name)
  {
    //
    // Invalid chars:
    //   '=',
    //   '[',
    //   ']',
    //   '&',
    //   '?',
    //   '"',
    //   ''',
    //   '\b',
    //   '\t',
    //   '\n', and
    //   ' '
    //
    if ((*name == '=') || (*name == '[') || (*name == ']') || (*name == '&') || (*name == '?') || (*name == '"') ||
        (*name == '\'') || (*name == '\b') || (*name == '\t') || (*name == '\n') || (*name == ' '))
    {
      LM_W(("Invalid character: 0x%x", *name & 0xFF));
      *detailsPP = (char*) "invalid character in name";
      return false;
    }
  }

  return true;
}



// -----------------------------------------------------------------------------
//
// pCheckName -
//
bool pCheckName(char* name)
{
  if (name == NULL)
  {
    orionldError(OrionldBadRequestData, "Invalid attribute name", "empty string", 400);
    return false;
  }

  for (; *name != 0; ++name)
  {
    //
    // Invalid chars:
    //   '=',
    //   '[',
    //   ']',
    //   '&',
    //   '?',
    //   '"',
    //   ''',
    //   '\b',
    //   '\t',
    //   '\n', and
    //   ' '
    //
    if ((*name == '=') || (*name == '[') || (*name == ']') || (*name == '&') || (*name == '?') || (*name == '"') ||
        (*name == '\'') || (*name == '\b') || (*name == '\t') || (*name == '\n') || (*name == ' '))
    {
      LM_W(("Invalid character: 0x%x", *name & 0xFF));
      orionldError(OrionldBadRequestData, "Invalid attribute name", "invalid character", 400);
      return false;
    }
  }

  return true;
}
