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

#include "main.h"
#include <QCoreApplication>
#include <QFile>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QMap>
#include <QBuffer>
#include <QDate>
#include <QTextStream>
#include <QString>
#include <QByteArray>
#include <QtDebug>
#include <CommandParser.h>

#define OST_VERSION_STR  "0.02.2126"

QT_BEGIN_NAMESPACE

/**
 * @brief _buildCMake
 */
APX_SETTING(_buildCMake, name, apx, nb) {
  Q_UNUSED(nb)
  Q_UNUSED(apx)
  Q_UNUSED(name)

  QFile file;
  QByteArray bytearray;
  QBuffer buffer(&bytearray);

  const QString nombre = "CMakeLists.txt";
  file.setFileName(nombre);
  file.open(QIODevice::WriteOnly);
  buffer.open(QIODevice::WriteOnly);

  buffer.write("cmake_minimum_required(VERSION 3.0)\n"
               "set(TARGET_NAME ????.??? )\n\n"
               "project(${TARGET_NAME})\n\n"
               "# Check the build type and ask the user to set concrete one\n"
               "if(NOT CMAKE_BUILD_TYPE)\n"
               "   set(CMAKE_BUILD_TYPE RelWithDebInfo)\n"
               "   message(WARNING \"CMAKE_BUILD_TYPE is not set, forcing to RelWithDebInfo\")\n"
               "endif()\n\n"
               "# Set compiler flags\n"
               "if(${CMAKE_CXX_COMPILER_ID} MATCHES \"GNU\" OR ${CMAKE_CXX_COMPILER_ID} MATCHES \"Clang\")\n"
               "        set(CMAKE_CXX_FLAGS \"-std=c++11 -Wall -Wextra\")\n"
               "        set(CMAKE_CXX_FLAGS_DEBUG \"-O0 -g3\")\n"
               "        set(CMAKE_CXX_FLAGS_RELEASE \"-O3\")\n"
               "        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO \"-O3 -g3\")\n"
               "        set(CMAKE_CXX_FLAGS_MINSIZEREL \"-Os\")\n"
               "endif()\n\n"
               "find_package(Qt5Widgets REQUIRED)\n"
               "find_package(Qt5Network REQUIRED)\n\n"
               "include_directories(\n"
               "        ${CMAKE_CURRENT_BINARY_DIR}\n"
               "        ${CMAKE_CURRENT_SOURCE_DIR}\n"
               ")\n\n"
               "# Instruct CMake to run moc automatically when needed\n"
               "set(CMAKE_AUTOMOC ON)\n"
               "set(CMAKE_AUTORCC ON)\n"
               "set(CMAKE_AUTOUIC ON)\n\n"
               "# Source files\n"
               "set(SOURCES\n"
               ")\n\n"
               "# User interface files\n"
               "set(FORMS\n"
               "        forms/mainform.ui\n"
               ")\n\n"
               "# Resource files\n"
               "set(RESOURCES\n"
               "        resources.qrc\n"
               ")\n\n"
               "# Shared libraries\n"
               "set(LIBRARIES\n"
               "        Qt5::Widgets\n"
               ")\n\n"
               "# Generate additional sources with MOC and UIC\n"
               "qt5_wrap_ui(UIC_SOURCES ${FORMS})\n"
               "qt5_add_resources(RCC_SOURCES ${RESOURCES})\n\n"
               "# Set target\n"
               "add_executable(${TARGET_NAME} ${SOURCES} ${HEADERS} ${UIC_SOURCES} ${RCC_SOURCES})\n\n"
               "# Link with libraries\n"
               "target_link_libraries(${TARGET_NAME} ${LIBRARIES})\n\n"
               "# Installation\n"
               "install(TARGETS ${TARGET_NAME} RUNTIME DESTINATION bin)\n"
               "install(FILES resources/${TARGET_NAME}.png DESTINATION share/icons/hicolor/48x48/apps)\n"
               "install(FILES ${TARGET_NAME}.desktop DESTINATION share/applications)\n"
         );


  file.write(bytearray, qstrlen(bytearray));
  buffer.close();
  file.close();
}

/**
 * @brief _buildRc
 */
