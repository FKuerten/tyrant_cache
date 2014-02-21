# Configuration section
MODULE_NAME=tyrantCache
DEPENDENCIES=core basics
LIBS:=-lboost_program_options -lsqlite3 -lboost_regex
CXXFLAGS+= --std=c++11
ARFLAGS:=crvs

# Automatic section
INCLUDEDIRS:=${MODULEDIR}/target/generated
iftrue ${DEPENDENCIES}
	INCLUDEDIRS+=${MODULEDIR}/../${DEPENDENCIES}/src/main/c++
endif
CPPFLAGS+=-I${INCLUDEDIRS}
