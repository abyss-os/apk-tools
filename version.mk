GIT_VERSION != git describe --tags | sed 's/^v//'

ifdef $(VERSION)
    VERSION := $(VERSION)
else
    VERSION = $(GIT_VERSION)
endif

export VERSION
