COMMANDS = \
	basename \
	cat \
	chroot \
	comm \
	csplit \
	dirname \
	echo \
	expand \
	false \
	fmt \
	fold \
	head \
	true \
	unexpand

all:
	for command in $(COMMANDS) ; do $(MAKE) -C $${command} ; done

install:
	for command in $(COMMANDS) ; do $(MAKE) -C $${command} install ; done

clean:
	for command in $(COMMANDS) ; do $(MAKE) -C $${command} clean ; done

.PHONY: all
