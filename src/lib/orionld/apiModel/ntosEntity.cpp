/*
*
* Copyright 2022 FIWARE Foundation e.V.
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
#include <string.h>                                              // strcmp

extern "C"
{
#include "kjson/KjNode.h"                                        // KjNode
#include "kjson/kjLookup.h"                                      // kjLookup
#include "kjson/kjBuilder.h"                                     // kjChildRemove
}

#include "logMsg/logMsg.h"                                       // LM_*

#include "orionld/apiModel/ntosEntity.h"                         // Own interface



// -----------------------------------------------------------------------------
//
// ntosEntity - normalized to simplified for an entity
//
// The combination Simplified+KeyValues isn't allowed, we'd never get this far
//
void ntosEntity(KjNode* apiEntityP, const char* lang)
{
  KjNode* attrP = apiEntityP->value.firstChildP;
  KjNode* next;

  while (attrP != NULL)
  {
    next = attrP->next;

    if (strcmp(attrP->name, "id") == 0)
    {
      attrP = next;
      continue;
    }
    if (strcmp(attrP->name, "type") == 0)
    {
      attrP = next;
      continue;
    }

    if (strcmp(attrP->name, "createdAt") == 0)
    {
      kjChildRemove(apiEntityP, attrP);
      attrP = next;
      continue;
    }

    if (strcmp(attrP->name, "modifiedAt") == 0)
    {
      kjChildRemove(apiEntityP, attrP);
      attrP = next;
      continue;
    }

    //
    // It's an attribute
    //
    KjNode* valueP = kjLookup(attrP, "value");

    if (valueP == NULL)
      valueP = kjLookup(attrP, "object");

    if (valueP == NULL)
      valueP = kjLookup(attrP, "languageMap");

    if (valueP != NULL)
    {
      attrP->value     = valueP->value;
      attrP->type      = valueP->type;
      attrP->lastChild = valueP->lastChild;
    }
    else
      LM_E(("No attribute value (object/languageMap) found - this should never happen!!!"));

    attrP = next;
  }
}