######################################################################
# Communi
######################################################################

TEMPLATE = subdirs
SUBDIRS += filter
SUBDIRS += verifier
SUBDIRS += znc
osx:SUBDIRS += osx
qtHaveModule(x11extras):SUBDIRS += gnome
