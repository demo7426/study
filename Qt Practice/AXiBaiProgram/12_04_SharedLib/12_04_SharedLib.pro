TEMPLATE = subdirs

SUBDIRS += \
    SharedLib \
    user

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/user/lib/ -lSharedLibd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/user/lib/ -lSharedLibdd

INCLUDEPATH += $$PWD/user/lib
DEPENDPATH += $$PWD/user/lib
