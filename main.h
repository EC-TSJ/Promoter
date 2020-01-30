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

#include <QCoreApplication>

#ifndef __MAIN_H
# define __MAIN_H

#define V_POSITRON      1
#define V_MODE          1
#define APX_SETTING(name, _name, _apx, _nb)   static void name(const QString _name, const QString _apx, const short _nb)

APX_SETTING(_buildCMake, name, apx, nb);
APX_SETTING(_buildRc, name, apx, nb);
APX_SETTING(_buildManifest, name, apx, nb);
APX_SETTING(_buildQT, name, apx, nb);
APX_SETTING(_buildVxx, name, apx, nb);
APX_SETTING(_buildPython, name, apx, nb);
APX_SETTING(_buildHtml, name, apx, nb);
APX_SETTING(_buildSh, name, apx, nb);
APX_SETTING(_buildJob, name, apx, nb);
APX_SETTING(_buildGo, name, apx, nb);
int runPromoter(int argc, char *argv[]);

#endif // MAIN_H
