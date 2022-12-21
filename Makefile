# SPDX-License-Identifier: Apache-2.0

.PHONY: all clean build debug release

BUILD_TYPE := Release

all: debug

clean:
	@rm -rf build-*

build-common:
	@mkdir -p build-${BUILD_TYPE}
	@cd build-${BUILD_TYPE} && \
	cmake -Wno-dev \
		  -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
		  -DPREFER_STATIC_LIBS=OFF \
		  $(FORCE_COLOR) \
		  ..

build:
	VERBOSE=1 cmake --build build-${BUILD_TYPE} -j $${CPU_COUNT:-`nproc`} || \
	cmake --build build-${BUILD_TYPE}

debug:
	@$(MAKE) build-common BUILD_TYPE=Debug
	@$(MAKE) build BUILD_TYPE=Debug

release:
	@$(MAKE) build-common BUILD_TYPE=Release
	@$(MAKE) build BUILD_TYPE=Release

test-cider:
	@cd build-${BUILD_TYPE}/src/cider/tests && \
	ctest -j $${CPU_COUNT:-`nproc`} -V

test-debug:
	@$(MAKE) test-cider BUILD_TYPE=Debug
	@$(MAKE) test-cider-velox BUILD_TYPE=Debug