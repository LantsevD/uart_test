# list foor desktop tests

set(GROUP_i386_SRC
    ./i386_Tests/Src/main.c
    ./i386_Tests/Src/Tests/uart_test.c
)

set(GROUP_MODULES
    ./Src/uart.c
	./Src/ring_buf.c
)

set(GROUP_MUNIT
    ./i386_Tests/munit/munit.c
)

include_directories(./Inc)
include_directories(./i386_Tests/Inc)
include_directories(./i386_Tests/munit)

set(LIST_OF_SOURCES
    ${GROUP_i386_SRC}
    ${GROUP_MUNIT}
    ${GROUP_MODULES}
)