APX_SETTING(_buildRc, name, apx, nb) {
  Q_UNUSED(nb)

  QFile file;
  QByteArray bytearray;
  QBuffer buffer(&bytearray);

  const QString nombre = name + "." + apx;
  file.setFileName(nombre);
  file.open(QIODevice::WriteOnly);
  buffer.open(QIODevice::WriteOnly);

  buffer.write("#include <winver.h>\n\n"
  "IDI_ICON1 ICON DISCARDABLE \"main.ico\"\n\n"
  "#ifdef __ICON2__\n\n"
  "2 ICON DISCARDABLE \"asm.15.ico\"\n\n"
  "#endif\n\n"
  "#ifdef __MANIFEST__\n\n"
  "1 RT_MANIFEST \"Promoter.exe.manifest\"\n\n"
  "#endif\n\n"
  "#define __VERSION__\n"
  "#ifdef  __VERSION__\n\n"
  "VS_VERSION_INFO VERSIONINFO\n"
  " FILEVERSION 0, 2, 2125, 5\n"
  " PRODUCTVERSION 0, 1, 0, 0\n"
  " FILEFLAGSMASK 0x3fL\n"
  " FILEFLAGS 0\n"
  " FILEOS VOS_NT_WINDOWS32\n"
  " FILETYPE VFT_APP\n"
  " FILESUBTYPE VFT2_UNKNOWN\n"
  "BEGIN\n"
  "  BLOCK \"VarFileInfo\"\n"
  "  BEGIN\n"
  "    VALUE \"Translation\", 0x409, 1200\n"
  "  END\n"
  "  BLOCK \"StringFileInfo\"\n"
  "  BEGIN\n"
  "    BLOCK \"040904b0\"\n"
  "    BEGIN\n"
  "      VALUE \"CompanyName\", \"Boolean Logicals\"\n"
  "      VALUE \"FileDescription\", \"Generador de ficheros de uso comun\"\n"
  "      VALUE \"FileVersion\", \"0.02.2125\"\n"
  "      VALUE \"InternalName\", \"Promoter\"\n"
  "      VALUE \"LegalCopyright\", \"Copyright 2019 by Boolean Logicals\"\n"
  "      VALUE \"OriginalFilename\", \"promoter.exe\"\n"
  "      VALUE \"ProductName\", \"OSX Corporative\"\n"
  "      VALUE \"ProductVersion\", \"0.02.2125\"\n"
  "    END\n"
  "  END\n"
  "END\n\n"
  "#endif\n"  );


  file.write(bytearray, qstrlen(bytearray));
  buffer.close();
  file.close();
}

/**
 * @brief _buildGo
 */
APX_SETTING(_buildGo, name, apx, nb) {
  Q_UNUSED(nb)

  QFile file;
  QByteArray bytearray;
  QBuffer buffer(&bytearray);

  const QString nombre = name + "." + apx;
  file.setFileName(nombre);
  file.open(QIODevice::WriteOnly);
  buffer.open(QIODevice::WriteOnly);

  buffer.write("/************************************/\n"
               "/*  (%T% %S%), %J% <$B$> <$1.00$>   */\n"
               "/*  (%W% 30-09-1991 )               */\n"
               "/*  (%X%            )               */\n"
               "/*  (%M%            )               */\n"
               "/*  <$  $>                          */\n"
               "/************************************/\n\n"
               "package main\n\n"
               "import (\n"
               "        \"fmt\"\n"
               ")\n\n"
               "func main() {\n"
               "}\n\n" );


  file.write(bytearray, qstrlen(bytearray));
  buffer.close();
  file.close();
}

/**
 * @brief _buildManifest
 */
APX_SETTING(_buildManifest, name, apx, nb) {
  QFile file;
  QByteArray bytearray;
  QBuffer buffer(&bytearray);

  const QString nombre = name + "." + apx;
  file.setFileName(nombre);
  file.open(QIODevice::WriteOnly);
  buffer.open(QIODevice::WriteOnly);

  buffer.write("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n"
  "<assembly xmlns=\"urn:schemas-microsoft-com:asm.v1\" manifestVersion=\"1.0\">\n"
  "  <trustInfo xmlns=\"urn:schemas-microsoft-com:asm.v3\">\n"
  "    <security>\n"
  "      <requestedPrivileges>\n"
  "        <requestedExecutionLevel level=\"%1\" uiAccess=\"false\"/>\n"
  "      </requestedPrivileges>\n"
  "    </security>\n"
  "  </trustInfo>\n"
  "</assembly>\n%2");


  QString data = QString::fromLocal8Bit(bytearray).arg(nb==1?"requireAdministrator":"asInvoker", QString());
  file.write(data.toUtf8(), qstrlen(data.toUtf8()));
  buffer.close();
  file.close();

}

