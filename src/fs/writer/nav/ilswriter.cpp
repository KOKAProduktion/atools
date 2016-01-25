/*
 * IlsWriter.cpp
 *
 *  Created on: 01.05.2015
 *      Author: alex
 */

#include "fs/writer/nav/ilswriter.h"
#include "fs/bgl/nav/dme.h"
#include "fs/bgl/nav/glideslope.h"
#include "fs/bgl/nav/localizer.h"
#include "fs/bgl/util.h"
#include "fs/writer/datawriter.h"
#include "sql/sqlquery.h"
#include "fs/bglreaderoptions.h"
#include "fs/writer/runwayindex.h"

namespace atools {
namespace fs {
namespace writer {

using atools::fs::bgl::Dme;
using atools::fs::bgl::Glideslope;
using atools::fs::bgl::Localizer;
using atools::fs::bgl::Ils;
using atools::sql::SqlQuery;

void IlsWriter::writeObject(const Ils *type)
{
  if(getOptions().isVerbose())
    qDebug() << "Writing ILS " << type->getIdent() << " name " << type->getName();

  bind(":ils_id", getNextId());
  bind(":ident", type->getIdent());
  bind(":name", type->getName());
  bind(":region", type->getRegion());
  bind(":frequency", type->getFrequency());
  bind(":range", bgl::util::meterToNm(type->getRange()));
  bind(":mag_var", type->getMagVar());
  bind(":is_backcourse", type->isIsBackcourse());
  bind(":altitude", bgl::util::meterToFeet(type->getPosition().getAltitude()));
  bind(":lonx", type->getPosition().getLonX());
  bind(":laty", type->getPosition().getLatY());

  const Dme *dme = type->getDme();
  if(dme != nullptr)
  {
    bind(":dme_range", bgl::util::meterToNm(dme->getRange()));
    bind(":dme_altitude", bgl::util::meterToFeet(dme->getPosition().getAltitude()));
    bind(":dme_lonx", dme->getPosition().getLonX());
    bind(":dme_laty", dme->getPosition().getLatY());
  }

  const Glideslope *gs = type->getGlideslope();
  if(gs != nullptr)
  {
    bind(":gs_range", bgl::util::meterToNm(gs->getRange()));
    bind(":gs_pitch", gs->getPitch());
    bind(":gs_altitude", bgl::util::meterToFeet(gs->getPosition().getAltitude()));
    bind(":gs_lonx", gs->getPosition().getLonX());
    bind(":gs_laty", gs->getPosition().getLatY());
  }

  bool isComplete = false;
  const Localizer *loc = type->getLocalizer();
  QString apIdent = type->getAirportIdent();
  if(loc != nullptr && !apIdent.isEmpty())
  {
    QString msg(" ILS ID " + QString::number(getCurrentId()) +
                " ident " + type->getIdent() + " name " + type->getName());
    if(getOptions().doesAirportIcaoMatch(apIdent))
    {
      int id = getRunwayIndex()->getRunwayEndId(apIdent, loc->getRunwayName(), msg);

      if(id != -1)
      {
        isComplete = true;
        bind(":loc_runway_end_id", id);
      }
      else
        bind(":loc_runway_end_id", QVariant(QVariant::Int));
    }

    bind(":loc_heading", loc->getHeading());
    bind(":loc_width", loc->getWidth());
  }
  else
    isComplete = true;

  if(!getOptions().noIncompleteObjects() || isComplete)
    executeStatement();
  else
    clearStatement();
}

} // namespace writer
} // namespace fs
} // namespace atools