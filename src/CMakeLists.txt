#add_definitions(-O -Wall -Werror --std=gnu99 -D_GNU_SOURCE)

# Check the third party Libraries
find_package(Libssh2 REQUIRED)

include_directories(${LIBSSH2_INCLUDE_DIR})
set(EXTRA_LIBS ${LIBSSH2_LIBRARY})

add_executable(
    EtoneSSH
    main.cpp
    Com.cpp
    ConfigCom.cpp
    ConfigLoad.cpp
    Log.cpp
    Singleton.cpp
    Ssh.cpp
)

target_link_libraries(EtoneSSH ${EXTRA_LIBS})

install(
    TARGETS EtoneSSH
    RUNTIME DESTINATION sbin
)
