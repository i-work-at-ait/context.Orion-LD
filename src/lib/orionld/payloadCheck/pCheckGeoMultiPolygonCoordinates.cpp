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
#include <unistd.h>                                                 // NULL

extern "C"
{
#include "kjson/KjNode.h"                                           // KjNode
}

#include "logMsg/logMsg.h"                                          // LM_*

#include "orionld/common/orionldError.h"                            // orionldError
#include "orionld/payloadCheck/pCheckGeoPolygonCoordinates.h"       // pCheckGeoPolugonCoordinates
#include "orionld/payloadCheck/pCheckGeoMultiPolygonCoordinates.h"  // Own interface



// -----------------------------------------------------------------------------
//
// pCheckGeoMultiPolygonCoordinates -
//
bool pCheckGeoMultiPolygonCoordinates(KjNode* coordinatesP)
{
  for (KjNode* memberP = coordinatesP->value.firstChildP; memberP != NULL; memberP = memberP->next)
  {
    if (memberP->type != KjArray)
    {
      LM_W(("Bad Input ('coordinates' must be a JSON Array)"));
      orionldError(OrionldBadRequestData, "Invalid GeoJSON", "'coordinates' in a 'MultiPolygon' must be a JSON Array of 'Polygon arrays'", 400);
      return false;
    }

    if (pCheckGeoPolygonCoordinates(memberP) == false)
      return false;
  }

  return true;
}
