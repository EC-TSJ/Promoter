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

#include "CommandParser.h"
#include "QCommandLineParser"
#include "QCommandLineOption"
#include "main.h"

#if V_POSITRON

QT_BEGIN_NAMESPACE 

/**
 * @brief QCommandParser::addOption Añade una opción para el menú
 * @param vType Nombre de la Opción
 * @param vDescription Descripción
 * @param vFile Pedir fichero
 * @param function Callback
 */
void QCommandParser::addOption( QString vType, QString vDescription, QString vFile, Callback function) {
    QCommandLineOption *p = new QCommandLineOption(vType, vDescription, vFile);
    qlp.addOption(*p);
    _options[vType] = function;
  }

/**
 * @brief QCommandParser::addPositional Añade una opción posicional para el menú
 * @param vType Nombre de la opción
 * @param vDescription Descripción
 */
void QCommandParser::addPositional( QString vType, QString vDescription) {
    qlp.addPositionalArgument(vType, vDescription);
  }

#if !V_MODE


QMap<QString, void (*)(QString, QString, short int)> QCommandParser::options() const {
  return _options;
}

#else

/**
 * @brief QCommandParser::_getOptions getter para Options
 * @return QMap
 */
QMap<QString, void (*)(QString, QString, short int)> QCommandParser::_getOptions() const {
  return _options;
}

#endif

QT_END_NAMESPACE

#endif
