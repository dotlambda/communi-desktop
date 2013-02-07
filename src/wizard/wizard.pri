######################################################################
# Communi: wizard.pri
######################################################################

DEPENDPATH += $$PWD
INCLUDEPATH += $$PWD
QMAKE_CLEAN += $$PWD/*~

FORMS += $$PWD/aliaseswizardpage.ui
FORMS += $$PWD/colorswizardpage.ui
FORMS += $$PWD/connectionwizardpage.ui
FORMS += $$PWD/generalwizardpage.ui
FORMS += $$PWD/shortcutswizardpage.ui
FORMS += $$PWD/serverwizardpage.ui
FORMS += $$PWD/userwizardpage.ui

HEADERS += $$PWD/aliaseswizardpage.h
HEADERS += $$PWD/colorswizardpage.h
HEADERS += $$PWD/connectionwizard.h
HEADERS += $$PWD/connectionwizardpage.h
HEADERS += $$PWD/generalwizardpage.h
HEADERS += $$PWD/shortcutswizardpage.h
HEADERS += $$PWD/serverwizardpage.h
HEADERS += $$PWD/settingswizard.h
HEADERS += $$PWD/userwizardpage.h
HEADERS += $$PWD/wizardtreewidget.h

SOURCES += $$PWD/aliaseswizardpage.cpp
SOURCES += $$PWD/colorswizardpage.cpp
SOURCES += $$PWD/connectionwizard.cpp
SOURCES += $$PWD/connectionwizardpage.cpp
SOURCES += $$PWD/generalwizardpage.cpp
SOURCES += $$PWD/shortcutswizardpage.cpp
SOURCES += $$PWD/serverwizardpage.cpp
SOURCES += $$PWD/settingswizard.cpp
SOURCES += $$PWD/userwizardpage.cpp
SOURCES += $$PWD/wizardtreewidget.cpp
