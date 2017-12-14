TEMPLATE = subdirs

SUBDIRS += \
    Quiz-Desktop \
    Quiz-Model \
    Quiz-Android

Quiz-Desktop.depends = Quiz-Model
Quiz-Android.depends = Quiz-Model
