set(project pnms-daemon)

set(${project}_files
    ${CMAKE_CURRENT_SOURCE_DIR}/Connection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Daemon.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DaemonInnerTCPServerThread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DaemonMain.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DaemonMessageHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DaemonMessageHandlerThread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DaemonMutex.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DaemonPingerThread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DaemonService.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DaemonUDPServerThread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DispatcherRequest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/InnerTCPClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/InnerTCPClientFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RegisteredDispatcher.cpp
)

add_executable(${project} ${${project}_files} )

target_link_libraries(${project} pnms-common)