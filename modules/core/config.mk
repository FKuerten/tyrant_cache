# Configuration section
MODULE_NAME=core
DEPENDENCIES=basics
LIBS:=-lcrypto++
CXXFLAGS+= --std=c++11
ARFLAGS:=crvs

# Automatic section
INCLUDEDIRS:=${MODULEDIR}/target/generated
iftrue ${DEPENDENCIES}
	INCLUDEDIRS+=${MODULEDIR}/../${DEPENDENCIES}/src/main/c++
endif
CPPFLAGS+=-I${INCLUDEDIRS}
