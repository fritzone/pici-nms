set(project pnms-dispatcher)

FIND_PACKAGE( Boost 1.49 COMPONENTS system thread REQUIRED)

set(${project}_files
    ${CMAKE_CURRENT_SOURCE_DIR}/ClientInfo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DispatcherSvc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExceptionCI.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExceptionDispatcher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExceptionRuntime.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/QueuedMessage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Service.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SubscriptionInfo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TCPClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ThreadDispatcher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ThreadPinger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ThreadQueue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utilConversion.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/util.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utilDebug.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utilMath.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utilSTL.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utilStrings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vasprintf.cpp
)

add_executable(${project} ${${project}_files} )

target_link_libraries(${project} pnms-common ${Boost_LIBRARIES} )