/**
 * @brief _buildQT
 */
APX_SETTING(_buildQT, name, apx, nb) {
  Q_UNUSED(nb)

  QFile file;
  QByteArray bytearray;
  QBuffer buffer(&bytearray);

  const QString nombre = name + "." + apx;
  file.setFileName(nombre);
  file.open(QIODevice::WriteOnly);
  buffer.open(QIODevice::WriteOnly);

  buffer.write("QT -= gui\n"
      "TARGET =\n\n"
      "CONFIG += c++11 console\n"
      "CONFIG -= app_bundle\n\n"
      "# The following define makes your compiler emit warnings if you use\n"
      "# any Qt feature that has been marked deprecated (the exact warnings\n"
      "# depend on your compiler). Please consult the documentation of the\n"
      "# deprecated API in order to know how to port your code away from it.\n"
      "DEFINES += QT_DEPRECATED_WARNINGS\n\n"
      "# You can also make your code fail to compile if it uses deprecated APIs.\n"
      "# In order to do so, uncomment the following line.\n"
      "# You can also select to disable deprecated APIs only up to a certain version of Qt.\n"
      "#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0\n\n"
      "#RC_ICONS = main.ico\n"
      "win32:RC_FILE += main.rc\n\n"
      "SOURCES +=\n\n"
      "# Default rules for deployment.\n"
      "qnx: target.path = /tmp/$${TARGET}/bin\n"
      "else: unix:!android: target.path = /opt/$${TARGET}/bin\n"
      "!isEmpty(target.path): INSTALLS += target\n\n"
      "win32:INCLUDEPATH += \n"
      "    D:/EC-TSJ/Documents/CODE/INCLUDE\n\n"
      "HEADERS += \n"
      "    ../../../../../INCLUDE/_types \n");

  file.write(bytearray, qstrlen(bytearray));        // write to stderr
  buffer.close();
  file.close();
}

/**
 * @brief _buildVxx
 */
APX_SETTING(_buildVxx, name, apx, nb) {
  Q_UNUSED(nb)

  QFile file;
  QByteArray bytearray;
  QBuffer buffer(&bytearray);

  const QString nombre = name + "." + apx;
  file.setFileName(nombre);
  file.open(QIODevice::WriteOnly);
  buffer.open(QIODevice::WriteOnly);

  buffer.write("\n"
    "//************************************/\n"
    "//*  (%T% %S%), %J% <#B#> <0.0.00$>  */\n"
    "//*  (%W% %1 )               */\n"
    "//*  (%X%            )               */\n"
    "//*  (%M%            )               */\n"
    "//*  <# #>                           */\n"
    "//************************************/\n"
    "\n");

  if(apx == "js") {
     buffer.write("%2\n");
    }

  if(apx == "h") {
     buffer.write("\n"
    "#include <iostream>\n\n"
    "#ifndef __%2_H\n"
    "# define __%2__H\n\n\n"
    "#endif //_%2_H\n");
    }

  if(apx == "c") {
    buffer.write("\n"
    "#include <stdio.h>\n\n"
    "#ifndef __%2_C\n"
    "# define __%2_C\n\n"
    "int main(int argc, char *argv[]) {\n"
    "}\n\n"
    "#endif // __%2_C}\n");
   }

  if(apx == "cpp") {
    buffer.write("\n"
    "#include <iostream>\n\n"
    "#ifndef __%2_CPP\n"
    "# define __%2_CPP\n\n"
    "int main(int argc, char *argv[]) {\n"
    "}\n\n"
    "#endif // __%2_CPP\n" ) ;
    }

  QString data = QString::fromLocal8Bit(bytearray).
      arg((QDate::currentDate()).toString("dd/MM/yyyy"), apx == "js" ? "" : name.toUpper());
//  const char *full = qPrintable (msgB);
  file.write(data.toUtf8(), qstrlen(data.toUtf8()));
  buffer.close();
  file.close();
}

/**
 * @brief _buildPython
 */
