GIT_VERSION != git describe --tags --abbrev=0 | sed 's/^v//'

ifdef $(VERSION)
    VERSION := $(VERSION)
else
    VERSION = $(GIT_VERSION)
endif

export VERSION
