
TOPDIR:=${CURDIR}/tools
TZ:=UTC

export TOPDIR TZ

empty:=
space:= $(empty) $(empty)
$(if $(findstring $(space),$(TOPDIR)),$(error ERROR: The path to the Tools directory must not include any spaces))

include ${TOPDIR}/begin.mk

include project.mk

include ${TOPDIR}/end.mk