APX_SETTING(_buildPython, name, apx, nb) {
  Q_UNUSED(nb)

  QFile file;
  QByteArray bytearray;
  QBuffer buffer(&bytearray);

  const QString nombre = name + "." + apx;
  file.setFileName(nombre);
  file.open(QIODevice::WriteOnly);
  buffer.open(QIODevice::WriteOnly);

  buffer.write("#!/bin/python\n"
    "#************************************/\n"
    "#*  (%T% %S%), %J% <#B#> <0.0.00$>  */\n"
    "#*  (%W% %1 )               */\n"
    "#*  (%X%            )               */\n"
    "#*  (%M%            )               */\n"
    "#*  <# #>                           */\n"
    "#************************************/\n"
    "\n"
    "if __name__ == '__main__':\n%2");

  QString data = QString::fromLocal8Bit(bytearray).arg((QDate::currentDate()).toString("dd/MM/yyyy"), QString());
  file.write(data.toUtf8(), qstrlen(data.toUtf8()));        // write to stderr
  buffer.close();
  file.close();
}

/**
 * @brief _buildHtml
 */
APX_SETTING(_buildHtml, name, apx, nb) {
  Q_UNUSED(nb)

  QFile file;
  QByteArray bytearray;
  QBuffer buffer(&bytearray);

  const QString nombre = name + "." + apx;
  file.setFileName(nombre);
  file.open(QIODevice::WriteOnly);
  buffer.open(QIODevice::WriteOnly);

  buffer.write("\n"
      "<!DOCTYPE html>\n"
      "<HTML>\n"
      "<!--\n"
      "/************************************/\n"
      "/*  (%T% %S%), %J% <#B#> <1.0.00>  */\n"
      "/*  (%W% %1 )               */\n"
      "/*  (%X%            )               */\n"
      "/*  (%M%            )               */\n"
      "/*  <# #>                           */\n"
      "/************************************/\n"
      "-->\n"
      "  <head>\n"
      "    <title></title>\n"
      "  </head>\n"
      "  <body>\n"
      "  </body>\n"
      "</HTML>\n%2");

  QString data = QString::fromLocal8Bit(bytearray).arg((QDate::currentDate()).toString("dd/MM/yyyy"), QString());
  file.write(data.toUtf8(), qstrlen(data.toUtf8()));        // write to stderr
  buffer.close();
  file.close();
}

/**
 * @brief _buildSh
 */
APX_SETTING(_buildSh, name, apx, nb) {
  Q_UNUSED(nb)

  QFile file;
  QByteArray bytearray;
  QBuffer buffer(&bytearray);

  const QString nombre = name + "." + apx;
  file.setFileName(nombre);
  file.open(QIODevice::WriteOnly);
  buffer.open(QIODevice::WriteOnly);

  buffer.write("#!/bin/bash\n"
     "\n"
    "#************************************/\n"
    "#*  (%T% %S%), %J% <#B#> <0.0.00$>  */\n"
    "#*  (%W% %1 )               */\n"
    "#*  (%X%            )               */\n"
    "#*  (%M%            )               */\n"
    "#*  <# #>                           */\n"
    "#************************************/\n"
    "\n"
    "\n%2");

  QString data = QString::fromLocal8Bit(bytearray).arg((QDate::currentDate()).toString("dd/MM/yyyy"), QString());
  file.write(data.toUtf8(), qstrlen(data.toUtf8()));
  buffer.close();
  file.close();
}

/**
 * @brief _buildJob
 */
APX_SETTING(_buildJob, name, apx, nb) {
  Q_UNUSED(nb)

  QFile file;
  QByteArray bytearray;
  QBuffer buffer(&bytearray);

  const QString nombre = name + "." + apx;
  file.setFileName(nombre);
  file.open(QIODevice::WriteOnly);
  buffer.open(QIODevice::WriteOnly);

  buffer.write("{\n"
               "\"__version__\" : \"0.0.1\",\n"
               "\"Configurations\": [\n"
               "  {\n"
               "    \"Files\":  None,\n"
               "    \"Directories\": None,\n"
               "    \"Destino\" : \"Uso no dispuesto\"\n"
               "  }\n"
               "]}\n"
    );

  QString data = QString::fromLocal8Bit(bytearray);
  file.write(data.toUtf8(), qstrlen(data.toUtf8()));
  buffer.close();
  file.close();

}

/**
 * @brief runPromoter Corre la aplicación
 * @param argc Nº de argumentos
 * @param argv Argumentos
 * @return 0 ó 1
 */
