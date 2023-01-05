# Copyright (C) 2019 David Cantrell <dcantrell@burdell.org>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# Set the top level source directory
topdir := $(shell realpath $(dir $(lastword $(MAKEFILE_LIST)))/..)

# Figure out if we need to run dnf or yum
_HAVE_DNF := $(shell ls -1 /usr/bin/dnf 2>/dev/null)
ifeq ($(_HAVE_DNF),)
PKG_CMD = yum
else
PKG_CMD = dnf
endif

# Install packages before anything else
_install := $(shell $(PKG_CMD) install -y git)
_safedir := $(shell git config --global --add safe.directory $(topdir))

# Pass BUILDTYPE=release to generate a release SRPM
BUILDTYPE ?= copr

# Spec file and template
SPEC_TEMPLATE = $(shell ls -1 $(topdir)/*.spec.in)
SPEC = $(topdir)/$(shell basename $(SPEC_TEMPLATE) .in)

# Replace placeholders in the spec file template
RPMDATE = $(shell date +'%a %b %d %Y')
RPMAUTHOR = $(shell git log | tac | grep ^Author: | head -n 1 | cut -d ' ' -f 2,3,4)

# Various things we need to generate a tarball
PKG = $(shell grep ^Name: "$(SPEC_TEMPLATE)" | awk '{ print $$2; }')
VER = $(shell grep 'version :' $(topdir)/meson.build | grep -E "'[0-9]+\.[0-9]+'" | cut -d "'" -f 2)

ifeq ($(BUILDTYPE),copr)
GITDATE          = $(shell date +'%Y%m%d%H%M')
GITHASH          = $(shell git rev-parse --short HEAD)
TARBALL_BASENAME = $(PKG)-$(VER)-$(GITDATE)git$(GITHASH)
TAG              = HEAD
else
TAG              = $(shell git tag -l | tail -n 1)
endif

ifeq ($(BUILDTYPE),release)
TARBALL_BASENAME = $(PKG)-$(VER)
endif

srpm:
	sed -e 's|%%VERSION%%|$(VER)|g' < "$(SPEC_TEMPLATE)" > "$(SPEC)"
	sed -i -e 's|%%GPGKEYRING%%|gpgkey-$(GPGKEY).gpg|g' "$(SPEC)"
ifeq ($(BUILDTYPE),copr)
	sed -i -e '/^Release:/ s/1[^%]*/0.1.$(GITDATE)git$(GITHASH)/' "$(SPEC)"
	sed -i -e 's|^Source0:.*$$|Source0: $(TARBALL_BASENAME).tar.xz|g' "$(SPEC)"
	sed -i -e 's|^%autosetup.*$$|%autosetup -n $(TARBALL_BASENAME)|g' "$(SPEC)"
	sed -i -e '/^Source1:.*$$/d' "$(SPEC)"
	sed -i -e '/^Source2:.*$$/d' "$(SPEC)"
	sed -i -e '/^%{gpgverify}.*$$/d' "$(SPEC)"
	echo "* $(RPMDATE) $(RPMAUTHOR) - $(VER)-$(GITDATE)git$(GITHASH)" >> "$(SPEC)"
	echo "- Build $(PKG)-$(VER)-$(GITDATE)git$(GITHASH) snapshot" >> "$(SPEC)"
endif
	rm -f "$(TARBALL_BASENAME)".tar.xz.asc
	git archive \
		--format=tar \
		--output='$(topdir)/$(TARBALL_BASENAME).tar' \
		--prefix='$(TARBALL_BASENAME)/' $(TAG) $(topdir)
	xz -9f $(topdir)/$(TARBALL_BASENAME).tar
ifeq ($(BUILDTYPE),release)
	gpg --detach-sign --armor "$(TARBALL_BASENAME)".tar.xz
	gpg --export -a $(GPGKEY) > gpgkey-$(GPGKEY).gpg
endif
	rpmbuild \
		-bs --nodeps \
		--define "_sourcedir $(topdir)" \
		--define "_srcrpmdir $(outdir)" \
		--define "_rpmdir $(outdir)" "$(SPEC)"
