set(project pnms-common)

set(${project}_files
    ${CMAKE_CURRENT_SOURCE_DIR}/AbstractSocket.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BasicServerImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ConfigReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/constants.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Host.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MessageDigest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Mutex.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NetworkAddress.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NetworkComponent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RegConfReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SocketErrorCodes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TCPServer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TCPServerThread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TCPSocket.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Thread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ThreadedTCPServer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ThreadedUDPServer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UDPServer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UDPServerThread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UDPSocket.cpp
)

add_library( ${project} ${${project}_files} )

target_link_libraries( ${project} xml2 pthread crypto)
