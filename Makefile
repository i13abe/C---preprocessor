SRC= cccp.cmm including.cmm definition.cmm condition.cmm

all: cpp--

cpp--: ${SRC}
	cm2c -o cpp-- ${SRC}

install: cpp--
	install -m 755 cpp-- /usr/local/bin
