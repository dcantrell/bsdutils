COMMANDS = \
	basename \
	cat \
	chroot \
	comm \
	csplit \
	cut \
	dirname \
	echo \
	env \
	expand \
	factor \
	false \
	fmt \
	fold \
	head \
	join \
	mknod \
	mktemp \
	nice \
	nl \
	nohup \
	paste \
	pr \
	printenv \
	printf \
	pwd \
	rmdir \
	sleep \
	sync \
	tee \
	touch \
	true \
	unexpand

all:
	for command in $(COMMANDS) ; do $(MAKE) -C $${command} ; done

install:
	for command in $(COMMANDS) ; do $(MAKE) -C $${command} install ; done

clean:
	for command in $(COMMANDS) ; do $(MAKE) -C $${command} clean ; done

.PHONY: all
