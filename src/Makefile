COMMANDS = \
	basename \
	cat \
	chroot \
	comm \
	csplit \
	true

all:
	for command in $(COMMANDS) ; do $(MAKE) -C $${command} ; done

install:
	for command in $(COMMANDS) ; do $(MAKE) -C $${command} install ; done

clean:
	for command in $(COMMANDS) ; do $(MAKE) -C $${command} clean ; done

.PHONY: all
