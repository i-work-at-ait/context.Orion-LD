/*
*
* Copyright 2018 FIWARE Foundation e.V.
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
#include <string.h>                                                        // strcmp

extern "C"
{
#include "kjson/KjNode.h"                                                  // KjNode
}

#include "orionld/kjTree/kjStringValueLookupInArray.h"                     // Own interface



// ----------------------------------------------------------------------------
//
// kjStringValueLookupInArray -
//
// NOTE
//   This lookup function works on string items in an array.
//   The caller needs to be sure that the 'stringArray' is really an array and that ALL its items are Strings
//
KjNode* kjStringValueLookupInArray(KjNode* stringArray, const char* value)
{
  if (stringArray != NULL)
  {
    if ((stringArray->type != KjArray) && (stringArray->type != KjObject))
      return NULL;

    for (KjNode* nodeP = stringArray->value.firstChildP; nodeP != NULL; nodeP = nodeP->next)
    {
      if (nodeP->type != KjString)
        continue;

      if (strcmp(value, nodeP->value.s) == 0)
        return nodeP;
    }
  }

  return NULL;
}