int runPromoter(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  QCoreApplication::setApplicationVersion(QStringLiteral(OST_VERSION_STR));

#if V_POSITRON
  QCommandParser psr;

  psr.qlp.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
  psr.qlp.setApplicationDescription(QLatin1String("Qt Promoter version " OST_VERSION_STR));
  psr.qlp.addHelpOption();
  psr.qlp.addVersionOption();
#else
  QCommandLineParser parser;

  parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
  parser.setApplicationDescription(QLatin1String("Qt Promoter version " OST_VERSION_STR));
  parser.addHelpOption();
  parser.addVersionOption();
#endif

#if V_POSITRON
  psr.addOption(QStringLiteral("pro"), QStringLiteral("Genera un fichero <.pro>."), QStringLiteral("file"), _buildQT);
  psr.addOption(QStringLiteral("hpp"), QStringLiteral("Genera un fichero <.h>."), QStringLiteral("file"), _buildVxx );
  psr.addOption(QStringLiteral("c"), QStringLiteral("Genera un fichero <.c>."), QStringLiteral("file"), _buildVxx );
  psr.addOption(QStringLiteral("cpp"), QStringLiteral("Genera un fichero <.cpp>."), QStringLiteral("file"), _buildVxx );
  psr.addOption(QStringLiteral("py"), QStringLiteral("Genera un fichero <.py>."), QStringLiteral("file"), _buildPython );
  psr.addOption(QStringLiteral("js"), QStringLiteral("Genera un fichero <.js>."), QStringLiteral("file"), _buildVxx );
  psr.addOption(QStringLiteral("html"), QStringLiteral("Genera un fichero <.html>."), QStringLiteral("file"), _buildHtml );
  psr.addOption(QStringLiteral("css"), QStringLiteral("Genera un fichero <.css>."), QStringLiteral("file"), _buildVxx );
  psr.addOption(QStringLiteral("sh"), QStringLiteral("Genera un fichero <.sh>."), QStringLiteral("file"), _buildSh );
  psr.addOption(QStringLiteral("json"), QStringLiteral("Genera un fichero <job.json>."), QStringLiteral("file"), _buildJob);
  psr.addOption(QStringLiteral("go"), QStringLiteral("Genera un fichero <.go>."), QStringLiteral("file"), _buildGo);
  psr.addOption(QStringLiteral("manifest"), QStringLiteral("Genera un fichero <.manifest>."),QStringLiteral("file"), _buildManifest);
  psr.addOption(QStringLiteral("rc"), QStringLiteral("Genera un fichero destinado a versión <.rc>."),QStringLiteral("file"),_buildRc);
  psr.addOption(QStringLiteral("cmake"), QStringLiteral("Genera un CMakeLists.txt para QT"), QString(), _buildCMake );
  psr.addPositional(QStringLiteral("administrative"), QStringLiteral("Dar funciones de administrador/usuario en <.manifest>"));

  psr.qlp.process(a);

#else

  // QCommandLineOption(QStringLiteral("pro"), QCoreApplication::translate("main", "Show progress during copy"));
  QCommandLineOption pro(QStringLiteral("pro"), QStringLiteral("Genera un fichero <.pro>."), QStringLiteral("file") );
  parser.addOption(pro);

  QCommandLineOption hpp(QStringLiteral("hpp"), QStringLiteral("Genera un fichero <.h>."), QStringLiteral("file") );
  parser.addOption(hpp);

  QCommandLineOption c(QStringLiteral("c"), QStringLiteral("Genera un fichero <.c>."), QStringLiteral("file") );
  parser.addOption(c);

  QCommandLineOption cpp(QStringLiteral("cpp"), QStringLiteral("Genera un fichero <.cpp>."), QStringLiteral("file") );
  parser.addOption(cpp);

  QCommandLineOption py(QStringLiteral("py"), QStringLiteral("Genera un fichero <.py>."), QStringLiteral("file") );
  parser.addOption(py);

  QCommandLineOption js(QStringLiteral("js"), QStringLiteral("Genera un fichero <.js>."), QStringLiteral("file") );
  parser.addOption(js);

  QCommandLineOption html(QStringLiteral("html"), QStringLiteral("Genera un fichero <.html>."), QStringLiteral("file") );
  parser.addOption(html);

  QCommandLineOption css(QStringLiteral("css"), QStringLiteral("Genera un fichero <.css>."), QStringLiteral("file") );
  parser.addOption(css);

  QCommandLineOption sh(QStringLiteral("sh"), QStringLiteral("Genera un fichero <.sh>."), QStringLiteral("file") );
  parser.addOption(sh);

  QCommandLineOption json(QStringLiteral("json"), QStringLiteral("Genera un fichero <job.json>."), QStringLiteral("file"));
  parser.addOption(json);

  QCommandLineOption go(QStringLiteral("go"), QStringLiteral("Genera un fichero <.go>."), QStringLiteral("file"));
  parser.addOption(go);

  QCommandLineOption manifest(QStringLiteral("manifest"), QStringLiteral("Genera un fichero <.manifest>."),QStringLiteral("file"));
  parser.addOption(manifest);

  QCommandLineOption rc(QStringLiteral("rc"), QStringLiteral("Genera un fichero destinado a versión <.rc>."),QStringLiteral("file"));
  parser.addOption(rc);

  QCommandLineOption cmake(QStringLiteral("cmake"), QStringLiteral("Genera un CMakeLists.txt para QT"));
  parser.addOption(cmake);

  parser.addPositionalArgument(QStringLiteral("administrative"), QStringLiteral("Para dar funciones de administrador en <.manifest>"));

  parser.process(a);

  // construye fn's donde irán cada uno de los tipos
  QMap<QString, void (*)(QString, QString, short int)> options;
  options["pro"] =        _buildQT;
  options["hpp"] =        _buildVxx;
  options["c"] =          _buildVxx;
  options["cpp"] =        _buildVxx;
  options["py"] =         _buildPython;
  options["js"] =         _buildVxx;
  options["html"] =       _buildHtml;
  options["css"] =        _buildVxx;
  options["sh"] =         _buildSh;
  options["json"] =       _buildJob;
  options["manifest"] =   _buildManifest;
  options["rc"] =         _buildRc;
  options["cmake"] =      _buildCMake;
  options["go"] =         _buildGo;

#endif


  // nombre del fichero si posicionales
  //const QStringList filenamesIn = parser.positionalArguments();
  // ó
  // const QString nameOf = parser.positionalArguments().first();

#if V_POSITRON
# if V_MODE
  QMap<QString, void (*)(QString, QString, short int)> pep = psr.options;
  QList<QString> vf = pep.keys();
# else
  QList<QString> vf = psr.options().keys();
# endif
#else
  QList<QString> vf = options.keys();
#endif
  bool message = false; // emite mensaje
  short num = 0;

  // mira si hay alguna opción activada
#if V_POSITRON
# if V_MODE
  while(num < pep.size())
# else
  while(num < psr.options().size())
# endif
    if(psr.qlp.isSet(vf[num++])) {
#else
  while(num < options.size())
    if(parser.isSet(vf[num++])) {
#endif
      message = true;
      break;
    }

  // si alguno es seleccionado, imprimirá el mensaje
  if(message)
    qInfo() << "OK. Comienza el proceso.";

  // proceso para desplazarse por las opciones.
  // Mirará por todas las opciones y ejecutará las que sean válidas
  num = 0;
#if V_POSITRON
  const QStringList namesIn = psr.qlp.positionalArguments(); // posicionales
#else
  const QStringList namesIn = parser.positionalArguments(); // posicionales
#endif
  if(message)
    do {
      QString name = vf[num]; //nombre de la opción
#if V_POSITRON
      if(psr.qlp.isSet(name)) { // si existe
#else
      if(parser.isSet(name)) { // si existe
#endif
          void (*ptr)(QString, QString, short) =
#if V_POSITRON
#   if V_MODE
              (void (*)(QString, QString, short))pep[name]; // fn a ejecutar
#   else
              (void (*)(QString, QString, short))psr.options()[name]; // fn a ejecutar
#   endif
          QString value = psr.qlp.value(name); // nombre  // opcion -> name
#else
              (void (*)(QString, QString, short))options[name]; // fn a ejecutar
          QString value = parser.value(name); // nombre  // opcion -> name
#endif
          short nb= 0; //opción para la fn
          if(  name == "manifest" && // si es administrativo el permiso
               namesIn.size() > 0 &&
               namesIn.contains("administrative") )
            nb = 1;
          ptr(value, name == "hpp" ? "h" : name, nb); // ejecuta la fn
          qInfo("  Fichero '%s' creado.", qPrintable(value + "." + name)); // mensaje de creado
        }
      num++;
#if V_POSITRON
#   if V_MODE
      } while(num < pep.size());
#   else
      } while(num < psr.options().size());
#   endif
#else
      } while(num < options.size());
#endif

  // mensaje de salida
  if(message)
    qInfo() << "OK. Operación terminada.";

  return 0;
}

QT_END_NAMESPACE

/**
 * @brief main Aplicación
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]){
  return QT_PREPEND_NAMESPACE(runPromoter)(argc, argv);
}
