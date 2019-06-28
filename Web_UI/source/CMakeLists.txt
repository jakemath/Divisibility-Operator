SET(bigint_application_source
bigint.h
bigint.cpp
bigint_application.h
bigint_application.cpp
bigint_application_main.C
)
SET(bigint_application_target bigint_application.wt)
ADD_EXECUTABLE(${bigint_application_target} ${bigint_application_source})
TARGET_LINK_LIBRARIES(${bigint_application_target} ${WT_CONNECTOR} wt)
INCLUDE_DIRECTORIES(/usr/local/include)
