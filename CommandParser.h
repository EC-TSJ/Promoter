/*********************************************************/
/*  (%T% %S%), %J% <$A$> <$2.126$>                       */
/*  (%W% 02/12/2019 ) Escrito                            */
/*  (%X% 05/12/2019 ) Añadido _buildJob                  */
/*  (%X% 05/12/2019 ) Añadido ejecución administrativa   */
/*  (%X% 06/12/2019 ) Añadido _buildManifest             */
/*  (%X% 06/12/2019 ) Añadido _buildRc                   */
/*  (%M% 06/12/2019 )                                    */
/*  (%M% 08/12/2019 ) Se añade multicreación             */
/*         o sea, creación de varios a la vez            */
/*  (%M% 17/12/2019 ) Se añade CMakeList.txt             */
/*  (%M% 10/01/2020 ) Se añade _buildGo                  */
/*  (%M% 25/01/2020 ) Se añade QProperty                 */
/*  <$Válido$>                                           */
/*********************************************************/

#ifndef COMMANDPARSER_H
# define COMMANDPARSER_H

#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QMap>
#include "Property.h"
#include "main.h"

#if V_POSITRON
typedef  void (*Callback)(QString, QString, short int);

class QCommandParser {
public:
#if !V_MODE
  QCommandParser() {}
#else
  QCommandParser(): options(this, &QCommandParser::_getOptions, nullptr) {}
#endif
  void addOption( QString vType, QString vDescription, QString vFile, Callback function);
  void addPositional( QString vType, QString vDescription);
  QCommandLineParser qlp;
#if !V_MODE
  QMap<QString, void (*)(QString, QString, short int)> options() const;
#else
  QProperty<QCommandParser, QMap<QString, void (*)(QString, QString, short int)>, 1> options;
#endif

private:
  QMap<QString, void (*)(QString, QString, short int)> _options;
  QMap<QString, void (*)(QString, QString, short int)> _getOptions() const;
};
#endif

#endif // COMMANDPARSER_H
